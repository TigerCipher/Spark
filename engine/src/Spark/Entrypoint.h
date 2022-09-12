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
// File Name: Entrypoint.h
// Date File Created: 9/12/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#ifndef SPARK_ENTRYPOINT_H
#define SPARK_ENTRYPOINT_H

#include "Core/Application.h"
#include "Core/Logger.h"
#include "Game.h"

extern b8 create_game(game* out_game);

int main()
{
    game game_inst;
    if(!create_game(&game_inst))
    {
        SFATAL("Failed to create the game");
        return -1;
    }

    if(!game_inst.initialize || !game_inst.update || !game_inst.render || !game_inst.on_resize)
    {
        SFATAL("Game does not implement all the required functions");
        return -2;
    }

    if(!application_create(&game_inst))
    {
        SFATAL("Failed to create application");
        return 1;
    }
    if(!application_run())
    {
        SFATAL("Applicationed failed to shutdown properly");
        return 2;
    }

    return 0;
}


#endif //SPARK_ENTRYPOINT_H
