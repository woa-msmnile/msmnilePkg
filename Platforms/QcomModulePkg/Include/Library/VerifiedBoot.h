/* Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 *  with the distribution.
 *   * Neither the name of The Linux Foundation nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __VERIFIEDBOOT_H__
#define __VERIFIEDBOOT_H__

#include <Uefi.h>

enum
{
  NO_AVB = 0,
  AVB_1,
  AVB_2,
  AVB_LE
};

#define VB_SHA256_SIZE  32
#define LE_BOOTIMG_SIG_SIZE 256

typedef enum {
  VB_UNDEFINED_HASH = 0,
  VB_SHA1,
  VB_SHA256,
  VB_UNSUPPORTED_HASH,
  VB_RESERVED_HASH = 0x7fffffff /* force to 32 bits */
} VB_HASH;

#define GUARD(code)                                                            \
  do {                                                                         \
    Status = (code);                                                           \
    if (Status != EFI_SUCCESS) {                                               \
      DEBUG ((EFI_D_ERROR, "Err: line:%d %a() status: %r\n", __LINE__,         \
              __FUNCTION__, Status));                                          \
      return Status;                                                           \
    }                                                                          \
  } while (0)

#define GUARD_OUT(code)                                                        \
  do {                                                                         \
    Status = (code);                                                           \
    if (Status != EFI_SUCCESS) {                                               \
      DEBUG ((EFI_D_ERROR, "Err: line:%d %a() status: %r\n", __LINE__,         \
              __FUNCTION__, Status));                                          \
      goto out;                                                                \
    }                                                                          \
  } while (0)

/* forward declare BootInfo */
typedef struct BootInfo BootInfo;

BOOLEAN
VerifiedBootEnbled ();

/**
 * @return  0 - AVB disabled
 *          1 - VB 1.0
 *          2 - VB 2.0
 */
UINT32
GetAVBVersion ();

/**
 * Authenticates and loads boot image in
 * Info->Images on EFI_SUCCESS.
 * Also provides Verified Boot command
 * arguments (if any) in Info->VBCmdLine
 *
 * @return EFI_STATUS
 */
EFI_STATUS
LoadImageAndAuth (BootInfo *Info);

/**
 *  Free resources/memory allocated by
 *  verified boot, ImageBuffer, VBCmdLine
 *  VBData...
 *
 * @return VOID
 */
VOID
FreeVerifiedBootResource (BootInfo *Info);

/**
 *
 * Returns the Finger print for this
 * boot. A hash of user public key.
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetCertFingerPrint (UINT8 *FingerPrint,
                    UINTN FingerPrintLen,
                    UINTN *FingerPrintLenOut);
#endif /* __VERIFIEDBOOT_H__ */
