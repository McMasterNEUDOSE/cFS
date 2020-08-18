/*
**  GSC-18128-1, "Core Flight Executive Version 6.7"
**
**  Copyright (c) 2006-2019 United States Government as represented by
**  the Administrator of the National Aeronautics and Space Administration.
**  All Rights Reserved.
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

/*
** cfe_psp_config.h
**
*/

#ifndef _cfe_psp_config_
#define _cfe_psp_config_



#include "common_types.h"

/*
** This define sets the number of memory ranges that are defined in the memory range defintion
** table.
*/
#define CFE_PSP_MEM_TABLE_SIZE 10

/**
 * This define sets the maximum number of exceptions
 * that can be stored.
 *
 * It must always be a power of two.
 */
#define CFE_PSP_MAX_EXCEPTION_ENTRIES           4


/*
** Typedef for the layout of the header in the reserved memory block
*/


typedef struct
{
    uint32 reserved;

} CFE_PSP_ReservedMemoryBootRecord_t;


/**
 * \brief The data type used by the underlying OS to represent a thread ID.
 */
typedef void* CFE_PSP_Exception_SysTaskId_t;  //TODO need to redefine for FreeRTOS

/**
 * \brief Exception context data which is relevant for offline/post-mortem diagnosis.
 *
 * This may be stored in a persistent exception log file for later analysis.
 */
typedef struct
{
    uint32 reserved; /* prevent empty structure */
} CFE_PSP_Exception_ContextDataEntry_t;

/*
** Watchdog minimum and maximum values ( in milliseconds )
*/
#define CFE_PSP_WATCHDOG_MIN (0)
#define CFE_PSP_WATCHDOG_MAX (0xFFFFFFFF) 

/*
** Number of EEPROM banks on this platform
*/
#define CFE_PSP_NUM_EEPROM_BANKS 1

#endif

