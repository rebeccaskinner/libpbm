#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PNM_BITMAP (0x01)
#define PNM_GREY   (0x02)
#define PNM_COLOR  (0x03)
#define PNM_BINARY (0x04)
#define PNM_ASCII  (0x00)

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint8_t  flags;
    uint8_t* data;
} netpnm;

netpnm* netpnm_open(const char* filename)
{
    FILE* pnm;
    char buffer[64] = {0};
    uint32_t width, height;
    uint8_t flags;
    if(NULL == (pnm = fopen(filename,"r")))
        return fprint_err(stderr, NULL,
                "Error opening %s: %s\n",filename,strerror(errno));

}
