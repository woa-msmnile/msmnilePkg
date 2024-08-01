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

#include "VerifiedBoot.h"
#include "avb_sha.h"
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/Hash2.h>
#include <Uefi.h>

/*
  Initializes the SHA-256 context.
  Ctx cannot be NULL here, it is caller's responsibility
  to ensure Ctx is not NULL.
*/
void
avb_sha256_init (AvbSHA256Ctx *Ctx)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HASH2_PROTOCOL *pEfiHash2Protocol = NULL;

  GUARD_OUT (gBS->LocateProtocol (&gEfiHash2ProtocolGuid, NULL,
                                  (VOID **)&pEfiHash2Protocol));

  Ctx->user_data = (VOID *)pEfiHash2Protocol;

  GUARD_OUT (pEfiHash2Protocol->HashInit (pEfiHash2Protocol,
                                          &gEfiHashAlgorithmSha256Guid));

out:
  if (Status != EFI_SUCCESS) {
    Ctx->user_data = NULL;
  }
}

/*
  Updates the SHA-256 context with |len| bytes from |data|.
  Ctx cannot be NULL here, it is caller's responsibility
  to ensure Ctx is not NULL.
*/
void
avb_sha256_update (AvbSHA256Ctx *Ctx, const uint8_t *Data, uint32_t Len)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HASH2_PROTOCOL *pEfiHash2Protocol = NULL;

  if (Data == NULL) {
    DEBUG ((EFI_D_ERROR, "avb_sha256_update failed, Data is NULL\n"));
    return;
  }

  pEfiHash2Protocol = Ctx->user_data;
  if (pEfiHash2Protocol == NULL) {
    DEBUG ((EFI_D_ERROR, "avb_sha256_update failed, Ctx->user_data is NULL\n"));
    return;
  }

  Status = pEfiHash2Protocol->HashUpdate (pEfiHash2Protocol, Data, Len);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "avb_sha256_update: HashUpdate failed\n"));
  }
}

/*
  Returns the SHA-256 digest.
  Ctx cannot be NULL here, it is caller's responsibility
  to ensure Ctx is not NULL.
*/
uint8_t *
avb_sha256_final (AvbSHA256Ctx *Ctx)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HASH2_OUTPUT Hash2Output;
  EFI_HASH2_PROTOCOL *pEfiHash2Protocol = NULL;

  pEfiHash2Protocol = Ctx->user_data;
  if (pEfiHash2Protocol == NULL) {
    DEBUG ((EFI_D_ERROR, "avb_sha256_final failed, Ctx->user_data is NULL\n"));
    Status = EFI_INVALID_PARAMETER;
    goto out;
  }

  GUARD_OUT (pEfiHash2Protocol->HashFinal (pEfiHash2Protocol, &Hash2Output));

  if (sizeof (Hash2Output.Sha256Hash) > sizeof (Ctx->buf)) {
    DEBUG ((EFI_D_ERROR, "avb_sha256_final failed, output too large\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto out;
  }
  CopyMem (Ctx->buf, Hash2Output.Sha256Hash, sizeof (Hash2Output.Sha256Hash));

out:
  if (Status != EFI_SUCCESS) {
    SetMem (Ctx->buf, 0, sizeof (Ctx->buf));
  }
  return Ctx->buf;
}
