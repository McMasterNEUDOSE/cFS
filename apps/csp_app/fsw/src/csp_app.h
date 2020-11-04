/**
  * @file   csp_app.h
  * @brief  This file is the main header file for the CSP application.
  * @author Stephen Scott
  */

#ifndef _csp_app_h_
#define _csp_app_h_

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
#include "csp_app_tbldefs.h"

/* Depth of the command and telemetry pipes */
#define CSP_CMD_PIPE_DEPTH  32
#define CSP_TLM_PIPE_DEPTH 	32

/* LibCSP Nodes */
#define CSP_OBC_NODE    0
#define CSP_PDM_NODE    1
#define CSP_RAD_NODE    2
#define CSP_DAM_NODE    3
#define CSP_SOBC_NODE   4

/**
  * @union  CSP_HkBuffer_t
  * @brief  Buffer to hold telemetry data prior to sending.
  *         Defined as a union to ensure proper alignment for a CFE_SB_Msg_t
  */
typedef union
{
    CFE_SB_Msg_t    MsgHdr; /*!< Software bus message header */
    CSP_HkTlm_t     HkTlm;  /*!< Housekeeping telemetry data */
} CSP_HkBuffer_t;

/**
  * @struct CSP_AppData_t
  * @brief  Contains the global data for the CSP app
  */
typedef struct
{
    uint8           CmdCounter;     /*!< Command counter */
    uint8           ErrCounter;     /*!< Error counter */
    CSP_HkBuffer_t  HkBuf;          /*!< Housekeeping telemetry buffer */
    uint32          RunStatus;      /*!< Application run status */
    CFE_SB_PipeId_t CmdPipe;        /*!< Command pipe ID */
    CFE_SB_MsgPtr_t CmdPtr;         /*!< Command message pointer */
    CFE_SB_PipeId_t TlmPipe;        /*!< Telemetry pipe ID */
    CFE_SB_MsgPtr_t TlmPtr;         /*!< Telemetry message pointer */
    char            CmdPipeName[16];/*!< Command pipe name */
    uint16          CmdPipeDepth;   /*!< Command pipe depth */
    char            TlmPipeName[16];/*!< Telemetry pipe name */
    uint16          TlmPipeDepth;   /*!< Telemetry pipe depth */
    CFE_EVS_BinFilter_t EventFilters[CSP_EVENT_COUNTS]; /*!< Application events */

} CSP_AppData_t;

/**
  * @brief Global CSP app data variable
  */
CSP_AppData_t       CSP_AppData;

/**
  * @brief Global CSP app subscription table pointer
  */
CSP_App_SubTable_t  *CSP_App_SubTbl;

/**
  * @brief Global CSP app subscription table handle
  */
CFE_TBL_Handle_t    CSP_App_SubTblHandle;

/* Local function prototypes */
void  CSP_AppMain(void);
int32 CSP_AppInit(void);
void  CSP_ProcessCommandPacket(CFE_SB_MsgPtr_t Msg);
void  CSP_ProcessGroundCommand(CFE_SB_MsgPtr_t Msg);
int32 CSP_ReportHousekeeping(const CFE_SB_CmdHdr_t *Msg);
int32 CSP_ResetCounters(const CSP_ResetCounters_t *Msg);
int32 CSP_Noop(const CSP_Noop_t *Msg);
bool  CSP_VerifyCmdLength(CFE_SB_MsgPtr_t Msg, uint16 ExpectedLength);

#endif /* _csp_app_h_ */
