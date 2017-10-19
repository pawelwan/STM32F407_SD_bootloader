#ifndef __DBGU_H__
#define __DBGU_H__

#include "stm32f4xx.h"

void debug_init(void);
void debug_deinit(void);
int debug_test(void);
void debug_chr(char chr);
char debug_waitkey(void);

#endif
