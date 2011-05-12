#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdarg.h>

#include "utils.h"

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

static int skip_comments(FILE* stream)
{
    int skip_count = 0;
    char buffer[2] = {0};
    fread(buffer,1,sizeof(char),stream);
    while('#' == buffer[0])
    {
        buffer[1] = 0;
        fread(buffer,1,sizeof(char),stream);
        do
        {
            fread(buffer+1,1,sizeof(char),stream);
        } while('\n' != buffer[1]);
        ++skip_count;
    }
    fseek(stream,-(!!skip_count),SEEK_CUR);
    return skip_count;
}

static int scan_next_line(FILE* stream, const char* fmt, ...)
{
    int processed;
    skip_comments(stream);
    va_list ap;
    va_start(ap,fmt);
    processed = vfscanf(stream,fmt,ap);
    va_end(ap);
    return processed;
}

netpnm* netpnm_new(uint8_t flags)
{
    netpnm* i = malloc(sizeof(netpnm));
    i->width  = 0;
    i->height = 0;
    i->data   = 0;
    i->flags  = flags;
}

netpnm* netpnm_size_new(uint32_t width, uint32_t height, uint8_t flags)
{
    netpnm* i = netpnm_new(flags);
    i->width = width;
    i->height = height;
    if(PNM_COLOR & flags) i->data = malloc(3*width*height);
    else i->data = malloc(width*height);
    return i;
}

void netpnm_load_ascii(FILE* stream, netpnm* img)
{
    char buffer[3];
    printf("img total size: %d\n",img->width * img->height);
    for(int i = 0; i < (img->width * img->height); ++i)
    {
        fscanf(stream,"%3s",buffer);
        printf("read idx %d: \"%3c\"\n",i,buffer);
    }
}

netpnm* netpnm_open(const char* filename)
{
    FILE* pnm;
    uint32_t width, height;
    uint8_t flags, type;
    int rval;
    if(NULL == (pnm = fopen(filename,"r")))
        return fprint_err(stderr, NULL,
                "Error opening %s: %s\n",filename,strerror(errno));
    if(EOF == fscanf(pnm,"P%1d\n",&type))
        return print_err(NULL,"Invalid PNM Header\n");

    scan_next_line(pnm,"%d %d",&width,&height);

    netpnm* image = netpnm_size_new(width,height,type);
    printf("Type: P%d, width=%d, height=%d\n",type,width,height);

    netpnm_load_ascii(pnm, image);

    return NULL;
}

#ifdef SELF_TEST
int main(int argc, char** argv)
{
    netpnm_open(argv[1]);
    return 0;
}
#endif
