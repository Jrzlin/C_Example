/*
 * base64.h --- Header file for base64 coding scheme.
 */

#ifndef __BASE64_H__
#define __BASE64_H__


#include <stdio.h>


/*
 * We have 2 map tables for encode/decode.
 */
#define BASE64_MAP_TABLE_NUM            2

/*
 * Constant defines.
 */
#define BASE64_ENCODE_LEN               128         // char from 0x00 to 0x7E
#define BASE64_ENCODE0_PADDING_CHAR     '='
#define BASE64_ENCODE1_PADDING_CHAR     '$'

#define BASE64_ENCODE_LEN_NEEDED(L)     (((L) + 3) / 3 * 4 + 1)


/*
 * Forward functions declaration.
 */
extern int  base64_init(void);
extern int  base64_encode0(char *in, ssize_t in_len, char *out,
                           ssize_t *out_len);
extern int  base64_decode0(char *in, ssize_t in_len, char *out,
                           ssize_t *out_len);
extern int  base64_encode1(char *in, ssize_t in_len, char *out,
                           ssize_t *out_len);
extern int  base64_decode1(char *in, ssize_t in_len, char *out,
                           ssize_t *out_len);


#endif /* __BASE64_H__ */
