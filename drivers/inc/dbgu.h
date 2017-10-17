#ifndef __DBGU_H__
#define __DBGU_H__

#include "stm32f4xx.h"

void debug_init_default(void);
void debug_chr(char chr);
int debug_test(void);
char debug_inkey(void);
char debug_waitkey(void);
void debug_msg(const char *str);
void debug_txt(const char *str);
void dbg_shdn(uint32_t shdn_on);

#endif
