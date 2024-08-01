/* Copyright (c) 2017, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
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

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>

/* Maximum string length considering 64 bit number */
#define STR_LENGTH 21

enum Kind {
  TK_Integer = 0x0000,
  TK_Float = 0x0001,
  TK_Unknown = 0x00ff,
};

CONST CHAR8 *TypeCheckKind[] = {
    "load of",
    "store do",
    "reference binding to",
    "member access within",
    "member call on",
    "constructor call on",
    "downcast of",
    "downcast of",
    "upcast of",
    "cast to virtual base of",
    "_Nonnull binding to"
};

struct TypeDescriptor {
  UINT16 TypeKind;

  /* Type-specific value providing information
       to interpret meaning of Value of this type.
     Bit 0 gives Signed/Unsigned information.
     Bit 1 - Bit 15 gives length of data type in power of 2.
  */
  UINT16 TypeInfo;

  CHAR8 TypeName[1];
};

struct SourceLocation {
  CONST CHAR8 *FileName;
  UINT32 Line;
  UINT32 Column;
};

struct OverflowData {
  struct SourceLocation Loc;
  struct TypeDescriptor *Type;
};

struct OutOfBounds {
  struct SourceLocation Loc;
  struct TypeDescriptor *ArrayType;
  struct TypeDescriptor *IndexType;
};

struct ShiftOutOfBoundsData {
  struct SourceLocation Loc;
  struct TypeDescriptor *LHSType;
  struct TypeDescriptor *RHSType;
};

struct TypeMismatchData {
  struct SourceLocation Loc;
  struct TypeDescriptor *Type;
  UINT32 *Alignment;
  UINT8 TypeCheckKind;
};

struct FloatCastOverflowData {
  struct TypeDescriptor *FromType;
  struct TypeDescriptor *ToType;
};

struct FloatCastOverflowDataV2 {
  struct SourceLocation Loc;
  struct TypeDescriptor *FromType;
  struct TypeDescriptor *ToType;
};

struct UnreachableData {
  struct SourceLocation Loc;
};

struct VLABoundData {
  struct SourceLocation Loc;
  struct TypeDescriptor *Type;
};

struct InvalidValueData {
  struct SourceLocation Loc;
  struct TypeDescriptor *Type;
};

struct NonNullReturnData {
  struct SourceLocation Loc;
  struct SourceLocation AttrLoc;
};

STATIC INT32
GetBitLength (UINT16 typeInfo)
{
  /* Bit 0 is removed and shifting 1 by number
     from Bit 1 - Bit 15 gives length of datatype
  */
  return (1 << (typeInfo >> 1));
}

STATIC BOOLEAN
IsSignedInteger (struct TypeDescriptor *type)
{
  /* Bit 0 gives whether value is Signed or Unsigned
  */

  if (type->TypeKind == TK_Integer) {
    return (type->TypeInfo & 1);
  }

  return FALSE;
}

STATIC VOID
UbsanBegin (struct SourceLocation *Loc)
{
  DEBUG ((EFI_D_ERROR, "=========================================\n"));
  DEBUG ((EFI_D_ERROR, "UBSAN: Undefined Behavior found in %a:%d:%d\n",
          Loc->FileName, Loc->Line, Loc->Column));
}

STATIC VOID UbsanEnd (VOID)
{
  DEBUG ((EFI_D_ERROR, "=========================================\n"));
}

