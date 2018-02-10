#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include "vnc.h"

//Thanks StackOverflow
uint32_t ntohl_md(uint32_t netlong)
{
	uint8_t data[4] = {0};
	memcpy(&data, &netlong, sizeof(data));
	return ((uint32_t) data[3] << 0)| ((uint32_t) data[2] << 8)| ((uint32_t) data[1] << 16)| ((uint32_t) data[0] << 24);
}

uint16_t ntohs_md(uint16_t netlong)
{
	uint8_t data[2] = {0};
	memcpy(&data, &netlong, sizeof(data));
	return (((uint16_t) data[1] << 0)| ((uint16_t) data[0] << 8));
}

int main(void)
{
	vnc *g_vnc = malloc(sizeof(*g_vnc));
	video_init();
	
	g_vnc->fd = vnc_connect("192.168.225.242", "5900");
	vnc_sock_read(g_vnc->fd, g_vnc->ver, 12); 
	vnc_sock_write(g_vnc->fd, "RFB 003.003\n", 12);
	g_vnc->ver[11] = '\0'; //Append NULL
	printf("VNC server RFB ver:-%s\n",g_vnc->ver);
	
	vnc_sock_read(g_vnc->fd, &g_vnc->connstat, sizeof(g_vnc->connstat));
	g_vnc->connstat =  ntohl_md(g_vnc->connstat);
	if(g_vnc->connstat == CONN_FAILED)
	{
		int i = vnc_sock_read(g_vnc->fd, &g_vnc->connstat, sizeof(g_vnc->connstat));
		if(i == g_vnc->connstat)
		{
			i = vnc_sock_read(g_vnc->fd, &g_vnc->failure, ntohl_md(g_vnc->connstat));
			printf("VNC init failed %s\n", g_vnc->failure);
		}
	}
	
	server_init server;
	client_init client;
	client.shared = 1;
	
	vnc_sock_write(g_vnc->fd, &client, sizeof(client));
	vnc_sock_read(g_vnc->fd, &server, sizeof(server)); 
	printf("server->width %"PRIu16"\n", ntohs_md(server.width));
	
	video_exit();
}