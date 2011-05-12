#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* fprint_err(FILE* dest, void* rval, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(dest,fmt,ap);
    va_end(ap);
    return rval;
}

void* print_err(void* rval, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(dest,fmt,ap);
    va_end(ap);
    return rval;
}
