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
// File Name: Platform.h
// Date File Created: 9/11/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#ifndef SPARK_PLATFORM_H
#define SPARK_PLATFORM_H

#include "Spark/Common.h"

typedef struct platform_state_
{
    void* internal_state;
} platform_state;

b8 platform_startup(platform_state* plat_state, const char* app_name, s32 x, s32 y, s32 width, s32 height);

void platform_shutdown(platform_state* plat_state);

b8 platform_pump_messages(platform_state* plat_state);

SAPI void* platform_allocate(u64 size, b8 aligned);
SAPI void  platform_free(void* block, b8 aligned);
void* platform_zero_memory(void* block, u64 size);
void* platform_copy_memory(void* dest, const void* src, u64 size);
void* platform_set_memory(void* dest, s32 value, u64 size);

void platform_console_write(const char* message, u8 color);
void platform_console_write_error(const char* message, u8 color);

f64 platform_get_time();

void platform_sleep(u64 milliseconds);


#endif //SPARK_PLATFORM_H
