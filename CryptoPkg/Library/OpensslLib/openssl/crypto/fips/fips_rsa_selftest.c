/* ====================================================================
 * Copyright (c) 2003-2007 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <string.h>
#include <openssl/err.h>
#ifdef OPENSSL_FIPS
# include <openssl/fips.h>
# include "internal/fips_int.h"
#endif
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/opensslconf.h>
#include "fips_locl.h"

#ifdef OPENSSL_FIPS

static int setrsakey(RSA *key)
{
    static const unsigned char keydata_n[] = {
        0x00, 0xc9, 0xd5, 0x6d, 0x9d, 0x90, 0xdb, 0x43, 0xd6, 0x02, 0xed, 0x96, 0x88, 0x13, 0x8a,
        0xb2, 0xbf, 0x6e, 0xa1, 0x06, 0x10, 0xb2, 0x78, 0x37, 0xa7, 0x14, 0xa8, 0xff, 0xdd, 0x00,
        0xdd, 0xb4, 0x93, 0xa0, 0x45, 0xcc, 0x96, 0x90, 0xed, 0xad, 0xa9, 0xdd, 0xc4, 0xd6, 0xca,
        0x0c, 0xf0, 0xed, 0x4f, 0x72, 0x5e, 0x21, 0x49, 0x9a, 0x18, 0x12, 0x15, 0x8f, 0x90, 0x5a,
        0xdb, 0xb6, 0x33, 0x99, 0xa3, 0xe6, 0xb4, 0xf0, 0xc4, 0x97, 0x21, 0x26, 0xbb, 0xe3, 0xba,
        0xf2, 0xff, 0xa0, 0x72, 0xda, 0x89, 0x63, 0x8e, 0x8b, 0x3e, 0x08, 0x9d, 0x92, 0x2a, 0xbe,
        0x16, 0xe1, 0x43, 0x15, 0xfc, 0x57, 0xc7, 0x1f, 0x09, 0x11, 0x67, 0x1c, 0xa9, 0x96, 0xd1,
        0x8b, 0x3e, 0x80, 0x93, 0xc1, 0x59, 0xd0, 0x6d, 0x39, 0xf2, 0xac, 0x95, 0xcc, 0x10, 0x75,
        0xe9, 0x31, 0x24, 0xd1, 0x43, 0xaf, 0x68, 0x52, 0x4b, 0xe7, 0x16, 0xd7, 0x49, 0x65, 0x6f,
        0x26, 0xc0, 0x86, 0xad, 0xc0, 0x07, 0x0a, 0xc1, 0xe1, 0x2f, 0x87, 0x85, 0x86, 0x3b, 0xdc,
        0x5a, 0x99, 0xbe, 0xe9, 0xf9, 0xb9, 0xe9, 0x82, 0x27, 0x51, 0x04, 0x15, 0xab, 0x06, 0x0e,
        0x76, 0x5a, 0x28, 0x8d, 0x92, 0xbd, 0xc5, 0xb5, 0x7b, 0xa8, 0xdf, 0x4e, 0x47, 0xa2, 0xc1,
        0xe7, 0x52, 0xbf, 0x47, 0xf7, 0x62, 0xe0, 0x3a, 0x6f, 0x4d, 0x6a, 0x4d, 0x4e, 0xd4, 0xb9,
        0x59, 0x69, 0xfa, 0xb2, 0x14, 0xc1, 0xee, 0xe6, 0x2f, 0x95, 0xcd, 0x94, 0x72, 0xae, 0xe4,
        0xdb, 0x18, 0x9a, 0xc4, 0xcd, 0x70, 0xbd, 0xee, 0x31, 0x16, 0xb7, 0x49, 0x65, 0xac, 0x40,
        0x19, 0x0e, 0xb5, 0x6d, 0x83, 0xf1, 0x36, 0xbb, 0x08, 0x2f, 0x2e, 0x4e, 0x92, 0x62, 0xa4,
        0xff, 0x50, 0xdb, 0x20, 0x45, 0xa2, 0xeb, 0x16, 0x7a, 0xf2, 0xd5, 0x28, 0xc1, 0xfd, 0x4e,
        0x03, 0x71
    };

    static const unsigned char keydata_e[] = { 0x01, 0x00, 0x01 };

    static const unsigned char keydata_d[] = {
        0x36, 0x27, 0x3d, 0xb1, 0xf9, 0x1b, 0xdb, 0xa7, 0xa0, 0x41, 0x7f, 0x12, 0x23, 0xac, 0x23,
        0x29, 0x99, 0xd5, 0x3a, 0x7b, 0x60, 0x67, 0x41, 0x07, 0x63, 0x53, 0xb4, 0xd2, 0xe7, 0x58,
        0x95, 0x0a, 0xc7, 0x05, 0xf3, 0x4e, 0xb2, 0xb4, 0x12, 0xd4, 0x70, 0xdc, 0x4f, 0x85, 0x06,
        0xd3, 0xdd, 0xd8, 0x63, 0x27, 0x3e, 0x67, 0x31, 0x21, 0x24, 0x39, 0x04, 0xbc, 0x06, 0xa4,
        0xcc, 0xce, 0x2b, 0x7a, 0xfe, 0x7b, 0xad, 0xde, 0x11, 0x6e, 0xa3, 0xa5, 0xe6, 0x04, 0x53,
        0x0e, 0xa3, 0x4e, 0x2d, 0xb4, 0x8f, 0x31, 0xbf, 0xca, 0x75, 0x25, 0x52, 0x02, 0x85, 0xde,
        0x3d, 0xb2, 0x72, 0x43, 0xb2, 0x89, 0x8a, 0x9a, 0x34, 0x41, 0x26, 0x3f, 0x9a, 0x67, 0xbe,
        0xa4, 0x96, 0x7b, 0x0e, 0x75, 0xba, 0xa6, 0x93, 0xd5, 0xb8, 0xd8, 0xb8, 0x57, 0xf2, 0x4b,
        0x0f, 0x14, 0x81, 0xd1, 0x57, 0x4e, 0xf6, 0x45, 0x4c, 0xa6, 0x3b, 0xd0, 0x70, 0xca, 0xd3,
        0x9d, 0x55, 0xde, 0x22, 0x05, 0xe7, 0x8e, 0x28, 0x4d, 0xee, 0x11, 0xcf, 0xb6, 0x67, 0x76,
        0x09, 0xd3, 0xe3, 0x3c, 0x13, 0xf9, 0x99, 0x34, 0x10, 0x7b, 0xec, 0x81, 0x38, 0xf0, 0xb6,
        0x34, 0x9c, 0x9b, 0x50, 0x6f, 0x0b, 0x91, 0x81, 0x4d, 0x89, 0x94, 0x04, 0x7b, 0xf0, 0x3c,
        0xf4, 0xb1, 0xb2, 0x00, 0x48, 0x8d, 0x5a, 0x8f, 0x88, 0x9e, 0xc5, 0xab, 0x3a, 0x9e, 0x44,
        0x3f, 0x54, 0xe7, 0xd9, 0x6e, 0x47, 0xaa, 0xa1, 0xbd, 0x40, 0x46, 0x31, 0xf9, 0xf0, 0x34,
        0xb6, 0x04, 0xe1, 0x2b, 0x5b, 0x73, 0x86, 0xdd, 0x3a, 0x92, 0x1b, 0x71, 0xc7, 0x3f, 0x32,
        0xe5, 0xc3, 0xc2, 0xab, 0xa1, 0x7e, 0xbf, 0xa4, 0x52, 0xa0, 0xb0, 0x68, 0x90, 0xd1, 0x20,
        0x12, 0x79, 0xe9, 0xd7, 0xc9, 0x40, 0xba, 0xf2, 0x19, 0xc7, 0xa5, 0x00, 0x92, 0x86, 0x0d,
        0x01
    };

    static const unsigned char keydata_p[] = {
        0x00, 0xfc, 0x5c, 0x6e, 0x16, 0xce, 0x1f, 0x03, 0x7b, 0xcd, 0xf7, 0xb3, 0x72, 0xb2, 0x8f,
        0x16, 0x72, 0xb8, 0x56, 0xae, 0xf7, 0xcd, 0x67, 0xd8, 0x4e, 0x7d, 0x07, 0xaf, 0xd5, 0x43,
        0x26, 0xc3, 0x35, 0xbe, 0x43, 0x8f, 0x4e, 0x2f, 0x1c, 0x43, 0x4e, 0x6b, 0xd2, 0xb2, 0xec,
        0x52, 0x6d, 0x97, 0x52, 0x2b, 0xcc, 0x5c, 0x3a, 0x6b, 0xf4, 0x14, 0xc6, 0x74, 0xda, 0x66,
        0x38, 0x1c, 0x7a, 0x3f, 0x84, 0x2f, 0xe3, 0xf9, 0x5a, 0xb8, 0x65, 0x69, 0x46, 0x06, 0xa3,
        0x37, 0x79, 0xb2, 0xa1, 0x5b, 0x58, 0xed, 0x5e, 0xa7, 0x5f, 0x8c, 0x65, 0x66, 0xbb, 0xd1,
        0x24, 0x36, 0xe6, 0x37, 0xa7, 0x3d, 0x49, 0x77, 0x8a, 0x8c, 0x34, 0xd8, 0x69, 0x29, 0xf3,
        0x4d, 0x58, 0x22, 0xb0, 0x51, 0x24, 0xb6, 0x40, 0xa8, 0x86, 0x59, 0x0a, 0xb7, 0xba, 0x5c,
        0x97, 0xda, 0x57, 0xe8, 0x36, 0xda, 0x7a, 0x9c, 0xad
    };

    static const unsigned char keydata_q[] = {
        0x00, 0xcc, 0xbe, 0x7b, 0x09, 0x69, 0x06, 0xee, 0x45, 0xbf, 0x88, 0x47, 0x38, 0xa8, 0xf8,
        0x17, 0xe5, 0xb6, 0xba, 0x67, 0x55, 0xe3, 0xe8, 0x05, 0x8b, 0xb8, 0xe2, 0x53, 0xd6, 0x8e,
        0xef, 0x2c, 0xe7, 0x4f, 0x4a, 0xf7, 0x4e, 0x26, 0x8d, 0x85, 0x0b, 0x3f, 0xec, 0xc3, 0x1c,
        0xd4, 0xeb, 0xec, 0x6a, 0xc8, 0x72, 0x2a, 0x25, 0x7d, 0xfd, 0xa6, 0x77, 0x96, 0xf0, 0x1e,
        0xcd, 0x28, 0x57, 0xf8, 0x37, 0x30, 0x75, 0x6b, 0xbd, 0xd4, 0x7b, 0x0c, 0x87, 0xc5, 0x6c,
        0x87, 0x40, 0xa5, 0xbb, 0x27, 0x2c, 0x78, 0xc9, 0x74, 0x5a, 0x54, 0x5b, 0x0b, 0x30, 0x6f,
        0x44, 0x4a, 0xfa, 0x71, 0xe4, 0x21, 0x61, 0x66, 0xf9, 0xee, 0x65, 0xde, 0x7c, 0x04, 0xd7,
        0xfd, 0xa9, 0x15, 0x5b, 0x7f, 0xe2, 0x7a, 0xba, 0x69, 0x86, 0x72, 0xa6, 0x06, 0x8d, 0x9b,
        0x90, 0x55, 0x60, 0x9e, 0x4c, 0x5d, 0xa9, 0xb6, 0x55
    };

    static const unsigned char keydata_dmp1[] = {
        0x7a, 0xd6, 0x12, 0xd0, 0x0e, 0xec, 0x91, 0xa9, 0x85, 0x8b, 0xf8, 0x50, 0xf0, 0x11, 0x2e,
        0x00, 0x11, 0x32, 0x40, 0x60, 0x66, 0x1f, 0x11, 0xee, 0xc2, 0x75, 0x27, 0x65, 0x4b, 0x16,
        0x67, 0x16, 0x95, 0xd2, 0x14, 0xc3, 0x1d, 0xb3, 0x48, 0x1f, 0xb7, 0xe4, 0x0b, 0x2b, 0x74,
        0xc3, 0xdb, 0x50, 0x27, 0xf9, 0x85, 0x3a, 0xfa, 0xa9, 0x08, 0x23, 0xc1, 0x65, 0x3d, 0x34,
        0x3a, 0xc8, 0x56, 0x7a, 0x65, 0x45, 0x36, 0x6e, 0xae, 0x2a, 0xce, 0x9f, 0x43, 0x43, 0xd7,
        0x10, 0xe9, 0x9e, 0x18, 0xf4, 0xa4, 0x35, 0xda, 0x8a, 0x6b, 0xb0, 0x3f, 0xdd, 0x53, 0xe3,
        0xa8, 0xc5, 0x4e, 0x79, 0x9d, 0x1f, 0x51, 0x8c, 0xa2, 0xca, 0x66, 0x3c, 0x6a, 0x2a, 0xff,
        0x8e, 0xd2, 0xf3, 0xb7, 0xcb, 0x82, 0xda, 0xde, 0x2c, 0xe6, 0xd2, 0x8c, 0xb3, 0xad, 0xb6,
        0x4c, 0x95, 0x55, 0x76, 0xbd, 0xc9, 0xc8, 0xd1
    };

    static const unsigned char keydata_dmq1[] = {
        0x00, 0x83, 0x23, 0x1d, 0xbb, 0x11, 0x42, 0x17, 0x2b, 0x25, 0x5a, 0x2c, 0x03, 0xe6, 0x75,
        0xc1, 0x18, 0xa8, 0xc9, 0x0b, 0x96, 0xbf, 0xba, 0xc4, 0x92, 0x91, 0x80, 0xa5, 0x22, 0x2f,
        0xba, 0x91, 0x90, 0x36, 0x01, 0x56, 0x15, 0x00, 0x2c, 0x74, 0xa2, 0x97, 0xf7, 0x15, 0xa1,
        0x49, 0xdf, 0x32, 0x35, 0xd2, 0xdd, 0x0c, 0x91, 0xa6, 0xf8, 0xe7, 0xbe, 0x81, 0x36, 0x9b,
        0x03, 0xdc, 0x6b, 0x3b, 0xd8, 0x5d, 0x79, 0x57, 0xe0, 0xe6, 0x4f, 0x49, 0xdf, 0x4c, 0x5c,
        0x0e, 0xe5, 0x21, 0x41, 0x95, 0xfd, 0xad, 0xff, 0x9a, 0x3e, 0xa0, 0xf9, 0x0f, 0x59, 0x9e,
        0x6a, 0xa7, 0x7b, 0x71, 0xa7, 0x24, 0x9a, 0x36, 0x52, 0xae, 0x97, 0x20, 0xc1, 0x5e, 0x78,
        0xd9, 0x47, 0x8b, 0x1e, 0x67, 0xf2, 0xaf, 0x98, 0xe6, 0x2d, 0xef, 0x10, 0xd7, 0xf1, 0xab,
        0x49, 0xee, 0xe5, 0x4b, 0x7e, 0xae, 0x1f, 0x1d, 0x61
    };

    static const unsigned char keydata_iqmp[] = {
        0x23, 0x96, 0xc1, 0x91, 0x17, 0x5e, 0x0a, 0x83, 0xd2, 0xdc, 0x7b, 0x69, 0xb2, 0x59, 0x1d,
        0x33, 0x58, 0x52, 0x3f, 0x18, 0xc7, 0x09, 0x50, 0x1c, 0xb9, 0xa1, 0xbb, 0x4c, 0xa2, 0x38,
        0x40, 0x4c, 0x9a, 0x8e, 0xfe, 0x9c, 0x90, 0x92, 0xd0, 0x71, 0x9f, 0x89, 0x99, 0x50, 0x91,
        0x1f, 0x34, 0x8b, 0x74, 0x53, 0x11, 0x11, 0x4a, 0x70, 0xe2, 0xf7, 0x30, 0xd8, 0x8c, 0x80,
        0xe1, 0xcc, 0x9f, 0xf1, 0x63, 0x17, 0x1a, 0x7d, 0x67, 0x29, 0x4c, 0xcb, 0x4e, 0x74, 0x7b,
        0xe0, 0x3e, 0x9e, 0x2f, 0xf4, 0x67, 0x8f, 0xec, 0xb9, 0x5c, 0x00, 0x1e, 0x7e, 0xa2, 0x7b,
        0x92, 0xc9, 0x6f, 0x4c, 0xe4, 0x0e, 0xf9, 0x48, 0x63, 0xcd, 0x50, 0x22, 0x5d, 0xbf, 0xb6,
        0x9d, 0x01, 0x33, 0x6a, 0xf4, 0x50, 0xbe, 0x86, 0x98, 0x4f, 0xca, 0x3f, 0x3a, 0xfa, 0xcf,
        0x07, 0x40, 0xc4, 0xaa, 0xad, 0xae, 0xbe, 0xbf
    };

    int rv = 0;
    BIGNUM *n = NULL, *e = NULL, *d = NULL, *p = NULL, *q = NULL, *dmp1 = NULL, *dmq1 = NULL, *iqmp = NULL;

    fips_load_key_component(n, keydata);
    fips_load_key_component(e, keydata);
    fips_load_key_component(d, keydata);
    fips_load_key_component(p, keydata);
    fips_load_key_component(q, keydata);
    fips_load_key_component(dmp1, keydata);
    fips_load_key_component(dmq1, keydata);
    fips_load_key_component(iqmp, keydata);

    RSA_set0_key(key, n, e, d);
    RSA_set0_factors(key, p, q);
    RSA_set0_crt_params(key, dmp1, dmq1, iqmp);

    rv = 1;
err:
    if (!rv) {
        BN_free(n);
        BN_free(e);
        BN_free(d);
        BN_free(p);
        BN_free(q);
        BN_free(dmp1);
        BN_free(dmq1);
        BN_free(iqmp);
    }
    return rv;
}

/* Known Answer Test (KAT) data for the above RSA private key signing
 * kat_tbs.
 */

