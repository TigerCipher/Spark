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
// File Name: Asserts.h
// Date File Created: 9/11/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#ifndef SPARK_ASSERTS_H
#define SPARK_ASSERTS_H

#include "Spark/Common.h"

#define SASSERTIONS_ENABLED 1

#if SASSERTIONS_ENABLED
    #if _MSC_VER
        #include <intrin.h>
        #define debug_break() __debugbreak()
    #else
        #define debug_break() __builtin_trap()
    #endif

SAPI void report_assertion_failure(const char* expression, const char* message, const char* file, s32 line);

    #define SASSERT(expr)                                                                                              \
        {                                                                                                              \
            if (expr)                                                                                                  \
            {                                                                                                          \
            } else                                                                                                     \
            {                                                                                                          \
                report_assertion_failure(#expr, "", __FILE__, __LINE__);                                               \
                debug_break();                                                                                         \
            }                                                                                                          \
        }

    #define SASSERT_MSG(expr, msg)                                                                                     \
        {                                                                                                              \
            if (expr)                                                                                                  \
            {                                                                                                          \
            } else                                                                                                     \
            {                                                                                                          \
                report_assertion_failure(#expr, msg, __FILE__, __LINE__);                                              \
                debug_break();                                                                                         \
            }                                                                                                          \
        }

    #ifdef _DEBUG
        #define SASSERT_DEBUG(expr)                                                                                    \
            {                                                                                                          \
                if (expr)                                                                                              \
                {                                                                                                      \
                } else                                                                                                 \
                {                                                                                                      \
                    report_assertion_failure(#expr, "", __FILE__, __LINE__);                                           \
                    debug_break();                                                                                     \
                }                                                                                                      \
            }
    #else
        #define SASSERT_DEBUG(expr)
    #endif

#else

    #define SASSERT(exr)
    #define SASSERT_MSG(expr, msg)
    #define SASSERT_DEBUG(expr)

#endif

#endif //SPARK_ASSERTS_H
