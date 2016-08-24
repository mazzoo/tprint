#include <stdarg.h>
#include <stdint.h>

#include <tprint.h>

char g_buf[BUFLEN];

/***********************************************/
/* implement architecture/application specific */
/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/***********************************************/
int putchar(int c);

void tputc(char c)
{
    /* implement architecture/application specific */
    putchar(c);
}
/************************************************/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/* /implement architecture/application specific */
/************************************************/

void tputs(char * s)
{
    while (*s) tputc(*s++);
}

void error_unsupported(void)
{
    tputs("ERROR: unsupported tprint format\n");
}

void tprint(char * fmt, ...)
{
    char * buf = g_buf;
    buf[0] = 0;
    int buf_off = 0;
    char ch;
    va_list ap;
    va_start(ap, fmt);
    int16_t len_mod = 0;
    while ((ch = *fmt))
    {
        if (ch == '%')
        {
            len_mod = 0;
            ch = *++fmt;
            uint8_t fmt_done = 0;
            while (!fmt_done)
            {
                switch (ch)
                {
                    case '%':
                        buf[buf_off++] = ch;
                        fmt++;
                        fmt_done = 1;
                        break;
                    case 's':
                        {
                            char * p = va_arg(ap, char *);
                            while (len_mod < 0)
                            {
                                buf[buf_off++] = ' ';
                                len_mod++;
                            }
                            while (*p)
                            {
                                buf[buf_off++] = *p++;
                            }
                            while (len_mod > 0)
                            {
                                buf[buf_off++] = ' ';
                                len_mod--;
                            }
                            fmt++;
                            fmt_done = 1;
                        }
                        break;
                    case 'c':
                        {
                            char c = va_arg(ap, int);
                            buf[buf_off++] = c;
                            fmt++;
                            fmt_done = 1;
                        }
                        break;
                    case 'u':
                        {
                            switch (len_mod)
                            {
                                case 0:
                                case 4:
                                    {
                                        uint32_t u = va_arg(ap, uint32_t);
                                        buf_off += strdec32(&buf[buf_off], u);
                                    }
                                    break;
                                case 1:
                                    {
                                        uint8_t u = va_arg(ap, unsigned int);
                                        buf_off += strdec8(&buf[buf_off], u);
                                    }
                                    break;
                                case 2:
                                    {
                                        uint16_t u = va_arg(ap, unsigned int);
                                        buf_off += strdec16(&buf[buf_off], u);
                                    }
                                    break;
                                case 8:
                                    {
                                        uint64_t u = va_arg(ap, uint64_t);
                                        buf_off += strdec64(&buf[buf_off], u);
                                    }
                                    break;
                                default:
                                    error_unsupported();
                            }
                            fmt++;
                            fmt_done = 1;
                        }
                        break;
                    case 'd':
                        {
                            switch (len_mod)
                            {
                                case 0:
                                case 4:
                                    {
                                        int32_t d = va_arg(ap, int32_t);
                                        buf_off += strsigned32(&buf[buf_off], d);
                                    }
                                    break;
                                case 1:
                                    {
                                        int8_t d = va_arg(ap, int);
                                        buf_off += strsigned8(&buf[buf_off], d);
                                    }
                                    break;
                                case 2:
                                    {
                                        int16_t d = va_arg(ap, int);
                                        buf_off += strsigned16(&buf[buf_off], d);
                                    }
                                    break;
                                case 8:
                                    {
                                        int64_t d = va_arg(ap, int64_t);
                                        buf_off += strsigned64(&buf[buf_off], d);
                                    }
                                    break;
                                default:
                                    error_unsupported();
                            }
                            fmt++;
                            fmt_done = 1;
                        }
                        break;
                    case 'x':
                        {
                            switch (len_mod)
                            {
                                case 0:
                                case 4:
                                    {
                                        int32_t i = va_arg(ap, int32_t);
                                        strhex32(&buf[buf_off], i);
                                        buf_off += 8;
                                    }
                                    break;
                                case 1:
                                    {
                                        int8_t i = va_arg(ap, int);
                                        strhex8(&buf[buf_off], i);
                                        buf_off += 2;
                                    }
                                    break;
                                case 2:
                                    {
                                        int16_t i = va_arg(ap, int);
                                        strhex16(&buf[buf_off], i);
                                        buf_off += 4;
                                    }
                                    break;
                                case 8:
                                    {
                                        int64_t i = va_arg(ap, int64_t);
                                        strhex64(&buf[buf_off], i);
                                        buf_off += 16;
                                    }
                                    break;
                                default:
                                    error_unsupported();
                            }
                            fmt_done = 1;
                            fmt++;
                        }
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        len_mod = 10 * len_mod + ch - '0';
                        fmt++;
                        ch = *fmt;
                        break;
                    case '-':
                        len_mod = - len_mod;
                        fmt++;
                        ch = *fmt;
                        break;
                    default:
                        error_unsupported();
                        fmt_done = 1;
                }
            }
        }else{
            buf[buf_off++] = ch;
            fmt++;
        }
    }
    va_end(ap);
    buf[buf_off] = 0;
    tputs(g_buf);
}

