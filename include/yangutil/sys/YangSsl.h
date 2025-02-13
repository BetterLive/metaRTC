﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef INCLUDE_YANGUTIL_SYS_YANGSSL_H_
#define INCLUDE_YANGUTIL_SYS_YANGSSL_H_
#include <yangutil/yangtype.h>
#include <stdint.h>
#include <string.h>
#if Yang_HaveDtls
#include <openssl/ssl.h>
typedef struct{
    char fingerprint[128];
    int32_t ecdsa_mode;
    X509* dtls_cert;
    EVP_PKEY* dtls_pkey;
    EC_KEY* eckey;
}YangCertificate;
#ifdef __cplusplus
extern "C"{
#endif
int32_t hmac_encode(const char* algo, const char* key, const int key_length,
       const char* input, const int32_t input_length, char* output, unsigned int* output_length);

int32_t yang_create_certificate(YangCertificate* cer);
void yang_destroy_certificate(YangCertificate* cer);
void g_yang_create_srtp();
void g_yang_destroy_srtp();
#ifdef __cplusplus
}
#endif

#endif
#endif /* INCLUDE_YANGUTIL_SYS_YANGSSL_H_ */
