#include <inttypes.h>

enum conn
{
	CONN_FAILED = 0,
	CONN_NOAUTH,
	CONN_AUTH,
};

typedef struct
{
	uint8_t bpp;
	uint8_t depth;
	uint8_t big_endian_flag;
	uint8_t true_color_flag;
	uint16_t rmax;
	uint16_t gmax;
	uint16_t bmax;
	uint8_t rshift;
	uint8_t gshift;
	uint8_t bshift;
	uint8_t padding[3];
}pixel_format;

typedef struct
{
	uint16_t width;
	uint16_t height;
	pixel_format format;
	uint32_t len;
	char *name;
}server_init;

typedef struct
{
	uint8_t shared;
}client_init;

typedef struct 
{
	int fd;
	char ver[12];
	int connstat;
	char failure[100];
}vnc;

typedef struct
{
	uint8_t type;
	uint8_t incremental;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
}fb_update;