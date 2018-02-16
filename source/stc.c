// Handles Server to Client Messages
#include "stc.h"
#include "platform.h"
#include <stdio.h>
static vnc *s_vnc; 
void framebuffer_update()
{
	fb_update_from_server fbdata;
	uint16_t number_of_rects;
	vnc_sock_read(s_vnc->fd, &number_of_rects, sizeof(uint16_t));
	
	for(int i = 0; i < number_of_rects; i++)
	{
		vnc_sock_read(s_vnc->fd, &fbdata, sizeof(fbdata));
		fbdata.h = ntohs_md(fbdata.h);
		fbdata.w = ntohs_md(fbdata.w);
		fbdata.x = ntohs_md(fbdata.x);
		fbdata.y = ntohs_md(fbdata.y);
		fbdata.encoding_type = ntohl_md(fbdata.encoding_type);
	
	
		switch(fbdata.encoding_type)
		{
			case 0: //RAW ENCODING
			{
				uint32_t len = fbdata.h * fbdata.w * s_vnc->format.bpp;
				void *pixel_data = malloc(len);
				vnc_sock_read(s_vnc->fd, pixel_data, len);
				vnc_draw_screen(fbdata.w, fbdata.h, fbdata.x, fbdata.y, pixel_data); 
				free(pixels);
			}
		}	
	}
}

int handleServerToClientMessages(vnc *_vnc)
{
	static uint8_t s_message;
	static uint8_t s_padding;
	s_vnc = _vnc;
	vnc_sock_read(s_vnc->fd, &s_message, sizeof(unsigned char));
	printf("s_message %d\n", s_message);
	vnc_sock_read(s_vnc->fd, &s_padding, sizeof(unsigned char)); // Skip Padding  
	
	switch(s_message)
	{
		case 0: //FramebufferUpdate
		{
			framebuffer_update();
			break;
		}
		
		case 1: //SetColourMapEntries
		{
			//set_colormap_entries();
			break;
		}
		
		case 2: //Bell
		{
			//bell();
			break;
		}
		
		case 3:
		{
			//server_cut_text();
			break;
		}
		
	}
}