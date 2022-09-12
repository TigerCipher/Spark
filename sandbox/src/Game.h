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
// File Name: Game.h
// Date File Created: 9/12/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#ifndef SPARK_GAME_H
#define SPARK_GAME_H
#include <Spark/Common.h>
#include <Spark/Game.h>

typedef struct game_state
{
    f32 delta;
} game_state;

b8 game_initialize(game* game_inst);
b8 game_update(game* game_inst, f32 delta);
b8 game_render(game* game_inst, f32 delta);
void game_on_resize(game* game_inst, s32 width, s32 height);

#endif //SPARK_GAME_H
