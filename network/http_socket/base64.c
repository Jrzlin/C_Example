/*
 * base64.c --- Coding scheme used by MIME in RFC1113.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "base64.h"


/*
 * Encoding data mapping array.
 */
static char base64_encode_maps[][BASE64_ENCODE_LEN] = {
  { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" },
  { "qazwersdfxcvbgtyhnmjklpoiu5647382910+/POIKLMJUYTGHNBVFREWSDCXZAQ" },
};


/*
 * Decoding data mapping array.
 */
static char base64_decode_maps[][BASE64_ENCODE_LEN] = { { 0 }, { 0 } };

/*
 * base64_init_decode_map()
 *
 * Init. one decode mapping array.
 *
 * Input:
 *      @ index    -- decode table index.
 *      @ pad_char -- padding character.
 *
 * Output:
 *      @ decode map table data.
 */
static void base64_init_decode_map (int index, char pad_char)
{
  char      *enc = base64_encode_maps[index];   // encode map table
  char      *dec = base64_decode_maps[index];   // decode map table
  ssize_t   len = strlen(enc);                  // length of encode table
  int       i;                                  // working variable

  memset(dec, 0, BASE64_ENCODE_LEN);
  for (i = 0; i < len; i++, enc++) {
    dec[(int)*enc] = i;
  }

  dec[(int)pad_char] = 0;
}

/*
 * base64_init()
 *
 * Set up decode data mapping arrays.
 *
 * Input:
 *      None.
 *
 * Output:
 *      @ BASE64_NO_ERROR.
 */
int base64_init (void)
{
  base64_init_decode_map(0, BASE64_ENCODE0_PADDING_CHAR);
  base64_init_decode_map(1, BASE64_ENCODE1_PADDING_CHAR);

  return(0);
}

/*
 * base64_encode_block()
 *
 * Encode 3 bytes character to 4 (6-bits) characters.
 *
 * Input:
 *      @ in       -- input data to be encoded.
 *      @ out      -- encoded data to be stored.
 *      @ enc_maps -- point to encode map table to be used.
 *
 * Output:
 *      @ encoded data stored in 'out' parameter.
 */
static void base64_encode_block (uint8_t *in, uint8_t *out, char *enc_maps)
{
  out[0] = enc_maps[(in[0] >> 2) &  0x7F];
  out[1] = enc_maps[((in[0] & 0x03) << 4) | ((in[1] & 0xF0) >> 4)];
  out[2] = enc_maps[((in[1] & 0x0F) << 2) | ((in[2] & 0xC0) >> 6)];
  out[3] = enc_maps[(in[2] & 0x3F)];
}

/*
 * base64_encode()
 *
 * Base64 encode data function.
 *
 * Input:
 *      @ in       -- input data to be encoded.
 *      @ in_len   -- length of input data.
 *      @ out      -- buffer for encoded data.
 *      @ out_len  -- (In)  size of output buffer.
 *                    (Out) length of encoded output data.
 *      @ enc_maps -- encoding map table.
 *      @ pad_char -- padding character.
 *
 * Output:
 *      @ BASE64_NO_ERROR if successfully encoded.
 *      @ encoded data are stored in 'out' parameter, moreover,
 *        null ('\0') character is attached at the end of buffer.
 *      @ BASE64_ERR_xxxx if fail to encode data.
 *
 */
int base64_encode (char *in, ssize_t in_len, char *out, ssize_t *out_len,
                   char *enc_maps, char pad_char)
{
  uint8_t   *uin = (uint8_t *)in;       // working pointer for input
  uint8_t   *uout = (uint8_t *)out;     // working pointer for output
  ssize_t   times = (in_len + 2) / 3;   // do encoding every 3 bytes
  int       left = in_len % 3;          // bytes left to encode
  ssize_t   i;

  /*
   * Sanity check the length.
   */
  if ((((in_len / 3) + 1) * 4) > *out_len) {
    return(-1);
  }

  /*
   * Work through input data to do the encoding for every 3 bytes each time.
   */
  if (left) {
    times--;
  }
  for (i = 0; i < times; i++) {
    base64_encode_block(uin, uout, enc_maps);

    /*
     * Advance input/output pointer by 3/4 respectively.
     */
    uin += 3;
    uout += 4;
  }

  /*
   * Do the last round if the input data length is not multiple of 3.
   */
  if (left) {
    *uout++ = enc_maps[(*uin >> 2) & 0x7F];
    if (left == 1) {
      *uout++ = enc_maps[(*uin & 0x03) << 4];
      *uout++ = pad_char;
    } else {
      *uout++ = enc_maps[((*uin & 0x03) << 4) | ((*(uin + 1) & 0xF0) >> 4)];
      *uout++ = enc_maps[((*(uin + 1) & 0x0F) << 2)];
    }
    *uout++ = pad_char;
  }

  /*
   * Return the output data length.
   * Null-terminated string, caller need to make sure to allocate 1 more byte
   * of buffer.
   */
  *out_len = (ssize_t)(uout - (uint8_t *)out);
  out[*out_len] = '\0';

  return(0);
}

/*
 * base64_decode_block()
 *
 * Decode 4 (6-bits) characters to 3 bytes characters.
 *
 * Input:
 *      @ in  -- input data to be decoded.
 *      @ out -- buffer for decoded outputs.
 *
 * Output:
 *      @ decode data are stored in 'out' parameter.
 */
static void base64_decode_block (uint8_t *in, uint8_t *out)
{
  out[0] = (in[0] << 2) | (in[1] >> 4);
  out[1] = (in[1] << 4) | (in[2] >> 2);
  out[2] = (in[2] << 6) | in[3];
}

/*
 * base64_decode()
 *
 * Base64 decode data function.
 *
 * Input:
 *      @ in       -- input data to be decoded.
 *      @ in_len   -- length of input data.
 *      @ out      -- buffer for decoded data.
 *      @ out_len  -- (In)  sizeof output buffer.
 *                    (Out) length of decoded output data.
 *      @ dec_maps -- decodeing map table.
 *      @ pad_char -- padding character.
 *
 * Output:
 *      @ BASE64_NO_ERROR if successfully decoded.
 *      @ decoded data are stored in 'out' parameter, moreover,
 *        null ('\0') character is attached at the end of buffer.
 *      @ BASE64_ERR_xxxx if failed to decode data.
 */
int base64_decode (char *in, ssize_t in_len, char *out, ssize_t *out_len,
                   char *dec_maps, char pad_char)
{
  uint8_t   *uin = (uint8_t *)in;       // working pointer for input
  uint8_t   *uout = (uint8_t *)out;     // working pointer for output
  ssize_t   times = in_len >> 2;        // do decoding every 4 bytes
  uint8_t   tmp[4];                     // tmp storage for decoding
  ssize_t   i;
  int       j;

  /*
   * Sanity check the length.
   */
  if ((in_len / 4 * 3) > *out_len) {
    return(-1);
  }

  /*
   * For each input data, retrieve corresponding decode data mapping before
   * doing the real decode process.
   */
  for (i = 0; i < times; i++) {
    for (j = 0; j < 4; j++) {
      tmp[j] = dec_maps[*uin++];
    }
    base64_decode_block(tmp, uout);

    /*
     * Advance output pointer by 3.
     */
    uout += 3;
  }

  /*
   * Adjust output length, if any padding character attahed.
   */
  if (*(uin - 1) == pad_char) {
    uout--;
    if (*(uin - 2) == pad_char) {
      uout--;
    }
  }

  /*
   * Return the output data length.
   * Null-terminated string, caller need to make sure to allocate 1 more byte
   * of buffer.
   */
  *out_len = (ssize_t)(uout - (uint8_t *)out);
  out[*out_len] = '\0';

  return(0);
}

/*
 * base64_encode0
 * base64_decode0
 *
 * Wrapper routine for base64 encode/decode to use map table 0.
 */
int base64_encode0 (char *in, ssize_t in_len, char *out, ssize_t *out_len)
{
  return(base64_encode(in, in_len, out, out_len, base64_encode_maps[0],
                       BASE64_ENCODE0_PADDING_CHAR));
}
int base64_decode0 (char *in, ssize_t in_len, char *out, ssize_t *out_len)
{
  return(base64_decode(in, in_len, out, out_len, base64_decode_maps[0],
                       BASE64_ENCODE0_PADDING_CHAR));
}

/*
 * base64_encode1
 * base64_decode1
 *
 * Wrapper routine for base64 encode/decode to use map table 1.
 */
int base64_encode1 (char *in, ssize_t in_len, char *out, ssize_t *out_len)
{
  return(base64_encode(in, in_len, out, out_len, base64_encode_maps[1],
                       BASE64_ENCODE1_PADDING_CHAR));
}
int base64_decode1 (char *in, ssize_t in_len, char *out, ssize_t *out_len)
{
  return(base64_decode(in, in_len, out, out_len, base64_decode_maps[1],
                       BASE64_ENCODE1_PADDING_CHAR));
}
