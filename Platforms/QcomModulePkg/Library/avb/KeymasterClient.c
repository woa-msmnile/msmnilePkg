/* Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
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
#include "KeymasterClient.h"
#include "VerifiedBoot.h"
#include "libavb/libavb.h"
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EFIQseecom.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/scm_sip_interface.h>

typedef struct {
  QCOM_QSEECOM_PROTOCOL *QseeComProtocol;
  UINT32 AppId;
} KMHandle;

/**
 * KM Commands supported
 */
#define KEYMASTER_CMD_ID_OLD 0UL
#define KEYMASTER_CMD_ID 0x100UL
#define KEYMASTER_UTILS_CMD_ID 0x200UL
#define GK_CMD_ID 0x1000UL

typedef enum {
  /*
         * List the commands supportedin by the hardware.
         */
  KEYMASTER_GET_SUPPORTED_ALGORITHMS = (KEYMASTER_CMD_ID + 1UL),
  KEYMASTER_GET_SUPPORTED_BLOCK_MODES = (KEYMASTER_CMD_ID + 2UL),
  KEYMASTER_GET_SUPPORTED_PADDING_MODES = (KEYMASTER_CMD_ID + 3UL),
  KEYMASTER_GET_SUPPORTED_DIGESTS = (KEYMASTER_CMD_ID + 4UL),
  KEYMASTER_GET_SUPPORTED_IMPORT_FORMATS = (KEYMASTER_CMD_ID + 5UL),
  KEYMASTER_GET_SUPPORTED_EXPORT_FORMATS = (KEYMASTER_CMD_ID + 6UL),
  KEYMASTER_ADD_RNG_ENTROPY = (KEYMASTER_CMD_ID + 7UL),
  KEYMASTER_GENERATE_KEY = (KEYMASTER_CMD_ID + 8UL),
  KEYMASTER_GET_KEY_CHARACTERISTICS = (KEYMASTER_CMD_ID + 9UL),
  KEYMASTER_RESCOPE = (KEYMASTER_CMD_ID + 10UL),
  KEYMASTER_IMPORT_KEY = (KEYMASTER_CMD_ID + 11UL),
  KEYMASTER_EXPORT_KEY = (KEYMASTER_CMD_ID + 12UL),
  KEYMASTER_DELETE_KEY = (KEYMASTER_CMD_ID + 13UL),
  KEYMASTER_DELETE_ALL_KEYS = (KEYMASTER_CMD_ID + 14UL),
  KEYMASTER_BEGIN = (KEYMASTER_CMD_ID + 15UL),
  KEYMASTER_UPDATE = (KEYMASTER_CMD_ID + 17UL),
  KEYMASTER_FINISH = (KEYMASTER_CMD_ID + 18UL),
  KEYMASTER_ABORT = (KEYMASTER_CMD_ID + 19UL),
  KEYMASTER_UPGRADE = (KEYMASTER_CMD_ID + 20UL),
  KEYMASTER_ATTEST = (KEYMASTER_CMD_ID + 21UL),
  KEYMASTER_CONFIGURE = (KEYMASTER_CMD_ID + 22UL),

  KEYMASTER_GET_VERSION = (KEYMASTER_UTILS_CMD_ID + 0UL),
  KEYMASTER_SET_ROT = (KEYMASTER_UTILS_CMD_ID + 1UL),
  KEYMASTER_READ_KM_DEVICE_STATE = (KEYMASTER_UTILS_CMD_ID + 2UL),
  KEYMASTER_WRITE_KM_DEVICE_STATE = (KEYMASTER_UTILS_CMD_ID + 3UL),
  KEYMASTER_MILESTONE_CALL = (KEYMASTER_UTILS_CMD_ID + 4UL),
  KEYMASTER_GET_AUTH_TOKEN_KEY = (KEYMASTER_UTILS_CMD_ID + 5UL),
  KEYMASTER_SECURE_WRITE_PROTECT = (KEYMASTER_UTILS_CMD_ID + 6UL),
  KEYMASTER_SET_VERSION = (KEYMASTER_UTILS_CMD_ID + 7UL),
  KEYMASTER_SET_BOOT_STATE = (KEYMASTER_UTILS_CMD_ID + 8UL),
  KEYMASTER_PROVISION_ATTEST_KEY = (KEYMASTER_UTILS_CMD_ID + 9UL),
  KEYMASTER_SET_VBH = (KEYMASTER_UTILS_CMD_ID + 17UL),
  KEYMASTER_GET_DATE_SUPPORT = (KEYMASTER_UTILS_CMD_ID + 21UL),

  KEYMASTER_LAST_CMD_ENTRY = (int)0xFFFFFFFFULL
} KeyMasterCmd;

