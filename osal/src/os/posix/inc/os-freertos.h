/*
 *  NASA Docket No. GSC-18,370-1, and identified as "Operating System Abstraction Layer"
 *
 *  Copyright (c) 2019 United States Government as represented by
 *  the Administrator of the National Aeronautics and Space Administration.
 *  All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
 * \file     os-posix.h
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 * Purpose: This file contains definitions that are shared across the POSIX
 *          OSAL implementation.  This file is private to the POSIX port and it
 *          may contain POSIX-specific definitions.
 */

#ifndef INCLUDE_OS_POSIX_H_
#define INCLUDE_OS_POSIX_H_


/****************************************************************************************
                                    COMMON INCLUDE FILES
 ***************************************************************************************/

/*
 * Use the global definitions from the shared layer
 */
#include "os-shared-globaldefs.h"

/****************************************************************************************
                                     DEFINES
 ***************************************************************************************/

/****************************************************************************************
                                    TYPEDEFS
 ***************************************************************************************/

typedef struct
{
   int reserve;
} FREERTOS_GlobalVars_t;


/****************************************************************************************
                                   GLOBAL DATA
 ***************************************************************************************/

extern FREERTOS_GlobalVars_t FREERTOS_GlobalVars;


/****************************************************************************************
                       POSIX IMPLEMENTATION FUNCTION PROTOTYPES
 ***************************************************************************************/

int32 OS_FreeRTOS_TaskAPI_Impl_Init(void);
int32 OS_FreeRTOS_QueueAPI_Impl_Init(void);
int32 OS_FreeRTOS_BinSemAPI_Impl_Init(void);
int32 OS_FreeRTOS_CountSemAPI_Impl_Init(void);
int32 OS_FreeRTOS_MutexAPI_Impl_Init(void);
int32 OS_FreeRTOS_ModuleAPI_Impl_Init(void);
int32 OS_FreeRTOS_TimeBaseAPI_Impl_Init(void);
int32 OS_FreeRTOS_StreamAPI_Impl_Init(void);
int32 OS_FreeRTOS_DirAPI_Impl_Init(void);
int32 OS_FreeRTOS_FileSysAPI_Impl_Init(void);

int32 OS_FreeRTOS_TableMutex_Init(uint32 idtype);

#endif  /* INCLUDE_OS_POSIX_H_ */

