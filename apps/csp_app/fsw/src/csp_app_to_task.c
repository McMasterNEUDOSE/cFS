/**
  * @file   csp_app_to_task.c
  * @brief  CSP Telemetry Output task
  * @author Stephen Scott
  */

#include "csp_app_to_task.h"
#include "csp_app.h"
#include "csp_app_events.h"
#include "csp_app_tbldefs.h"
#include "csp/csp.h"

/**
  * @brief  Main telemetry output task.
            Forwards subscribed messages from SB to CSP interface
  * @retval None
  */
void CSP_TO_Task(void)
{
    int32 status;

    /* Register the task with executive services */
    status = CFE_ES_RegisterChildTask();
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_REGISTERCHILD_ERR_EID,
                          "CSP - TO Task: Failed to register child task\n");
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - TO Task: Registered\n");

    /* Set connectionless socket option */
    uint32 opts = CSP_SO_CONN_LESS;

    /* Create a socket */
    csp_socket_t *socket = csp_socket(opts);
    if (socket == NULL)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_SOCKET_ERR_EID,
                          "CSP - TO Task: Failed to create CSP socket\n");
        CFE_ES_ExitChildTask();
    }

    /* CSP packet for main loop */
    csp_packet_t *packet;

    /* Main process loop */
    while(1)
    {
        /* Pend on receiving subscribed messages from the TLM pipe */
        status = CFE_SB_RcvMsg(&CSP_AppData.TlmPtr, CSP_AppData.TlmPipe, CFE_SB_PEND_FOREVER);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_PIPE_ERR_EID,
                          "CSP - TO Task: Failed to receive from TLM pipe\n");
            continue;
        }

        /* Get packet from CSP buffer - size of SB message */
        packet = csp_buffer_get(sizeof(CFE_SB_Msg_t));
        if (packet == NULL)
        {
            CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                              CSP_BUFFERGET_ERR_EID,
                              "CSP - TO Task: Failed to get packet from CSP buffer\n");
            continue;
        }

        /* Assign data to CSP packet */
        memcpy(packet->data, CSP_AppData.TlmPtr, sizeof(CFE_SB_Msg_t));

        /* Assign header to CSP packet */
        uint8 prio      = CSP_PRIO_NORM;
        uint8 dst       = CSP_OBC_NODE;
        uint8 dst_port  = 1;
        uint8 src_port  = 2;
        uint32 timeout  = CSP_MAX_TIMEOUT;

        /* Send the packet to the CSP loopback interface */
        status = csp_sendto(prio, dst, dst_port, src_port, opts, packet, timeout);
        if (status != CSP_ERR_NONE)
        {
            CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                              CSP_BUFFERGET_ERR_EID,
                              "CSP - TO Task: Failed to send CSP packet\n");
            csp_buffer_free(packet);
        }
    }

    /* Exit task */
    CFE_ES_ExitChildTask();
}
