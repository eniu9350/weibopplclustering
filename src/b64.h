#ifndef _WBPC_B64_H_
#define _WBPC_B64_H_

#include <string.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


char *base64(const unsigned char *input, int length);
#endif