void strhex4(char * b, uint8_t c)
{
    c &= 0x0f;
    if (c > 9) b[0] = c + 'a' - 10;
    else       b[0] = c + '0';
    b[1] = 0; /* well ... size savings >> runtime */
}

void strhex8(char * b, uint8_t c)
{
    strhex4(&b[0], c>>4);
    strhex4(&b[1], c&0x0f);
}

void strhex16(char * b, uint16_t c)
{
    strhex8(&b[0], c>>8);
    strhex8(&b[2], c&0xff);
}

void strhex32(char * b, uint32_t c)
{
    strhex16(&b[0], c>>16);
    strhex16(&b[4], c&0xffff);
}

void strhex64(char * b, uint64_t c)
{
    strhex32(&b[0], c>>32);
    strhex32(&b[8], c&0xffffffff);
}

int strsigned8(char * b, int8_t c)
{
    if (c<0)
    {
        b[0] = '-';
        c = -c;
        return 1 + strdec8(&b[1], c);
    }
    else
    {
        return strdec8(b, c);
    }
}

int strdec8(char * b, uint8_t c)
{
    int i = 0;
    uint8_t dig3 = 0;
    if (c > 99)
    {
        b[i++] = ('0' + c / 100);
        c -= (c / 100) * 100;
        dig3 = 1;
    }
    if ( (c > 9) || (dig3) )
    {
        b[i++] = ('0' + c / 10);
        c -= (c / 10) * 10;
    }
    b[i++] = ('0' + c);
    b[i] = 0;
    return i;
}

int strsigned16(char * b, int16_t c)
{
    if (c<0)
    {
        b[0] = '-';
        c = -c;
        return 1 + strdec16(&b[1], c);
    }
    else
    {
        return strdec16(b, c);
    }
}

int strdec16(char * b, uint16_t c)
{
    int i = 0;
    uint8_t lead = 0;
    if (c > 9999)
    {
        b[i++] = ('0' + c / 10000);
        c -= (c / 10000) * 10000;
        lead = 1;
    }
    if ( (c > 999) || (lead) )
    {
        b[i++] = ('0' + c / 1000);
        c -= (c / 1000) * 1000;
        lead = 1;
    }
    if ( (c > 99) || (lead) )
    {
        b[i++] = ('0' + c / 100);
        c -= (c / 100) * 100;
        lead = 1;
    }
    if ( (c > 9) || (lead) )
    {
        b[i++] = ('0' + c / 10);
        c -= (c / 10) * 10;
    }
    b[i++] = ('0' + c);
    b[i] = 0;
    return i;
}

int strsigned32(char * b, int32_t c)
{
    if (c<0)
    {
        b[0] = '-';
        c = -c;
        return 1 + strdec32(&b[1], c);
    }
    else
    {
        return strdec32(b, c);
    }
}

int strdec32(char * b, uint32_t c)
{
    int i = 0;
    uint8_t lead = 0;
    if (c > 999999999)
    {
        b[i++] = ('0' + c / 1000000000);
        c -= (c / 1000000000) * 1000000000;
        lead = 1;
    }
    if ( (c > 99999999) || (lead) )
    {
        b[i++] = ('0' + c / 100000000);
        c -= (c / 100000000) * 100000000;
        lead = 1;
    }
    if ( (c > 9999999) || (lead) )
    {
        b[i++] = ('0' + c / 10000000);
        c -= (c / 10000000) * 10000000;
        lead = 1;
    }
    if ( (c > 999999) || (lead) )
    {
        b[i++] = ('0' + c / 1000000);
        c -= (c / 1000000) * 1000000;
        lead = 1;
    }
    if ( (c > 99999) || (lead) )
    {
        b[i++] = ('0' + c / 100000);
        c -= (c / 100000) * 100000;
        lead = 1;
    }
    if ( (c > 9999) || (lead) )
    {
        b[i++] = ('0' + c / 10000);
        c -= (c / 10000) * 10000;
        lead = 1;
    }
    if ( (c > 999) || (lead) )
    {
        b[i++] = ('0' + c / 1000);
        c -= (c / 1000) * 1000;
        lead = 1;
    }
    if ( (c > 99) || (lead) )
    {
        b[i++] = ('0' + c / 100);
        c -= (c / 100) * 100;
        lead = 1;
    }
    if ( (c > 9) || (lead) )
    {
        b[i++] = ('0' + c / 10);
        c -= (c / 10) * 10;
    }
    b[i++] = ('0' + c);
    b[i] = 0;
    return i;
}

int strsigned64(char * b, int64_t c)
{
    if (c<0)
    {
        b[0] = '-';
        c = -c;
        return 1 + strdec64(&b[1], c);
    }
    else
    {
        return strdec64(b, c);
    }
}

