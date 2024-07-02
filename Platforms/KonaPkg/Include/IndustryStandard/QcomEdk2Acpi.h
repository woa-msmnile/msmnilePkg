/** @file
*
*  Copyright (c) 2020, Linaro Limited. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef QCOM_EDK2_ACPI_H_
#define QCOM_EDK2_ACPI_H_

// A macro to initialise the common header part of EFI ACPI tables as defined by
// EFI_ACPI_DESCRIPTION_HEADER structure.
#define QCOMEDK2_ACPI_HEADER(Signature, Type, Revision)  {                     \
    Signature,                                    /* UINT32  Signature */       \
    sizeof (Type),                                /* UINT32  Length */          \
    Revision,                                     /* UINT8   Revision */        \
    0,                                            /* UINT8   Checksum */        \
    { 'Q', 'C', 'O', 'M', ' ', ' ' },             /* UINT8   OemId[6] */        \
    FixedPcdGet64 (PcdAcpiDefaultOemTableId),     /* UINT64  OemTableId */      \
    FixedPcdGet32 (PcdAcpiDefaultOemRevision),    /* UINT32  OemRevision */     \
    FixedPcdGet32 (PcdAcpiDefaultCreatorId),      /* UINT32  CreatorId */       \
    FixedPcdGet32 (PcdAcpiDefaultCreatorRevision) /* UINT32  CreatorRevision */ \
  }

#endif