static const unsigned char kat_tbs[] =
    "OpenSSL FIPS 140-2 Public Key RSA KAT";

static const unsigned char kat_RSA_PSS_SHA256[] = {
    0x38, 0xDA, 0x99, 0x51, 0x26, 0x38, 0xC6, 0x7F, 0xC4, 0x81, 0x57, 0x19,
    0x35, 0xC6, 0xF6, 0x1E, 0x90, 0x47, 0x20, 0x55, 0x47, 0x56, 0x26, 0xE9,
    0xF2, 0xA8, 0x39, 0x6C, 0xD5, 0xCD, 0xCB, 0x55, 0xFC, 0x0C, 0xC5, 0xCB,
    0xF7, 0x40, 0x17, 0x3B, 0xCF, 0xE4, 0x05, 0x03, 0x3B, 0xA0, 0xB2, 0xC9,
    0x0D, 0x5E, 0x48, 0x3A, 0xE9, 0xAD, 0x28, 0x71, 0x7D, 0x8F, 0x89, 0x16,
    0x59, 0x93, 0x35, 0xDC, 0x4D, 0x7B, 0xDF, 0x84, 0xE4, 0x68, 0xAA, 0x33,
    0xAA, 0xDC, 0x66, 0x50, 0xC8, 0xA9, 0x32, 0x12, 0xDC, 0xC6, 0x90, 0x49,
    0x0B, 0x75, 0xFF, 0x9B, 0x95, 0x00, 0x9A, 0x90, 0xE0, 0xD4, 0x0E, 0x67,
    0xAB, 0x3C, 0x47, 0x36, 0xC5, 0x2E, 0x1C, 0x46, 0xF0, 0x2D, 0xD3, 0x8B,
    0x42, 0x08, 0xDE, 0x0D, 0xB6, 0x2C, 0x86, 0xB0, 0x35, 0x71, 0x18, 0x6B,
    0x89, 0x67, 0xC0, 0x05, 0xAD, 0xF4, 0x1D, 0x62, 0x4E, 0x75, 0xEC, 0xD6,
    0xC2, 0xDB, 0x07, 0xB0, 0xB6, 0x8D, 0x15, 0xAD, 0xCD, 0xBF, 0xF5, 0x60,
    0x76, 0xAE, 0x48, 0xB8, 0x77, 0x7F, 0xC5, 0x01, 0xD9, 0x29, 0xBB, 0xD6,
    0x17, 0xA2, 0x20, 0x5A, 0xC0, 0x4A, 0x3B, 0x34, 0xC8, 0xB9, 0x39, 0xCF,
    0x06, 0x89, 0x95, 0x6F, 0xC7, 0xCA, 0xC4, 0xE4, 0x43, 0xDF, 0x5A, 0x23,
    0xE2, 0x89, 0xA3, 0x38, 0x78, 0x31, 0x38, 0xC6, 0xA4, 0x6F, 0x5F, 0x73,
    0x5A, 0xE5, 0x9E, 0x09, 0xE7, 0x6F, 0xD4, 0xF8, 0x3E, 0xB7, 0xB0, 0x56,
    0x9A, 0xF3, 0x65, 0xF0, 0xC2, 0xA6, 0x8A, 0x08, 0xBA, 0x44, 0xAC, 0x97,
    0xDE, 0xB4, 0x16, 0x83, 0xDF, 0xE3, 0xEE, 0x71, 0xFA, 0xF9, 0x51, 0x50,
    0x14, 0xDC, 0xFD, 0x6A, 0x82, 0x20, 0x68, 0x64, 0x7D, 0x4E, 0x82, 0x68,
    0xD7, 0x45, 0xFA, 0x6A, 0xE4, 0xE5, 0x29, 0x3A, 0x70, 0xFB, 0xE4, 0x62,
    0x2B, 0x31, 0xB9, 0x7D
};

