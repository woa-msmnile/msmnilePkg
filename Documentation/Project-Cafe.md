# Project Cafe Technical Specification DRAFT

Project Cafe is used in conjunction with Project Croissant WITHOUT Project Chocolatine.

The aim of Project Cafe is providing open ACPI tables as well as dynamic ACPI table generation using the Project Mu / EDK2 ACPI build infrastructure.

## DSDT Device ID Ranges

Project Cafe in contrast to QTI is going to use the manufacturer prefix CAFE for all devices.

It is not yet decided if each SoC are going to get their own reserved CAFEx000 range yet or not (depends if we go with universal driver support or not).

## Common SoC HW blocks across most device families

- Peripheral Buses:
    - SPI
    - UART
    - I2C
    - QuadSPI
    - 4 wire UART

- Power Management Buses:
    - SPMI
    - SPMI over I2C

- Clock Buses:
    - NPU CC
    - Debug CC
    - Video CC
    - GPU CC
    - CPU CC
    - etc...

- Subsystem Buses:
    - WCNSS
    - MBA
    - VENUS
    - EVASS
    - SLPI
    - SPSS
    - ADSP
    - CDSP
    - CDSP1
    - etc..