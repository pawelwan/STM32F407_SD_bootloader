#ifndef __DBGU_H__
#define __DBGU_H__

#include "stm32f4xx.h"

void debug_init_default(void);
void debug_chr(char chr);
int debug_test(void);
char debug_inkey(void);
char debug_waitkey(void);
void debug_ascii(uint8_t b);
void debug_msg(const char *str);
void debug_txt(const char *str);
void debug_txt_limit(const char *str, uint8_t len);
void debug8_t(uint8_t val);
void debug16_t (uint16_t val);
void debug32_t (uint32_t val);
void debug_value( const char* s, uint32_t value);
void debug_array( void *array, uint16_t size );
void debug_dump(void *address, uint16_t len);
uint8_t debug_input_string(char * pBuf, uint8_t BufSize);
uint32_t debug_input_hex(uint32_t input);
void dbg_shdn(uint32_t shdn_on);

#endif
