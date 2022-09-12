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
// File Name: Logger.c
// Date File Created: 9/11/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Logger.h"
#include "Asserts.h"
#include "Spark/Platform/Platform.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

const char* level_strings [ 6 ] = { "[TRACE]:", "[DEBUG]:", "[INFO]:", "[WARN]:", "[ERROR]:", "[FATAL]:" };

#if SASSERTIONS_ENABLED
void report_assertion_failure(const char* expression, const char* message, const char* file, s32 line)
{
    log_message(LOG_LEVEL_FATAL, "Assertion Failure: (%s), msg: '%s'. Occurred in file %s at line %d\n", expression,
                message, file, line);
}
#endif

b8 initialize_logger()
{
    // TODO: Create log file(s)
    return TRUE;
}

void shutdown_logger()
{
    // TODO: Clear queued messages
}

void log_message(log_level level, const char* msg, ...)
{
    b8   err = level > LOG_LEVEL_WARN;
    char buffer [ 32000 ];
    memset(buffer, 0, sizeof(buffer));

    __builtin_va_list argptr;
    va_start(argptr, msg);
    vsnprintf(buffer, 32000, msg, argptr);
    va_end(argptr);

    // [level]: msg
    char out_message [ 32000 ];
    sprintf(out_message, "%s %s\n", level_strings [ level ], buffer);

//    printf("%s", out_message);
    if(err) platform_console_write_error(out_message, level);
    else
        platform_console_write(out_message, level);
}
