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
// File Name: Application.h
// Date File Created: 9/12/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#ifndef SPARK_APPLICATION_H
#define SPARK_APPLICATION_H

#include "Spark/Common.h"

struct game;

typedef struct application_config
{
    s16   pos_x;
    s16   pos_y;
    s16   width;
    s16   height;
    char* name;
} application_desc;

SAPI b8 application_create(struct game* game_inst);
SAPI b8 application_run();


#endif //SPARK_APPLICATION_H
