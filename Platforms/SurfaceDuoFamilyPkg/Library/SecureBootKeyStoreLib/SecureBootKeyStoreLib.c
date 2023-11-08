/** @file PlatformKeyLib.c

  Copyright (C) Microsoft Corporation. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>
#include <UefiSecureBoot.h>

#include <Pi/PiFirmwareFile.h>

#include <Guid/ImageAuthentication.h>

#include <Library/DebugLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SecureBootVariableLib.h>

#define PLATFORM_SECURE_BOOT_KEY_COUNT 1

SECURE_BOOT_PAYLOAD_INFO *gSecureBootPayload      = NULL;
UINT8                     gSecureBootPayloadCount = 0;

UINT8 mSecureBootPayloadCount = PLATFORM_SECURE_BOOT_KEY_COUNT;
SECURE_BOOT_PAYLOAD_INFO mSecureBootPayload[PLATFORM_SECURE_BOOT_KEY_COUNT] = {{
    .SecureBootKeyName = L"Microsoft Plus 3rd Party Plus Windows On Andromeda",
    .PkPtr             = NULL,
    .PkSize            = 0,
    .KekPtr            = NULL,
    .KekSize           = 0,
    .DbPtr             = NULL,
    .DbSize            = 0,
    .DbxPtr            = NULL,
    .DbxSize           = 0,
    .DbtPtr            = NULL,
    .DbtSize           = 0,
  }
};

/**
  Interface to fetch platform Secure Boot Certificates, each payload
  corresponds to a designated set of db, dbx, dbt, KEK, PK.

  @param[in]  Keys        Pointer to hold the returned sets of keys. The
                          returned buffer will be treated as CONST and
                          permanent pointer. The consumer will NOT free
                          the buffer after use.
  @param[in]  KeyCount    The number of sets available in the returned Keys.

  @retval     EFI_SUCCESS             The Keys are properly fetched.
  @retval     EFI_INVALID_PARAMETER   Inputs have NULL pointers.
  @retval     Others                  Something went wrong. Investigate further.
**/
EFI_STATUS
EFIAPI
GetPlatformKeyStore (
  OUT SECURE_BOOT_PAYLOAD_INFO  **Keys,
  OUT UINT8                     *KeyCount
  )
{
  if ((Keys == NULL) || (KeyCount == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *Keys     = gSecureBootPayload;
  *KeyCount = gSecureBootPayloadCount;

  return EFI_SUCCESS;
}

/**
  The constructor gets the secure boot platform keys populated.

  @retval EFI_SUCCESS     The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
SecureBootKeyStoreLibConstructor (
  VOID
  )
{
  EFI_STATUS          Status;
  UINTN               DataSize;
  EFI_SIGNATURE_LIST *SigListBuffer = NULL;

  // Windows On Andromeda Root Platform Key
  UINT8 *mDevelopmentPlatformKeyCertificate     = NULL;
  UINTN  mDevelopmentPlatformKeyCertificateSize = 0;
  UINT8 *mKekDefault                            = NULL;
  UINTN  mKekDefaultSize                        = 0;
  UINT8 *mDbDefault                             = NULL;
  UINTN  mDbDefaultSize                         = 0;
  UINT8 *mDbxDefault                            = NULL;
  UINTN  mDbxDefaultSize                        = 0;

  Status = GetSectionFromAnyFv(
      &gDefaultPKFileGuid, EFI_SECTION_RAW, 0,
      (VOID **)&mDevelopmentPlatformKeyCertificate,
      &mDevelopmentPlatformKeyCertificateSize);

  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "%a - Failed to get PK payload!\n", __FUNCTION__));
    ASSERT(FALSE);
  }

  SECURE_BOOT_CERTIFICATE_INFO  TempInfo       = {
    .Data     = mDevelopmentPlatformKeyCertificate,
    .DataSize = mDevelopmentPlatformKeyCertificateSize
  };

  Status = GetSectionFromAnyFv(
      &gDefaultKEKFileGuid, EFI_SECTION_RAW, 0, (VOID **)&mKekDefault,
      &mKekDefaultSize);

  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "%a - Failed to get KEK payload!\n", __FUNCTION__));
    ASSERT(FALSE);
  }

  Status = GetSectionFromAnyFv(
      &gDefaultdbFileGuid, EFI_SECTION_RAW, 0, (VOID **)&mDbDefault,
      &mDbDefaultSize);

  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "%a - Failed to get DB payload!\n", __FUNCTION__));
    ASSERT(FALSE);
  }

  Status = GetSectionFromAnyFv(
      &gDefaultdbxFileGuid, EFI_SECTION_RAW, 0, (VOID **)&mDbxDefault,
      &mDbxDefaultSize);

  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "%a - Failed to get DBX payload!\n", __FUNCTION__));
    ASSERT(FALSE);
  }

  //
  // First, we must build the PK buffer with the correct data.
  //
  Status = SecureBootCreateDataFromInput (&DataSize, &SigListBuffer, 1, &TempInfo);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "%a - Failed to build PK payload!\n", __FUNCTION__));
    ASSERT (FALSE);
  }

  mSecureBootPayload[0].KekPtr  = mKekDefault;
  mSecureBootPayload[0].KekSize = mKekDefaultSize;
  mSecureBootPayload[0].DbPtr   = mDbDefault;
  mSecureBootPayload[0].DbSize  = mDbDefaultSize;
  mSecureBootPayload[0].DbxPtr  = mDbxDefault;
  mSecureBootPayload[0].DbxSize = mDbxDefaultSize;
  mSecureBootPayload[0].DbtPtr  = NULL;
  mSecureBootPayload[0].DbtSize = 0;

  mSecureBootPayload[0].PkPtr  = SigListBuffer;
  mSecureBootPayload[0].PkSize = DataSize;

  gSecureBootPayload      = mSecureBootPayload;
  gSecureBootPayloadCount = mSecureBootPayloadCount;

  return EFI_SUCCESS;
}

/**
  Destructor of SecureBootKeyStoreLib, to free any allocated resources.

  @retval EFI_SUCCESS   The destructor completed successfully.
  @retval Other value   The destructor did not complete successfully.

**/
EFI_STATUS
EFIAPI
SecureBootKeyStoreLibDestructor (
  VOID
  )
{
  VOID  *SigListBuffer;

  // This should be initialized from constructor, so casting here is fine
  SigListBuffer = (VOID *)mSecureBootPayload[0].PkPtr;
  if (SigListBuffer != NULL) {
    FreePool (SigListBuffer);
  }

  return EFI_SUCCESS;
}
