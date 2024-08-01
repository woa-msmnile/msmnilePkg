/* Copyright (c) 2016, The Linux Foundation. All rights reserved.
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

#ifndef _VERIFIEDBOOTMENU_H_
#define _VERIFIEDBOOTMENU_H_

#include <DrawUI.h>

#if VERIFIED_BOOT || VERIFIED_BOOT_2
EFI_STATUS
DisplayVerifiedBootMenu (DISPLAY_MENU_TYPE Type);
EFI_STATUS
VerifiedBootOptionMenuShowScreen (OPTION_MENU_INFO *OptionMenuInfo);
EFI_STATUS
VerifiedBootMenuShowScreen (OPTION_MENU_INFO *OptionMenuInfo,
                            DISPLAY_MENU_TYPE Type);
EFI_STATUS
VerifiedBootMenuUpdateShowScreen (OPTION_MENU_INFO *OptionMenuInfo);
#else
STATIC inline EFI_STATUS
DisplayVerifiedBootMenu (DISPLAY_MENU_TYPE Type)
{
  return EFI_UNSUPPORTED;
}
STATIC inline EFI_STATUS
VerifiedBootOptionMenuShowScreen (OPTION_MENU_INFO *OptionMenuInfo)
{
  return EFI_UNSUPPORTED;
}
STATIC inline EFI_STATUS
VerifiedBootMenuShowScreen (OPTION_MENU_INFO *OptionMenuInfo,
                            DISPLAY_MENU_TYPE Type)
{
  return EFI_UNSUPPORTED;
}
STATIC inline EFI_STATUS
VerifiedBootMenuUpdateShowScreen (OPTION_MENU_INFO *OptionMenuInfo)
{
  return EFI_UNSUPPORTED;
}
#endif

#endif