STATIC VOID
HandleTypeMismatch (struct TypeMismatchData *data, UINT32 *ptr)
{
  UINT32 *Alignment = data->Alignment;

  if (!ptr) {
    DEBUG ((EFI_D_ERROR, "%a null pointer of type %a\n",
            TypeCheckKind[data->TypeCheckKind], data->Type->TypeName));
  } else if (Alignment && ((UINTN)ptr & (UINTN) (Alignment - 1))) {
    DEBUG ((EFI_D_ERROR, "%a misaligned address 0x%x for type %a, which "
                         "requires %d byte alignment\n",
            TypeCheckKind[data->TypeCheckKind], (VOID *)ptr,
            data->Type->TypeName, Alignment));
  } else {
    DEBUG ((
        EFI_D_ERROR,
        "%a address 0x%x with insufficient space for an object of type %a\n",
        TypeCheckKind[data->TypeCheckKind], (VOID *)ptr, data->Type->TypeName));
  }
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_type_mismatch (struct TypeMismatchData *data, UINT32 *ptr)
{
  UbsanBegin (&data->Loc);
  HandleTypeMismatch (data, ptr);
  UbsanEnd ();
}

STATIC VOID
HandleShiftOutOfBounds (struct ShiftOutOfBoundsData *data,
                        UINT32 lhs,
                        UINT32 rhs)
{
  INT32 LHSVal = (INT32)lhs;
  INT32 RHSVal = (INT32)rhs;

  INT32 LHSValBitLength = GetBitLength ((UINT16)data->LHSType->TypeInfo);

  if (RHSVal < 0) {
    DEBUG ((EFI_D_INFO, "shift exponent %d is negative\n", RHSVal));
  } else if (RHSVal >= LHSValBitLength) {
    DEBUG ((EFI_D_INFO, "shift exponent %d is too large for %d-bit type %a\n",
            RHSVal, LHSValBitLength, data->LHSType->TypeName));
  } else if (LHSVal < 0) {
    DEBUG ((EFI_D_INFO, "left shift of negative value %d\n", LHSVal));
  } else {
    DEBUG ((EFI_D_INFO,
            "left shift of %d by %d places cannot be represented in type %a\n",
            LHSVal, RHSVal, data->LHSType->TypeName));
  }
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_shift_out_of_bounds (struct ShiftOutOfBoundsData *data,
                                    UINT32 lhs,
                                    UINT32 rhs)
{
  UbsanBegin (&data->Loc);
  HandleShiftOutOfBounds (data, lhs, rhs);
  UbsanEnd ();
}

STATIC VOID
HandleOutOfBounds (struct OutOfBounds *data, UINT32 Index)
{
  CHAR8 index_str[STR_LENGTH];
  AsciiValueToStringS (index_str, LEFT_JUSTIFY, Index, sizeof (index_str) - 1, STR_LENGTH);
  DEBUG ((EFI_D_INFO, "index %a out of bounds for type %a\n", index_str,
          data->ArrayType->TypeName));
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_out_of_bounds (struct OutOfBounds *data, UINT32 Index)
{
  UbsanBegin (&data->Loc);
  HandleOutOfBounds (data, Index);
  UbsanEnd ();
}

STATIC VOID
OverFlowHandler (struct TypeDescriptor *type,
                 UINT32 lhs,
                 UINT32 rhs,
                 CONST CHAR8 *operation)
{
  CHAR8 lhs_val_str[STR_LENGTH];
  CHAR8 rhs_val_str[STR_LENGTH];

  BOOLEAN IsSigned = IsSignedInteger (type);

  AsciiValueToStringS (lhs_val_str, LEFT_JUSTIFY, lhs, sizeof (lhs_val_str) - 1, STR_LENGTH);
  AsciiValueToStringS (rhs_val_str, LEFT_JUSTIFY, rhs, sizeof (rhs_val_str) - 1, STR_LENGTH);

  DEBUG ((EFI_D_ERROR,
          "%a integer overflow, %a %a %a can't be represented by type %a\n",
          IsSigned ? "signed" : "unsigned", lhs_val_str, operation, rhs_val_str,
          type->TypeName));
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_add_overflow (struct OverflowData *data, UINT32 lhs, UINT32 rhs)
{
  UbsanBegin (&data->Loc);
  OverFlowHandler (data->Type, lhs, rhs, "+");
  UbsanEnd ();
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_sub_overflow (struct OverflowData *data, UINT32 lhs, UINT32 rhs)
{
  UbsanBegin (&data->Loc);
  OverFlowHandler (data->Type, lhs, rhs, "-");
  UbsanEnd ();
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_mul_overflow (struct OverflowData *data, UINT32 lhs, UINT32 rhs)
{
  UbsanBegin (&data->Loc);
  OverFlowHandler (data->Type, lhs, rhs, "*");
  UbsanEnd ();
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_divrem_overflow (struct OverflowData *data,
                                UINT32 lhs,
                                UINT32 rhs)
{
  UbsanBegin (&data->Loc);
  OverFlowHandler (data->Type, lhs, rhs, "/");
  UbsanEnd ();
}

STATIC VOID
HandleNegateOverflow (struct OverflowData *data, UINT32 oldval)
{
  CHAR8 old_val_str[STR_LENGTH];
  AsciiValueToStringS (old_val_str, LEFT_JUSTIFY, oldval,
                      sizeof (old_val_str) - 1, STR_LENGTH);

  if (IsSignedInteger (data->Type)) {
    DEBUG ((EFI_D_INFO, "negation of %a can't be represented in type %a,"
                        "cast to unsigned type to negate this value to itself",
            old_val_str, data->Type->TypeName));
  } else {
    DEBUG ((EFI_D_INFO, "negation of %a can't be represented in type %a\n",
            old_val_str, data->Type->TypeName));
  }
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_negate_overflow (struct OverflowData *data, UINT32 oldval)
{
  UbsanBegin (&data->Loc);
  HandleNegateOverflow (data, oldval);
  UbsanEnd ();
}

STATIC BOOLEAN
LooksLikeFloatCastOverflowDataV1 (VOID *data)
{
  UINT8 *FilenameOrTypeDescriptor = data;
  INT16 MaybeFromTypeKind =
      FilenameOrTypeDescriptor[0] + FilenameOrTypeDescriptor[1];

  /*
   * For float_cast_overflow, the TypeKind will be either TK_Integer
   * (0x0), TK_Float (0x1) or TK_Unknown (0xff). If both types are known,
   * adding both bytes will be 0 or 1. If it were a filename, adding
   * two printable characters will not yield such a value. Otherwise,
   * if one of them is 0xff, this is most likely TK_Unknown type descriptor.
   */

  return MaybeFromTypeKind < 2 || FilenameOrTypeDescriptor[0] == TK_Unknown ||
         FilenameOrTypeDescriptor[1] == TK_Unknown;
}

STATIC VOID
HandleFloatCastOverflow (VOID *data, UINT32 From)
{
  struct TypeDescriptor *FromType, *ToType;
  CHAR8 from_type_str[STR_LENGTH];

  if (LooksLikeFloatCastOverflowDataV1 (data)) {
    struct FloatCastOverflowData *Data = (struct FloatCastOverflowData *)data;
    FromType = Data->FromType;
    ToType = Data->ToType;
  } else {
    struct FloatCastOverflowDataV2 *Data = data;
    FromType = Data->FromType;
    ToType = Data->ToType;
    UbsanBegin (&Data->Loc);
  }

  AsciiValueToStringS (from_type_str, LEFT_JUSTIFY, From,
                      sizeof (from_type_str) - 1, STR_LENGTH);

  DEBUG ((EFI_D_INFO, "value %a '%a' is outside the range of representable "
                      "values of type '%a'\n",
          from_type_str, FromType->TypeName, ToType->TypeName));
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_float_cast_overflow (VOID *data, UINT32 From)
{
  HandleFloatCastOverflow (data, From);
  UbsanEnd ();
}

STATIC VOID
HandleBuiltinUnreachable ()
{
  DEBUG ((EFI_D_INFO, "execution reached __builtin_unreachable() call\n"));
  ASSERT (TRUE);
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_builtin_unreachable (struct UnreachableData *data)
{
  UbsanBegin (&data->Loc);
  HandleBuiltinUnreachable ();
  UbsanEnd ();
}

STATIC VOID
HandleMissingReturn ()
{
  DEBUG ((EFI_D_INFO,
          "Execution reached the end of a value-returning function without"
          "returning a value\n"));
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_missing_return (struct UnreachableData *data)
{
  UbsanBegin (&data->Loc);
  HandleMissingReturn ();
  UbsanEnd ();
}

STATIC VOID
HandleVlaBoundNotPositive (struct VLABoundData *data, UINT32 Bound)
{
  CHAR8 bound_str[STR_LENGTH];
  AsciiValueToStringS (bound_str, LEFT_JUSTIFY, Bound, sizeof (bound_str) - 1, STR_LENGTH);
  DEBUG ((EFI_D_INFO, "variable length array bound evaluates to"
                      "non-positive value %a\n",
          bound_str));
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_vla_bound_not_positive (struct VLABoundData *data, UINT32 Bound)
{
  UbsanBegin (&data->Loc);
  HandleVlaBoundNotPositive (data, Bound);
  UbsanEnd ();
}

STATIC VOID
HandleLoadInvalidValue (struct InvalidValueData *data, UINT32 val)
{
  CHAR8 val_str[STR_LENGTH];
  AsciiValueToStringS (val_str, LEFT_JUSTIFY, val, sizeof (val_str) - 1, STR_LENGTH);
  DEBUG ((EFI_D_INFO,
          "load of value %a, which is not a valid value for type %a\n", val_str,
          data->Type->TypeName));
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_load_invalid_value (struct InvalidValueData *data, UINT32 val)
{
  UbsanBegin (&data->Loc);
  HandleLoadInvalidValue (data, val);
  UbsanEnd ();
}

STATIC VOID
HandleNonnullReturn (struct NonNullReturnData *data)
{
  DEBUG ((EFI_D_INFO, "null pointer returned from function declared to never"
                      "return null\n"));
  DEBUG ((EFI_D_INFO, "returns_nonull attributed is specified here %a\n",
          data->AttrLoc));
}

__attribute__ ((no_sanitize ("undefined"))) VOID
__ubsan_handle_nonnull_return (struct NonNullReturnData *data)
{
  UbsanBegin (&data->Loc);
  HandleNonnullReturn (data);
  UbsanEnd ();
}
