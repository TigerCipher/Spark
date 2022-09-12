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
// File Name: Game.c
// Date File Created: 9/12/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Game.h"
#include <Spark/Core/Logger.h>

b8 game_initialize(game* game_inst)
{
    SDEBUG("game_initialize");
    return TRUE;
}

b8 game_update(game* game_inst, f32 delta)
{
    SDEBUG("game_update");
    return TRUE;
}

b8 game_render(game* game_inst, f32 delta)
{
    SDEBUG("game_render");
    return TRUE;
}
void game_on_resize(game* game_inst, s32 width, s32 height) { SDEBUG("game_on_resize"); }