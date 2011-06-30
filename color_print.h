#ifndef __COLOR_PRINT_H
#define __COLOR_PRINT_H

#define CPF_RESET     0
#define CPF_NORMAL    0
#define CPF_BOLD      1
#define CPF_DIM       2
#define CPF_UNDERLINE 4
#define CPF_BLINK     5
#define CPF_NEGATIVE  7

#define CPF_BLACK       0
#define CPF_RED         1
#define CPF_GREEN       2
#define CPF_BROWN       3
#define CPF_BLUE        4
#define CPF_MAGENTA     5
#define CPF_CYAN        6
#define CPF_WHITE       7

#define CPF_ESCAPE      0x1B

#ifdef __cplusplus
extern "C" {
#endif
void color_start(int mode, int fg, int bg);
void color_stop();
void color_printf(int mode, int fg, int bg, const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
