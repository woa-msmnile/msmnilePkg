/** @file LECmdLine.h
 *
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
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

#ifndef __LECMDLINE_H__
#define __LECMDLINE_H__

#include <Uefi.h>

/**
   This function gets verity build time parameters passed in SourceCmdLine, and
   constructs complete verity command line into LEVerityCmdLine.
   @param[in]   String   Pointer to a Null-terminated ASCII string.
   @param[out]  String   Pointer to a Null-terminated ASCII string.
   @param[out]  UINT32*  String length of LEVerityCmdLine including NULL
                         terminator.
   @retval  EFI_SUCCESS  Verity command line is constructed successfully.
   @retval  other        Failed to construct Verity command line.
 **/
EFI_STATUS
GetLEVerityCmdLine (CONST CHAR8 *SourceCmdLine,
                    CHAR8 **LEVerityCmdLine,
                    UINT32 *Len);

/**
   This function checks if VERITY_LE is defined or not.
   @param[in]   VOID   VOID
   @retval      TRUE   If VERITY_LE is defined.
   @retval      FALSE  If VERITY_LE is not defined.
 **/
BOOLEAN IsLEVerity (VOID);

#endif