typedef enum {
  KM_ERROR_INVALID_TAG = -40,
} KeyMasterError;

typedef struct {
  UINT32 CmdId;
  UINT32 RotOffset;
  UINT32 RotSize;
  CHAR8 RotDigest[AVB_SHA256_DIGEST_SIZE];
} __attribute__ ((packed)) KMSetRotReq;

typedef struct {
  INT32 Status;
} __attribute__ ((packed)) KMSetRotRsp;

typedef struct {
  UINT32 IsUnlocked;
  CHAR8 PublicKey[AVB_SHA256_DIGEST_SIZE];
  UINT32 Color;
  UINT32 SystemVersion;
  UINT32 SystemSecurityLevel;
} __attribute__ ((packed)) KMBootState;

typedef struct {
  UINT32 CmdId;
  UINT32 Version;
  UINT32 Offset;
  UINT32 Size;
  KMBootState BootState;
} __attribute__ ((packed)) KMSetBootStateReq;

typedef struct {
  INT32 Status;
} __attribute__ ((packed)) KMSetBootStateRsp;

typedef struct {
  UINT32 CmdId;
} __attribute__ ((packed)) KMGetVersionReq;

typedef struct {
  INT32 Status;
  UINT32 Major;
  UINT32 Minor;
  UINT32 AppMajor;
  UINT32 AppMinor;
} __attribute__ ((packed)) KMGetVersionRsp;

typedef struct
{
  UINT32 CmdId;
  CHAR8 Vbh[AVB_SHA256_DIGEST_SIZE];
} __attribute__ ((packed)) KMSetVbhReq;

typedef struct
{
  INT32 Status;
} __attribute__ ((packed)) KMSetVbhRsp;

typedef struct {
  UINT32 CmdId;
} __attribute__ ((packed)) KMGetDateSupportReq;

typedef struct {
  INT32 Status;
} __attribute__ ((packed)) KMGetDateSupportRsp;

EFI_STATUS
KeyMasterStartApp (KMHandle *Handle)
{
  EFI_STATUS Status = EFI_SUCCESS;
  KMGetVersionReq Req = {0};
  KMGetVersionRsp Rsp = {0};

  if (Handle == NULL) {
    DEBUG ((EFI_D_ERROR, "KeyMasterStartApp: Invalid Handle\n"));
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateProtocol (&gQcomQseecomProtocolGuid, NULL,
                                (VOID **)&(Handle->QseeComProtocol));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Unable to locate QSEECom protocol: %r\n", Status));
    return Status;
  }

  Status = Handle->QseeComProtocol->QseecomStartApp (
      Handle->QseeComProtocol, "keymaster", &(Handle->AppId));
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR,
            "KeyMasterStartApp: QseecomStartApp failed status: %r\n", Status));
    return Status;
  }

  DEBUG ((EFI_D_VERBOSE, "keymaster app id %d\n", Handle->AppId));

  Req.CmdId = KEYMASTER_GET_VERSION;
  Status = Handle->QseeComProtocol->QseecomSendCmd (
      Handle->QseeComProtocol, Handle->AppId, (UINT8 *)&Req, sizeof (Req),
      (UINT8 *)&Rsp, sizeof (Rsp));
  if (Status != EFI_SUCCESS || Rsp.Status != 0 || Rsp.Major < 2) {
    DEBUG ((EFI_D_ERROR, "KeyMasterStartApp: Get Version err, status: "
                         "%d, response status: %d, Major: %d\n",
            Status, Rsp.Status, Rsp.Major));
    return EFI_LOAD_ERROR;
  }
  DEBUG ((EFI_D_VERBOSE, "KeyMasterStartApp success AppId: 0x%x, Major: %d\n",
          Handle->AppId, Rsp.Major));
  return Status;
}

