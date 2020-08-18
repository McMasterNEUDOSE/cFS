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

/******************************************************************************
S
** File:  cfe_psp_exception.c
**
**      FreeRTOS version
**
** Purpose:
**   cFE PSP Exception handling functions
**
** History:
**
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"
#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_exceptionstorage_types.h"
#include "cfe_psp_exceptionstorage_api.h"


/*
**
** LOCAL FUNCTION PROTOTYPES
**
*/


/***************************************************************************
 **                        FUNCTIONS DEFINITIONS
 ***************************************************************************/


void CFE_PSP_AttachExceptions(void)
{

}

/*
**
**   Name: CFE_PSP_SetDefaultExceptionEnvironment
**
**   Purpose: This function sets a default exception environment that can be used
**
**   Notes: The exception environment is local to each task Therefore this must be
**          called for each task that that wants to do floating point and catch exceptions
**          Currently, this is automaticall called from OS_TaskRegister for every task
*/

void CFE_PSP_SetDefaultExceptionEnvironment(void)
{

}

int32 CFE_PSP_ExceptionGetSummary_Impl(const CFE_PSP_Exception_LogData_t* Buffer, char *ReasonBuf, uint32 ReasonSize)
{
    return 0;
}

