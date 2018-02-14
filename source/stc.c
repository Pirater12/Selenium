// Handles Server to Client Messages
#include "stc.h"
#include "platform.h"
#include <stdio.h>

void framebuffer_update()
{
	
}

int handleServerToClientMessages(vnc *s_vnc)
{
	uint8_t s_message;
	printf("Works till b4 sockread");
	vnc_sock_read(s_vnc->fd, &s_message, sizeof(unsigned char));
	printf("s_message %d\n", s_message);
	/*switch(s_message)
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
	*/
}