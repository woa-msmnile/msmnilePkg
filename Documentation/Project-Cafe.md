# Project Cafe Technical Specification DRAFT

Project Cafe is used in conjunction with Project Croissant WITHOUT Project Chocolatine.

The aim of Project Cafe is providing open ACPI tables as well as dynamic ACPI table generation using the Project Mu / EDK2 ACPI build infrastructure.

## DSDT Device ID Ranges

Project Cafe in contrast to QTI is going to use the manufacturer prefix CAFE for all devices.

It is not yet decided if each SoC are going to get their own reserved CAFEx000 range yet or not (depends if we go with universal driver support or not).