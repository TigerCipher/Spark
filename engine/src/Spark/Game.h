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

#ifndef SPARK_ENGINE_GAME_H
#define SPARK_ENGINE_GAME_H

#include "Core/Application.h"

typedef struct game
{
    application_desc app_desc;
    b8 (*initialize)(struct game* game_inst);
    b8 (*update)(struct game* game_inst, f32 delta);
    b8 (*render)(struct game* game_inst, f32 delta);

    void (*on_resize)(struct game* game_inst, s32 width, s32 height);

    void* state;
} game;

#endif //SPARK_ENGINE_GAME_H
