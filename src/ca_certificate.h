/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __CA_CERTIFICATE_H__
#define __CA_CERTIFICATE_H__

#define CA_CERTIFICATE_TAG 1

/* By default only certificates in DER format are supported. If you want to use
 * certificate in PEM format, you can enable support for it in Kconfig.
 */

/* GlobalSign Root CA - R1 for https://google.com */
#if defined(CONFIG_TLS_CREDENTIAL_FILENAMES)
static const unsigned char ca_certificate[] = "globalsign_r1.der";
#else

static const unsigned char eclipse_leshan_ca_crt[] = {
    #include "LeshanServerCertificate.der.inc"
};

#endif

#endif /* __CA_CERTIFICATE_H__ */