int strdec64(char * b, uint64_t c)
{
    int i = 0;
    uint8_t lead = 0;
    if (c > 9999999999999999999ULL)
    {
        b[i++] = ('0' + c / 10000000000000000000ULL);
        c -= (c / 10000000000000000000ULL) * 10000000000000000000ULL;
        lead = 1;
    }
    if ( (c > 999999999999999999) || (lead) )
    {
        b[i++] = ('0' + c / 1000000000000000000);
        c -= (c / 1000000000000000000) * 1000000000000000000;
        lead = 1;
    }
    if ( (c > 99999999999999999) || (lead) )
    {
        b[i++] = ('0' + c / 100000000000000000);
        c -= (c / 100000000000000000) * 100000000000000000;
        lead = 1;
    }
    if ( (c > 9999999999999999) || (lead) )
    {
        b[i++] = ('0' + c / 10000000000000000);
        c -= (c / 10000000000000000) * 10000000000000000;
        lead = 1;
    }
    if ( (c > 999999999999999) || (lead) )
    {
        b[i++] = ('0' + c / 1000000000000000);
        c -= (c / 1000000000000000) * 1000000000000000;
        lead = 1;
    }
    if ( (c > 99999999999999) || (lead) )
    {
        b[i++] = ('0' + c / 100000000000000);
        c -= (c / 100000000000000) * 100000000000000;
        lead = 1;
    }
    if ( (c > 9999999999999) || (lead) )
    {
        b[i++] = ('0' + c / 10000000000000);
        c -= (c / 10000000000000) * 10000000000000;
        lead = 1;
    }
    if ( (c > 999999999999) || (lead) )
    {
        b[i++] = ('0' + c / 1000000000000);
        c -= (c / 1000000000000) * 1000000000000;
        lead = 1;
    }
    if ( (c > 99999999999) || (lead) )
    {
        b[i++] = ('0' + c / 100000000000);
        c -= (c / 100000000000) * 100000000000;
        lead = 1;
    }
    if ( (c > 9999999999) || (lead) )
    {
        b[i++] = ('0' + c / 10000000000);
        c -= (c / 10000000000) * 10000000000;
        lead = 1;
    }
    if ( (c > 999999999) || (lead) )
    {
        b[i++] = ('0' + c / 1000000000);
        c -= (c / 1000000000) * 1000000000;
        lead = 1;
    }
    if ( (c > 99999999) || (lead) )
    {
        b[i++] = ('0' + c / 100000000);
        c -= (c / 100000000) * 100000000;
        lead = 1;
    }
    if ( (c > 9999999) || (lead) )
    {
        b[i++] = ('0' + c / 10000000);
        c -= (c / 10000000) * 10000000;
        lead = 1;
    }
    if ( (c > 999999) || (lead) )
    {
        b[i++] = ('0' + c / 1000000);
        c -= (c / 1000000) * 1000000;
        lead = 1;
    }
    if ( (c > 99999) || (lead) )
    {
        b[i++] = ('0' + c / 100000);
        c -= (c / 100000) * 100000;
        lead = 1;
    }
    if ( (c > 9999) || (lead) )
    {
        b[i++] = ('0' + c / 10000);
        c -= (c / 10000) * 10000;
        lead = 1;
    }
    if ( (c > 999) || (lead) )
    {
        b[i++] = ('0' + c / 1000);
        c -= (c / 1000) * 1000;
        lead = 1;
    }
    if ( (c > 99) || (lead) )
    {
        b[i++] = ('0' + c / 100);
        c -= (c / 100) * 100;
        lead = 1;
    }
    if ( (c > 9) || (lead) )
    {
        b[i++] = ('0' + c / 10);
        c -= (c / 10) * 10;
    }
    b[i++] = ('0' + c);
    b[i] = 0;
    return i;
}

void puthex4(uint8_t c)
{
    strhex4(g_buf, c);
    tputs(g_buf);
}

void puthex8(uint8_t c)
{
    strhex8(g_buf, c);
    tputs(g_buf);
}

void puthex16(uint16_t c)
{
    strhex16(g_buf, c);
    tputs(g_buf);
}

void puthex32(uint32_t c)
{
    strhex32(g_buf, c);
    tputs(g_buf);
}

void puthex64(uint64_t c)
{
    strhex64(g_buf, c);
    tputs(g_buf);
}

void putdec8(uint8_t c)
{
    strdec8(g_buf, c);
    tputs(g_buf);
}

void putdec16(uint16_t c)
{
    strdec16(g_buf, c);
    tputs(g_buf);
}

void putdec32(uint32_t c)
{
    strdec32(g_buf, c);
    tputs(g_buf);
}

void putsigned16(int16_t c)
{
    strsigned16(g_buf, c);
    tputs(g_buf);
}

void putsigned32(int32_t c)
{
    strsigned32(g_buf, c);
    tputs(g_buf);
}
