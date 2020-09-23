/*******************************************************************************
**
** File: csp_app.c
**
** Purpose:
**   This file contains the source code for the CSP App.
**
** Author:
**   Stephen Scott
**
*******************************************************************************/

/*
** Include Files:
*/
#include <string.h>

#include "csp_app.h"
#include "csp_app_events.h"
#include "csp_app_version.h"
#include "csp_app_tbldefs.h"
#include "csp/csp.h"

/*
** global data
*/
CSP_AppData_t 		CSP_AppData;
CSP_App_SubTable_t 	*CSP_App_SubTbl;
CFE_TBL_Handle_t 	CSP_App_SubTblHandle;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/*                                                                            */
/* CSP_AppMain() -- Application entry point and main process loop             */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void CSP_AppMain( void )
{
    int32  status;

    /*
    ** Register the app with Executive services
    */
    status = CFE_ES_RegisterApp();
    if (status != CFE_SUCCESS)
    {
        CSP_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

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
        status = CFE_SB_RcvMsg(&CSP_AppData.CmdPtr,
                               CSP_AppData.CmdPipe,
                               CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(CSP_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            CSP_ProcessCommandPacket(CSP_AppData.CmdPtr);
        }
        else
        {
            CFE_EVS_SendEvent(CSP_PIPE_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "CSP: SB Pipe Read Error, App Will Exit");

            CSP_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }

    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(CSP_APP_PERF_ID);

    CFE_ES_ExitApp(CSP_AppData.RunStatus);

} /* End of CSP_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_RouterTask() --  performs csp router work                              */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CSP_RouterTask(void)
{
    int32 status;

    status = CFE_ES_RegisterChildTask();
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_REGISTERCHILD_ERR_EID,
                          "CSP - Router Task: Failed to register CSP router task\n");
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - Router Task: Registered\n");

    /* Here there will be routing */
    while (1) {
        csp_route_work(CSP_MAX_TIMEOUT);
    }

    CFE_ES_ExitChildTask();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_ServerTask() --  Mock node for communication                           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CSP_ServerTask(void)
{
    int32 status;

    status = CFE_ES_RegisterChildTask();
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_REGISTERCHILD_ERR_EID,
                          "CSP - Server Task: Failed to register CSP server task\n");
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - Server Task: Registered\n");

    /*
    ** Set connectionless socket option
    */
    uint32 opts = CSP_SO_CONN_LESS;

    /*
    ** Create a socket
    */
    csp_socket_t *socket = csp_socket(opts);
    if (socket == NULL)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_SOCKET_ERR_EID,
                          "CSP - Server Task: Failed to create CSP socket\n");
        CFE_ES_ExitChildTask();
    }

    uint8 SERVER_PORT = 1;

    /*
    ** Bind server port to socket
    */
    status = csp_bind(socket, SERVER_PORT);
    if (status != CSP_ERR_NONE)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_BIND_ERR_EID,
                          "CSP - Server Task: Failed to bind CSP socket\n");
        CFE_ES_ExitChildTask();
    }

    /*
    ** Create a packet
    */
    csp_packet_t *packet = NULL;

    /*
    ** Receive a packet with infinite timeout
    */
    uint32 timeout = CSP_MAX_TIMEOUT;
    packet = csp_recvfrom(socket, timeout);
    if (packet == NULL)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_RECVFROM_ERR_EID,
                          "CSP - Server Task: Failed to receive CSP packet\n");
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - Server Task: Packet received, data: %u", packet->data[0]);

    csp_buffer_free(packet);

    CFE_ES_ExitChildTask();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_ClientTask() --  Mock node for communication                           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CSP_ClientTask(void)
{
    int32 status;

    status = CFE_ES_RegisterChildTask();
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_REGISTERCHILD_ERR_EID,
                          "CSP - Client Task: Failed to register CSP client task\n");
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - Client Task: Registered\n");

    /*
    ** Set connectionless socket option
    */
    uint32 opts = CSP_SO_CONN_LESS;

    /*
    ** Create a socket
    */
    csp_socket_t *socket = csp_socket(opts);
    if (socket == NULL)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_SOCKET_ERR_EID,
                          "CSP - Client Task: Failed to create CSP socket\n");
        CFE_ES_ExitChildTask();
    }

    /*
    ** Get a 100 byte packet from the CSP buffer
    */
    csp_packet_t *packet;
    size_t data_size = 100;

    packet = csp_buffer_get(data_size);
    if (packet == NULL)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_BUFFERGET_ERR_EID,
                          "CSP - Client Task: Failed to get CSP packet from buffer\n");
        CFE_ES_ExitChildTask();
    }

    /*
    ** Copy data to packet
    */
    uint8 MOCKDATA = 200;
    packet->data[0] = MOCKDATA;

    uint8 prio      = CSP_PRIO_NORM;
    uint8 dst       = CSP_OBC_NODE;
    uint8 dst_port  = 1;
    uint8 src_port  = 2;
    uint32 timeout  = CSP_MAX_TIMEOUT;

    /*
    ** Send the packet
    */
    status = csp_sendto(prio, dst, dst_port, src_port, opts, packet, timeout);
    if (status != CSP_ERR_NONE)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_BUFFERGET_ERR_EID,
                          "CSP - Client Task: Failed to send CSP packet\n");
        csp_buffer_free(packet);
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - Client Task: Packet sent, data: %u\n", packet->data[0]);

    CFE_ES_ExitChildTask();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* CSP_AppInit() --  initialization                                           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 CSP_AppInit( void )
{
    int32 	status;
    uint16 	i;

    CSP_AppData.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    CSP_AppData.CmdCounter = 0;
    CSP_AppData.ErrCounter = 0;

    /*
    ** Initialize app configuration data
    */
    CSP_AppData.CmdPipeDepth = CSP_CMD_PIPE_DEPTH;
	strcpy(CSP_AppData.CmdPipeName, "CSP_CMD_PIPE");

	CSP_AppData.TlmPipeDepth = CSP_TLM_PIPE_DEPTH;
	strcpy(CSP_AppData.TlmPipeName, "CSP_TLM_PIPE");

    /*
    ** Initialize event filter table...
    */
    CSP_AppData.EventFilters[0].EventID     = CSP_STARTUP_INF_EID;
    CSP_AppData.EventFilters[0].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[1].EventID     = CSP_COMMAND_ERR_EID;
    CSP_AppData.EventFilters[1].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[2].EventID     = CSP_COMMANDNOP_INF_EID;
    CSP_AppData.EventFilters[2].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[3].EventID     = CSP_COMMANDRST_INF_EID;
    CSP_AppData.EventFilters[3].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[4].EventID     = CSP_INVALID_MSGID_ERR_EID;
    CSP_AppData.EventFilters[4].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[5].EventID     = CSP_LEN_ERR_EID;
    CSP_AppData.EventFilters[5].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[6].EventID     = CSP_PIPE_ERR_EID;
    CSP_AppData.EventFilters[6].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[7].EventID     = CSP_REGISTERCHILD_ERR_EID;
    CSP_AppData.EventFilters[7].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[8].EventID     = CSP_SOCKET_ERR_EID;
    CSP_AppData.EventFilters[8].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[9].EventID     = CSP_BIND_ERR_EID;
    CSP_AppData.EventFilters[9].Mask        = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[10].EventID    = CSP_BUFFERGET_ERR_EID;
    CSP_AppData.EventFilters[10].Mask       = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[11].EventID    = CSP_SENDTO_ERR_EID;
    CSP_AppData.EventFilters[11].Mask       = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[12].EventID    = CSP_RECVFROM_ERR_EID;
    CSP_AppData.EventFilters[12].Mask       = CFE_EVS_NO_FILTER;
    CSP_AppData.EventFilters[13].EventID    = CSP_TBL_ERR_EID;
    CSP_AppData.EventFilters[13].Mask       = CFE_EVS_NO_FILTER;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(CSP_AppData.EventFilters,
                              CSP_EVENT_COUNTS,
                              CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP: Error Registering Events, RC = 0x%08lX\n",
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
    ** Register the subscription table
    */
    status = CFE_TBL_Register(&CSP_App_SubTblHandle, "CSP_App_SubTbl",
    						  sizeof(*CSP_App_SubTbl), CFE_TBL_OPT_DEFAULT, NULL);
    if (status != CFE_SUCCESS)
    {
    	CFE_ES_WriteToSysLog("CSP: Error registering subscription table, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Load the subscription table
    */
    status = CFE_TBL_Load(CSP_App_SubTblHandle, CFE_TBL_SRC_FILE, "/cf/csp_app_subtbl.tbl");
    if (status != CFE_SUCCESS)
    {
    	CFE_ES_WriteToSysLog("CSP: Error loading subscription table, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Get the subscription table address
    */
    status = CFE_TBL_GetAddress((void *)(&CSP_App_SubTbl), CSP_App_SubTblHandle);
    if (status != (CFE_SUCCESS | CFE_TBL_INFO_UPDATED) )
    {
    	CFE_ES_WriteToSysLog("CSP: Error getting subscription table address RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Create command pipe
    */
    status = CFE_SB_CreatePipe(&CSP_AppData.CmdPipe,
                               CSP_AppData.CmdPipeDepth,
                               CSP_AppData.CmdPipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP: Error creating command pipe, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(CSP_APP_SEND_HK_MID,
                              CSP_AppData.CmdPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP: Error Subscribing to HK request, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(CSP_APP_CMD_MID,
                              CSP_AppData.CmdPipe);
    if (status != CFE_SUCCESS )
    {
        CFE_ES_WriteToSysLog("CSP: Error Subscribing to Command, RC = 0x%08lX\n",
                             (unsigned long)status);

        return ( status );
    }

    /*
    ** Create telemetry pipe
    */
    status = CFE_SB_CreatePipe(&CSP_AppData.TlmPipe,
                               CSP_AppData.TlmPipeDepth,
                               CSP_AppData.TlmPipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP: Error creating telemetry pipe, RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /*
    ** Subscribe to telemetry packets
    */
    for (i = 0; (i < (sizeof(CSP_App_SubTbl->Subs) / sizeof(CSP_App_SubTbl->Subs[0]))); i++)
    {
    	if (CFE_SB_IsValidMsgId(CSP_App_SubTbl->Subs[i].Stream) && (CSP_App_SubTbl->Subs[i].Stream != 0) ) 
    	{
    		status = CFE_SB_Subscribe(CSP_App_SubTbl->Subs[i].Stream, CSP_AppData.TlmPipe);
    	}
    	else /* Reached the end of the subscriptions */
    	{
    		break;
    	}

    	if (status != CFE_SUCCESS)
    	{
    		CFE_ES_WriteToSysLog("CSP: Can't subscribe to stream 0x%x, RC = 0x%08lX\n",
    						 (unsigned int)CFE_SB_MsgIdToValue(CSP_App_SubTbl->Subs[i].Stream),
                             (unsigned long)status);
        	return ( status );
    	}
    }

    /*
    ** Configure CSP
    */
    csp_conf_t csp_conf;
    csp_conf_get_defaults(&csp_conf);
    csp_conf.address = CSP_OBC_NODE;

    /* 
    ** Initialize CSP
    */
    status = csp_init(&csp_conf);
    if (status != CSP_ERR_NONE)
    {
        CFE_ES_WriteToSysLog("CSP: Error initalizing CSP,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /* 
    ** Start CSP router task
    */
    uint32 csp_routertask_id_ptr;

    status = CFE_ES_CreateChildTask(&csp_routertask_id_ptr, "CSP Router", CSP_RouterTask, NULL, 500, 64, 0);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP: Error starting CSP router task,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /* 
    ** Start CSP server task
    */
    uint32 csp_servertask_id_ptr;

    status = CFE_ES_CreateChildTask(&csp_servertask_id_ptr, "CSP server", CSP_ServerTask, NULL, 500, 64, 0);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP: Error starting CSP server task,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

    /* 
    ** Start CSP client task
    */
    uint32 csp_clienttask_id_ptr;

    status = CFE_ES_CreateChildTask(&csp_clienttask_id_ptr, "CSP client", CSP_ClientTask, NULL, 500, 64, 0);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CSP: Error starting CSP client task,  RC = 0x%08lX\n",
                             (unsigned long)status);
        return ( status );
    }

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
/*  Name:  CSP_ProcessCommandPacket                                           */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the CSP       */
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
                              "CSP: Invalid ground command code: CC = %d",
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
