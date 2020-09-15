/*******************************************************************************
**
** File: csp_app.h
**
** Purpose:
**   This file is the main hdr file for the CSP application.
**
** Author:
**   Stephen Scott
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
#include "cfe_tbl.h"

#include "csp_app_perfids.h"
#include "csp_app_msgids.h"
#include "csp_app_msg.h"
#include "csp_app_events.h"

/************************************************************************
** Depth of the Command Pipe for Application
*************************************************************************/
#define CSP_CMD_PIPE_DEPTH  32
#define CSP_TLM_PIPE_DEPTH 	32

/************************************************************************
** LibCSP Nodes
*************************************************************************/
#define CSP_OBC_NODE    0
#define CSP_PDM_NODE    1
#define CSP_RAD_NODE    2
#define CSP_DAM_NODE    3
#define CSP_SOBC_NODE   4

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
    CSP_HkTlm_t         HkTlm;
} CSP_HkBuffer_t;

/*
** Global Data
*/
typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8               CmdCounter;
    uint8               ErrCounter;

    /*
    ** Housekeeping telemetry packet...
    */
    CSP_HkBuffer_t      HkBuf;

    /*
    ** Run Status variable used in the main processing loop
    */
    uint32 RunStatus;

    /*
    ** Command pipe...
    */
    CFE_SB_PipeId_t     CmdPipe;
    CFE_SB_MsgPtr_t     CmdPtr;

    /*
    ** Telemetry pipe...
    */
    CFE_SB_PipeId_t     TlmPipe;
    CFE_SB_MsgPtr_t     TlmPtr;

    /*
    ** Initialization data (not reported in housekeeping)...
    */
    char                CmdPipeName[16];
    uint16              CmdPipeDepth;
    char                TlmPipeName[16];
    uint16              TlmPipeDepth;

    CFE_EVS_BinFilter_t  EventFilters[CSP_EVENT_COUNTS];

} CSP_AppData_t;

/****************************************************************************/

/*
** Local function prototypes.
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
