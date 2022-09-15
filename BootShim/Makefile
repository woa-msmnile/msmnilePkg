ARCH              = arm64
TARGET            = aarch64-linux-gnu
CROSS_COMPILE     = $(TARGET)-
CC                = $(CROSS_COMPILE)gcc
OBJCOPY           = $(CROSS_COMPILE)objcopy

all: BootShim.Epsilon.elf BootShim.Epsilon.bin BootShim.Zeta.elf BootShim.Zeta.bin

BootShim.Epsilon.bin: BootShim.Epsilon.elf
	$(OBJCOPY) -O binary $< $@

BootShim.Zeta.bin: BootShim.Zeta.elf
	$(OBJCOPY) -O binary $< $@

BootShim.Epsilon.elf: BootShim.Epsilon.S
	$(CC) -c $< -o $@

BootShim.Zeta.elf: BootShim.Zeta.S
	$(CC) -c $< -o $@

BootShim.Epsilon.S:

BootShim.Zeta.S:
