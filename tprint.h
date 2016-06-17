#ifndef _TPRINT_H_
#define _TPRINT_H_

#include <stdint.h>

#define BUFLEN 4096

void tprint(char * fmt, ...);

void strhex4(char * b, uint8_t c);
void strhex8(char * b, uint8_t c);
void strhex16(char * b, uint16_t c);
void strhex32(char * b, uint32_t c);
void strhex64(char * b, uint64_t c);

int strdec8(char * b, uint8_t c);
int strdec16(char * b, uint16_t c);
int strdec32(char * b, uint32_t c);
int strdec64(char * b, uint64_t c);

int strsigned8(char * b, int8_t c);
int strsigned16(char * b, int16_t c);
int strsigned32(char * b, int32_t c);
int strsigned64(char * b, int64_t c);

void puthex4(uint8_t c);
void puthex8(uint8_t c);
void puthex16(uint16_t c);
void puthex32(uint32_t c);

void putdec8(uint8_t c);
void putdec16(uint16_t c);
void putdec32(uint32_t c);

#endif /* _TPRINT_H_ */
