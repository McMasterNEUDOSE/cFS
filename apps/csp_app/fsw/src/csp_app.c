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
** File: csp_app.c
**
** Purpose:
**   This file contains the source code for the CSP App.
**
*******************************************************************************/

/*
** Include Files:
*/
#include <string.h>
#include "csp_app_events.h"
#include "csp_app_version.h"
#include "csp_app.h"

#include <csp/csp.h>

#include <to_lab_app.c>

/*
** global data
*/
CSP_AppData_t CSP_AppData;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/* CSP_AppMain() -- Application entry point and main process loop          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void CSP_AppMain( void )
{
    int32  status;

    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp();

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(CSP_APP_PERF_ID);

    /*
    ** Perform application specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = CSP_AppInit();
    if (status != CFE_SUCCESS)
    {
        CSP_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** CSP Runloop
    */
    while (CFE_ES_RunLoop(&CSP_AppData.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(CSP_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status = CFE_SB_RcvMsg(&CSP_AppData.MsgPtr,
                               CSP_AppData.CommandPipe,
                               CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(CSP_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            CSP_ProcessCommandPacket(CSP_AppData.MsgPtr);
        }
        else
        {
            CFE_EVS_SendEvent(CSP_PIPE_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "CSP APP: SB Pipe Read Error, App Will Exit");

            CSP_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }

    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(CSP_APP_PERF_ID);

    CFE_ES_ExitApp(CSP_AppData.RunStatus);

} /* End of CSP_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* CSP_RouterTask() --  performs csp router work                              */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CSP_RouterTask(void)
{
    /* Here there will be routing */
    while (1) {
        csp_route_work(CSP_MAX_TIMEOUT);
    }

    CFE_ES_ExitChildTask();
}

void CSP_ServerTask(void)
{
    int32 status;

    status = CFE_ES_RegisterChildTask();
    if (status != CFE_SUCCESS)
    {
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP App: Server task registered\n");

    /* Set connectionless socket option */
    uint32 opts = CSP_SO_CONN_LESS;

    /* Create a socket */
    csp_socket_t *socket = csp_socket(opts);
    if (socket == NULL)
    {
        CFE_ES_WriteToSysLog("CSP App: CSP socket error\n");
        CFE_ES_ExitChildTask();
    }

    uint8 SERVER_PORT = 1;

    /* Bind server port to socket */
    status = csp_bind(socket, SERVER_PORT);
    if (status != CSP_ERR_NONE)
    {
        CFE_ES_WriteToSysLog("CSP App: CSP bind error\n");
        CFE_ES_ExitChildTask();
    }

    /* Create a packet */
    csp_packet_t *packet = NULL;

    uint32 timeout = 1000;

    while (packet == NULL)
    {
        packet = csp_recvfrom(socket, timeout);
    }

    CFE_ES_WriteToSysLog("CSP App: Packet received: %u", packet->data[0]);

    csp_buffer_free(packet);

    CFE_ES_ExitChildTask();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* CSP_AppInit() --  initialization                                           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 CSP_AppInit( void )
{
    int32    status;

    CSP_AppData.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    CSP_AppData.CmdCounter = 0;
    CSP_AppData.ErrCounter = 0;

    /*
    ** Initialize app configuration data
    */
    CSP_AppData.PipeDepth = CSP_PIPE_DEPTH;

    strcpy(CSP_AppData.PipeName, "CSP_CMD_PIPE");

    /*
    ** Initialize event filter table...
    */
    CSP_AppData.EventFilters[0].EventID = CSP_STARTUP_INF_EID;
    CSP_AppData.EventFilters[0].Mask    = 0x0000;
    CSP_AppData.EventFilters[1].EventID = CSP_COMMAND_ERR_EID;
    CSP_AppData.EventFilters[1].Mask    = 0x0000;
    CSP_AppData.EventFilters[2].EventID = CSP_COMMANDNOP_INF_EID;
    CSP_AppData.EventFilters[2].Mask    = 0x0000;
    CSP_AppData.EventFilters[3].EventID = CSP_COMMANDRST_INF_EID;
    CSP_AppData.EventFilters[3].Mask    = 0x0000;
    CSP_AppData.EventFilters[4].EventID = CSP_INVALID_MSGID_ERR_EID;
    CSP_AppData.EventFilters[4].Mask    = 0x0000;
    CSP_AppData.EventFilters[5].EventID = CSP_LEN_ERR_EID;
    CSP_AppData.EventFilters[5].Mask    = 0x0000;
    CSP_AppData.EventFilters[6].EventID = CSP_PIPE_ERR_EID;
    CSP_AppData.EventFilters[6].Mask    = 0x0000;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(CSP_AppData.EventFilters,
                              CSP_EVENT_COUNTS,
                              CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP App: Error Registering Events, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_SB_InitMsg(&CSP_AppData.HkBuf.MsgHdr,
                   CSP_APP_HK_TLM_MID,
                   sizeof(CSP_AppData.HkBuf),
                   true);

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&CSP_AppData.CommandPipe,
                               CSP_AppData.PipeDepth,
                               CSP_AppData.PipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP App: Error creating pipe, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(CSP_APP_SEND_HK_MID,
                              CSP_AppData.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP App: Error Subscribing to HK request, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(CSP_APP_CMD_MID,
                              CSP_AppData.CommandPipe);
    if (status != CFE_SUCCESS )
    {
        CFE_ES_WriteToSysLog("CSP App: Error Subscribing to Command, RC = 0x%08lX\n",
                             (unsigned long)status);

        return ( status );
    }
    /*
    ** Initialize CSP
    */
    csp_conf_t csp_conf;
    csp_conf_get_defaults(&csp_conf);
    status = csp_init(&csp_conf);
    if (status != CSP_ERR_NONE)
    {
        CFE_ES_WriteToSysLog("CSP App: Error initalizing CSP,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    CFE_ES_WriteToSysLog("CSP App: CSP Initialized successfully\n");

    /* 
    ** Start CSP router task
    */
    uint32 csp_router_task_id_ptr;
    status = CFE_ES_CreateChildTask(&csp_router_task_id_ptr, "CSP Router", CSP_RouterTask, NULL, 500, 64, 0);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP App: Error starting CSP router task,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    CFE_ES_WriteToSysLog("CSP App: CSP router task started\n");

    /* 
    ** Start CSP server task
    */
    uint32 csp_server_task_id_ptr;
    status = CFE_ES_CreateChildTask(&csp_server_task_id_ptr, "CSP server", CSP_ServerTask, NULL, 500, 64, 0);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP App: Error starting CSP server task,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    CFE_ES_WriteToSysLog("CSP App: CSP server task started\n");

    /* 
    ** Start TO Lab task
    */
    uint32 to_lab_task_id_ptr;
    status = CFE_ES_CreateChildTask(&to_lab_task_id_ptr, "TO Lab", TO_Lab_AppMain, NULL, 500, 64, 0);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP App: Error starting TO Lab task,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    CFE_ES_WriteToSysLog("CSP App: TO Lab task started\n");

    CFE_EVS_SendEvent (CSP_STARTUP_INF_EID,
                       CFE_EVS_EventType_INFORMATION,
                       "CSP App Initialized. Version %d.%d.%d.%d",
                       CSP_APP_MAJOR_VERSION,
                       CSP_APP_MINOR_VERSION,
                       CSP_APP_REVISION,
                       CSP_APP_MISSION_REV);

    return ( CFE_SUCCESS );

} /* End of CSP_AppInit() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  CSP_ProcessCommandPacket                                        */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the CSP    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void CSP_ProcessCommandPacket( CFE_SB_MsgPtr_t Msg )
{
    CFE_SB_MsgId_t  MsgId;

    MsgId = CFE_SB_GetMsgId(Msg);

    switch (MsgId)
    {
        case CSP_APP_CMD_MID:
            CSP_ProcessGroundCommand(Msg);
            break;

        case CSP_APP_SEND_HK_MID:
            CSP_ReportHousekeeping((CFE_SB_CmdHdr_t *)Msg);
            break;

        default:
            CFE_EVS_SendEvent(CSP_INVALID_MSGID_ERR_EID,
                              CFE_EVS_EventType_ERROR,
         	                  "CSP: invalid command packet,MID = 0x%x",
                              (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }

    return;

} /* End CSP_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_ProcessGroundCommand() -- CSP ground commands                    */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CSP_ProcessGroundCommand( CFE_SB_MsgPtr_t Msg )
{
    uint16 CommandCode;

    CommandCode = CFE_SB_GetCmdCode(Msg);

    /*
    ** Process "known" CSP app ground commands
    */
    switch (CommandCode)
    {
        case CSP_APP_NOOP_CC:
            if (CSP_VerifyCmdLength(Msg, sizeof(CSP_Noop_t)))
            {
                CSP_Noop((CSP_Noop_t *)Msg);
            }

            break;

        case CSP_APP_RESET_COUNTERS_CC:
            if (CSP_VerifyCmdLength(Msg, sizeof(CSP_ResetCounters_t)))
            {
                CSP_ResetCounters((CSP_ResetCounters_t *)Msg);
            }

            break;

        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(CSP_COMMAND_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "Invalid ground command code: CC = %d",
                              CommandCode);
            break;
    }

    return;

} /* End of CSP_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  CSP_ReportHousekeeping                                          */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 CSP_ReportHousekeeping( const CFE_SB_CmdHdr_t *Msg )
{
    /*
    ** Get command execution counters...
    */
    CSP_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter = CSP_AppData.ErrCounter;
    CSP_AppData.HkBuf.HkTlm.Payload.CommandCounter = CSP_AppData.CmdCounter;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(&CSP_AppData.HkBuf.MsgHdr);
    CFE_SB_SendMsg(&CSP_AppData.HkBuf.MsgHdr);

    return CFE_SUCCESS;

} /* End of CSP_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_Noop -- CSP NOOP commands                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 CSP_Noop( const CSP_Noop_t *Msg )
{

    CSP_AppData.CmdCounter++;

    CFE_EVS_SendEvent(CSP_COMMANDNOP_INF_EID,
                      CFE_EVS_EventType_INFORMATION,
                      "CSP: NOOP command  Version %d.%d.%d.%d",
                      CSP_APP_MAJOR_VERSION,
                      CSP_APP_MINOR_VERSION,
                      CSP_APP_REVISION,
                      CSP_APP_MISSION_REV);

    return CFE_SUCCESS;

} /* End of CSP_Noop */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  CSP_ResetCounters                                               */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 CSP_ResetCounters( const CSP_ResetCounters_t *Msg )
{

    CSP_AppData.CmdCounter = 0;
    CSP_AppData.ErrCounter = 0;

    CFE_EVS_SendEvent(CSP_COMMANDRST_INF_EID,
                      CFE_EVS_EventType_INFORMATION,
                      "CSP: RESET command");

    return CFE_SUCCESS;

} /* End of CSP_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_VerifyCmdLength() -- Verify command packet length                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool CSP_VerifyCmdLength( CFE_SB_MsgPtr_t Msg, uint16 ExpectedLength )
{
    bool result = true;

    uint16 ActualLength = CFE_SB_GetTotalMsgLength(Msg);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID   = CFE_SB_GetMsgId(Msg);
        uint16         CommandCode = CFE_SB_GetCmdCode(Msg);

        CFE_EVS_SendEvent(CSP_LEN_ERR_EID,
                          CFE_EVS_EventType_ERROR,
                          "Invalid Msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
                          (unsigned int)CFE_SB_MsgIdToValue(MessageID),
                          CommandCode,
                          ActualLength,
                          ExpectedLength);

        result = false;

        CSP_AppData.ErrCounter++;
    }

    return( result );

} /* End of CSP_VerifyCmdLength() */
