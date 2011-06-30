#ifndef __PNM_UTILS_H__
#define __PNM_UTILS_H__

typedef unsigned char byte;

void* fprint_err(FILE* dest, void* rval, const char* fmt, ...) __attribute__((format(printf,3,4)));
void* print_err(void* rval, const char* fmt, ...) __attribute__((format(printf,2,3)));
#endif