static const unsigned char kat_RSA_SHA256[] = {
    0xC2, 0xB1, 0x97, 0x00, 0x9A, 0xE5, 0x80, 0x6A, 0xE2, 0x51, 0x68, 0xB9,
    0x7A, 0x0C, 0xF2, 0xB4, 0x77, 0xED, 0x15, 0x0C, 0x4E, 0xE1, 0xDC, 0xFF,
    0x8E, 0xBC, 0xDE, 0xC7, 0x9A, 0x96, 0xF1, 0x47, 0x45, 0x24, 0x9D, 0x6F,
    0xA6, 0xF3, 0x1D, 0x0D, 0x35, 0x4C, 0x1A, 0xF3, 0x58, 0x2C, 0x6C, 0x06,
    0xD6, 0x22, 0x37, 0x77, 0x8C, 0x33, 0xE5, 0x07, 0x53, 0x93, 0x28, 0xCF,
    0x67, 0xFA, 0xC4, 0x1F, 0x1B, 0x24, 0xDB, 0x4C, 0xC5, 0x2A, 0x51, 0xA2,
    0x60, 0x15, 0x8C, 0x54, 0xB4, 0x30, 0xE2, 0x24, 0x47, 0x86, 0xF2, 0xF8,
    0x6C, 0xD6, 0x12, 0x59, 0x2C, 0x74, 0x9A, 0x37, 0xF3, 0xC4, 0xA2, 0xD5,
    0x4E, 0x1F, 0x77, 0xF0, 0x27, 0xCE, 0x77, 0xF8, 0x4A, 0x79, 0x03, 0xBE,
    0xC8, 0x06, 0x2D, 0xA7, 0xA6, 0x46, 0xF5, 0x55, 0x79, 0xD7, 0x5C, 0xC6,
    0x5B, 0xB1, 0x00, 0x4E, 0x7C, 0xD9, 0x11, 0x85, 0xE0, 0xB1, 0x4D, 0x2D,
    0x13, 0xD7, 0xAC, 0xEA, 0x64, 0xD1, 0xAC, 0x8F, 0x8D, 0x8F, 0xEA, 0x42,
    0x7F, 0xF9, 0xB7, 0x7D, 0x2C, 0x68, 0x49, 0x07, 0x7A, 0x74, 0xEF, 0xB4,
    0xC9, 0x97, 0x16, 0x5C, 0x6C, 0x6E, 0x5C, 0x09, 0x2E, 0x8E, 0x13, 0x2E,
    0x1A, 0x8D, 0xA6, 0x0C, 0x6E, 0x0C, 0x1C, 0x0F, 0xCC, 0xB2, 0x78, 0x8A,
    0x07, 0xFC, 0x5C, 0xC2, 0xF5, 0x65, 0xEC, 0xAB, 0x8B, 0x3C, 0xCA, 0x91,
    0x6F, 0x84, 0x7C, 0x21, 0x0E, 0xB8, 0xDA, 0x7B, 0x6C, 0xF7, 0xDF, 0xAB,
    0x7E, 0x15, 0xFD, 0x85, 0x0B, 0x33, 0x9B, 0x6A, 0x3A, 0xC3, 0xEF, 0x65,
    0x04, 0x6E, 0xB2, 0xAC, 0x98, 0xFD, 0xEB, 0x02, 0xF5, 0xC0, 0x0B, 0x5E,
    0xCB, 0xD4, 0x83, 0x82, 0x18, 0x1B, 0xDA, 0xB4, 0xCD, 0xE8, 0x71, 0x6B,
    0x1D, 0xB5, 0x4F, 0xE9, 0xD6, 0x43, 0xA0, 0x0A, 0x14, 0xA0, 0xE7, 0x5D,
    0x47, 0x9D, 0x18, 0xD7
};

