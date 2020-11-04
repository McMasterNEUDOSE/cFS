/*******************************************************************************
**
** File: csp_app_fwdgrnd.c
**
** Purpose:
**   Acts in place of COMMS subsystem to forward/receive CSP messages
**   from the CSP loopback interface to/from the ground system.
**
** Author:
**   Stephen Scott
**
*******************************************************************************/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

/*
** Implements
*/
#include "csp_app_fwdgrnd.h"

/*
** CSP app required
*/
#include <string.h>
#include "csp_app.h"
#include "csp_app_events.h"

/*
** LibCSP required
*/
#include "csp/csp.h"

/*
** UDP required
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_fwdto_ground() --  Forwards packets from CSP loopback to UDP socket    */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CSP_fwdto_ground(void)
{
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* Child task Initialization                                              */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

	int32 status;

	status = CFE_ES_RegisterChildTask();
	if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_REGISTERCHILD_ERR_EID,
                          "CSP - fwdto-Ground Task: Failed to register child task\n");
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - fwdto-Ground Task: Registered\n");

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* CSP Initialization                                                     */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

    /*
    ** Set connectionless socket option
    */
    uint32 opts = CSP_SO_CONN_LESS;

    /*
    ** Create a CSP socket
    */
    csp_socket_t *csp_sockid = csp_socket(opts);
    if (csp_sockid == NULL)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_SOCKET_ERR_EID,
                          "CSP - fwdto-Ground Task: Failed to create CSP socket\n");
        CFE_ES_ExitChildTask();
    }

    /*
    ** Bind CSP socket to OBC TLM port
    */
    uint8 OBC_TLM_PORT = 1;
    status = csp_bind(csp_sockid, OBC_TLM_PORT);
    if (status != CSP_ERR_NONE)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_BIND_ERR_EID,
                          "CSP - fwdto-Ground Task: Failed to bind CSP socket\n");
        CFE_ES_ExitChildTask();
    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* UDP Initialization                                                     */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

    /*
    ** Create a UDP socket
    */
    int32 udp_sockid = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sockid == -1)
    {
    	CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_SOCKET_ERR_EID,
                          "CSP - fwdto-Ground Task: Failed to create UDP socket\n");
        CFE_ES_ExitChildTask();
    }

    /*
    ** Initialize Ground address
    */
    struct sockaddr_in grnd_addr;
    size_t addrlen = sizeof(struct sockaddr_in);
	memset(&grnd_addr, 0, addrlen);
	grnd_addr.sin_addr.s_addr = INADDR_ANY;
	uint16 TLM_PORT = 1235;
	grnd_addr.sin_port = htons(TLM_PORT);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* Initialize loop variables                                              */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

    /*
	** Create a CSP packet
	*/
    csp_packet_t *packet;

    /*
    ** Set CSP timeout on recvfrom
    */
    uint32 timeout = CSP_MAX_TIMEOUT;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* Main loop                                                              */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

	while(1)
	{
	    /*
	    ** Receive a packet from CSP loopback with infinite timeout
	    */
	    packet = csp_recvfrom(csp_sockid, timeout);
	    if (packet == NULL)
	    {
	        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
	                          CSP_RECVFROM_ERR_EID,
	                          "CSP - fwdto-Ground Task: Failed to receive CSP packet\n");
	        continue;
	        
	    }

	    /*
	    ** Forward the packet data to the UDP socket
	    */
	    status = sendto(udp_sockid, (const CFE_SB_Msg_t *) packet->data, sizeof(CFE_SB_Msg_t),
	    	            0, (const struct sockaddr *) &grnd_addr, addrlen);
	    if (status == -1)
	    {
	    	CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
	                          CSP_SENDTO_ERR_EID,
	                          "CSP - fwdto-Ground Task: Failed to send UDP packet\n");
	    }
	}

	/*
	** Cleanup and exit
	*/
	CFE_ES_ExitChildTask();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CSP_fwdfrom_ground() --  Forwards packets from UDP socket to CSP loopback  */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CSP_fwdfrom_ground(void)
{
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* Child task Initialization                                              */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

	int32 status;

	status = CFE_ES_RegisterChildTask();
	if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_REGISTERCHILD_ERR_EID,
                          "CSP - fwdfrom-Ground Task: Failed to register child task\n");
        CFE_ES_ExitChildTask();
    }

    CFE_ES_WriteToSysLog("CSP - fwdfrom-Ground Task: Registered\n");

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* CSP Initialization                                                     */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

    /*
    ** Set connectionless socket option
    */
    uint32 opts = CSP_SO_CONN_LESS;

    /*
    ** Create a CSP socket
    */
    csp_socket_t *csp_sockid = csp_socket(opts);
    if (csp_sockid == NULL)
    {
        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_SOCKET_ERR_EID,
                          "CSP - fwdfrom-Ground Task: Failed to create CSP socket\n");
        CFE_ES_ExitChildTask();
    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* UDP Initialization                                                     */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

    /*
    ** Create a UDP socket
    */
    int32 udp_sockid = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sockid == -1)
    {
    	CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_SOCKET_ERR_EID,
                          "CSP - fwdfrom-Ground Task: Failed to create UDP socket\n");
        CFE_ES_ExitChildTask();
    }

    /*
    ** Initialize Ground and OBC address
    */
    struct sockaddr_in grnd_addr, obc_addr;
    uint32 obc_addr_len = sizeof(struct sockaddr_in);
    uint32 grnd_addr_len = sizeof(struct sockaddr_in);
	memset(&obc_addr, 0, obc_addr_len);
	memset(&grnd_addr, 0, grnd_addr_len);
	obc_addr.sin_addr.s_addr = INADDR_ANY;
	uint16 CMD_PORT = 1234;
	obc_addr.sin_port = htons(CMD_PORT);

	/*
    ** Bind UDP socket to CMD port
    */
    status = bind(udp_sockid, (const struct sockaddr *) &obc_addr, obc_addr_len);
    if (status == -1)
    {
    	CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_BIND_ERR_EID,
                          "CSP - fwdfrom-Ground Task: Failed to bind UDP socket\n");
        CFE_ES_ExitChildTask();
    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* Initialize loop variables                                              */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

    /*
    ** Buffer for recvfrom
    */
	CFE_SB_Msg_t *PktPtr = malloc(sizeof(CFE_SB_Msg_t));

	/*
	** Bytes received from recvfrom
	*/
	uint32 bytes_recvd;

	/*
	** Create CSP packet
	*/
	csp_packet_t *packet;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
    /*                                                                        */
    /* Main loop                                                              */
    /*                                                                        */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

    while(1)
    {
		/*
    	** Receive a packet from the UDP socket
    	*/
    	bytes_recvd = recvfrom(udp_sockid, PktPtr, sizeof(CFE_SB_Msg_t),
    						   0, (struct sockaddr *) &grnd_addr, &grnd_addr_len);
    	if (bytes_recvd == -1)
    	{
    		CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
                          CSP_RECVFROM_ERR_EID,
                          "CSP - fwdfrom-Ground Task: Failed to receive from UDP socket\n");
	        continue;
    	}

    	/*
    	** Get packet from CSP buffer
    	*/
    	packet = csp_buffer_get(sizeof(CFE_SB_Msg_t));
    	if (packet == NULL)
    	{
	        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
	                          CSP_BUFFERGET_ERR_EID,
	                          "CSP - fwdfrom-Ground: Failed to get packet from CSP buffer\n");
	        continue;
    	}

    	/*
    	** Assign data to CSP packet
    	*/
    	memcpy(packet->data, PktPtr, sizeof(CFE_SB_Msg_t));

    	/*
    	** Assign header to CSP packet
    	*/
	    uint8 prio      = CSP_PRIO_NORM;
	    uint8 dst       = CSP_OBC_NODE;
	    uint8 dst_port  = 3;
	    uint8 src_port  = 4;
	    uint32 timeout  = CSP_MAX_TIMEOUT;

	    /*
	    ** Send the packet to the CSP loopback interface
	    */
	    status = csp_sendto(prio, dst, dst_port, src_port, opts, packet, timeout);
	    if (status != CSP_ERR_NONE)
	    {
	        CFE_EVS_SendEvent(CFE_EVS_EventType_ERROR,
	                          CSP_BUFFERGET_ERR_EID,
	                          "CSP - Client Task: Failed to send CSP packet\n");
	        csp_buffer_free(packet);
	    }
    }

    /*
	** Cleanup and exit
	*/
	CFE_ES_ExitChildTask();
}
