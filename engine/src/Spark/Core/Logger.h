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
// File Name: Logger.h
// Date File Created: 9/11/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#ifndef SPARK_LOGGER_H
#define SPARK_LOGGER_H

#include "Spark/Common.h"

#define LOG_TRACE_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_INFO_ENABLED  1
#define LOG_WARN_ENABLED  1

#if SRELEASE
    #define LOG_DEBUG_ENABLED 0
    #define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level_
{
    LOG_LEVEL_TRACE = 0,
    LOG_LEVEL_DEBUG = 1,
    LOG_LEVEL_INFO  = 2,
    LOG_LEVEL_WARN  = 3,
    LOG_LEVEL_ERROR = 4,
    LOG_LEVEL_FATAL = 5,
} log_level;

b8   initialize_logger();
void shutdown_logger();

SAPI void log_message(log_level level, const char* msg, ...);


#if LOG_TRACE_ENABLED
    #define STRACE(msg, ...) log_message(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__)
#else
    #define STRACE(msg, ...)
#endif

#if LOG_DEBUG_ENABLED
    #define SDEBUG(msg, ...) log_message(LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__)
#else
    #define SDEBUG(msg, ...)
#endif

#if LOG_INFO_ENABLED
    #define SINFO(msg, ...) log_message(LOG_LEVEL_INFO, msg, ##__VA_ARGS__)
#else
    #define SINFO(msg, ...)
#endif

#if LOG_WARN_ENABLED
    #define SWARN(msg, ...) log_message(LOG_LEVEL_WARN, msg, ##__VA_ARGS__)
#else
    #define SWARN(msg, ...)
#endif

#ifndef SERROR
    #define SERROR(msg, ...) log_message(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__)
#endif

#ifndef SFATAL
    #define SFATAL(msg, ...) log_message(LOG_LEVEL_FATAL, msg, ##__VA_ARGS__)
#endif

#endif //SPARK_LOGGER_H