EFI_STATUS
KeyMasterSetRotAndBootState (KMRotAndBootState *BootState)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHAR8 *RotDigest = NULL;
  CHAR8 *BootStateDigest = NULL;
  CHAR8 BootStateOrgangeDigest[AVB_SHA256_DIGEST_SIZE] = {0};
  AvbSHA256Ctx RotCtx;
  AvbSHA256Ctx BootStateCtx;
  KMHandle Handle = {NULL};
  KMSetRotReq RotReq = {0};
  KMSetRotRsp RotRsp = {0};
  KMSetBootStateReq BootStateReq = {0};
  KMSetBootStateRsp BootStateRsp = {0};
  BOOLEAN secure_device = FALSE;

  if (BootState == NULL) {
    DEBUG ((EFI_D_ERROR, "Invalid parameter BootState\n"));
    return EFI_INVALID_PARAMETER;
  }

  /* Compute ROT digest */
  avb_sha256_init (&RotCtx);

  switch (BootState->Color) {
  case GREEN:
  case YELLOW:
    avb_sha256_update (&RotCtx, (const uint8_t *)BootState->PublicKey,
                       BootState->PublicKeyLength);
    avb_sha256_update (&RotCtx, (const uint8_t *)&BootState->IsUnlocked,
                       sizeof (BootState->IsUnlocked));
    break;
  case ORANGE:
    avb_sha256_update (&RotCtx, (const uint8_t *)&BootState->IsUnlocked,
                       sizeof (BootState->IsUnlocked));
    break;
  case RED:
  default:
    DEBUG ((EFI_D_ERROR, "Invalid state to boot!\n"));
    return EFI_LOAD_ERROR;
  }
  /* RotDigest is a fixed size array, cannot be NULL */
  RotDigest = (CHAR8 *)avb_sha256_final (&RotCtx);

  /* Compute BootState digest */
  switch (BootState->Color) {
  case GREEN:
  case YELLOW:
    avb_sha256_init (&BootStateCtx);
    avb_sha256_update (&BootStateCtx, (const uint8_t *)BootState->PublicKey,
                       BootState->PublicKeyLength);
    /* BootStateDigest is a fixed size array, cannot be NULL */
    BootStateDigest = (CHAR8 *)avb_sha256_final (&BootStateCtx);
    break;
  case ORANGE:
    BootStateDigest = BootStateOrgangeDigest;
    break;
  case RED:
  default:
    DEBUG ((EFI_D_ERROR, "Invalid state to boot!\n"));
    return EFI_LOAD_ERROR;
  }

  /* Load KeyMaster App */
  GUARD (KeyMasterStartApp (&Handle));

  /* Set ROT */
  RotReq.CmdId = KEYMASTER_SET_ROT;
  RotReq.RotOffset = (UINT8 *)&RotReq.RotDigest - (UINT8 *)&RotReq;
  RotReq.RotSize = sizeof (RotReq.RotDigest);
  CopyMem (RotReq.RotDigest, RotDigest, AVB_SHA256_DIGEST_SIZE);

  Status = Handle.QseeComProtocol->QseecomSendCmd (
      Handle.QseeComProtocol, Handle.AppId, (UINT8 *)&RotReq, sizeof (RotReq),
      (UINT8 *)&RotRsp, sizeof (RotRsp));
  if (Status != EFI_SUCCESS || RotRsp.Status != 0) {
    DEBUG ((EFI_D_ERROR, "KeyMasterSendRotAndBootState: Set ROT err, "
                         "Status: %r, response status: %d\n",
            Status, RotRsp.Status));
    return EFI_LOAD_ERROR;
  }

  /* Set Boot State */
  BootStateReq.CmdId = KEYMASTER_SET_BOOT_STATE;
  BootStateReq.Version = 0;
  BootStateReq.Size = sizeof (BootStateReq.BootState);
  BootStateReq.Offset =
      (UINT8 *)&BootStateReq.BootState - (UINT8 *)&BootStateReq;
  BootStateReq.BootState.Color = BootState->Color;
  BootStateReq.BootState.IsUnlocked = BootState->IsUnlocked;
  BootStateReq.BootState.SystemSecurityLevel = BootState->SystemSecurityLevel;
  BootStateReq.BootState.SystemVersion = BootState->SystemVersion;
  CopyMem (BootStateReq.BootState.PublicKey, BootStateDigest,
           AVB_SHA256_DIGEST_SIZE);

  Status = Handle.QseeComProtocol->QseecomSendCmd (
      Handle.QseeComProtocol, Handle.AppId, (UINT8 *)&BootStateReq,
      sizeof (BootStateReq), (UINT8 *)&BootStateRsp, sizeof (BootStateRsp));
  if (Status != EFI_SUCCESS || BootStateRsp.Status != 0) {
    DEBUG ((EFI_D_ERROR, "KeyMasterSendRotAndBootState: Set BootState err, "
                         "Status: %r, response status: %d\n",
            Status, BootStateRsp.Status));
    return EFI_LOAD_ERROR;
  }

  /* Provide boot tamper state to TZ */
  if (((Status = IsSecureDevice (&secure_device)) == EFI_SUCCESS) &&
      secure_device && (BootState->Color != GREEN)) {
    if (AllowSetFuse ()) {
      Status = SetFuse (TZ_HLOS_IMG_TAMPER_FUSE);
      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "KeyMasterSetRotAndBootState: "
                             "SetFuse (TZ_HLOS_IMG_TAMPER_FUSE) fails!\n"));
        return Status;
      }
      Status = SetFuse (TZ_HLOS_TAMPER_NOTIFY_FUSE);
      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "KeyMasterSetRotAndBootState: "
                             "SetFuse (TZ_HLOS_TAMPER_NOTIFY_FUSE) fails!\n"));
        return Status;
      }
    }
  }
  DEBUG ((EFI_D_VERBOSE, "KeyMasterSetRotAndBootState success\n"));
  return Status;
}

