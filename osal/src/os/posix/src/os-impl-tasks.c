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
 * \file     os-impl-tasks.c
 * \ingroup  FreeRTOS
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-impl-tasks.h"

#include "os-freertos.h"
#include "os-shared-task.h"
#include "os-shared-idmap.h"

/* Tables where the OS object information is stored */
OS_impl_task_internal_record_t      OS_impl_task_table          [OS_MAX_TASKS];


/*
 *********************************************************************************
 *          TASK API
 *********************************************************************************
 */

/*---------------------------------------------------------------------------------------
   Name: OS_Posix_TaskAPI_Impl_Init

   Purpose: Initialize the Posix Task data structures

 ----------------------------------------------------------------------------------------*/
int32 OS_FreeRTOS_TaskAPI_Impl_Init(void)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_Posix_TaskAPI_Impl_Init */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskCreate_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskCreate_Impl (uint32 task_id, uint32 flags)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskCreate_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskMatch_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskMatch_Impl(uint32 task_id)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskMatch_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskDelete_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskDelete_Impl (uint32 task_id)
{
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskDelete_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskExit_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
void OS_TaskExit_Impl()
{

} /* end OS_TaskExit_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskDelay_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskDelay_Impl(uint32 millisecond)
{
  return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskDelay_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskSetPriority_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskSetPriority_Impl (uint32 task_id, uint32 new_priority)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskSetPriority_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskRegister_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskRegister_Impl(uint32 global_task_id)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskRegister_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskGetId_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 OS_TaskGetId_Impl (void)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskGetId_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskGetInfo_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskGetInfo_Impl (uint32 task_id, OS_task_prop_t *task_prop)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TaskGetInfo_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskIdMatchSystemData_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
bool OS_TaskIdMatchSystemData_Impl(void *ref, uint32 local_id, const OS_common_record_t *obj)
{
    return false;
}

/*----------------------------------------------------------------
 *
 * Function: OS_TaskValidateSystemData_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskValidateSystemData_Impl(const void *sysdata, uint32 sysdata_size)
{
    return OS_ERR_NOT_IMPLEMENTED;
}



