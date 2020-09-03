/*******************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.7"
**
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
** File: csp_app.h
**
** Purpose:
**   This file is main hdr file for the CSP application.
**
**
*******************************************************************************/

#ifndef _csp_app_h_
#define _csp_app_h_

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include "csp_app_perfids.h"
#include "csp_app_msgids.h"
#include "csp_app_msg.h"

/************************************************************************
** Depth of the Command Pipe for Application
*************************************************************************/
#define CSP_PIPE_DEPTH  32

/************************************************************************
** Type Definitions
*************************************************************************/

/*
 * Buffer to hold telemetry data prior to sending
 * Defined as a union to ensure proper alignment for a CFE_SB_Msg_t type
 */
typedef union
{
    CFE_SB_Msg_t        MsgHdr;
    CSP_HkTlm_t      HkTlm;
} CSP_HkBuffer_t;

/*
** Global Data
*/
typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8                 CmdCounter;
    uint8                 ErrCounter;

    /*
    ** Housekeeping telemetry packet...
    */
    CSP_HkBuffer_t     HkBuf;

    /*
    ** Run Status variable used in the main processing loop
    */
    uint32 RunStatus;

    /*
    ** Operational data (not reported in housekeeping)...
    */
    CFE_SB_PipeId_t    CommandPipe;
    CFE_SB_MsgPtr_t    MsgPtr;

    /*
    ** Initialization data (not reported in housekeeping)...
    */
    char     PipeName[16];
    uint16   PipeDepth;

    CFE_EVS_BinFilter_t  EventFilters[CSP_EVENT_COUNTS];

} CSP_AppData_t;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (CSP_AppMain), these
**       functions are not called from any other source module.
*/
void  CSP_AppMain(void);
int32 CSP_AppInit(void);
void  CSP_ProcessCommandPacket(CFE_SB_MsgPtr_t Msg);
void  CSP_ProcessGroundCommand(CFE_SB_MsgPtr_t Msg);
int32 CSP_ReportHousekeeping(const CFE_SB_CmdHdr_t *Msg);
int32 CSP_ResetCounters(const CSP_ResetCounters_t *Msg);
int32 CSP_Noop(const CSP_Noop_t *Msg);
bool  CSP_VerifyCmdLength(CFE_SB_MsgPtr_t Msg, uint16 ExpectedLength);

#endif /* _csp_app_h_ */
