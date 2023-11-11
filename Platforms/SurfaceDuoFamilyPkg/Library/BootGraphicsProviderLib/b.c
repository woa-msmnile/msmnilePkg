**/
EFI_STATUS
EFIAPI
GetBootGraphic(
    BOOT_GRAPHIC Graphic, OUT UINTN *ImageSize, OUT UINT8 **ImageData)
{
  EFI_GUID      *g = NULL;
  unsigned char *DecodedData;
  unsigned int   Width;
  unsigned int   Height;
  UINT32         DecoderError;
  EFI_STATUS     Status = EFI_SUCCESS;

  switch (Graphic) {
  case BG_SYSTEM_LOGO:
    g = PcdGetPtr(PcdLogoFile);
    break;
  case BG_CRITICAL_OVER_TEMP:
    g = PcdGetPtr(PcdThermalFile);
    break;
  case BG_CRITICAL_LOW_BATTERY:
    g = PcdGetPtr(PcdLowBatteryFile);
    break;
  default:
    DEBUG((DEBUG_ERROR, "Unsupported Boot Graphic Type 0x%X\n", Graphic));
    return EFI_UNSUPPORTED;
  }

  //
  // Get the specified image from FV.
  //
  Status =
      GetSectionFromAnyFv(g, EFI_SECTION_RAW, 0, (VOID **)ImageData, ImageSize);

  if (!EFI_ERROR(Status) &&
    (*ImageSize > 4) &&
    ((unsigned char *)*ImageData)[1] == 'P' &&
    ((unsigned char *)*ImageData)[2] == 'N' &&
    ((unsigned char *)*ImageData)[3] == 'G') {
