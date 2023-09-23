#ifndef __SFPD_PROTOCOL_H__
#define __SFPD_PROTOCOL_H__

#include <Uefi.h>

#define SFPD_PROTOCOL_GUID                                                     \
  {                                                                            \
    0x470d9ff7, 0x23d0, 0x4f25,                                                \
    {                                                                          \
      0x91, 0xaf, 0xe4, 0x5f, 0x3f, 0x6f, 0xe6, 0xb6                           \
    }                                                                          \
  }

typedef struct _SFPD_PROTOCOL SFPD_PROTOCOL;

typedef CHAR8 *(EFIAPI *GET_SURFACE_SERIAL_NUMBER)(VOID);

struct _SFPD_PROTOCOL {
  GET_SURFACE_SERIAL_NUMBER GetSurfaceSerialNumber;
};

extern EFI_GUID gSfpdProtocolGuid;

#endif