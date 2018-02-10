#include <stdio.h>
#include <stdarg.h>

/* These functions should be implemented for your platform.*/

/*
 * This function should initialize your display screen
 */
void video_init();
 
/*
 * This function should de-initialize your display screen
 */
void video_exit();

/*
 * This function should use sockets to connect to a vnc server
 */
 int vnc_connect(char *addr, char *port);
 
 /*
  * Just put a ; in this function if you don't need it.
  */
  void debug_print(char *format, ...);
  
 /*
  * This function should perform a read from the sockets.
  */
  size_t vnc_sock_read(int socket, void *buf, size_t size);
  
  /*
   * This function should perform a write to the connected socket.
   */
   size_t vnc_sock_write(int socket, void *buf, size_t size);