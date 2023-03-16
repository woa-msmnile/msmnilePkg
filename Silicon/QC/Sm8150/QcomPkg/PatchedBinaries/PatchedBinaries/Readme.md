# Patched Binaries

This file aims to provide further information about the different patches applied to Surface Duo stock firmware UEFI DXEs.

## Reasoning behind each patch

- DisplayDxe: Panels get deinitialized partially on exit boot services by the stock firmware, it is thus needed to reinitialize them, but due to them being partially deinitialized, running some routines again will break the platform. An MMU Domain is already setup by the previous firmware and gets re-set again, causing a crash.

- UFSDxe: An MMU Domain is already setup by the previous firmware and gets re-set again, causing a crash.

- UsbConfigDxe: Important to get USB to work after exit boot services for KdNet or DeveloperMenu or FFULoader.

- ButtonsDxe: to help navigating menus more easily.

- ColorbarsDxe: so the driver loads and provides accurate device state.

- FmpDxe: so the driver loads and provides firmware manegement interfaces to FrontPage.

## UFSDxe & DisplayDxe

MMU related setup routine was patched to not recreate already existing MMU domains.

## DisplayDxe

Panel Reset function was patched to not run again.

Exit BootServices routine was patched to not deinitialize the panels.

## UsbConfigDxe

Exit BootServices routine was patched to not deinit USB after exit boot services.

## ButtonsDxe

Key code was patched for the power button to be mapped as ENTER instead of SUSPEND.

## ColorbarsDxe & FmpDxe
The current PCD Token Store in our UEFI is as follows:

```
PcdTokenNumber: 
('PcdSKUEnableDfci', 'gDfciPkgTokenSpaceGuid') : 1
('PcdSetupUiReducedFunction', 'gDfciPkgTokenSpaceGuid') : 2
('PcdDeviceStateBitmask', 'gEfiMdeModulePkgTokenSpaceGuid') : 3
('PcdConOutRow', 'gEfiMdeModulePkgTokenSpaceGuid') : 4
('PcdConOutColumn', 'gEfiMdeModulePkgTokenSpaceGuid') : 5
('PcdTestKeyUsed', 'gEfiMdeModulePkgTokenSpaceGuid') : 6
('PcdVideoHorizontalResolution', 'gEfiMdeModulePkgTokenSpaceGuid') : 7
('PcdVideoVerticalResolution', 'gEfiMdeModulePkgTokenSpaceGuid') : 8
('PcdNvStoreDefaultValueBuffer', 'gEfiMdeModulePkgTokenSpaceGuid') : 9
('PcdSetNvStoreDefaultId', 'gEfiMdeModulePkgTokenSpaceGuid') : 10
('PcdVpdBaseAddress64', 'gEfiMdeModulePkgTokenSpaceGuid') : 11
('PcdCurrentPointerState', 'gMsGraphicsPkgTokenSpaceGuid') : 12
('PcdPostBackgroundColoringSkipCount', 'gMsGraphicsPkgTokenSpaceGuid') : 13
```

ColorbarsDxe depends on the following Dynamic Pcd:
```
('PcdDeviceStateBitmask', 'gEfiMdeModulePkgTokenSpaceGuid') : 2
```

FmpDxe depends on the following Dynamic Pcd:
```
('PcdTestKeyUsed', 'gEfiMdeModulePkgTokenSpaceGuid') : 3
```

The DXEs were patched to check for 3 and 6 instead of 2 and 3 respectively.