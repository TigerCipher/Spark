// ------------------------------------------------------------------------------
//
// Spark
//    Copyright 2022 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: Application.c
// Date File Created: 9/12/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Application.h"
#include "Logger.h"
#include "Spark/Platform/Platform.h"
#include "Spark/Game.h"

typedef struct app_state
{
    game*          game_inst;
    b8             running;
    b8             suspended;
    platform_state platform;
    s16            width;
    s16            height;
    f64            last_time;
} app_state;

static b8        initialized = FALSE;
static app_state appstate;

b8 application_create(game* game_inst)
{
    if (initialized)
    {
        SERROR("application_create cannot be called more than once");
        return FALSE;
    }
    appstate.game_inst = game_inst;

    // subsystems
    initialize_logger();
#pragma region temp
    STRACE("Test msg %f", 3.14159f);
    SDEBUG("Test msg %f", 3.14159f);
    SINFO("Test msg %f", 3.14159f);
    SWARN("Test msg %f", 3.14159f);
    SERROR("Test msg %f", 3.14159f);
    SFATAL("Test msg %f", 3.14159f);
#pragma endregion

    appstate.running   = TRUE;
    appstate.suspended = FALSE;

    if (!platform_startup(&appstate.platform, game_inst->app_desc.name, game_inst->app_desc.pos_x,
                          game_inst->app_desc.pos_y, game_inst->app_desc.width, game_inst->app_desc.height))
    {
        SFATAL("Platform startup failed");
        return FALSE;
    }

    SINFO("Platform startup completed successfully");

    if(!appstate.game_inst->initialize(appstate.game_inst))
    {
        SFATAL("Game failed to initialize");
        return FALSE;
    }

    appstate.game_inst->on_resize(appstate.game_inst, appstate.width, appstate.height);

    SINFO("Game initialized successfully");

    initialized = TRUE;
    return TRUE;
}

b8 application_run()
{
    while (appstate.running)
    {
        if (!platform_pump_messages(&appstate.platform)) { appstate.running = FALSE; }
        if(!appstate.suspended)
        {
            if(!appstate.game_inst->update(appstate.game_inst, 0.0f))
            {
                SFATAL("Game tick failed, aborting");
                appstate.running = FALSE;
                break;
            }

            if(!appstate.game_inst->render(appstate.game_inst, 0.0f))
            {
                SFATAL("Game render failed, aborting");
                appstate.running = FALSE;
                break;
            }
        }
    }

    if(appstate.game_inst->state)
        platform_free(appstate.game_inst->state, FALSE);
    platform_shutdown(&appstate.platform);
    return TRUE;
}