static int fips_rsa_encrypt_test(RSA *rsa, const unsigned char *plaintext,
                                 int ptlen)
{
    unsigned char *ctbuf = NULL, *ptbuf = NULL;
    int ret = 0;
    int len;

    ctbuf = OPENSSL_malloc(RSA_size(rsa));
    if (!ctbuf)
        goto err;

    len = RSA_public_encrypt(ptlen, plaintext, ctbuf, rsa, RSA_PKCS1_PADDING);
    if (len <= 0)
        goto err;
    /* Check ciphertext doesn't match plaintext */
    if (len >= ptlen && !memcmp(plaintext, ctbuf, ptlen))
        goto err;

    ptbuf = OPENSSL_malloc(RSA_size(rsa));
    if (!ptbuf)
        goto err;

    len = RSA_private_decrypt(len, ctbuf, ptbuf, rsa, RSA_PKCS1_PADDING);
    if (len != ptlen)
        goto err;
    if (memcmp(ptbuf, plaintext, len))
        goto err;

    ret = 1;

 err:
    if (ctbuf)
        OPENSSL_free(ctbuf);
    if (ptbuf)
        OPENSSL_free(ptbuf);
    return ret;
}

int FIPS_selftest_rsa()
{
    int ret = 0;
    RSA *key;
    EVP_PKEY *pk = NULL;

    if ((key = RSA_new()) == NULL)
        goto err;

    if (!setrsakey(key))
        goto err;

    if ((pk = EVP_PKEY_new()) == NULL)
        goto err;

    EVP_PKEY_set1_RSA(pk, key);

    if (!fips_pkey_signature_test(pk, kat_tbs, sizeof(kat_tbs) - 1,
                                  kat_RSA_SHA256, sizeof(kat_RSA_SHA256),
                                  EVP_sha256(), EVP_MD_CTX_FLAG_PAD_PKCS1,
                                  "RSA SHA256 PKCS#1"))
        goto err;

    if (!fips_pkey_signature_test(pk, kat_tbs, sizeof(kat_tbs) - 1,
                                  kat_RSA_PSS_SHA256,
                                  sizeof(kat_RSA_PSS_SHA256), EVP_sha256(),
                                  EVP_MD_CTX_FLAG_PAD_PSS, "RSA SHA256 PSS"))
        goto err;

    if (!fips_rsa_encrypt_test(key, kat_tbs, sizeof(kat_tbs) - 1))
        goto err;

    ret = 1;

 err:
    if (pk)
        EVP_PKEY_free(pk);
    if (key)
        RSA_free(key);
    return ret;
}

#endif                          /* def OPENSSL_FIPS */
