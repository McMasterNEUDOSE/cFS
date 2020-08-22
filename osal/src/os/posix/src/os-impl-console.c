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
 * \file     os-impl-console.c
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-impl-console.h"

#include "os-shared-printf.h"

/********************************************************************/
/*                 CONSOLE OUTPUT                                   */
/********************************************************************/

/*----------------------------------------------------------------
 *
 * Function: OS_ConsoleWakeup_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
void  OS_ConsoleWakeup_Impl(uint32 local_id)
{

} /* end OS_ConsoleWakeup_Impl */

/*----------------------------------------------------------------
 *
 * Function: OS_ConsoleCreate_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_ConsoleCreate_Impl(uint32 local_id)
{

    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_ConsoleCreate_Impl */