EFI_STATUS
SetVerifiedBootHash (CONST CHAR8 *Vbh, UINTN VbhSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  KMSetVbhReq VbhReq = {0};
  KMSetVbhRsp VbhRsp = {0};
  KMHandle Handle = {NULL};

  if (!Vbh ||
      VbhSize != sizeof (VbhReq.Vbh)) {
    DEBUG ((EFI_D_ERROR, "Vbh input params invalid\n"));
    return EFI_INVALID_PARAMETER;
  }

  /* Load KeyMaster App */
  GUARD (KeyMasterStartApp (&Handle));
  VbhReq.CmdId = KEYMASTER_SET_VBH;
  CopyMem (VbhReq.Vbh, Vbh, VbhSize);

  Status = Handle.QseeComProtocol->QseecomSendCmd (
      Handle.QseeComProtocol, Handle.AppId, (UINT8 *)&VbhReq,
      sizeof (VbhReq), (UINT8 *)&VbhRsp, sizeof (VbhRsp));
  if (Status != EFI_SUCCESS ||
                VbhRsp.Status != 0) {
    DEBUG ((EFI_D_ERROR, "Set Vbh Error, "
                         "Status: %r, response status: %d\n",
            Status, VbhRsp.Status));
    if (Status == EFI_SUCCESS &&
                VbhRsp.Status == KM_ERROR_INVALID_TAG) {
      DEBUG ((EFI_D_ERROR, "VBH not supported in keymaster\n"));
      return EFI_SUCCESS;
    }
    return EFI_LOAD_ERROR;
  }
  return EFI_SUCCESS;
}

EFI_STATUS
KeyMasterGetDateSupport (BOOLEAN *Supported)
{
  EFI_STATUS Status = EFI_SUCCESS;
  KMGetDateSupportReq Req = {0};
  KMGetDateSupportRsp Rsp = {0};
  KMHandle Handle = {NULL};

  GUARD (KeyMasterStartApp (&Handle));
  Req.CmdId = KEYMASTER_GET_DATE_SUPPORT;
  Status = Handle.QseeComProtocol->QseecomSendCmd (
      Handle.QseeComProtocol, Handle.AppId, (UINT8 *)&Req, sizeof (Req),
      (UINT8 *)&Rsp, sizeof (Rsp));
  if (Status != EFI_SUCCESS ||
                Rsp.Status != 0 ) {
    DEBUG ((EFI_D_ERROR, "Keymaster: Get date support error, status: "
                         "%d, response status: %d\n",
            Status, Rsp.Status));
    if (Status == EFI_SUCCESS &&
                Rsp.Status == KM_ERROR_INVALID_TAG) {
      DEBUG ((EFI_D_ERROR, "Date in patch level not supported in keymaster\n"));
      *Supported = FALSE;
      return EFI_SUCCESS;
    }
    return EFI_LOAD_ERROR;
  }

  *Supported = TRUE;
  return Status;
}
