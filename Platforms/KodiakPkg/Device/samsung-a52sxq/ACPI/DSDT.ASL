// CreatorID=MSFT	CreatorRev=5.0.0
// FileLength=83445	FileChkSum=0xa

DefinitionBlock("DSDT.aml", "DSDT", 0x02, "QCOMM ", "SDM7280 ", 0x00000003)
{
    Scope(\_SB_)
    {
        Name(PSUB, "IDP07280")
        Name(SOID, 0xffffffff)
        Name(STOR, 0xabcabcab)
        Name(SIDS, "899800000000000")
        Name(SIDV, 0xffffffff)
        Name(SVMJ, 0xffff)
        Name(SVMI, 0xffff)
        Name(SDFE, 0xffff)
        Name(SFES, "899800000000000")
        Name(SIDM, 0xfffffffff)
        Name(SUFS, 0xffffffff)
        Name(PUS3, 0xffffffff)
        Name(SUS3, 0xffffffff)
        Name(SIDT, 0xffffffff)
        Name(SJTG, 0xffffffff)
        Name(SOSN, 0xaaaaaaaabbbbbbbb)
        Name(PLST, 0xffffffff)
        Name(EMUL, 0xffffffff)
        Name(RMTB, 0xaaaaaaaa)
        Name(RMTX, 0xbbbbbbbb)
        Name(RFMB, 0xcccccccc)
        Name(RFMS, 0xdddddddd)
        Name(RFAB, 0xeeeeeeee)
        Name(RFAS, 0x77777777)
        Name(TCMA, 0xdeadbeef)
        Name(TCML, 0xbeefdead)
        Name(SOSI, 0xdeadbeefffffffff)
        Name(PRP1, 0xffffffff)
        Name(SKUV, 0xffffffff)
        Name(SDDR, 0xffffffff)
        Device(UFS0)
        {
            Name(_HID, "QCOM24A5")
            Alias(\_SB_.PSUB, _SUB)
            Alias(\_SB_.EMUL, EMUL)
            Name(_UID, Zero)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xd8, 0x01, 0x00, 0xc0, 0x01, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x29, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Device(DEV0)
            {
                Method(_ADR, 0x0, NotSerialized)
                {
                    Return(0x8)
                }
                Method(_RMV, 0x0, NotSerialized)
                {
                    Return(Zero)
                }
            }
        }
        Device(SDC1)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_HID, "QCOM24BF")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0x7c, 0x00, 0x00, 0x10, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0xac, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Device(EMMC)
            {
                Method(_ADR, 0x0, NotSerialized)
                {
                    Return(0x8)
                }
                Method(_RMV, 0x0, NotSerialized)
                {
                    Return(Zero)
                }
            }
            Method(_DIS, 0x0, NotSerialized)
            {
            }
        }
        Device(SDC2)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.PEP0,
                \_SB_.GIO0
            })
            Name(_HID, "QCOM2466")
            Name(_UID, One)
            Name(_CCA, Zero)
            Alias(\_SB_.PSUB, _SUB)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x5d)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0x80, 0x08, 0x00, 0x10, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0xef, 0x00, 0x00, 0x00, 0x8c, 0x20, 0x00,
	0x01, 0x00, 0x01, 0x00, 0x1d, 0x00, 0x01, 0x00, 0x00, 0x88, 0x13, 0x17,
	0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x8c, 0x20, 0x00, 0x01,
	0x01, 0x01, 0x00, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x5b, 0x00, 0x5c, 0x5f, 0x53,
	0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Method(_DIS, 0x0, NotSerialized)
            {
            }
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
        }
        Device(ABD_)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_HID, "QCOM0427")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            OperationRegion(ROP1, GenericSerialBus, Zero, 0x100)
            Name(AVBL, Zero)
            Method(_REG, 0x2, NotSerialized)
            {
                If(LEqual(Arg0, 0x9))
                {
                    Store(Arg1, AVBL)
                }
            }
        }
        Name(ESNL, 0x14)
        Name(DBFL, 0x17)
        Device(PMIC)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.SPMI
            })
            Name(_HID, "QCOM0A2B")
            Name(_CID, "PNP0CA3")
            Alias(\_SB_.PSUB, _SUB)
            Method(PMCF, 0x0, NotSerialized)
            {
                Name(CFG0, Package(0xb)
                {
                    0xa,
                    Package(0x2)
                    {
                        Zero,
                        0x10
                    },
                    Package(0x2)
                    {
                        One,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x2,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x3,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x4,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x10,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x10,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x10,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x10,
                        0x10
                    },
                    Package(0x2)
                    {
                        0x10,
                        0x10
                    }
                })
                Return(CFG0)
            }
        }
        Device(PML0)
        {
            Name(_HID, "QCOM0AD3")
            Name(_DEP, Package(0x2)
            {
                \_SB_.I2C2,
                \_SB_.PM01
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xb)
            }
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LEqual(SKUV, One))
                {
                    Return("SKU17280")
                }
                Return("IDP07280")
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                If(LEqual(SKUV, One))
                {
                    Name(RBFC, Buffer(0xb8)
                    {
	0x8e, 0x19, 0x00, 0x01, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x06, 0x00,
	0xa0, 0x86, 0x01, 0x00, 0x08, 0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x49,
	0x32, 0x43, 0x32, 0x00, 0x8e, 0x19, 0x00, 0x01, 0x00, 0x01, 0x02, 0x00,
	0x00, 0x01, 0x06, 0x00, 0xa0, 0x86, 0x01, 0x00, 0x09, 0x00, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x49, 0x32, 0x43, 0x32, 0x00, 0x8e, 0x19, 0x00, 0x01,
	0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x06, 0x00, 0xa0, 0x86, 0x01, 0x00,
	0x10, 0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x49, 0x32, 0x43, 0x32, 0x00,
	0x8e, 0x19, 0x00, 0x01, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x06, 0x00,
	0xa0, 0x86, 0x01, 0x00, 0x11, 0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x49,
	0x32, 0x43, 0x32, 0x00, 0x8c, 0x20, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00,
	0x00, 0x03, 0xc8, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23,
	0x00, 0x00, 0x00, 0x12, 0x01, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d,
	0x30, 0x31, 0x00, 0x8c, 0x20, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
	0x03, 0xc8, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00,
	0x00, 0x00, 0x13, 0x01, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30,
	0x31, 0x00, 0x79, 0x00
                    })
                    Return(RBFC)
                }
                Else
                {
                    Name(RBUF, Buffer(0x5d)
                    {
	0x8e, 0x19, 0x00, 0x01, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x06, 0x00,
	0xa0, 0x86, 0x01, 0x00, 0x08, 0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x49,
	0x32, 0x43, 0x32, 0x00, 0x8e, 0x19, 0x00, 0x01, 0x00, 0x01, 0x02, 0x00,
	0x00, 0x01, 0x06, 0x00, 0xa0, 0x86, 0x01, 0x00, 0x09, 0x00, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x49, 0x32, 0x43, 0x32, 0x00, 0x8c, 0x20, 0x00, 0x01,
	0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0xc8, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x13, 0x01, 0x5c, 0x5f, 0x53,
	0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x79, 0x00
                    })
                    Return(RBUF)
                }
            }
        }
        Device(PM01)
        {
            Name(_HID, "QCOM0A2D")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, One)
            Name(_DEP, Package(One)
            {
                \_SB_.PMIC
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0xb)
                {
	0x89, 0x06, 0x00, 0x09, 0x01, 0x01, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Method(_DSM, 0x4, NotSerialized)
            {
                While(One)
                {
                    Name(_T_0, Buffer(One)
                    {
	0x00
                    })
                    CopyObject(ToBuffer(Arg0, ), _T_0)
                    If(LEqual(_T_0, Buffer(0x10)
                    {
	0x40, 0x8f, 0x24, 0x4f, 0xe2, 0xd5, 0x9f, 0x49, 0x83, 0x4c, 0x27, 0x75,
	0x8e, 0xa1, 0xcd, 0x3f
                    }))
                    {
                        While(One)
                        {
                            Name(_T_1, Zero)
                            Store(ToInteger(Arg2, ), _T_1)
                            If(LEqual(_T_1, Zero))
                            {
                                Return(Buffer(One)
                                {
	0x03
                                })
                            }
                            Else
                            {
                                If(LEqual(_T_1, One))
                                {
                                    Return(Package(0x2)
                                    {
                                        0x7,
                                        0x6
                                    })
                                }
                                Else
                                {
                                }
                            }
                            Break
                        }
                    }
                    Else
                    {
                        Return(Buffer(One)
                        {
	0x00
                        })
                    }
                    Break
                }
            }
        }
        Device(PMAP)
        {
            Name(_HID, "QCOM0A2C")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(0x3)
            {
                \_SB_.PMIC,
                \_SB_.ABD_,
                \_SB_.SCM0
            })
            Method(GEPT, 0x0, NotSerialized)
            {
                Name(BUFF, Buffer(0x4)
                {
                })
                CreateByteField(BUFF, Zero, STAT)
                CreateWordField(BUFF, 0x2, DATA)
                Store(0x2, DATA)
                Return(DATA)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x2)
                {
	0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(PRTC)
        {
            Name(_HID, "ACPI000E")
            Name(_DEP, Package(One)
            {
                "\\_SB.PMAP"
            })
            Method(_GCP, 0x0, NotSerialized)
            {
                Return(0x4)
            }
            Field(\_SB_.ABD_.ROP1, BufferAcc, NoLock, Preserve)
            {
                Connection(
                    I2CSerialBus(0x2, ControllerInitiated, 0, AddressingMode7Bit, "\\_SB.ABD", 0, ResourceConsumer, , )
                ),
                AccessAs(BufferAcc, AttribRawBytes(24)),
                FLD0, 192
            }
            Method(_GRT, 0x0, NotSerialized)
            {
                Name(BUFF, Buffer(0x1a)
                {
                })
                CreateField(BUFF, 0x10, 0x80, TME1)
                CreateField(BUFF, 0x90, 0x20, ACT1)
                CreateField(BUFF, 0xb0, 0x20, ACW1)
                Store(FLD0, BUFF)
                Return(TME1)
            }
            Method(_SRT, 0x1, NotSerialized)
            {
                Name(BUFF, Buffer(0x32)
                {
                })
                CreateByteField(BUFF, Zero, STAT)
                CreateField(BUFF, 0x10, 0x80, TME1)
                CreateField(BUFF, 0x90, 0x20, ACT1)
                CreateField(BUFF, 0xb0, 0x20, ACW1)
                Store(Zero, ACT1)
                Store(Arg0, TME1)
                Store(Zero, ACW1)
                Store(Store(BUFF, FLD0), BUFF)
                If(LNot(LEqual(STAT, Zero)))
                {
                    Return(One)
                }
                Return(Zero)
            }
        }
        Device(PMBM)
        {
            Name(_HID, "QCOM0A2A")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.PMGK
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x2)
                {
	0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(BCL1)
        {
            Name(_HID, "QCOM0A77")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.PMIC
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x11a)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x0b, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x08,
	0x01, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c,
	0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x09, 0x01,
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c, 0x20,
	0x00, 0x01, 0x00, 0x01, 0x00, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x0a, 0x01, 0x5c,
	0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c, 0x20, 0x00,
	0x01, 0x00, 0x01, 0x00, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17,
	0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x0b, 0x01, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c, 0x20, 0x00, 0x01,
	0x00, 0x01, 0x00, 0x0b, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x60, 0x01, 0x5c, 0x5f, 0x53,
	0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c, 0x20, 0x00, 0x01, 0x00,
	0x01, 0x00, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00,
	0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x61, 0x01, 0x5c, 0x5f, 0x53, 0x42,
	0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c, 0x20, 0x00, 0x01, 0x00, 0x01,
	0x00, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x19,
	0x00, 0x23, 0x00, 0x00, 0x00, 0x62, 0x01, 0x5c, 0x5f, 0x53, 0x42, 0x2e,
	0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00,
	0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00,
	0x23, 0x00, 0x00, 0x00, 0x63, 0x01, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50,
	0x4d, 0x30, 0x31, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Method(BCLQ, 0x0, NotSerialized)
            {
                Name(CFG0, Package(0x8)
                {
                    "PM3_BCLBIG_LVL0",
                    "PM3_BCLBIG_LVL1",
                    "PM3_BCLBIG_LVL2",
                    "PM3_BCLBIG_BAN",
                    "PM4_BCLBIG_LVL0",
                    "PM4_BCLBIG_LVL1",
                    "PM4_BCLBIG_LVL2",
                    "PM4_BCLBIG_BAN"
                })
                Return(CFG0)
            }
        }
        Device(PMGK)
        {
            Name(_HID, "QCOM0A8E")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(0x2)
            {
                \_SB_.GLNK,
                \_SB_.ABD_
            })
            Name(LKUP, Zero)
            Method(GEPT, 0x0, NotSerialized)
            {
                Name(BUFF, Buffer(0x4)
                {
                })
                CreateByteField(BUFF, Zero, STAT)
                CreateWordField(BUFF, 0x2, DATA)
                Store(0x3, DATA)
                Return(DATA)
            }
            Name(BUFF, Buffer(0x32)
            {
            })
            CreateField(BUFF, Zero, 0x8, BSTA)
            CreateField(BUFF, 0x8, 0x8, BSIZ)
            CreateField(BUFF, 0x10, 0x10, BVER)
            CreateField(BUFF, 0x30, 0x20, BCCI)
            CreateField(BUFF, 0x50, 0x40, BCTL)
            CreateField(BUFF, 0x90, 0x80, BMGI)
            CreateField(BUFF, 0x110, 0x80, BMGO)
            Method(USBN, 0x1, NotSerialized)
            {
                Store(UCSI, BUFF)
                Store(BVER, \_SB_.UCSI.VERS)
                Store(BMGI, \_SB_.UCSI.MSGI)
                Store(BCCI, \_SB_.UCSI.CCI_)
                Notify(\_SB_.UCSI, Arg0)
                Return(Zero)
            }
            Method(UPAN, 0x1, NotSerialized)
            {
                Name(VNTF, 0xffffffff)
                Name(VPRT, 0x4)
                Name(VMUX, Zero)
                Name(VCCS, 0x2)
                Name(VDPP, Zero)
                Name(VHPD, Zero)
                Name(VHSF, 0x2)
                Name(VHIQ, Zero)
                Name(BCCX, Zero)
                Name(BDIX, Zero)
                Store(Arg0, VNTF)
                And(VNTF, 0xff, VPRT)
                ShiftRight(VNTF, 0x8, VNTF)
                And(VNTF, 0xff, VCCS)
                ShiftRight(VNTF, 0x8, VNTF)
                And(VNTF, 0xff, VMUX)
                While(One)
                {
                    Name(_T_0, Zero)
                    Store(VMUX, _T_0)
                    If(LEqual(_T_0, Zero))
                    {
                        Store(Zero, VHSF)
                        Break
                    }
                    Else
                    {
                        If(LEqual(_T_0, One))
                        {
                            Store(Zero, VHSF)
                            Break
                        }
                        Else
                        {
                            If(LEqual(_T_0, 0x2))
                            {
                                Store(One, VHSF)
                                Break
                            }
                            Else
                            {
                                If(LEqual(_T_0, 0x3))
                                {
                                    Store(Zero, VHSF)
                                    Break
                                }
                            }
                        }
                    }
                    Break
                }
                ShiftRight(VNTF, 0x8, VNTF)
                And(VNTF, 0x80, VHIQ)
                If(LEqual(VHIQ, Zero))
                {
                    Store(Zero, VHIQ)
                }
                Else
                {
                    Store(One, VHIQ)
                }
                And(VNTF, 0x40, VHPD)
                If(LEqual(VHPD, Zero))
                {
                    Store(Zero, VHPD)
                }
                Else
                {
                    Store(One, VHPD)
                }
                And(VNTF, 0x3f, VDPP)
                If(LEqual(VDPP, Zero))
                {
                    Store(Zero, VDPP)
                }
                Else
                {
                    If(LEqual(VCCS, One))
                    {
                        Add(VDPP, 0x6, VDPP)
                    }
                }
                Store(VCCS, BCCX)
                ShiftLeft(VMUX, 0x2, VMUX)
                Or(VMUX, BCCX, BCCX)
                ShiftLeft(VHSF, 0x4, VHSF)
                Or(VHSF, BCCX, BCCX)
                Store(VDPP, BDIX)
                ShiftLeft(VHPD, 0x4, VHPD)
                Or(VHPD, BDIX, BDIX)
                ShiftLeft(VHIQ, 0x5, VHIQ)
                Or(VHIQ, BDIX, BDIX)
                Store(0x2, \_SB_.UCS0.EINF)
                While(One)
                {
                    Name(_T_1, Zero)
                    Store(VPRT, _T_1)
                    If(LEqual(_T_1, Zero))
                    {
                        Or(One, \_SB_.UCS0.EUPD, \_SB_.UCS0.EUPD)
                        Store(BCCX, \_SB_.UCS0.ECC0)
                        Store(BDIX, \_SB_.UCS0.EDI0)
                        \_SB_.UCS0.USBR
                        Break
                    }
                    Else
                    {
                        If(LEqual(_T_1, One))
                        {
                            Or(0x2, \_SB_.UCS0.EUPD, \_SB_.UCS0.EUPD)
                            Store(BCCX, \_SB_.UCS0.ECC1)
                            Store(BDIX, \_SB_.UCS0.EDI1)
                            \_SB_.UCS0.USBR
                            Break
                        }
                    }
                    Break
                }
                Return(Zero)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x2)
                {
	0x79, 0x00
                })
                Return(RBUF)
            }
            Method(LKST, 0x1, NotSerialized)
            {
                Store(Arg0, LKUP)
                Notify(\_SB_.UCSI, Zero)
                Return(Zero)
            }
            Field(\_SB_.ABD_.ROP1, BufferAcc, NoLock, Preserve)
            {
                Connection(
                    I2CSerialBus(0x3, ControllerInitiated, 0, AddressingMode7Bit, "\\_SB.ABD", 0, ResourceConsumer, , )
                ),
                AccessAs(BufferAcc, AttribRawBytes(48)),
                UCSI, 384
            }
        }
        Device(PEP0)
        {
            Name(_HID, "QCOM0A17")
            Name(_CID, "PNP0D80")
            Method(THTZ, 0x4, NotSerialized)
            {
                While(One)
                {
                    Name(_T_0, Zero)
                    Store(ToInteger(Arg0, ), _T_0)
                    If(LEqual(_T_0, One))
                    {
                        While(One)
                        {
                            Name(_T_1, Zero)
                            Store(ToInteger(Arg3, ), _T_1)
                            If(LEqual(_T_1, Zero))
                            {
                                If(Arg2)
                                {
                                    Store(Arg1, \_SB_.TZ1_.TPSV)
                                    Notify(\_SB_.TZ1_, 0x81)
                                }
                                Return(\_SB_.TZ1_._PSV())
                            }
                            Else
                            {
                                If(LEqual(_T_1, 0x2))
                                {
                                    If(Arg2)
                                    {
                                        Store(Arg1, \_SB_.TZ1_.TTSP)
                                        Notify(\_SB_.TZ1_, 0x81)
                                    }
                                    Return(\_SB_.TZ1_._TSP())
                                }
                                Else
                                {
                                    If(LEqual(_T_1, 0x3))
                                    {
                                        If(Arg2)
                                        {
                                            Store(Arg1, \_SB_.TZ1_.TTC1)
                                            Notify(\_SB_.TZ1_, 0x81)
                                        }
                                        Return(\_SB_.TZ1_._TC1())
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_1, 0x4))
                                        {
                                            If(Arg2)
                                            {
                                                Store(Arg1, \_SB_.TZ1_.TTC2)
                                                Notify(\_SB_.TZ1_, 0x81)
                                            }
                                            Return(\_SB_.TZ1_._TC2())
                                        }
                                        Else
                                        {
                                            Return(0xffff)
                                        }
                                    }
                                }
                            }
                            Break
                        }
                    }
                    Else
                    {
                        If(LEqual(_T_0, 0x3))
                        {
                            While(One)
                            {
                                Name(_T_2, Zero)
                                Store(ToInteger(Arg3, ), _T_2)
                                If(LEqual(_T_2, Zero))
                                {
                                    If(Arg2)
                                    {
                                        Store(Arg1, \_SB_.TZ3_.TPSV)
                                        Notify(\_SB_.TZ3_, 0x81)
                                    }
                                    Return(\_SB_.TZ3_._PSV())
                                }
                                Else
                                {
                                    If(LEqual(_T_2, 0x2))
                                    {
                                        If(Arg2)
                                        {
                                            Store(Arg1, \_SB_.TZ3_.TTSP)
                                            Notify(\_SB_.TZ3_, 0x81)
                                        }
                                        Return(\_SB_.TZ3_._TSP())
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_2, 0x3))
                                        {
                                            If(Arg2)
                                            {
                                                Store(Arg1, \_SB_.TZ3_.TTC1)
                                                Notify(\_SB_.TZ3_, 0x81)
                                            }
                                            Return(\_SB_.TZ3_._TC1())
                                        }
                                        Else
                                        {
                                            If(LEqual(_T_2, 0x4))
                                            {
                                                If(Arg2)
                                                {
                                                    Store(Arg1, \_SB_.TZ3_.TTC2)
                                                    Notify(\_SB_.TZ3_, 0x81)
                                                }
                                                Return(\_SB_.TZ3_._TC2())
                                            }
                                            Else
                                            {
                                                Return(0xffff)
                                            }
                                        }
                                    }
                                }
                                Break
                            }
                        }
                        Else
                        {
                            If(LEqual(_T_0, 0x5))
                            {
                                While(One)
                                {
                                    Name(_T_3, Zero)
                                    Store(ToInteger(Arg3, ), _T_3)
                                    If(LEqual(_T_3, Zero))
                                    {
                                        If(Arg2)
                                        {
                                            Store(Arg1, \_SB_.TZ5_.TPSV)
                                            Notify(\_SB_.TZ5_, 0x81)
                                        }
                                        Return(\_SB_.TZ5_._PSV())
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_3, 0x2))
                                        {
                                            If(Arg2)
                                            {
                                                Store(Arg1, \_SB_.TZ5_.TTSP)
                                                Notify(\_SB_.TZ5_, 0x81)
                                            }
                                            Return(\_SB_.TZ5_._TSP())
                                        }
                                        Else
                                        {
                                            If(LEqual(_T_3, 0x3))
                                            {
                                                If(Arg2)
                                                {
                                                    Store(Arg1, \_SB_.TZ5_.TTC1)
                                                    Notify(\_SB_.TZ5_, 0x81)
                                                }
                                                Return(\_SB_.TZ5_._TC1())
                                            }
                                            Else
                                            {
                                                If(LEqual(_T_3, 0x4))
                                                {
                                                    If(Arg2)
                                                    {
                                                        Store(Arg1, \_SB_.TZ5_.TTC2)
                                                        Notify(\_SB_.TZ5_, 0x81)
                                                    }
                                                    Return(\_SB_.TZ5_._TC2())
                                                }
                                                Else
                                                {
                                                    Return(0xffff)
                                                }
                                            }
                                        }
                                    }
                                    Break
                                }
                            }
                            Else
                            {
                                If(LEqual(_T_0, 0x6))
                                {
                                    While(One)
                                    {
                                        Name(_T_4, Zero)
                                        Store(ToInteger(Arg3, ), _T_4)
                                        If(LEqual(_T_4, Zero))
                                        {
                                            If(Arg2)
                                            {
                                                Store(Arg1, \_SB_.TZ6_.TPSV)
                                                Notify(\_SB_.TZ6_, 0x81)
                                            }
                                            Return(\_SB_.TZ6_._PSV())
                                        }
                                        Else
                                        {
                                            If(LEqual(_T_4, 0x2))
                                            {
                                                If(Arg2)
                                                {
                                                    Store(Arg1, \_SB_.TZ6_.TTSP)
                                                    Notify(\_SB_.TZ6_, 0x81)
                                                }
                                                Return(\_SB_.TZ6_._TSP())
                                            }
                                            Else
                                            {
                                                If(LEqual(_T_4, 0x3))
                                                {
                                                    If(Arg2)
                                                    {
                                                        Store(Arg1, \_SB_.TZ6_.TTC1)
                                                        Notify(\_SB_.TZ6_, 0x81)
                                                    }
                                                    Return(\_SB_.TZ6_._TC1())
                                                }
                                                Else
                                                {
                                                    If(LEqual(_T_4, 0x4))
                                                    {
                                                        If(Arg2)
                                                        {
                                                            Store(Arg1, \_SB_.TZ6_.TTC2)
                                                            Notify(\_SB_.TZ6_, 0x81)
                                                        }
                                                        Return(\_SB_.TZ6_._TC2())
                                                    }
                                                    Else
                                                    {
                                                        Return(0xffff)
                                                    }
                                                }
                                            }
                                        }
                                        Break
                                    }
                                }
                                Else
                                {
                                    If(LEqual(_T_0, 0xa))
                                    {
                                        While(One)
                                        {
                                            Name(_T_5, Zero)
                                            Store(ToInteger(Arg3, ), _T_5)
                                            If(LEqual(_T_5, Zero))
                                            {
                                                If(Arg2)
                                                {
                                                    Store(Arg1, \_SB_.TZ10.TPSV)
                                                    Notify(\_SB_.TZ10, 0x81)
                                                }
                                                Return(\_SB_.TZ10._PSV())
                                            }
                                            Else
                                            {
                                                If(LEqual(_T_5, 0x2))
                                                {
                                                    If(Arg2)
                                                    {
                                                        Store(Arg1, \_SB_.TZ10.TTSP)
                                                        Notify(\_SB_.TZ10, 0x81)
                                                    }
                                                    Return(\_SB_.TZ10._TSP())
                                                }
                                                Else
                                                {
                                                    If(LEqual(_T_5, 0x3))
                                                    {
                                                        If(Arg2)
                                                        {
                                                            Store(Arg1, \_SB_.TZ10.TTC1)
                                                            Notify(\_SB_.TZ10, 0x81)
                                                        }
                                                        Return(\_SB_.TZ10._TC1())
                                                    }
                                                    Else
                                                    {
                                                        If(LEqual(_T_5, 0x4))
                                                        {
                                                            If(Arg2)
                                                            {
                                                                Store(Arg1, \_SB_.TZ10.TTC2)
                                                                Notify(\_SB_.TZ10, 0x81)
                                                            }
                                                            Return(\_SB_.TZ10._TC2())
                                                        }
                                                        Else
                                                        {
                                                            Return(0xffff)
                                                        }
                                                    }
                                                }
                                            }
                                            Break
                                        }
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_0, 0xb))
                                        {
                                            While(One)
                                            {
                                                Name(_T_6, Zero)
                                                Store(ToInteger(Arg3, ), _T_6)
                                                If(LEqual(_T_6, Zero))
                                                {
                                                    If(Arg2)
                                                    {
                                                        Store(Arg1, \_SB_.TZ11.TPSV)
                                                        Notify(\_SB_.TZ11, 0x81)
                                                    }
                                                    Return(\_SB_.TZ11._PSV())
                                                }
                                                Else
                                                {
                                                    If(LEqual(_T_6, 0x2))
                                                    {
                                                        If(Arg2)
                                                        {
                                                            Store(Arg1, \_SB_.TZ11.TTSP)
                                                            Notify(\_SB_.TZ11, 0x81)
                                                        }
                                                        Return(\_SB_.TZ11._TSP())
                                                    }
                                                    Else
                                                    {
                                                        If(LEqual(_T_6, 0x3))
                                                        {
                                                            If(Arg2)
                                                            {
                                                                Store(Arg1, \_SB_.TZ11.TTC1)
                                                                Notify(\_SB_.TZ11, 0x81)
                                                            }
                                                            Return(\_SB_.TZ11._TC1())
                                                        }
                                                        Else
                                                        {
                                                            If(LEqual(_T_6, 0x4))
                                                            {
                                                                If(Arg2)
                                                                {
                                                                    Store(Arg1, \_SB_.TZ11.TTC2)
                                                                    Notify(\_SB_.TZ11, 0x81)
                                                                }
                                                                Return(\_SB_.TZ11._TC2())
                                                            }
                                                            Else
                                                            {
                                                                Return(0xffff)
                                                            }
                                                        }
                                                    }
                                                }
                                                Break
                                            }
                                        }
                                        Else
                                        {
                                            If(LEqual(_T_0, 0xd))
                                            {
                                                While(One)
                                                {
                                                    Name(_T_7, Zero)
                                                    Store(ToInteger(Arg3, ), _T_7)
                                                    If(LEqual(_T_7, Zero))
                                                    {
                                                        If(Arg2)
                                                        {
                                                            Store(Arg1, \_SB_.TZ13.TPSV)
                                                            Notify(\_SB_.TZ13, 0x81)
                                                        }
                                                        Return(\_SB_.TZ13._PSV)
                                                    }
                                                    Else
                                                    {
                                                        If(LEqual(_T_7, 0x2))
                                                        {
                                                            If(Arg2)
                                                            {
                                                                Store(Arg1, \_SB_.TZ13.TTSP)
                                                                Notify(\_SB_.TZ13, 0x81)
                                                            }
                                                            Return(\_SB_.TZ13._TSP)
                                                        }
                                                        Else
                                                        {
                                                            If(LEqual(_T_7, 0x3))
                                                            {
                                                                If(Arg2)
                                                                {
                                                                    Store(Arg1, \_SB_.TZ13.TTC1)
                                                                    Notify(\_SB_.TZ13, 0x81)
                                                                }
                                                                Return(\_SB_.TZ13._TC1)
                                                            }
                                                            Else
                                                            {
                                                                If(LEqual(_T_7, 0x4))
                                                                {
                                                                    If(Arg2)
                                                                    {
                                                                        Store(Arg1, \_SB_.TZ13.TTC2)
                                                                        Notify(\_SB_.TZ13, 0x81)
                                                                    }
                                                                    Return(\_SB_.TZ13._TC2)
                                                                }
                                                                Else
                                                                {
                                                                    Return(0xffff)
                                                                }
                                                            }
                                                        }
                                                    }
                                                    Break
                                                }
                                            }
                                            Else
                                            {
                                                If(LEqual(_T_0, 0xf))
                                                {
                                                    While(One)
                                                    {
                                                        Name(_T_8, Zero)
                                                        Store(ToInteger(Arg3, ), _T_8)
                                                        If(LEqual(_T_8, Zero))
                                                        {
                                                            If(Arg2)
                                                            {
                                                                Return(0xffff)
                                                            }
                                                            Return(\_SB_.TZ15._PSV())
                                                        }
                                                        Else
                                                        {
                                                            If(LEqual(_T_8, 0x2))
                                                            {
                                                                If(Arg2)
                                                                {
                                                                    Return(0xffff)
                                                                }
                                                                Return(\_SB_.TZ15._TSP)
                                                            }
                                                            Else
                                                            {
                                                                If(LEqual(_T_8, 0x3))
                                                                {
                                                                    If(Arg2)
                                                                    {
                                                                        Return(0xffff)
                                                                    }
                                                                    Return(\_SB_.TZ15._TC1())
                                                                }
                                                                Else
                                                                {
                                                                    If(LEqual(_T_8, 0x4))
                                                                    {
                                                                        If(Arg2)
                                                                        {
                                                                            Return(0xffff)
                                                                        }
                                                                        Return(\_SB_.TZ15._TC2())
                                                                    }
                                                                    Else
                                                                    {
                                                                        Return(0xffff)
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        Break
                                                    }
                                                }
                                                Else
                                                {
                                                    If(LEqual(_T_0, 0x10))
                                                    {
                                                        While(One)
                                                        {
                                                            Name(_T_9, Zero)
                                                            Store(ToInteger(Arg3, ), _T_9)
                                                            If(LEqual(_T_9, Zero))
                                                            {
                                                                If(Arg2)
                                                                {
                                                                    Store(Arg1, \_SB_.TZ16.TPSV)
                                                                    Notify(\_SB_.TZ16, 0x81)
                                                                }
                                                                Return(\_SB_.TZ16._PSV())
                                                            }
                                                            Else
                                                            {
                                                                If(LEqual(_T_9, One))
                                                                {
                                                                    If(Arg2)
                                                                    {
                                                                        Return(0xffff)
                                                                    }
                                                                    Return(\_SB_.TZ16._CRT())
                                                                }
                                                                Else
                                                                {
                                                                    If(LEqual(_T_9, 0x2))
                                                                    {
                                                                        If(Arg2)
                                                                        {
                                                                            Return(0xffff)
                                                                        }
                                                                        Return(\_SB_.TZ16._TSP)
                                                                    }
                                                                    Else
                                                                    {
                                                                        If(LEqual(_T_9, 0x3))
                                                                        {
                                                                            If(Arg2)
                                                                            {
                                                                                Return(0xffff)
                                                                            }
                                                                            Return(\_SB_.TZ16._TC1())
                                                                        }
                                                                        Else
                                                                        {
                                                                            If(LEqual(_T_9, 0x4))
                                                                            {
                                                                                If(Arg2)
                                                                                {
                                                                                    Return(0xffff)
                                                                                }
                                                                                Return(\_SB_.TZ16._TC2())
                                                                            }
                                                                            Else
                                                                            {
                                                                                Return(0xffff)
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            Break
                                                        }
                                                    }
                                                    Else
                                                    {
                                                        If(LEqual(_T_0, 0x11))
                                                        {
                                                            While(One)
                                                            {
                                                                Name(_T_A, Zero)
                                                                Store(ToInteger(Arg3, ), _T_A)
                                                                If(LEqual(_T_A, Zero))
                                                                {
                                                                    If(Arg2)
                                                                    {
                                                                        Return(0xffff)
                                                                    }
                                                                    Return(\_SB_.TZ17._PSV)
                                                                }
                                                                Else
                                                                {
                                                                    If(LEqual(_T_A, 0x2))
                                                                    {
                                                                        If(Arg2)
                                                                        {
                                                                            Return(0xffff)
                                                                        }
                                                                        Return(\_SB_.TZ17._TSP)
                                                                    }
                                                                    Else
                                                                    {
                                                                        If(LEqual(_T_A, 0x3))
                                                                        {
                                                                            If(Arg2)
                                                                            {
                                                                                Return(0xffff)
                                                                            }
                                                                            Return(\_SB_.TZ17._TC1)
                                                                        }
                                                                        Else
                                                                        {
                                                                            If(LEqual(_T_A, 0x4))
                                                                            {
                                                                                If(Arg2)
                                                                                {
                                                                                    Return(0xffff)
                                                                                }
                                                                                Return(\_SB_.TZ17._TC2)
                                                                            }
                                                                            Else
                                                                            {
                                                                                Return(0xffff)
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                Break
                                                            }
                                                        }
                                                        Else
                                                        {
                                                            If(LEqual(_T_0, 0x12))
                                                            {
                                                                While(One)
                                                                {
                                                                    Name(_T_B, Zero)
                                                                    Store(ToInteger(Arg3, ), _T_B)
                                                                    If(LEqual(_T_B, Zero))
                                                                    {
                                                                        If(Arg2)
                                                                        {
                                                                            Return(0xffff)
                                                                        }
                                                                        Return(\_SB_.TZ18._PSV())
                                                                    }
                                                                    Else
                                                                    {
                                                                        If(LEqual(_T_B, 0x2))
                                                                        {
                                                                            If(Arg2)
                                                                            {
                                                                                Return(0xffff)
                                                                            }
                                                                            Return(\_SB_.TZ18._TSP)
                                                                        }
                                                                        Else
                                                                        {
                                                                            If(LEqual(_T_B, 0x3))
                                                                            {
                                                                                If(Arg2)
                                                                                {
                                                                                    Return(0xffff)
                                                                                }
                                                                                Return(\_SB_.TZ18._TC1())
                                                                            }
                                                                            Else
                                                                            {
                                                                                If(LEqual(_T_B, 0x4))
                                                                                {
                                                                                    If(Arg2)
                                                                                    {
                                                                                        Return(0xffff)
                                                                                    }
                                                                                    Return(\_SB_.TZ18._TC2())
                                                                                }
                                                                                Else
                                                                                {
                                                                                    Return(0xffff)
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                    Break
                                                                }
                                                            }
                                                            Else
                                                            {
                                                                If(LEqual(_T_0, 0x1f))
                                                                {
                                                                    While(One)
                                                                    {
                                                                        Name(_T_C, Zero)
                                                                        Store(ToInteger(Arg3, ), _T_C)
                                                                        If(LEqual(_T_C, Zero))
                                                                        {
                                                                            If(Arg2)
                                                                            {
                                                                                Store(Arg1, \_SB_.TZ31.TPSV)
                                                                                Notify(\_SB_.TZ31, 0x81)
                                                                            }
                                                                            Return(\_SB_.TZ31._PSV)
                                                                        }
                                                                        Else
                                                                        {
                                                                            If(LEqual(_T_C, One))
                                                                            {
                                                                                If(Arg2)
                                                                                {
                                                                                    Store(Arg1, \_SB_.TZ31.TCRT)
                                                                                    Notify(\_SB_.TZ31, 0x81)
                                                                                }
                                                                                Return(\_SB_.TZ31._CRT)
                                                                            }
                                                                            Else
                                                                            {
                                                                                If(LEqual(_T_C, 0x2))
                                                                                {
                                                                                    If(Arg2)
                                                                                    {
                                                                                        Store(Arg1, \_SB_.TZ31.TTSP)
                                                                                        Notify(\_SB_.TZ31, 0x81)
                                                                                    }
                                                                                    Return(\_SB_.TZ31._TSP())
                                                                                }
                                                                                Else
                                                                                {
                                                                                    If(LEqual(_T_C, 0x3))
                                                                                    {
                                                                                        If(Arg2)
                                                                                        {
                                                                                            Store(Arg1, \_SB_.TZ31.TTC1)
                                                                                            Notify(\_SB_.TZ31, 0x81)
                                                                                        }
                                                                                        Return(\_SB_.TZ31._TC1())
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        If(LEqual(_T_C, 0x4))
                                                                                        {
                                                                                            If(Arg2)
                                                                                            {
                                                                                                Store(Arg1, \_SB_.TZ31.TTC2)
                                                                                                Notify(\_SB_.TZ31, 0x81)
                                                                                            }
                                                                                            Return(\_SB_.TZ31._TC2())
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            Return(0xffff)
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                        Break
                                                                    }
                                                                }
                                                                Else
                                                                {
                                                                    If(LEqual(_T_0, 0x20))
                                                                    {
                                                                        While(One)
                                                                        {
                                                                            Name(_T_D, Zero)
                                                                            Store(ToInteger(Arg3, ), _T_D)
                                                                            If(LEqual(_T_D, Zero))
                                                                            {
                                                                                If(Arg2)
                                                                                {
                                                                                    Store(Arg1, \_SB_.TZ32.TPSV)
                                                                                    Notify(\_SB_.TZ32, 0x81)
                                                                                }
                                                                                Return(\_SB_.TZ32._PSV())
                                                                            }
                                                                            Else
                                                                            {
                                                                                If(LEqual(_T_D, One))
                                                                                {
                                                                                    If(Arg2)
                                                                                    {
                                                                                        Store(Arg1, \_SB_.TZ32.TCRT)
                                                                                        Notify(\_SB_.TZ32, 0x81)
                                                                                    }
                                                                                    Return(\_SB_.TZ32._CRT())
                                                                                }
                                                                                Else
                                                                                {
                                                                                    If(LEqual(_T_D, 0x2))
                                                                                    {
                                                                                        If(Arg2)
                                                                                        {
                                                                                            Store(Arg1, \_SB_.TZ32.TTSP)
                                                                                            Notify(\_SB_.TZ32, 0x81)
                                                                                        }
                                                                                        Return(\_SB_.TZ32._TSP())
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        If(LEqual(_T_D, 0x3))
                                                                                        {
                                                                                            If(Arg2)
                                                                                            {
                                                                                                Store(Arg1, \_SB_.TZ32.TTC1)
                                                                                                Notify(\_SB_.TZ32, 0x81)
                                                                                            }
                                                                                            Return(\_SB_.TZ32._TC1())
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            If(LEqual(_T_D, 0x4))
                                                                                            {
                                                                                                If(Arg2)
                                                                                                {
                                                                                                    Store(Arg1, \_SB_.TZ32.TTC2)
                                                                                                    Notify(\_SB_.TZ32, 0x81)
                                                                                                }
                                                                                                Return(\_SB_.TZ32._TC2())
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                Return(0xffff)
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                            Break
                                                                        }
                                                                    }
                                                                    Else
                                                                    {
                                                                        If(LEqual(_T_0, 0x21))
                                                                        {
                                                                            While(One)
                                                                            {
                                                                                Name(_T_E, Zero)
                                                                                Store(ToInteger(Arg3, ), _T_E)
                                                                                If(LEqual(_T_E, Zero))
                                                                                {
                                                                                    If(Arg2)
                                                                                    {
                                                                                        Store(Arg1, \_SB_.TZ33.TPSV)
                                                                                        Notify(\_SB_.TZ33, 0x81)
                                                                                    }
                                                                                    Return(\_SB_.TZ33._PSV)
                                                                                }
                                                                                Else
                                                                                {
                                                                                    If(LEqual(_T_E, One))
                                                                                    {
                                                                                        If(Arg2)
                                                                                        {
                                                                                            Store(Arg1, \_SB_.TZ33.TCRT)
                                                                                            Notify(\_SB_.TZ33, 0x81)
                                                                                        }
                                                                                        Return(\_SB_.TZ33._CRT)
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        If(LEqual(_T_E, 0x2))
                                                                                        {
                                                                                            If(Arg2)
                                                                                            {
                                                                                                Store(Arg1, \_SB_.TZ33.TTSP)
                                                                                                Notify(\_SB_.TZ33, 0x81)
                                                                                            }
                                                                                            Return(\_SB_.TZ33._TSP())
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            If(LEqual(_T_E, 0x3))
                                                                                            {
                                                                                                If(Arg2)
                                                                                                {
                                                                                                    Store(Arg1, \_SB_.TZ33.TTC1)
                                                                                                    Notify(\_SB_.TZ33, 0x81)
                                                                                                }
                                                                                                Return(\_SB_.TZ33._TC1())
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                If(LEqual(_T_E, 0x4))
                                                                                                {
                                                                                                    If(Arg2)
                                                                                                    {
                                                                                                        Store(Arg1, \_SB_.TZ33.TTC2)
                                                                                                        Notify(\_SB_.TZ33, 0x81)
                                                                                                    }
                                                                                                    Return(\_SB_.TZ33._TC2())
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    Return(0xffff)
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                Break
                                                                            }
                                                                        }
                                                                        Else
                                                                        {
                                                                            If(LEqual(_T_0, 0x22))
                                                                            {
                                                                                While(One)
                                                                                {
                                                                                    Name(_T_F, Zero)
                                                                                    Store(ToInteger(Arg3, ), _T_F)
                                                                                    If(LEqual(_T_F, Zero))
                                                                                    {
                                                                                        If(Arg2)
                                                                                        {
                                                                                            Store(Arg1, \_SB_.TZ34.TPSV)
                                                                                            Notify(\_SB_.TZ34, 0x81)
                                                                                        }
                                                                                        Return(\_SB_.TZ34._PSV)
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        If(LEqual(_T_F, One))
                                                                                        {
                                                                                            If(Arg2)
                                                                                            {
                                                                                                Store(Arg1, \_SB_.TZ34.TCRT)
                                                                                                Notify(\_SB_.TZ34, 0x81)
                                                                                            }
                                                                                            Return(\_SB_.TZ34._CRT)
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            If(LEqual(_T_F, 0x2))
                                                                                            {
                                                                                                If(Arg2)
                                                                                                {
                                                                                                    Store(Arg1, \_SB_.TZ34.TTSP)
                                                                                                    Notify(\_SB_.TZ34, 0x81)
                                                                                                }
                                                                                                Return(\_SB_.TZ34._TSP)
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                If(LEqual(_T_F, 0x3))
                                                                                                {
                                                                                                    If(Arg2)
                                                                                                    {
                                                                                                        Store(Arg1, \_SB_.TZ34.TTC1)
                                                                                                        Notify(\_SB_.TZ34, 0x81)
                                                                                                    }
                                                                                                    Return(\_SB_.TZ34._TC1)
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    If(LEqual(_T_F, 0x4))
                                                                                                    {
                                                                                                        If(Arg2)
                                                                                                        {
                                                                                                            Store(Arg1, \_SB_.TZ34.TTC2)
                                                                                                            Notify(\_SB_.TZ34, 0x81)
                                                                                                        }
                                                                                                        Return(\_SB_.TZ34._TC2)
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        Return(0xffff)
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    Break
                                                                                }
                                                                            }
                                                                            Else
                                                                            {
                                                                                If(LEqual(_T_0, 0x23))
                                                                                {
                                                                                    While(One)
                                                                                    {
                                                                                        Name(_T_G, Zero)
                                                                                        Store(ToInteger(Arg3, ), _T_G)
                                                                                        If(LEqual(_T_G, Zero))
                                                                                        {
                                                                                            If(Arg2)
                                                                                            {
                                                                                                Store(Arg1, \_SB_.TZ35.TPSV)
                                                                                                Notify(\_SB_.TZ35, 0x81)
                                                                                            }
                                                                                            Return(\_SB_.TZ35._PSV)
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            If(LEqual(_T_G, One))
                                                                                            {
                                                                                                If(Arg2)
                                                                                                {
                                                                                                    Store(Arg1, \_SB_.TZ35.TCRT)
                                                                                                    Notify(\_SB_.TZ35, 0x81)
                                                                                                }
                                                                                                Return(\_SB_.TZ35._CRT)
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                If(LEqual(_T_G, 0x2))
                                                                                                {
                                                                                                    If(Arg2)
                                                                                                    {
                                                                                                        Store(Arg1, \_SB_.TZ35.TTSP)
                                                                                                        Notify(\_SB_.TZ35, 0x81)
                                                                                                    }
                                                                                                    Return(\_SB_.TZ35._TSP)
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    If(LEqual(_T_G, 0x3))
                                                                                                    {
                                                                                                        If(Arg2)
                                                                                                        {
                                                                                                            Store(Arg1, \_SB_.TZ35.TTC1)
                                                                                                            Notify(\_SB_.TZ35, 0x81)
                                                                                                        }
                                                                                                        Return(\_SB_.TZ35._TC1)
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        If(LEqual(_T_G, 0x4))
                                                                                                        {
                                                                                                            If(Arg2)
                                                                                                            {
                                                                                                                Store(Arg1, \_SB_.TZ35.TTC2)
                                                                                                                Notify(\_SB_.TZ35, 0x81)
                                                                                                            }
                                                                                                            Return(\_SB_.TZ35._TC2)
                                                                                                        }
                                                                                                        Else
                                                                                                        {
                                                                                                            Return(0xffff)
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                        Break
                                                                                    }
                                                                                }
                                                                                Else
                                                                                {
                                                                                    If(LEqual(_T_0, 0x24))
                                                                                    {
                                                                                        While(One)
                                                                                        {
                                                                                            Name(_T_H, Zero)
                                                                                            Store(ToInteger(Arg3, ), _T_H)
                                                                                            If(LEqual(_T_H, Zero))
                                                                                            {
                                                                                                If(Arg2)
                                                                                                {
                                                                                                    Store(Arg1, \_SB_.TZ36.TPSV)
                                                                                                    Notify(\_SB_.TZ36, 0x81)
                                                                                                }
                                                                                                Return(\_SB_.TZ36._PSV)
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                If(LEqual(_T_H, One))
                                                                                                {
                                                                                                    If(Arg2)
                                                                                                    {
                                                                                                        Store(Arg1, \_SB_.TZ36.TCRT)
                                                                                                        Notify(\_SB_.TZ36, 0x81)
                                                                                                    }
                                                                                                    Return(\_SB_.TZ36._CRT)
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    If(LEqual(_T_H, 0x2))
                                                                                                    {
                                                                                                        If(Arg2)
                                                                                                        {
                                                                                                            Store(Arg1, \_SB_.TZ36.TTSP)
                                                                                                            Notify(\_SB_.TZ36, 0x81)
                                                                                                        }
                                                                                                        Return(\_SB_.TZ36._TSP)
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        If(LEqual(_T_H, 0x3))
                                                                                                        {
                                                                                                            If(Arg2)
                                                                                                            {
                                                                                                                Store(Arg1, \_SB_.TZ36.TTC1)
                                                                                                                Notify(\_SB_.TZ36, 0x81)
                                                                                                            }
                                                                                                            Return(\_SB_.TZ36._TC1)
                                                                                                        }
                                                                                                        Else
                                                                                                        {
                                                                                                            If(LEqual(_T_H, 0x4))
                                                                                                            {
                                                                                                                If(Arg2)
                                                                                                                {
                                                                                                                    Store(Arg1, \_SB_.TZ36.TTC2)
                                                                                                                    Notify(\_SB_.TZ36, 0x81)
                                                                                                                }
                                                                                                                Return(\_SB_.TZ36._TC2)
                                                                                                            }
                                                                                                            Else
                                                                                                            {
                                                                                                                Return(0xffff)
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                            Break
                                                                                        }
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        If(LEqual(_T_0, 0x25))
                                                                                        {
                                                                                            While(One)
                                                                                            {
                                                                                                Name(_T_I, Zero)
                                                                                                Store(ToInteger(Arg3, ), _T_I)
                                                                                                If(LEqual(_T_I, Zero))
                                                                                                {
                                                                                                    If(Arg2)
                                                                                                    {
                                                                                                        Store(Arg1, \_SB_.TZ37.TPSV)
                                                                                                        Notify(\_SB_.TZ37, 0x81)
                                                                                                    }
                                                                                                    Return(\_SB_.TZ37._PSV)
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    If(LEqual(_T_I, One))
                                                                                                    {
                                                                                                        If(Arg2)
                                                                                                        {
                                                                                                            Store(Arg1, \_SB_.TZ37.TCRT)
                                                                                                            Notify(\_SB_.TZ37, 0x81)
                                                                                                        }
                                                                                                        Return(\_SB_.TZ37._CRT)
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        If(LEqual(_T_I, 0x2))
                                                                                                        {
                                                                                                            If(Arg2)
                                                                                                            {
                                                                                                                Store(Arg1, \_SB_.TZ37.TTSP)
                                                                                                                Notify(\_SB_.TZ37, 0x81)
                                                                                                            }
                                                                                                            Return(\_SB_.TZ37._TSP)
                                                                                                        }
                                                                                                        Else
                                                                                                        {
                                                                                                            If(LEqual(_T_I, 0x3))
                                                                                                            {
                                                                                                                If(Arg2)
                                                                                                                {
                                                                                                                    Store(Arg1, \_SB_.TZ37.TTC1)
                                                                                                                    Notify(\_SB_.TZ37, 0x81)
                                                                                                                }
                                                                                                                Return(\_SB_.TZ37._TC1)
                                                                                                            }
                                                                                                            Else
                                                                                                            {
                                                                                                                If(LEqual(_T_I, 0x4))
                                                                                                                {
                                                                                                                    If(Arg2)
                                                                                                                    {
                                                                                                                        Store(Arg1, \_SB_.TZ37.TTC2)
                                                                                                                        Notify(\_SB_.TZ37, 0x81)
                                                                                                                    }
                                                                                                                    Return(\_SB_.TZ37._TC2)
                                                                                                                }
                                                                                                                Else
                                                                                                                {
                                                                                                                    Return(0xffff)
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                                Break
                                                                                            }
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            If(LEqual(_T_0, 0x26))
                                                                                            {
                                                                                                While(One)
                                                                                                {
                                                                                                    Name(_T_J, Zero)
                                                                                                    Store(ToInteger(Arg3, ), _T_J)
                                                                                                    If(LEqual(_T_J, Zero))
                                                                                                    {
                                                                                                        If(Arg2)
                                                                                                        {
                                                                                                            Store(Arg1, \_SB_.TZ38.TPSV)
                                                                                                            Notify(\_SB_.TZ38, 0x81)
                                                                                                        }
                                                                                                        Return(\_SB_.TZ38._PSV)
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        If(LEqual(_T_J, One))
                                                                                                        {
                                                                                                            If(Arg2)
                                                                                                            {
                                                                                                                Store(Arg1, \_SB_.TZ38.TCRT)
                                                                                                                Notify(\_SB_.TZ38, 0x81)
                                                                                                            }
                                                                                                            Return(\_SB_.TZ38._CRT)
                                                                                                        }
                                                                                                        Else
                                                                                                        {
                                                                                                            If(LEqual(_T_J, 0x2))
                                                                                                            {
                                                                                                                If(Arg2)
                                                                                                                {
                                                                                                                    Store(Arg1, \_SB_.TZ38.TTSP)
                                                                                                                    Notify(\_SB_.TZ38, 0x81)
                                                                                                                }
                                                                                                                Return(\_SB_.TZ38._TSP)
                                                                                                            }
                                                                                                            Else
                                                                                                            {
                                                                                                                If(LEqual(_T_J, 0x3))
                                                                                                                {
                                                                                                                    If(Arg2)
                                                                                                                    {
                                                                                                                        Store(Arg1, \_SB_.TZ38.TTC1)
                                                                                                                        Notify(\_SB_.TZ38, 0x81)
                                                                                                                    }
                                                                                                                    Return(\_SB_.TZ38._TC1)
                                                                                                                }
                                                                                                                Else
                                                                                                                {
                                                                                                                    If(LEqual(_T_J, 0x4))
                                                                                                                    {
                                                                                                                        If(Arg2)
                                                                                                                        {
                                                                                                                            Store(Arg1, \_SB_.TZ38.TTC2)
                                                                                                                            Notify(\_SB_.TZ38, 0x81)
                                                                                                                        }
                                                                                                                        Return(\_SB_.TZ38._TC2)
                                                                                                                    }
                                                                                                                    Else
                                                                                                                    {
                                                                                                                        Return(0xffff)
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                    Break
                                                                                                }
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                If(LEqual(_T_0, 0x63))
                                                                                                {
                                                                                                    While(One)
                                                                                                    {
                                                                                                        Name(_T_K, Zero)
                                                                                                        Store(ToInteger(Arg3, ), _T_K)
                                                                                                        If(LEqual(_T_K, Zero))
                                                                                                        {
                                                                                                            If(Arg2)
                                                                                                            {
                                                                                                                Store(Arg1, \_SB_.TZ99.TPSV)
                                                                                                                Notify(\_SB_.TZ99, 0x81)
                                                                                                            }
                                                                                                            Return(\_SB_.TZ99._PSV())
                                                                                                        }
                                                                                                        Else
                                                                                                        {
                                                                                                            If(LEqual(_T_K, One))
                                                                                                            {
                                                                                                                If(Arg2)
                                                                                                                {
                                                                                                                    Store(Arg1, \_SB_.TZ99.TCRT)
                                                                                                                    Notify(\_SB_.TZ99, 0x81)
                                                                                                                }
                                                                                                                Return(\_SB_.TZ99._CRT())
                                                                                                            }
                                                                                                            Else
                                                                                                            {
                                                                                                                If(LEqual(_T_K, 0x2))
                                                                                                                {
                                                                                                                    If(Arg2)
                                                                                                                    {
                                                                                                                        Store(Arg1, \_SB_.TZ99.TTSP)
                                                                                                                        Notify(\_SB_.TZ99, 0x81)
                                                                                                                    }
                                                                                                                    Return(\_SB_.TZ99._TSP())
                                                                                                                }
                                                                                                                Else
                                                                                                                {
                                                                                                                    If(LEqual(_T_K, 0x3))
                                                                                                                    {
                                                                                                                        If(Arg2)
                                                                                                                        {
                                                                                                                            Store(Arg1, \_SB_.TZ99.TTC1)
                                                                                                                            Notify(\_SB_.TZ99, 0x81)
                                                                                                                        }
                                                                                                                        Return(\_SB_.TZ99._TC1())
                                                                                                                    }
                                                                                                                    Else
                                                                                                                    {
                                                                                                                        If(LEqual(_T_K, 0x4))
                                                                                                                        {
                                                                                                                            If(Arg2)
                                                                                                                            {
                                                                                                                                Store(Arg1, \_SB_.TZ99.TTC2)
                                                                                                                                Notify(\_SB_.TZ99, 0x81)
                                                                                                                            }
                                                                                                                            Return(\_SB_.TZ99._TC2())
                                                                                                                        }
                                                                                                                        Else
                                                                                                                        {
                                                                                                                            Return(0xffff)
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                        Break
                                                                                                    }
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    If(LEqual(_T_0, 0x33))
                                                                                                    {
                                                                                                        While(One)
                                                                                                        {
                                                                                                            Name(_T_L, Zero)
                                                                                                            Store(ToInteger(Arg3, ), _T_L)
                                                                                                            If(LEqual(_T_L, Zero))
                                                                                                            {
                                                                                                                If(Arg2)
                                                                                                                {
                                                                                                                    Store(Arg1, \_SB_.TZ51.TPSV)
                                                                                                                    Notify(\_SB_.TZ51, 0x81)
                                                                                                                }
                                                                                                                Return(\_SB_.TZ51._PSV())
                                                                                                            }
                                                                                                            Else
                                                                                                            {
                                                                                                                If(LEqual(_T_L, 0x2))
                                                                                                                {
                                                                                                                    If(Arg2)
                                                                                                                    {
                                                                                                                        Store(Arg1, \_SB_.TZ51.TTSP)
                                                                                                                        Notify(\_SB_.TZ51, 0x81)
                                                                                                                    }
                                                                                                                    Return(\_SB_.TZ51._TSP())
                                                                                                                }
                                                                                                                Else
                                                                                                                {
                                                                                                                    If(LEqual(_T_L, 0x3))
                                                                                                                    {
                                                                                                                        If(Arg2)
                                                                                                                        {
                                                                                                                            Store(Arg1, \_SB_.TZ51.TTC1)
                                                                                                                            Notify(\_SB_.TZ51, 0x81)
                                                                                                                        }
                                                                                                                        Return(\_SB_.TZ51._TC1())
                                                                                                                    }
                                                                                                                    Else
                                                                                                                    {
                                                                                                                        If(LEqual(_T_L, 0x4))
                                                                                                                        {
                                                                                                                            If(Arg2)
                                                                                                                            {
                                                                                                                                Store(Arg1, \_SB_.TZ51.TTC2)
                                                                                                                                Notify(\_SB_.TZ51, 0x81)
                                                                                                                            }
                                                                                                                            Return(\_SB_.TZ51._TC2())
                                                                                                                        }
                                                                                                                        Else
                                                                                                                        {
                                                                                                                            Return(0xffff)
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                            Break
                                                                                                        }
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        If(LEqual(_T_0, 0x34))
                                                                                                        {
                                                                                                            While(One)
                                                                                                            {
                                                                                                                Name(_T_M, Zero)
                                                                                                                Store(ToInteger(Arg3, ), _T_M)
                                                                                                                If(LEqual(_T_M, Zero))
                                                                                                                {
                                                                                                                    If(Arg2)
                                                                                                                    {
                                                                                                                        Store(Arg1, \_SB_.TZ52.TPSV)
                                                                                                                        Notify(\_SB_.TZ52, 0x81)
                                                                                                                    }
                                                                                                                    Return(\_SB_.TZ52._PSV())
                                                                                                                }
                                                                                                                Else
                                                                                                                {
                                                                                                                    If(LEqual(_T_M, 0x2))
                                                                                                                    {
                                                                                                                        If(Arg2)
                                                                                                                        {
                                                                                                                            Store(Arg1, \_SB_.TZ52.TTSP)
                                                                                                                            Notify(\_SB_.TZ52, 0x81)
                                                                                                                        }
                                                                                                                        Return(\_SB_.TZ52._TSP())
                                                                                                                    }
                                                                                                                    Else
                                                                                                                    {
                                                                                                                        If(LEqual(_T_M, 0x3))
                                                                                                                        {
                                                                                                                            If(Arg2)
                                                                                                                            {
                                                                                                                                Store(Arg1, \_SB_.TZ52.TTC1)
                                                                                                                                Notify(\_SB_.TZ52, 0x81)
                                                                                                                            }
                                                                                                                            Return(\_SB_.TZ52._TC1())
                                                                                                                        }
                                                                                                                        Else
                                                                                                                        {
                                                                                                                            If(LEqual(_T_M, 0x4))
                                                                                                                            {
                                                                                                                                If(Arg2)
                                                                                                                                {
                                                                                                                                    Store(Arg1, \_SB_.TZ52.TTC2)
                                                                                                                                    Notify(\_SB_.TZ52, 0x81)
                                                                                                                                }
                                                                                                                                Return(\_SB_.TZ52._TC2())
                                                                                                                            }
                                                                                                                            Else
                                                                                                                            {
                                                                                                                                Return(0xffff)
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                                Break
                                                                                                            }
                                                                                                        }
                                                                                                        Else
                                                                                                        {
                                                                                                            If(LEqual(_T_0, 0x35))
                                                                                                            {
                                                                                                                While(One)
                                                                                                                {
                                                                                                                    Name(_T_N, Zero)
                                                                                                                    Store(ToInteger(Arg3, ), _T_N)
                                                                                                                    If(LEqual(_T_N, Zero))
                                                                                                                    {
                                                                                                                        If(Arg2)
                                                                                                                        {
                                                                                                                            Store(Arg1, \_SB_.TZ53.TPSV)
                                                                                                                            Notify(\_SB_.TZ53, 0x81)
                                                                                                                        }
                                                                                                                        Return(\_SB_.TZ53._PSV)
                                                                                                                    }
                                                                                                                    Else
                                                                                                                    {
                                                                                                                        If(LEqual(_T_N, 0x2))
                                                                                                                        {
                                                                                                                            If(Arg2)
                                                                                                                            {
                                                                                                                                Store(Arg1, \_SB_.TZ53.TTSP)
                                                                                                                                Notify(\_SB_.TZ53, 0x81)
                                                                                                                            }
                                                                                                                            Return(\_SB_.TZ53._TSP)
                                                                                                                        }
                                                                                                                        Else
                                                                                                                        {
                                                                                                                            If(LEqual(_T_N, 0x3))
                                                                                                                            {
                                                                                                                                If(Arg2)
                                                                                                                                {
                                                                                                                                    Store(Arg1, \_SB_.TZ53.TTC1)
                                                                                                                                    Notify(\_SB_.TZ53, 0x81)
                                                                                                                                }
                                                                                                                                Return(\_SB_.TZ53._TC1)
                                                                                                                            }
                                                                                                                            Else
                                                                                                                            {
                                                                                                                                If(LEqual(_T_N, 0x4))
                                                                                                                                {
                                                                                                                                    If(Arg2)
                                                                                                                                    {
                                                                                                                                        Store(Arg1, \_SB_.TZ53.TTC2)
                                                                                                                                        Notify(\_SB_.TZ53, 0x81)
                                                                                                                                    }
                                                                                                                                    Return(\_SB_.TZ53._TC2)
                                                                                                                                }
                                                                                                                                Else
                                                                                                                                {
                                                                                                                                    Return(0xffff)
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                    Break
                                                                                                                }
                                                                                                            }
                                                                                                            Else
                                                                                                            {
                                                                                                                If(LEqual(_T_0, 0x36))
                                                                                                                {
                                                                                                                    While(One)
                                                                                                                    {
                                                                                                                        Name(_T_O, Zero)
                                                                                                                        Store(ToInteger(Arg3, ), _T_O)
                                                                                                                        If(LEqual(_T_O, Zero))
                                                                                                                        {
                                                                                                                            If(Arg2)
                                                                                                                            {
                                                                                                                                Store(Arg1, \_SB_.TZ54.TPSV)
                                                                                                                                Notify(\_SB_.TZ54, 0x81)
                                                                                                                            }
                                                                                                                            Return(\_SB_.TZ54._PSV)
                                                                                                                        }
                                                                                                                        Else
                                                                                                                        {
                                                                                                                            If(LEqual(_T_O, 0x2))
                                                                                                                            {
                                                                                                                                If(Arg2)
                                                                                                                                {
                                                                                                                                    Store(Arg1, \_SB_.TZ54.TTSP)
                                                                                                                                    Notify(\_SB_.TZ54, 0x81)
                                                                                                                                }
                                                                                                                                Return(\_SB_.TZ54._TSP)
                                                                                                                            }
                                                                                                                            Else
                                                                                                                            {
                                                                                                                                If(LEqual(_T_O, 0x3))
                                                                                                                                {
                                                                                                                                    If(Arg2)
                                                                                                                                    {
                                                                                                                                        Store(Arg1, \_SB_.TZ54.TTC1)
                                                                                                                                        Notify(\_SB_.TZ54, 0x81)
                                                                                                                                    }
                                                                                                                                    Return(\_SB_.TZ54._TC1)
                                                                                                                                }
                                                                                                                                Else
                                                                                                                                {
                                                                                                                                    If(LEqual(_T_O, 0x4))
                                                                                                                                    {
                                                                                                                                        If(Arg2)
                                                                                                                                        {
                                                                                                                                            Store(Arg1, \_SB_.TZ54.TTC2)
                                                                                                                                            Notify(\_SB_.TZ54, 0x81)
                                                                                                                                        }
                                                                                                                                        Return(\_SB_.TZ54._TC2)
                                                                                                                                    }
                                                                                                                                    Else
                                                                                                                                    {
                                                                                                                                        Return(0xffff)
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                        Break
                                                                                                                    }
                                                                                                                }
                                                                                                                Else
                                                                                                                {
                                                                                                                    If(LEqual(_T_0, 0x37))
                                                                                                                    {
                                                                                                                        While(One)
                                                                                                                        {
                                                                                                                            Name(_T_P, Zero)
                                                                                                                            Store(ToInteger(Arg3, ), _T_P)
                                                                                                                            If(LEqual(_T_P, Zero))
                                                                                                                            {
                                                                                                                                If(Arg2)
                                                                                                                                {
                                                                                                                                    Store(Arg1, \_SB_.TZ55.TPSV)
                                                                                                                                    Notify(\_SB_.TZ55, 0x81)
                                                                                                                                }
                                                                                                                                Return(\_SB_.TZ55._PSV)
                                                                                                                            }
                                                                                                                            Else
                                                                                                                            {
                                                                                                                                If(LEqual(_T_P, 0x2))
                                                                                                                                {
                                                                                                                                    If(Arg2)
                                                                                                                                    {
                                                                                                                                        Store(Arg1, \_SB_.TZ55.TTSP)
                                                                                                                                        Notify(\_SB_.TZ55, 0x81)
                                                                                                                                    }
                                                                                                                                    Return(\_SB_.TZ55._TSP)
                                                                                                                                }
                                                                                                                                Else
                                                                                                                                {
                                                                                                                                    If(LEqual(_T_P, 0x3))
                                                                                                                                    {
                                                                                                                                        If(Arg2)
                                                                                                                                        {
                                                                                                                                            Store(Arg1, \_SB_.TZ55.TTC1)
                                                                                                                                            Notify(\_SB_.TZ55, 0x81)
                                                                                                                                        }
                                                                                                                                        Return(\_SB_.TZ55._TC1)
                                                                                                                                    }
                                                                                                                                    Else
                                                                                                                                    {
                                                                                                                                        If(LEqual(_T_P, 0x4))
                                                                                                                                        {
                                                                                                                                            If(Arg2)
                                                                                                                                            {
                                                                                                                                                Store(Arg1, \_SB_.TZ55.TTC2)
                                                                                                                                                Notify(\_SB_.TZ55, 0x81)
                                                                                                                                            }
                                                                                                                                            Return(\_SB_.TZ55._TC2)
                                                                                                                                        }
                                                                                                                                        Else
                                                                                                                                        {
                                                                                                                                            Return(0xffff)
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                            Break
                                                                                                                        }
                                                                                                                    }
                                                                                                                    Else
                                                                                                                    {
                                                                                                                        If(LEqual(_T_0, 0x38))
                                                                                                                        {
                                                                                                                            While(One)
                                                                                                                            {
                                                                                                                                Name(_T_Q, Zero)
                                                                                                                                Store(ToInteger(Arg3, ), _T_Q)
                                                                                                                                If(LEqual(_T_Q, Zero))
                                                                                                                                {
                                                                                                                                    If(Arg2)
                                                                                                                                    {
                                                                                                                                        Store(Arg1, \_SB_.TZ56.TPSV)
                                                                                                                                        Notify(\_SB_.TZ56, 0x81)
                                                                                                                                    }
                                                                                                                                    Return(\_SB_.TZ56._PSV)
                                                                                                                                }
                                                                                                                                Else
                                                                                                                                {
                                                                                                                                    If(LEqual(_T_Q, 0x2))
                                                                                                                                    {
                                                                                                                                        If(Arg2)
                                                                                                                                        {
                                                                                                                                            Store(Arg1, \_SB_.TZ56.TTSP)
                                                                                                                                            Notify(\_SB_.TZ56, 0x81)
                                                                                                                                        }
                                                                                                                                        Return(\_SB_.TZ56._TSP)
                                                                                                                                    }
                                                                                                                                    Else
                                                                                                                                    {
                                                                                                                                        If(LEqual(_T_Q, 0x3))
                                                                                                                                        {
                                                                                                                                            If(Arg2)
                                                                                                                                            {
                                                                                                                                                Store(Arg1, \_SB_.TZ56.TTC1)
                                                                                                                                                Notify(\_SB_.TZ56, 0x81)
                                                                                                                                            }
                                                                                                                                            Return(\_SB_.TZ56._TC1)
                                                                                                                                        }
                                                                                                                                        Else
                                                                                                                                        {
                                                                                                                                            If(LEqual(_T_Q, 0x4))
                                                                                                                                            {
                                                                                                                                                If(Arg2)
                                                                                                                                                {
                                                                                                                                                    Store(Arg1, \_SB_.TZ56.TTC2)
                                                                                                                                                    Notify(\_SB_.TZ56, 0x81)
                                                                                                                                                }
                                                                                                                                                Return(\_SB_.TZ56._TC2)
                                                                                                                                            }
                                                                                                                                            Else
                                                                                                                                            {
                                                                                                                                                Return(0xffff)
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                                Break
                                                                                                                            }
                                                                                                                        }
                                                                                                                        Else
                                                                                                                        {
                                                                                                                            If(LEqual(_T_0, 0x39))
                                                                                                                            {
                                                                                                                                While(One)
                                                                                                                                {
                                                                                                                                    Name(_T_R, Zero)
                                                                                                                                    Store(ToInteger(Arg3, ), _T_R)
                                                                                                                                    If(LEqual(_T_R, Zero))
                                                                                                                                    {
                                                                                                                                        If(Arg2)
                                                                                                                                        {
                                                                                                                                            Store(Arg1, \_SB_.TZ57.TPSV)
                                                                                                                                            Notify(\_SB_.TZ57, 0x81)
                                                                                                                                        }
                                                                                                                                        Return(\_SB_.TZ57._PSV())
                                                                                                                                    }
                                                                                                                                    Else
                                                                                                                                    {
                                                                                                                                        If(LEqual(_T_R, 0x2))
                                                                                                                                        {
                                                                                                                                            If(Arg2)
                                                                                                                                            {
                                                                                                                                                Store(Arg1, \_SB_.TZ57.TTSP)
                                                                                                                                                Notify(\_SB_.TZ57, 0x81)
                                                                                                                                            }
                                                                                                                                            Return(\_SB_.TZ57._TSP())
                                                                                                                                        }
                                                                                                                                        Else
                                                                                                                                        {
                                                                                                                                            If(LEqual(_T_R, 0x3))
                                                                                                                                            {
                                                                                                                                                If(Arg2)
                                                                                                                                                {
                                                                                                                                                    Store(Arg1, \_SB_.TZ57.TTC1)
                                                                                                                                                    Notify(\_SB_.TZ57, 0x81)
                                                                                                                                                }
                                                                                                                                                Return(\_SB_.TZ57._TC1())
                                                                                                                                            }
                                                                                                                                            Else
                                                                                                                                            {
                                                                                                                                                If(LEqual(_T_R, 0x4))
                                                                                                                                                {
                                                                                                                                                    If(Arg2)
                                                                                                                                                    {
                                                                                                                                                        Store(Arg1, \_SB_.TZ57.TTC2)
                                                                                                                                                        Notify(\_SB_.TZ57, 0x81)
                                                                                                                                                    }
                                                                                                                                                    Return(\_SB_.TZ57._TC2())
                                                                                                                                                }
                                                                                                                                                Else
                                                                                                                                                {
                                                                                                                                                    Return(0xffff)
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    Break
                                                                                                                                }
                                                                                                                            }
                                                                                                                            Else
                                                                                                                            {
                                                                                                                                If(LEqual(_T_0, 0x3a))
                                                                                                                                {
                                                                                                                                    While(One)
                                                                                                                                    {
                                                                                                                                        Name(_T_S, Zero)
                                                                                                                                        Store(ToInteger(Arg3, ), _T_S)
                                                                                                                                        If(LEqual(_T_S, Zero))
                                                                                                                                        {
                                                                                                                                            If(Arg2)
                                                                                                                                            {
                                                                                                                                                Store(Arg1, \_SB_.TZ58.TPSV)
                                                                                                                                                Notify(\_SB_.TZ58, 0x81)
                                                                                                                                            }
                                                                                                                                            Return(\_SB_.TZ58._PSV())
                                                                                                                                        }
                                                                                                                                        Else
                                                                                                                                        {
                                                                                                                                            If(LEqual(_T_S, 0x2))
                                                                                                                                            {
                                                                                                                                                If(Arg2)
                                                                                                                                                {
                                                                                                                                                    Store(Arg1, \_SB_.TZ58.TTSP)
                                                                                                                                                    Notify(\_SB_.TZ58, 0x81)
                                                                                                                                                }
                                                                                                                                                Return(\_SB_.TZ58._TSP())
                                                                                                                                            }
                                                                                                                                            Else
                                                                                                                                            {
                                                                                                                                                If(LEqual(_T_S, 0x3))
                                                                                                                                                {
                                                                                                                                                    If(Arg2)
                                                                                                                                                    {
                                                                                                                                                        Store(Arg1, \_SB_.TZ58.TTC1)
                                                                                                                                                        Notify(\_SB_.TZ58, 0x81)
                                                                                                                                                    }
                                                                                                                                                    Return(\_SB_.TZ58._TC1())
                                                                                                                                                }
                                                                                                                                                Else
                                                                                                                                                {
                                                                                                                                                    If(LEqual(_T_S, 0x4))
                                                                                                                                                    {
                                                                                                                                                        If(Arg2)
                                                                                                                                                        {
                                                                                                                                                            Store(Arg1, \_SB_.TZ58.TTC2)
                                                                                                                                                            Notify(\_SB_.TZ58, 0x81)
                                                                                                                                                        }
                                                                                                                                                        Return(\_SB_.TZ58._TC2())
                                                                                                                                                    }
                                                                                                                                                    Else
                                                                                                                                                    {
                                                                                                                                                        Return(0xffff)
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        Break
                                                                                                                                    }
                                                                                                                                }
                                                                                                                                Else
                                                                                                                                {
                                                                                                                                    If(LEqual(_T_0, 0x3b))
                                                                                                                                    {
                                                                                                                                        While(One)
                                                                                                                                        {
                                                                                                                                            Name(_T_T, Zero)
                                                                                                                                            Store(ToInteger(Arg3, ), _T_T)
                                                                                                                                            If(LEqual(_T_T, Zero))
                                                                                                                                            {
                                                                                                                                                If(Arg2)
                                                                                                                                                {
                                                                                                                                                    Store(Arg1, \_SB_.TZ59.TPSV)
                                                                                                                                                    Notify(\_SB_.TZ59, 0x81)
                                                                                                                                                }
                                                                                                                                                Return(\_SB_.TZ59._PSV())
                                                                                                                                            }
                                                                                                                                            Else
                                                                                                                                            {
                                                                                                                                                If(LEqual(_T_T, 0x2))
                                                                                                                                                {
                                                                                                                                                    If(Arg2)
                                                                                                                                                    {
                                                                                                                                                        Store(Arg1, \_SB_.TZ59.TTSP)
                                                                                                                                                        Notify(\_SB_.TZ59, 0x81)
                                                                                                                                                    }
                                                                                                                                                    Return(\_SB_.TZ59._TSP())
                                                                                                                                                }
                                                                                                                                                Else
                                                                                                                                                {
                                                                                                                                                    If(LEqual(_T_T, 0x3))
                                                                                                                                                    {
                                                                                                                                                        If(Arg2)
                                                                                                                                                        {
                                                                                                                                                            Store(Arg1, \_SB_.TZ59.TTC1)
                                                                                                                                                            Notify(\_SB_.TZ59, 0x81)
                                                                                                                                                        }
                                                                                                                                                        Return(\_SB_.TZ59._TC1())
                                                                                                                                                    }
                                                                                                                                                    Else
                                                                                                                                                    {
                                                                                                                                                        If(LEqual(_T_T, 0x4))
                                                                                                                                                        {
                                                                                                                                                            If(Arg2)
                                                                                                                                                            {
                                                                                                                                                                Store(Arg1, \_SB_.TZ59.TTC2)
                                                                                                                                                                Notify(\_SB_.TZ59, 0x81)
                                                                                                                                                            }
                                                                                                                                                            Return(\_SB_.TZ59._TC2())
                                                                                                                                                        }
                                                                                                                                                        Else
                                                                                                                                                        {
                                                                                                                                                            Return(0xffff)
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            Break
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    Else
                                                                                                                                    {
                                                                                                                                        If(LEqual(_T_0, 0x3c))
                                                                                                                                        {
                                                                                                                                            While(One)
                                                                                                                                            {
                                                                                                                                                Name(_T_U, Zero)
                                                                                                                                                Store(ToInteger(Arg3, ), _T_U)
                                                                                                                                                If(LEqual(_T_U, Zero))
                                                                                                                                                {
                                                                                                                                                    If(Arg2)
                                                                                                                                                    {
                                                                                                                                                        Store(Arg1, \_SB_.TZ60.TPSV)
                                                                                                                                                        Notify(\_SB_.TZ60, 0x81)
                                                                                                                                                    }
                                                                                                                                                    Return(\_SB_.TZ60._PSV)
                                                                                                                                                }
                                                                                                                                                Else
                                                                                                                                                {
                                                                                                                                                    If(LEqual(_T_U, 0x2))
                                                                                                                                                    {
                                                                                                                                                        If(Arg2)
                                                                                                                                                        {
                                                                                                                                                            Store(Arg1, \_SB_.TZ60.TTSP)
                                                                                                                                                            Notify(\_SB_.TZ60, 0x81)
                                                                                                                                                        }
                                                                                                                                                        Return(\_SB_.TZ60._TSP)
                                                                                                                                                    }
                                                                                                                                                    Else
                                                                                                                                                    {
                                                                                                                                                        If(LEqual(_T_U, 0x3))
                                                                                                                                                        {
                                                                                                                                                            If(Arg2)
                                                                                                                                                            {
                                                                                                                                                                Store(Arg1, \_SB_.TZ60.TTC1)
                                                                                                                                                                Notify(\_SB_.TZ60, 0x81)
                                                                                                                                                            }
                                                                                                                                                            Return(\_SB_.TZ60._TC1)
                                                                                                                                                        }
                                                                                                                                                        Else
                                                                                                                                                        {
                                                                                                                                                            If(LEqual(_T_U, 0x4))
                                                                                                                                                            {
                                                                                                                                                                If(Arg2)
                                                                                                                                                                {
                                                                                                                                                                    Store(Arg1, \_SB_.TZ60.TTC2)
                                                                                                                                                                    Notify(\_SB_.TZ60, 0x81)
                                                                                                                                                                }
                                                                                                                                                                Return(\_SB_.TZ60._TC2)
                                                                                                                                                            }
                                                                                                                                                            Else
                                                                                                                                                            {
                                                                                                                                                                Return(0xffff)
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                Break
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        Else
                                                                                                                                        {
                                                                                                                                            If(LEqual(_T_0, 0x3d))
                                                                                                                                            {
                                                                                                                                                While(One)
                                                                                                                                                {
                                                                                                                                                    Name(_T_V, Zero)
                                                                                                                                                    Store(ToInteger(Arg3, ), _T_V)
                                                                                                                                                    If(LEqual(_T_V, Zero))
                                                                                                                                                    {
                                                                                                                                                        If(Arg2)
                                                                                                                                                        {
                                                                                                                                                            Store(Arg1, \_SB_.TZ61.TPSV)
                                                                                                                                                            Notify(\_SB_.TZ61, 0x81)
                                                                                                                                                        }
                                                                                                                                                        Return(\_SB_.TZ61._PSV)
                                                                                                                                                    }
                                                                                                                                                    Else
                                                                                                                                                    {
                                                                                                                                                        If(LEqual(_T_V, 0x2))
                                                                                                                                                        {
                                                                                                                                                            If(Arg2)
                                                                                                                                                            {
                                                                                                                                                                Store(Arg1, \_SB_.TZ61.TTSP)
                                                                                                                                                                Notify(\_SB_.TZ61, 0x81)
                                                                                                                                                            }
                                                                                                                                                            Return(\_SB_.TZ61._TSP)
                                                                                                                                                        }
                                                                                                                                                        Else
                                                                                                                                                        {
                                                                                                                                                            If(LEqual(_T_V, 0x3))
                                                                                                                                                            {
                                                                                                                                                                If(Arg2)
                                                                                                                                                                {
                                                                                                                                                                    Store(Arg1, \_SB_.TZ61.TTC1)
                                                                                                                                                                    Notify(\_SB_.TZ61, 0x81)
                                                                                                                                                                }
                                                                                                                                                                Return(\_SB_.TZ61._TC1)
                                                                                                                                                            }
                                                                                                                                                            Else
                                                                                                                                                            {
                                                                                                                                                                If(LEqual(_T_V, 0x4))
                                                                                                                                                                {
                                                                                                                                                                    If(Arg2)
                                                                                                                                                                    {
                                                                                                                                                                        Store(Arg1, \_SB_.TZ61.TTC2)
                                                                                                                                                                        Notify(\_SB_.TZ61, 0x81)
                                                                                                                                                                    }
                                                                                                                                                                    Return(\_SB_.TZ61._TC2)
                                                                                                                                                                }
                                                                                                                                                                Else
                                                                                                                                                                {
                                                                                                                                                                    Return(0xffff)
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                    Break
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            Else
                                                                                                                                            {
                                                                                                                                                If(LEqual(_T_0, 0x3e))
                                                                                                                                                {
                                                                                                                                                    While(One)
                                                                                                                                                    {
                                                                                                                                                        Name(_T_W, Zero)
                                                                                                                                                        Store(ToInteger(Arg3, ), _T_W)
                                                                                                                                                        If(LEqual(_T_W, Zero))
                                                                                                                                                        {
                                                                                                                                                            If(Arg2)
                                                                                                                                                            {
                                                                                                                                                                Store(Arg1, \_SB_.TZ62.TPSV)
                                                                                                                                                                Notify(\_SB_.TZ62, 0x81)
                                                                                                                                                            }
                                                                                                                                                            Return(\_SB_.TZ62._PSV)
                                                                                                                                                        }
                                                                                                                                                        Else
                                                                                                                                                        {
                                                                                                                                                            If(LEqual(_T_W, 0x2))
                                                                                                                                                            {
                                                                                                                                                                If(Arg2)
                                                                                                                                                                {
                                                                                                                                                                    Store(Arg1, \_SB_.TZ62.TTSP)
                                                                                                                                                                    Notify(\_SB_.TZ62, 0x81)
                                                                                                                                                                }
                                                                                                                                                                Return(\_SB_.TZ62._TSP)
                                                                                                                                                            }
                                                                                                                                                            Else
                                                                                                                                                            {
                                                                                                                                                                If(LEqual(_T_W, 0x3))
                                                                                                                                                                {
                                                                                                                                                                    If(Arg2)
                                                                                                                                                                    {
                                                                                                                                                                        Store(Arg1, \_SB_.TZ62.TTC1)
                                                                                                                                                                        Notify(\_SB_.TZ62, 0x81)
                                                                                                                                                                    }
                                                                                                                                                                    Return(\_SB_.TZ62._TC1)
                                                                                                                                                                }
                                                                                                                                                                Else
                                                                                                                                                                {
                                                                                                                                                                    If(LEqual(_T_W, 0x4))
                                                                                                                                                                    {
                                                                                                                                                                        If(Arg2)
                                                                                                                                                                        {
                                                                                                                                                                            Store(Arg1, \_SB_.TZ62.TTC2)
                                                                                                                                                                            Notify(\_SB_.TZ62, 0x81)
                                                                                                                                                                        }
                                                                                                                                                                        Return(\_SB_.TZ62._TC2)
                                                                                                                                                                    }
                                                                                                                                                                    Else
                                                                                                                                                                    {
                                                                                                                                                                        Return(0xffff)
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                        Break
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                Else
                                                                                                                                                {
                                                                                                                                                    Return(0xffff)
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Break
                }
            }
            Name(_DEP, Package(One)
            {
                \_SB_.IPCC
            })
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LOr(LEqual(\_SB_.SJTG, 0x1940e1), LEqual(\_SB_.SJTG, 0x101940e1)))
                {
                    If(LEqual(\_SB_.PSUB, "IDP07280"))
                    {
                        Return("IDP07295")
                    }
                    Else
                    {
                        If(LEqual(\_SB_.PSUB, "CRD07280"))
                        {
                            Return("CRD07295")
                        }
                    }
                }
                Else
                {
                    If(LOr(LEqual(\_SB_.SJTG, 0x101930e1), LEqual(\_SB_.SJTG, 0x1eb0e1)))
                    {
                        If(LEqual(\_SB_.PSUB, "IDP07280"))
                        {
                            Return("IDP07280")
                        }
                        Else
                        {
                            If(LEqual(\_SB_.PSUB, "CRD07280"))
                            {
                                Return("CRD07280")
                            }
                        }
                    }
                    Else
                    {
                        If(LOr(LEqual(\_SB_.SJTG, 0x101e30e1), LEqual(\_SB_.SJTG, 0x1020a0e1)))
                        {
                            If(LEqual(\_SB_.PSUB, "IDP07280"))
                            {
                                Return("IDP08270")
                            }
                            Else
                            {
                                If(LEqual(\_SB_.PSUB, "CRD07280"))
                                {
                                    Return("CRD08270")
                                }
                            }
                        }
                    }
                }
            }
            Method(_DSM, 0x4, NotSerialized)
            {
                While(One)
                {
                    Name(_T_0, Buffer(One)
                    {
	0x00
                    })
                    CopyObject(ToBuffer(Arg0, ), _T_0)
                    If(LEqual(_T_0, Buffer(0x10)
                    {
	0x4c, 0xa3, 0x5c, 0x8d, 0x83, 0xae, 0x2a, 0x4a, 0x9d, 0xd1, 0xa7, 0x4f,
	0xfe, 0xad, 0x54, 0x8b
                    }))
                    {
                        While(One)
                        {
                            Name(_T_1, Zero)
                            Store(ToInteger(Arg2, ), _T_1)
                            If(LEqual(_T_1, Zero))
                            {
                                While(One)
                                {
                                    Name(_T_2, Zero)
                                    Store(ToInteger(Arg1, ), _T_2)
                                    If(LEqual(_T_2, Zero))
                                    {
                                        Return(0x7e)
                                    }
                                    Break
                                }
                                Return(Zero)
                            }
                            Else
                            {
                                If(LEqual(_T_1, One))
                                {
                                    Name(SUBI, Package(0x6)
                                    {
                                        Package(0x3)
                                        {
                                            "adsp",
                                            One,
                                            0x2
                                        },
                                        Package(0x3)
                                        {
                                            "slpi",
                                            Zero,
                                            0x3
                                        },
                                        Package(0x3)
                                        {
                                            "cdsp",
                                            One,
                                            0x4
                                        },
                                        Package(0x3)
                                        {
                                            "modem",
                                            One,
                                            0x5
                                        },
                                        Package(0x3)
                                        {
                                            "spss",
                                            Zero,
                                            0x6
                                        },
                                        Package(0x3)
                                        {
                                            "wpss",
                                            One,
                                            0x7
                                        }
                                    })
                                    Return(SUBI)
                                }
                                Else
                                {
                                    If(LEqual(_T_1, 0x2))
                                    {
                                        If(CondRefOf(\_SB_.ADSP, ))
                                        {
                                            If(CondRefOf(\_SB_.ADSP._STA, ))
                                            {
                                                Return(\_SB_.ADSP._STA())
                                            }
                                            Else
                                            {
                                                Return(0xf)
                                            }
                                        }
                                        Else
                                        {
                                            Return(Zero)
                                        }
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_1, 0x3))
                                        {
                                            If(CondRefOf(\_SB_.SCSS, ))
                                            {
                                                If(CondRefOf(\_SB_.SCSS._STA, ))
                                                {
                                                    Return(\_SB_.SCSS._STA)
                                                }
                                                Else
                                                {
                                                    Return(0xf)
                                                }
                                            }
                                            Else
                                            {
                                                Return(Zero)
                                            }
                                        }
                                        Else
                                        {
                                            If(LEqual(_T_1, 0x4))
                                            {
                                                If(CondRefOf(\_SB_.NSP0, ))
                                                {
                                                    If(CondRefOf(\_SB_.NSP0._STA, ))
                                                    {
                                                        Return(\_SB_.NSP0._STA())
                                                    }
                                                    Else
                                                    {
                                                        Return(0xf)
                                                    }
                                                }
                                                Else
                                                {
                                                    Return(Zero)
                                                }
                                            }
                                            Else
                                            {
                                                If(LEqual(_T_1, 0x5))
                                                {
                                                    If(CondRefOf(\_SB_.AMSS, ))
                                                    {
                                                        If(CondRefOf(\_SB_.AMSS._STA, ))
                                                        {
                                                            Return(\_SB_.AMSS._STA())
                                                        }
                                                        Else
                                                        {
                                                            Return(0xf)
                                                        }
                                                    }
                                                    Else
                                                    {
                                                        Return(Zero)
                                                    }
                                                }
                                                Else
                                                {
                                                    If(LEqual(_T_1, 0x6))
                                                    {
                                                        If(CondRefOf(\_SB_.SPSS, ))
                                                        {
                                                            If(CondRefOf(\_SB_.SPSS._STA, ))
                                                            {
                                                                Return(\_SB_.SPSS._STA)
                                                            }
                                                            Else
                                                            {
                                                                Return(0xf)
                                                            }
                                                        }
                                                        Else
                                                        {
                                                            Return(Zero)
                                                        }
                                                    }
                                                    Else
                                                    {
                                                        If(LEqual(_T_1, 0x7))
                                                        {
                                                            If(CondRefOf(\_SB_.WPSS, ))
                                                            {
                                                                If(CondRefOf(\_SB_.WPSS._STA, ))
                                                                {
                                                                    Return(\_SB_.WPSS._STA())
                                                                }
                                                                Else
                                                                {
                                                                    Return(0xf)
                                                                }
                                                            }
                                                            Else
                                                            {
                                                                Return(Zero)
                                                            }
                                                        }
                                                        Else
                                                        {
                                                            Return(Zero)
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            Break
                        }
                    }
                    Else
                    {
                        Return(Zero)
                    }
                    Break
                }
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Return(Buffer(0x65)
                {
	0x89, 0x06, 0x00, 0x11, 0x01, 0x1a, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x11, 0x01, 0x1c, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x11, 0x01, 0x1b,
	0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x11, 0x01, 0x1d, 0x02, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x25, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x01, 0x01, 0x3e, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x01, 0x01, 0x3f,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x01, 0x01, 0x33, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x65, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x0d, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x13,
	0x01, 0x00, 0x00, 0x79, 0x00
                })
            }
            Field(\_SB_.ABD_.ROP1, BufferAcc, NoLock, Preserve)
            {
                Connection(
                    I2CSerialBus(0x1, ControllerInitiated, 0, AddressingMode7Bit, "\\_SB.ABD", 0, ResourceConsumer, , )
                ),
                AccessAs(BufferAcc, AttribRawBytes(21)),
                FLD0, 168
            }
            Method(GEPT, 0x0, NotSerialized)
            {
                Name(BUFF, Buffer(0x4)
                {
                })
                CreateByteField(BUFF, Zero, STAT)
                CreateWordField(BUFF, 0x2, DATA)
                Store(One, DATA)
                Return(DATA)
            }
            Name(ROST, Zero)
            Method(NPUR, 0x1, NotSerialized)
            {
                Store(Arg0, Index(\_SB_.AGR0._PUR, One, ))
                Notify(\_SB_.AGR0, 0x80)
            }
            Method(INTR, 0x0, NotSerialized)
            {
                Name(RBUF, Package(0x18)
                {
                    0x2,
                    One,
                    0x3,
                    One,
                    0x6,
                    0x17911008,
                    One,
                    Zero,
                    0x86000000,
                    0x200000,
                    Zero,
                    Zero,
                    0xc300000,
                    0x1000,
                    Zero,
                    Zero,
                    0x1fd4000,
                    0x8,
                    Zero,
                    Zero,
                    0x17c0000c,
                    Zero,
                    Zero,
                    Zero
                })
                Return(RBUF)
            }
            Method(STND, 0x0, NotSerialized)
            {
                Return(STNX)
            }
            Name(STNX, Package(0xb)
            {
                "DMPO",
                "MMVD",
                "DMSB",
                "DMPA",
                "DMPB",
                "DMDS",
                "DMPL",
                "DMWE",
                "XMPL",
                "XMPT",
                "DMEP"
            })
            Name(DCVS, Zero)
            Method(PGDS, 0x0, NotSerialized)
            {
                Return(DCVS)
            }
            Name(PPPP, Package(0x37)
            {
                Package(One)
                {
                    "PPP_RESOURCE_ID_SMPS1_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_SMPS2_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_SMPS7_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_SMPS8_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_SMPS1_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_SMPS9_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO1_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO2_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO3_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO6_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO7_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO8_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO9_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO11_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO12_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO13_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO14_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO15_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO16_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO17_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO18_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO19_B"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO1_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO2_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO3_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO4_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO5_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO6_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO7_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO8_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO9_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO10_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO11_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO12_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO13_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO1_P"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO2_P"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO3_P"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO4_P"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO5_P"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO6_P"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO7_P"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO1_Q"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO2_Q"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO3_Q"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO4_Q"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO5_Q"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO6_Q"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_LDO7_Q"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_CXO_BUFFERS_BBCLK2_A"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_CXO_BUFFERS_RFCLK1_A"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_CXO_BUFFERS_RFCLK2_A"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_BUCK_BOOST1_C"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_FIXED_VREG1"
                },
                Package(One)
                {
                    "PPP_RESOURCE_ID_FIXED_VREG2"
                }
            })
            Method(PPPM, 0x0, NotSerialized)
            {
                Return(PPPP)
            }
            Name(PRRP, Package(Zero)
            {
            })
            Method(PPRR, 0x0, NotSerialized)
            {
                Return(PRRP)
            }
            Name(FPDP, Zero)
            Method(FPMD, 0x0, NotSerialized)
            {
                Return(FPDP)
            }
            Method(DPRF, 0x0, NotSerialized)
            {
                Return(\_SB_.DPP0)
            }
            Method(DMRF, 0x0, NotSerialized)
            {
                Return(\_SB_.DPP1)
            }
            Method(MPRF, 0x0, NotSerialized)
            {
                Return(\_SB_.MPP0)
            }
            Method(MMRF, 0x0, NotSerialized)
            {
                Return(\_SB_.MPP1)
            }
        }
        Scope(\_SB_.PEP0)
        {
            Method(PEPH, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    "ACPI\\VEN_QCOM&DEV_0A17"
                })
            }
        }
        Scope(\_SB_.PEP0)
        {
            Method(APMD, 0x0, NotSerialized)
            {
                Return(APCC)
            }
            Name(APCC, Package(One)
            {
                Package(0x6)
                {
                    "DEVICE",
                    "\\_SB.ADSP.ADCM.AUCD.QCRT",
                    Package(0x3)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        }
                    },
                    Package(0x3)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_xo",
                                0x80
                            }
                        }
                    },
                    Package(0x3)
                    {
                        "DSTATE",
                        One,
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_xo",
                                Zero
                            }
                        }
                    },
                    Package(0x3)
                    {
                        "DSTATE",
                        0x2,
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_xo",
                                Zero
                            }
                        }
                    }
                }
            })
        }
        Scope(\_SB_.PEP0)
        {
            Method(PREL, 0x0, NotSerialized)
            {
                Name(PREX, Package(0x3)
                {
                    "DM0G",
                    "DM4G",
                    "DM5G"
                })
                Return(PREX)
            }
            Method(G0MD, 0x0, NotSerialized)
            {
                Name(GPCC, Package(One)
                {
                    Package(0x4)
                    {
                        "DEVICE",
                        0x82,
                        "\\_SB.GPU0",
                        Package(0xb)
                        {
                            "COMPONENT",
                            Zero,
                            Package(0x3)
                            {
                                "FSTATE",
                                Zero,
                                Package(0x1a)
                                {
                                    "EXIT",
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_xo_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_xo_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "dsi_phy_refgen_en",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "FOOTSWITCH",
                                        Package(0x3)
                                        {
                                            "disp_cc_mdss_core_gdsc",
                                            One,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_EBI1",
                                            0x2faf0800,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_hf_axi_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_pclk0_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_esc0_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_byte0_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_byte0_intf_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x4)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            0x3,
                                            0x16a65700,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO6_B",
                                            One,
                                            0x124f80,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO10_C",
                                            One,
                                            0xd6d80,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO8_C",
                                            One,
                                            0x1b7740,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO12_C",
                                            One,
                                            0x1b7740,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "TLMMGPIO",
                                        Package(0x6)
                                        {
                                            0x50,
                                            One,
                                            One,
                                            Zero,
                                            Zero,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "TLMMGPIO",
                                        Package(0x6)
                                        {
                                            0x51,
                                            One,
                                            Zero,
                                            One,
                                            Zero,
                                            Zero
                                        }
                                    }
                                }
                            },
                            Package(0x2)
                            {
                                "FSTATE",
                                One
                            },
                            Package(0x2)
                            {
                                "INIT_FSTATE",
                                Zero
                            },
                            Package(0x2)
                            {
                                "PRELOAD_FSTATE",
                                One
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                Zero,
                                Package(0x2)
                                {
                                    "PSTATE",
                                    Zero
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                One,
                                Package(0xd)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_EBI1",
                                            0x2faf0800,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_hf_axi_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_pclk0_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_esc0_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_byte0_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_byte0_intf_clk",
                                            One
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x2,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x4)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            0x3,
                                            0x16a65700,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x3,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_MNOC_HF_MEM_NOC",
                                            Zero,
                                            0x77359400
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MNOC_HF_MEM_NOC",
                                            "ICBID_SLAVE_EBI1",
                                            Zero,
                                            0x77359400
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x4,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_MNOC_HF_MEM_NOC",
                                            Zero,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MNOC_HF_MEM_NOC",
                                            "ICBID_SLAVE_EBI1",
                                            0x2faf0800,
                                            Zero
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            }
                        }
                    }
                })
                Return(GPCC)
            }
            Method(G4MD, 0x0, NotSerialized)
            {
                Name(GPCC, Package(One)
                {
                    Package(0x4)
                    {
                        "DEVICE",
                        0x82,
                        "\\_SB.GPU0",
                        Package(0xb)
                        {
                            "COMPONENT",
                            0x4,
                            Package(0x3)
                            {
                                "FSTATE",
                                Zero,
                                Package(0x16)
                                {
                                    "EXIT",
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_xo_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_xo_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "FOOTSWITCH",
                                        Package(0x3)
                                        {
                                            "disp_cc_mdss_core_gdsc",
                                            One,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_EBI1",
                                            0x2faf0800,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_hf_axi_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_aux_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_pixel_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_link_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_link_intf_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x4)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            0x3,
                                            0x16a65700,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    },
                                    Package(0x3)
                                    {
                                        "TLMMGPIO_V2",
                                        One,
                                        Package(0x6)
                                        {
                                            0x3c,
                                            Zero,
                                            One,
                                            Zero,
                                            Zero,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO10_C",
                                            One,
                                            0xd6d80,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO6_B",
                                            One,
                                            0x124f80,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    }
                                }
                            },
                            Package(0x2)
                            {
                                "FSTATE",
                                One
                            },
                            Package(0x2)
                            {
                                "INIT_FSTATE",
                                Zero
                            },
                            Package(0x2)
                            {
                                "PRELOAD_FSTATE",
                                One
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                Zero,
                                Package(0x2)
                                {
                                    "PSTATE",
                                    Zero
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                One,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x4)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            0x3,
                                            0x16a65700,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x2,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_MNOC_HF_MEM_NOC",
                                            Zero,
                                            0x77359400
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MNOC_HF_MEM_NOC",
                                            "ICBID_SLAVE_EBI1",
                                            Zero,
                                            0x77359400
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x3,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_MNOC_HF_MEM_NOC",
                                            Zero,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MNOC_HF_MEM_NOC",
                                            "ICBID_SLAVE_EBI1",
                                            0x2faf0800,
                                            Zero
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x4,
                                Package(0x6)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_aux_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_pixel_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_link_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_edp_link_intf_clk",
                                            One
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            }
                        }
                    }
                })
                Return(GPCC)
            }
            Method(G5MD, 0x0, NotSerialized)
            {
                Name(GPCC, Package(One)
                {
                    Package(0x4)
                    {
                        "DEVICE",
                        0x82,
                        "\\_SB.GPU0",
                        Package(0xb)
                        {
                            "COMPONENT",
                            0x5,
                            Package(0x3)
                            {
                                "FSTATE",
                                Zero,
                                Package(0x1c)
                                {
                                    "EXIT",
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_xo_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_xo_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "FOOTSWITCH",
                                        Package(0x3)
                                        {
                                            "disp_cc_mdss_core_gdsc",
                                            One,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_EBI1",
                                            0x2faf0800,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_disp_hf_axi_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_usb3_prim_phy_pipe_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_usb30_prim_sleep_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_usb3_prim_phy_aux_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "gcc_usb3_prim_phy_com_aux_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_rscc_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_ahb_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_vsync_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_aux_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_pixel_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_link_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_link_intf_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x4)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            0x3,
                                            0x16a65700,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO6_B",
                                            One,
                                            0x124f80,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO1_B",
                                            One,
                                            0xd6d80,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO1_C",
                                            One,
                                            0x1b7740,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO2_B",
                                            One,
                                            0x2ee000,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "PMICVREGVOTE",
                                        Package(0x8)
                                        {
                                            "PPP_RESOURCE_ID_LDO10_C",
                                            One,
                                            0xd6d80,
                                            One,
                                            0x7,
                                            Zero,
                                            "HLOS_DRV",
                                            "REQUIRED"
                                        }
                                    }
                                }
                            },
                            Package(0x2)
                            {
                                "FSTATE",
                                One
                            },
                            Package(0x2)
                            {
                                "INIT_FSTATE",
                                Zero
                            },
                            Package(0x2)
                            {
                                "PRELOAD_FSTATE",
                                One
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                Zero,
                                Package(0x2)
                                {
                                    "PSTATE",
                                    Zero
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                One,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x4)
                                        {
                                            "disp_cc_mdss_mdp_clk",
                                            0x3,
                                            0x16a65700,
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_APPSS_PROC",
                                            "ICBID_SLAVE_DISPLAY_CFG",
                                            0x47868c0,
                                            Zero
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x2,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_MNOC_HF_MEM_NOC",
                                            Zero,
                                            0x77359400
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MNOC_HF_MEM_NOC",
                                            "ICBID_SLAVE_EBI1",
                                            Zero,
                                            0x77359400
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x3,
                                Package(0x4)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MDP0",
                                            "ICBID_SLAVE_MNOC_HF_MEM_NOC",
                                            Zero,
                                            Zero
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "BUSARB",
                                        Package(0x5)
                                        {
                                            0x3,
                                            "ICBID_MASTER_MNOC_HF_MEM_NOC",
                                            "ICBID_SLAVE_EBI1",
                                            0x2faf0800,
                                            Zero
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE_SET",
                                0x4,
                                Package(0x6)
                                {
                                    "PSTATE",
                                    Zero,
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_aux_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_pixel_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_link_clk",
                                            One
                                        }
                                    },
                                    Package(0x2)
                                    {
                                        "CLOCK",
                                        Package(0x2)
                                        {
                                            "disp_cc_mdss_dp_link_intf_clk",
                                            One
                                        }
                                    }
                                },
                                Package(0x2)
                                {
                                    "PRELOAD_PSTATE",
                                    Zero
                                }
                            }
                        }
                    }
                })
                Return(GPCC)
            }
        }
        Scope(\_SB_.PEP0)
        {
            Method(MPMD, 0x0, NotSerialized)
            {
                Return(MPCC)
            }
            Name(MPCC, Package(Zero)
            {
            })
        }
        Scope(\_SB_.PEP0)
        {
            Method(OPMD, 0x0, NotSerialized)
            {
                Return(OPCC)
            }
            Name(OPCC, Package(Zero)
            {
            })
        }
        Scope(\_SB_.PEP0)
        {
            Method(LPMD, 0x0, NotSerialized)
            {
                Return(LPCC)
            }
            Name(LPCC, Package(0x5)
            {
                Package(0x7)
                {
                    "DEVICE",
                    "\\_SB.URS0",
                    Package(0x5)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "PSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "PSTATE",
                            One
                        }
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        Zero
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        One
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x2
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x3
                    }
                },
                Package(0x8)
                {
                    "DEVICE",
                    "\\_SB.URS0.USB0",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "PSTATE",
                            Zero
                        }
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_sleep_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                0x100
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                0x28000000,
                                0x28000000
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                0xbebc200,
                                Zero
                            }
                        }
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        One,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x2580,
                                0x5
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        0x2,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x14)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_sleep_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "ABANDON_DSTATE",
                        0x3
                    }
                },
                Package(0x8)
                {
                    "DEVICE",
                    "\\_SB.USB0",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "PSTATE",
                            Zero
                        }
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_sleep_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                0x100
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                0x28000000,
                                0x28000000
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                0xbebc200,
                                Zero
                            }
                        }
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        One,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x2580,
                                0x5
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        0x2,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x14)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_sleep_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "ABANDON_DSTATE",
                        0x3
                    }
                },
                Package(0x8)
                {
                    "DEVICE",
                    "\\_SB.URS0.UFN0",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "PSTATE",
                            Zero
                        }
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_sleep_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x8,
                                0xc8,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                0x100
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                0x28000000,
                                0x28000000
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                0xbebc200,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        One
                    },
                    Package(0x13)
                    {
                        "DSTATE",
                        0x2,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                0xdea80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x14)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_sleep_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_prim_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb3_prim_phy_com_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB3_0",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB3_0",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_prim_gdsc",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "ABANDON_DSTATE",
                        0x3
                    }
                },
                Package(0x8)
                {
                    "DEVICE",
                    "\\_SB.USB1",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "PSTATE",
                            Zero
                        }
                    },
                    Package(0xe)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_sleep_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_aggre_usb3_sec_axi_clk",
                                0x8,
                                0x78,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_cfg_noc_usb3_sec_axi_clk",
                                0x8,
                                0x78,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_sec_master_clk",
                                0x8,
                                0x78,
                                0x9
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_sec_mock_utmi_clk",
                                0x8,
                                0x4b00,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB2",
                                "ICBID_SLAVE_EBI1",
                                0x3938700,
                                0x3938700
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB2",
                                0xbebc200,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                0x100
                            }
                        }
                    },
                    Package(0xe)
                    {
                        "DSTATE",
                        One,
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_sec_master_clk",
                                0x3,
                                0x2580,
                                0x5
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_sec_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_sec_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB2",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB2",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0xe)
                    {
                        "DSTATE",
                        0x2,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_sec_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_sec_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_sec_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB2",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB2",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                0x1b7740,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                0x2ee000,
                                One,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0xf)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_sleep_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_aggre_usb3_sec_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_cfg_noc_usb3_sec_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_usb30_sec_master_clk",
                                0x3,
                                0x927c00,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_master_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_mock_utmi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_APPSS_PROC",
                                "ICBID_SLAVE_USB2",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_USB2",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_usb30_sec_gdsc",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_cx",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO2_B",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO1_C",
                                One,
                                Zero,
                                Zero,
                                0x4,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "ABANDON_DSTATE",
                        0x3
                    }
                }
            })
        }
        Scope(\_SB_.PEP0)
        {
            Method(BPMD, 0x0, NotSerialized)
            {
                If(LEqual(STOR, One))
                {
                    If(LEqual(PUS3, One))
                    {
                        Return(CPCC)
                    }
                    Else
                    {
                        Return(BPCC)
                    }
                }
                Else
                {
                    If(LEqual(STOR, 0x2))
                    {
                        Return(DPCC)
                    }
                    Else
                    {
                        Return(FPCC)
                    }
                }
            }
            Method(SDMD, 0x0, NotSerialized)
            {
                Return(SDCC)
            }
            Name(BPCC, Package(One)
            {
                Package(0x7)
                {
                    "DEVICE",
                    "\\_SB.UFS0",
                    Package(0x7)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x5)
                        {
                            "FSTATE",
                            Zero,
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    Zero,
                                    Zero
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    One,
                                    Zero
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    0x2,
                                    Zero
                                }
                            }
                        },
                        Package(0x5)
                        {
                            "FSTATE",
                            One,
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    0x2,
                                    One
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    One,
                                    One
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    Zero,
                                    One
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            Zero,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "FOOTSWITCH",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_gdsc",
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "FOOTSWITCH",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_gdsc",
                                        0x2
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            One,
                            Package(0xd)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_ufs_phy_axi_clk",
                                        0x8,
                                        0x11e1a300,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_ufs_phy_unipro_core_clk",
                                        0x8,
                                        0x11e1a300,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x3)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        0x9,
                                        0x12
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        0x3,
                                        0x11e1a300,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_aggre_ufs_phy_axi_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ahb_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_phy_aux_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_tx_symbol_0_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_0_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_1_clk",
                                        One
                                    }
                                }
                            },
                            Package(0xb)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_aggre_ufs_phy_axi_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ahb_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_phy_aux_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_tx_symbol_0_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_0_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_1_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_unipro_core_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_axi_clk",
                                        0x2
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            0x2,
                            Package(0x4)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_UFS_MEM",
                                        "ICBID_SLAVE_EBI1",
                                        0x47868c00,
                                        0x47868c00
                                    }
                                },
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_APPSS_PROC",
                                        "ICBID_SLAVE_UFS_MEM_CFG",
                                        0x11d260c0,
                                        Zero
                                    }
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_APPSS_PROC",
                                        "ICBID_SLAVE_UFS_MEM_CFG",
                                        Zero,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_UFS_MEM",
                                        "ICBID_SLAVE_EBI1",
                                        Zero,
                                        Zero
                                    }
                                }
                            }
                        }
                    },
                    Package(0xa)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO7_B",
                                One,
                                0x2c4fc0,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO9_B",
                                One,
                                0x124f80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "DELAY",
                            Package(One)
                            {
                                0x23
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                Zero
                            }
                        }
                    },
                    Package(0x9)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO9_B",
                                One,
                                0x124f80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO7_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                Zero,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                One
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_EXCEPTION",
                        Package(0x2)
                        {
                            "EXECUTE_FUNCTION",
                            Package(One)
                            {
                                "ExecuteOcdEMMCExceptions"
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_DSTATE",
                        Zero
                    }
                }
            })
            Name(CPCC, Package(One)
            {
                Package(0x6)
                {
                    "DEVICE",
                    "\\_SB.UFS0",
                    Package(0x7)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x5)
                        {
                            "FSTATE",
                            Zero,
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    Zero,
                                    Zero
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    One,
                                    Zero
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    0x2,
                                    Zero
                                }
                            }
                        },
                        Package(0x5)
                        {
                            "FSTATE",
                            One,
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    0x2,
                                    One
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    One,
                                    One
                                }
                            },
                            Package(0x2)
                            {
                                "PSTATE_ADJUST",
                                Package(0x2)
                                {
                                    Zero,
                                    One
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            Zero,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "FOOTSWITCH",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_gdsc",
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "FOOTSWITCH",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_gdsc",
                                        0x2
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            One,
                            Package(0xd)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_ufs_phy_axi_clk",
                                        0x8,
                                        0x11e1a300,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_ufs_phy_unipro_core_clk",
                                        0x8,
                                        0x11e1a300,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x3)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        0x9,
                                        0x12
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        0x3,
                                        0x11e1a300,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_aggre_ufs_phy_axi_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ahb_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_phy_aux_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_tx_symbol_0_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_0_clk",
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_1_clk",
                                        One
                                    }
                                }
                            },
                            Package(0xb)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_aggre_ufs_phy_axi_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ahb_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_phy_aux_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_tx_symbol_0_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_0_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_rx_symbol_1_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_ice_core_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_unipro_core_clk",
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_ufs_phy_axi_clk",
                                        0x2
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            0x2,
                            Package(0x4)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_UFS_MEM",
                                        "ICBID_SLAVE_EBI1",
                                        0x8f0d1800,
                                        0x8f0d1800
                                    }
                                },
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_APPSS_PROC",
                                        "ICBID_SLAVE_UFS_MEM_CFG",
                                        0x11d260c0,
                                        Zero
                                    }
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_APPSS_PROC",
                                        "ICBID_SLAVE_UFS_MEM_CFG",
                                        Zero,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_UFS_MEM",
                                        "ICBID_SLAVE_EBI1",
                                        Zero,
                                        Zero
                                    }
                                }
                            }
                        }
                    },
                    Package(0xa)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO7_B",
                                One,
                                0x263540,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO9_B",
                                One,
                                0x124f80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x7,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "DELAY",
                            Package(One)
                            {
                                0x23
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                Zero
                            }
                        }
                    },
                    Package(0x9)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO9_B",
                                One,
                                0x124f80,
                                One,
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO7_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                Zero,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                One
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_DSTATE",
                        Zero
                    }
                }
            })
            Name(FPCC, Package(One)
            {
                Package(0x6)
                {
                    "DEVICE",
                    "\\_SB.UFS0",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "FSTATE",
                            One
                        }
                    },
                    Package(0x2)
                    {
                        "PRELOAD_DSTATE",
                        0x3
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        Zero
                    },
                    Package(0x4)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO9_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO7_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        }
                    }
                }
            })
            Name(DPCC, Package(One)
            {
                Package(0x7)
                {
                    "DEVICE",
                    "\\_SB.SDC1",
                    Package(0xa)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "FSTATE",
                            One
                        },
                        Package(0x1a)
                        {
                            "PSTATE_SET",
                            Zero,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x2,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x3,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x4,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x5,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x6,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x7,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x8,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x9,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xa,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xb,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xc,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xd,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xe,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xf,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x10,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x11,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x12,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x13,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x14,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x15,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x5)
                            {
                                "PSTATE",
                                0x16,
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO7_B",
                                        One,
                                        0x2d2a80,
                                        One,
                                        0x7,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO19_B",
                                        One,
                                        0x1b7740,
                                        One,
                                        0x7,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        0x23
                                    }
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE",
                                0x17,
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO7_B",
                                        One,
                                        Zero,
                                        Zero,
                                        Zero,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        0x23
                                    }
                                }
                            }
                        },
                        Package(0xa)
                        {
                            "PSTATE_SET",
                            One,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x8,
                                        0x61a80,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x2,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x8,
                                        0x1312d00,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x3,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x8,
                                        0x17d7840,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x4,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x8,
                                        0x2faf080,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x5,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x8,
                                        0x5f5e100,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x6,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x8,
                                        0xb71b000,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x7,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_apps_clk",
                                        0x8,
                                        0x16e36000,
                                        0x2
                                    }
                                }
                            }
                        },
                        Package(0x7)
                        {
                            "PSTATE_SET",
                            0x2,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_1",
                                        "ICBID_SLAVE_EBI1",
                                        0x2faf0800,
                                        0x17d78400
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_1",
                                        "ICBID_SLAVE_EBI1",
                                        0x17d78400,
                                        0xbebc200
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x2,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_1",
                                        "ICBID_SLAVE_EBI1",
                                        0xbebc200,
                                        0x5f5e100
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x3,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_1",
                                        "ICBID_SLAVE_EBI1",
                                        0x2625a00,
                                        0x1312d00
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x4,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_1",
                                        "ICBID_SLAVE_EBI1",
                                        Zero,
                                        Zero
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            0x3,
                            Package(0x5)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        One,
                                        0x7
                                    }
                                },
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        0x2,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        0x5,
                                        0x3
                                    }
                                }
                            },
                            Package(0x5)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        One,
                                        0x5
                                    }
                                },
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        0x2,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        0x5,
                                        One
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            0x4,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_sdcc1_ahb_clk",
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_sdcc1_ahb_clk",
                                        0x2
                                    }
                                }
                            }
                        },
                        Package(0x6)
                        {
                            "PSTATE_SET",
                            0x5,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_sdcc1_ice_core_clk",
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_ice_core_clk",
                                        0x8,
                                        0x5f5e100,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x2,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_ice_core_clk",
                                        0x8,
                                        0x8f0d180,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x3,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc1_ice_core_clk",
                                        0x8,
                                        0x11e1a300,
                                        0x2
                                    }
                                }
                            }
                        }
                    },
                    Package(0xa)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "TLMMPORT",
                            Package(0x3)
                            {
                                0x1b3000,
                                0x1ffff,
                                0x1fe4
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMPORT",
                            Package(0x3)
                            {
                                0x1b3004,
                                0x1ffff,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                0x7
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x5,
                                0x3
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x4,
                                Zero
                            }
                        },
                        Package(One)
                        {
                            "PSTATE_RESTORE"
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                Zero,
                                0x16
                            }
                        }
                    },
                    Package(0x9)
                    {
                        "DSTATE",
                        0x3,
                        Package(One)
                        {
                            "PSTATE_SAVE"
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x5,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x4,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                0x4
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMPORT",
                            Package(0x3)
                            {
                                0x1b3000,
                                0x1ffff,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMPORT",
                            Package(0x3)
                            {
                                0x1b3004,
                                0x1ffff,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_EXCEPTION",
                        Package(0x2)
                        {
                            "EXECUTE_FUNCTION",
                            Package(One)
                            {
                                "ExecuteOcdEMMCExceptions"
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_DSTATE",
                        Zero
                    }
                }
            })
            Name(SDCC, Package(One)
            {
                Package(0x7)
                {
                    "DEVICE",
                    "\\_SB.SDC2",
                    Package(0x9)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "FSTATE",
                            One
                        },
                        Package(0x19)
                        {
                            "PSTATE_SET",
                            Zero,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x2,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x3,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x4,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x5,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x6,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x7,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x8,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x9,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xb,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xc,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xd,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xe,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0xf,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x10,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x11,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x12,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x13,
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        One
                                    }
                                }
                            },
                            Package(0x8)
                            {
                                "PSTATE",
                                0x14,
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO9_C",
                                        One,
                                        Zero,
                                        Zero,
                                        Zero,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO6_C",
                                        One,
                                        Zero,
                                        Zero,
                                        Zero,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        0x23
                                    }
                                },
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO9_C",
                                        One,
                                        0x2d2a80,
                                        One,
                                        0x7,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO6_C",
                                        One,
                                        0x2d0370,
                                        One,
                                        0x7,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        0x23
                                    }
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE",
                                0x15,
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO6_C",
                                        One,
                                        0x1b7740,
                                        One,
                                        0x7,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        0x23
                                    }
                                }
                            },
                            Package(0x5)
                            {
                                "PSTATE",
                                0x16,
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO9_C",
                                        One,
                                        0x2d2a80,
                                        One,
                                        0x7,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO6_C",
                                        One,
                                        0x2d0370,
                                        One,
                                        0x7,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        0x23
                                    }
                                }
                            },
                            Package(0x5)
                            {
                                "PSTATE",
                                0x17,
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO9_C",
                                        One,
                                        Zero,
                                        Zero,
                                        Zero,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "PMICVREGVOTE",
                                    Package(0x6)
                                    {
                                        "PPP_RESOURCE_ID_LDO6_C",
                                        One,
                                        Zero,
                                        Zero,
                                        Zero,
                                        Zero
                                    }
                                },
                                Package(0x2)
                                {
                                    "DELAY",
                                    Package(One)
                                    {
                                        0x23
                                    }
                                }
                            }
                        },
                        Package(0x5)
                        {
                            "PSTATE_SET",
                            One,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_sdcc2_apps_clk",
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc2_apps_clk",
                                        0x8,
                                        0x5f5e100,
                                        0x2
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x2,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x4)
                                    {
                                        "gcc_sdcc2_apps_clk",
                                        0x8,
                                        0xc0a4680,
                                        0x2
                                    }
                                }
                            }
                        },
                        Package(0x5)
                        {
                            "PSTATE_SET",
                            0x2,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_2",
                                        "ICBID_SLAVE_EBI1",
                                        0x17d78400,
                                        0xbebc200
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_2",
                                        "ICBID_SLAVE_EBI1",
                                        0xbebc200,
                                        0x5f5e100
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                0x2,
                                Package(0x2)
                                {
                                    "BUSARB",
                                    Package(0x5)
                                    {
                                        0x3,
                                        "ICBID_MASTER_SDCC_2",
                                        "ICBID_SLAVE_EBI1",
                                        Zero,
                                        Zero
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            0x3,
                            Package(0x4)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        One,
                                        0x2
                                    }
                                },
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        0x2,
                                        Zero
                                    }
                                }
                            },
                            Package(0x4)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        One,
                                        One
                                    }
                                },
                                Package(0x2)
                                {
                                    "PSTATE_ADJUST",
                                    Package(0x2)
                                    {
                                        0x2,
                                        One
                                    }
                                }
                            }
                        },
                        Package(0x4)
                        {
                            "PSTATE_SET",
                            0x4,
                            Package(0x3)
                            {
                                "PSTATE",
                                Zero,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_sdcc2_ahb_clk",
                                        One
                                    }
                                }
                            },
                            Package(0x3)
                            {
                                "PSTATE",
                                One,
                                Package(0x2)
                                {
                                    "CLOCK",
                                    Package(0x2)
                                    {
                                        "gcc_sdcc2_ahb_clk",
                                        0x2
                                    }
                                }
                            }
                        }
                    },
                    Package(0x7)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                Zero,
                                0x16
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMPORT",
                            Package(0x3)
                            {
                                0x1b4000,
                                0x7fff,
                                0x1fe4
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x4,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                0x2
                            }
                        }
                    },
                    Package(0x7)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x4,
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                0x2,
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMPORT",
                            Package(0x3)
                            {
                                0x1b4000,
                                0x7fff,
                                0xa00
                            }
                        },
                        Package(0x2)
                        {
                            "PSTATE_ADJUST",
                            Package(0x2)
                            {
                                Zero,
                                0x17
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_EXCEPTION",
                        Package(0x2)
                        {
                            "EXECUTE_FUNCTION",
                            Package(One)
                            {
                                "ExecuteOcdSdCardExceptions"
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_DSTATE",
                        Zero
                    }
                }
            })
        }
        Scope(\_SB_.PEP0)
        {
            Method(EWMD, 0x0, NotSerialized)
            {
                Return(WBRC)
            }
            Name(WBRC, Package(One)
            {
                Package(0x7)
                {
                    "DEVICE",
                    "\\_SB.WPSS.QWLN",
                    Package(0x3)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        }
                    },
                    Package(0x6)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_xo",
                                0x80
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS1_B",
                                0x2,
                                0x1c9080,
                                One,
                                0x6,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS7_B",
                                0x2,
                                0xe86c0,
                                One,
                                0x6,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS8_B",
                                0x2,
                                0x132a40,
                                One,
                                0x6,
                                Zero
                            }
                        }
                    },
                    Package(0x6)
                    {
                        "DSTATE",
                        0x2,
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_xo",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS1_B",
                                0x2,
                                Zero,
                                Zero,
                                0x5,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS7_B",
                                0x2,
                                Zero,
                                Zero,
                                0x5,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS8_B",
                                0x2,
                                Zero,
                                Zero,
                                0x5,
                                Zero
                            }
                        }
                    },
                    Package(0x6)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "NPARESOURCE",
                            Package(0x3)
                            {
                                One,
                                "/arc/client/rail_xo",
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS1_B",
                                0x2,
                                Zero,
                                Zero,
                                0x5,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS7_B",
                                0x2,
                                Zero,
                                Zero,
                                0x5,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_SMPS8_B",
                                0x2,
                                Zero,
                                Zero,
                                0x5,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "ABANDON_DSTATE",
                        0x2
                    }
                }
            })
        }
        Scope(\_SB_.PEP0)
        {
            Method(PEMD, 0x0, NotSerialized)
            {
                If(LEqual(SKUV, One))
                {
                    Return(PEMC)
                }
                Else
                {
                    Return(PEMX)
                }
            }
            Name(PEMC, Package(0x2)
            {
                Package(0x9)
                {
                    "DEVICE",
                    "\\_SB.PCI1",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "FSTATE",
                            One
                        }
                    },
                    Package(0xf)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x7)
                            {
                                0x13,
                                One,
                                Zero,
                                One,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_pcie_1_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_PCIE_1",
                                "ICBID_SLAVE_EBI1",
                                0x74d33a00,
                                0x74d33a00
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_pipe_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_axi_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_q2a_axi_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_mstr_axi_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_cfg_ahb_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_pcie_1_aux_clk",
                                0x8,
                                0x124f800,
                                0x3
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_pcie1_phy_rchng_clk",
                                0x8,
                                0x5f5e100,
                                0x3
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x7)
                            {
                                0x4f,
                                Zero,
                                0x3,
                                Zero,
                                0x3,
                                Zero,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        One
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x2
                    },
                    Package(0xe)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_q2a_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_mstr_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_cfg_ahb_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie1_phy_rchng_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_PCIE_1",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_pcie_1_gdsc",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x7)
                            {
                                0x13,
                                Zero,
                                Zero,
                                One,
                                Zero,
                                Zero,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_EXCEPTION",
                        Package(0x2)
                        {
                            "EXECUTE_FUNCTION",
                            Package(One)
                            {
                                "ExecuteOcdPCIeExceptions"
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_DSTATE",
                        Zero
                    }
                },
                Package(0x7)
                {
                    "DEVICE",
                    "\\_SB.PCI1.RP1",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "FSTATE",
                            One
                        }
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        Zero
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        One
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x2
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x3
                    }
                }
            })
            Name(PEMX, Package(0x2)
            {
                Package(0x9)
                {
                    "DEVICE",
                    "\\_SB.PCI1",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "FSTATE",
                            One
                        }
                    },
                    Package(0xf)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x7)
                            {
                                0x33,
                                One,
                                Zero,
                                One,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                0x124f80,
                                One,
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                0xd6d80,
                                One,
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_pcie_1_gdsc",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_PCIE_1",
                                "ICBID_SLAVE_EBI1",
                                0x74d33a00,
                                0x74d33a00
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_pipe_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_axi_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_q2a_axi_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_mstr_axi_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_cfg_ahb_clk",
                                One
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_pcie_1_aux_clk",
                                0x8,
                                0x124f800,
                                0x3
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x4)
                            {
                                "gcc_pcie1_phy_rchng_clk",
                                0x8,
                                0x5f5e100,
                                0x3
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x7)
                            {
                                0x4f,
                                Zero,
                                0x3,
                                Zero,
                                0x3,
                                Zero,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        One
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x2
                    },
                    Package(0xe)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_aux_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_slv_q2a_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_mstr_axi_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_cfg_ahb_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie1_phy_rchng_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "CLOCK",
                            Package(0x2)
                            {
                                "gcc_pcie_1_pipe_clk",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "BUSARB",
                            Package(0x5)
                            {
                                0x3,
                                "ICBID_MASTER_PCIE_1",
                                "ICBID_SLAVE_EBI1",
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "FOOTSWITCH",
                            Package(0x2)
                            {
                                "gcc_pcie_1_gdsc",
                                0x2
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO10_C",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x6)
                            {
                                "PPP_RESOURCE_ID_LDO6_B",
                                One,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x7)
                            {
                                0x33,
                                Zero,
                                Zero,
                                One,
                                Zero,
                                Zero,
                                Zero
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_EXCEPTION",
                        Package(0x2)
                        {
                            "EXECUTE_FUNCTION",
                            Package(One)
                            {
                                "ExecuteOcdPCIeExceptions"
                            }
                        }
                    },
                    Package(0x2)
                    {
                        "CRASHDUMP_DSTATE",
                        Zero
                    }
                },
                Package(0x7)
                {
                    "DEVICE",
                    "\\_SB.PCI1.RP1",
                    Package(0x4)
                    {
                        "COMPONENT",
                        Zero,
                        Package(0x2)
                        {
                            "FSTATE",
                            Zero
                        },
                        Package(0x2)
                        {
                            "FSTATE",
                            One
                        }
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        Zero
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        One
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x2
                    },
                    Package(0x2)
                    {
                        "DSTATE",
                        0x3
                    }
                }
            })
        }
        Scope(\_SB_.PEP0)
        {
            Method(LPMX, 0x0, NotSerialized)
            {
                Return(LPXC)
            }
            Name(LPXC, Package(One)
            {
                Package(0x4)
                {
                    "DEVICE",
                    "\\_SB.TSC1",
                    Package(0x6)
                    {
                        "DSTATE",
                        Zero,
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x8)
                            {
                                "PPP_RESOURCE_ID_LDO7_C",
                                One,
                                0x2dc6c0,
                                One,
                                0x7,
                                Zero,
                                "HLOS_DRV",
                                "REQUIRED"
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x6)
                            {
                                0x51,
                                Zero,
                                Zero,
                                Zero,
                                Zero,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x6)
                            {
                                0x51,
                                Zero,
                                Zero,
                                Zero,
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "DELAY",
                            Package(One)
                            {
                                0xc8
                            }
                        }
                    },
                    Package(0x5)
                    {
                        "DSTATE",
                        0x3,
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x6)
                            {
                                0x51,
                                Zero,
                                Zero,
                                Zero,
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "TLMMGPIO",
                            Package(0x6)
                            {
                                0x51,
                                Zero,
                                Zero,
                                Zero,
                                One,
                                Zero
                            }
                        },
                        Package(0x2)
                        {
                            "PMICVREGVOTE",
                            Package(0x7)
                            {
                                "PPP_RESOURCE_ID_LDO7_C",
                                One,
                                Zero,
                                One,
                                0x7,
                                Zero,
                                "REQUIRED"
                            }
                        }
                    }
                }
            })
        }
        Device(BAM1)
        {
            Name(_HID, "QCOM0A0A")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, One)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xdc, 0x01, 0x00, 0x40, 0x02, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x30, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(BAM5)
        {
            Name(_HID, "QCOM0A0A")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0x5)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xa8, 0x03, 0x00, 0x20, 0x03, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0xc4, 0x00, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(BAME)
        {
            Name(_HID, "QCOM0A0A")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0xe)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0x06, 0x06, 0x00, 0x50, 0x01, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0xc7, 0x00, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(BAMF)
        {
            Name(_HID, "QCOM0A0A")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0xf)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0x70, 0x0a, 0x00, 0x70, 0x01, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0xa4, 0x00, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(I2C2)
        {
            Name(_HID, "QCOM0A10")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0x2)
            Name(_DEP, Package(0x3)
            {
                \_SB_.PEP0,
                \_SB_.QGP0,
                \_SB_.MMU0
            })
            Name(_CCA, Zero)
            Name(_STR, Buffer(0x24)
            {
	0x51, 0x00, 0x55, 0x00, 0x50, 0x00, 0x5f, 0x00, 0x30, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x31, 0x00, 0x2c, 0x00, 0x53, 0x00,
	0x68, 0x00, 0x61, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00, 0x00, 0x00
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0x98, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x7a, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(UARD)
        {
            Name(_HID, "QCOM0A16")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0x6)
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_CCA, Zero)
            Name(_STR, Buffer(0x1e)
            {
	0x51, 0x00, 0x55, 0x00, 0x50, 0x00, 0x5f, 0x00, 0x30, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x35, 0x00, 0x2c, 0x00, 0x44, 0x00,
	0x42, 0x00, 0x47, 0x00, 0x00, 0x00
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x3a)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0x99, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x7e, 0x02, 0x00, 0x00, 0x8c, 0x20, 0x00,
	0x01, 0x00, 0x01, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x17,
	0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x17, 0x00, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(UAR8)
        {
            Name(_HID, "QCOM0A16")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0x8)
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_CCA, Zero)
            Name(_STR, Buffer(0x22)
            {
	0x51, 0x00, 0x55, 0x00, 0x50, 0x00, 0x5f, 0x00, 0x30, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x37, 0x00, 0x2c, 0x00, 0x34, 0x00,
	0x57, 0x00, 0x2c, 0x00, 0x42, 0x00, 0x54, 0x00, 0x00, 0x00
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x3a)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0xc0, 0x99, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x80, 0x02, 0x00, 0x00, 0x8c, 0x20, 0x00,
	0x01, 0x00, 0x01, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x17,
	0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xb)
            }
        }
        Device(IC10)
        {
            Name(_HID, "QCOM0A10")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0xa)
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_CCA, Zero)
            Name(_STR, Buffer(0x16)
            {
	0x51, 0x00, 0x55, 0x00, 0x50, 0x00, 0x5f, 0x00, 0x31, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x31, 0x00, 0x00, 0x00
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xa8, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x82, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(IC11)
        {
            Name(_HID, "QCOM0A10")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0xb)
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_CCA, Zero)
            Name(_STR, Buffer(0x16)
            {
	0x51, 0x00, 0x55, 0x00, 0x50, 0x00, 0x5f, 0x00, 0x31, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x32, 0x00, 0x00, 0x00
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x80, 0xa8, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x83, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(IC14)
        {
            Name(_HID, "QCOM0A10")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0xe)
            Name(_DEP, Package(0x3)
            {
                \_SB_.PEP0,
                \_SB_.QGP1,
                \_SB_.MMU0
            })
            Name(_CCA, Zero)
            Name(_STR, Buffer(0x16)
            {
	0x51, 0x00, 0x55, 0x00, 0x50, 0x00, 0x5f, 0x00, 0x31, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x35, 0x00, 0x00, 0x00
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xa9, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x86, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(SP14)
        {
            Name(_HID, "QCOM0A0E")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, 0xe)
            Name(_DEP, Package(0x3)
            {
                \_SB_.PEP0,
                \_SB_.QGP1,
                \_SB_.MMU0
            })
            Name(_CCA, Zero)
            Name(_STR, Buffer(0x16)
            {
	0x51, 0x00, 0x55, 0x00, 0x50, 0x00, 0x5f, 0x00, 0x31, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x35, 0x00, 0x00, 0x00
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xa9, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x86, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(RPEN)
        {
            Name(_HID, "QCOM06E1")
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(PILC)
        {
            Name(_HID, "QCOM06E0")
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(CDI_)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.PILC,
                \_SB_.RPEN
            })
            Name(_HID, "QCOM0A2F")
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(ADSP)
        {
            Name(_DEP, Package(0x9)
            {
                \_SB_.PEP0,
                \_SB_.PILC,
                \_SB_.GLNK,
                \_SB_.IPC0,
                \_SB_.RPEN,
                \_SB_.SSDD,
                \_SB_.ARPC,
                \_SB_.TFTP,
                \_SB_.PDSR
            })
            Name(_HID, "QCOM0A1B")
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0xb)
                {
	0x89, 0x06, 0x00, 0x03, 0x01, 0x06, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Device(SLM1)
            {
                Name(_ADR, Zero)
                Name(_CCA, Zero)
                Method(_CRS, 0x0, NotSerialized)
                {
                    Name(RBUF, Buffer(0x17)
                    {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xac, 0x03, 0x00, 0xc0, 0x02, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0xc3, 0x00, 0x00, 0x00, 0x79, 0x00
                    })
                    Return(RBUF)
                }
            }
            Device(ADCM)
            {
                Name(_ADR, One)
                Name(_DEP, Package(0x2)
                {
                    \_SB_.MMU0,
                    \_SB_.IMM0
                })
                Method(_STA, 0x0, NotSerialized)
                {
                    Return(0xf)
                }
                Method(CHLD, 0x0, NotSerialized)
                {
                    Return(Package(One)
                    {
                        "ADCM\\QCOM0AC1"
                    })
                }
                Device(AUCD)
                {
                    Name(_ADR, Zero)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Method(_CRS, 0x0, NotSerialized)
                    {
                        Name(RBUF, Buffer(0xa9)
                        {
	0x8c, 0x20, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x40, 0x06,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x53,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x8c,
	0x20, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x40, 0x06, 0x00,
	0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x3e, 0x00,
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x8c, 0x20,
	0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x40, 0x06, 0x00, 0x00,
	0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x5c,
	0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x8c, 0x20, 0x00,
	0x01, 0x00, 0x01, 0x00, 0x15, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x17,
	0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x01, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x89, 0x06, 0x00, 0x03,
	0x01, 0x10, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xbb, 0x00,
	0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xca, 0x00, 0x00, 0x00, 0x79,
	0x00
                        })
                        Return(RBUF)
                    }
                    Method(CHLD, 0x0, NotSerialized)
                    {
                        Name(CH__, Package(One)
                        {
                            "AUCD\\QCOM0A29"
                        })
                        Return(CH__)
                    }
                    Device(QCRT)
                    {
                        Method(_STA, 0x0, NotSerialized)
                        {
                            Return(0xf)
                        }
                        Name(_ADR, Zero)
                    }
                }
            }
        }
        Device(AMSS)
        {
            Name(_CCA, Zero)
            Name(_DEP, Package(0x9)
            {
                \_SB_.PEP0,
                \_SB_.GLNK,
                \_SB_.PILC,
                \_SB_.RFS0,
                \_SB_.RPEN,
                \_SB_.SSDD,
                \_SB_.IPC0,
                \_SB_.TFTP,
                \_SB_.PDSR
            })
            Name(_HID, "QCOM0A1C")
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0xb)
                {
	0x89, 0x06, 0x00, 0x03, 0x01, 0x28, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(QSM_)
        {
            Name(_HID, "QCOM0A1E")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(0x4)
            {
                \_SB_.GLNK,
                \_SB_.IPC0,
                \_SB_.PILC,
                \_SB_.RPEN
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(SSDD)
        {
            Name(_HID, "QCOM0A20")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.GLNK
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(PDSR)
        {
            Name(_HID, "QCOM06DF")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(0x3)
            {
                \_SB_.PEP0,
                \_SB_.GLNK,
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(NSP0)
        {
            Name(_DEP, Package(0x8)
            {
                \_SB_.PEP0,
                \_SB_.PILC,
                \_SB_.GLNK,
                \_SB_.IPC0,
                \_SB_.RPEN,
                \_SB_.SSDD,
                \_SB_.ARPC,
                \_SB_.PDSR
            })
            Name(_HID, "QCOM0AB0")
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0xb)
                {
	0x89, 0x06, 0x00, 0x03, 0x01, 0x62, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(WPSS)
        {
            Name(_DEP, Package(0x8)
            {
                \_SB_.PEP0,
                \_SB_.PILC,
                \_SB_.GLNK,
                \_SB_.IPC0,
                \_SB_.RPEN,
                \_SB_.SSDD,
                \_SB_.TFTP,
                \_SB_.PDSR
            })
            Name(_HID, "QCOM0AE2")
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0xb)
                {
	0x89, 0x06, 0x00, 0x03, 0x01, 0x6b, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Device(QWLN)
            {
                Name(_ADR, Zero)
                Name(_DEP, Package(0x3)
                {
                    \_SB_.PEP0,
                    \_SB_.MMU0,
                    \_SB_.IPC0
                })
                Name(_PRW, Package(0x2)
                {
                    Zero,
                    Zero
                })
                Name(_S0W, 0x3)
                Name(_S4W, 0x3)
                Name(_PRR, Package(One)
                {
                    \_SB_.WPSS.QWLN.WRST
                })
                Method(_CRS, 0x0, NotSerialized)
                {
                    Name(RBUF, Buffer(0x13a)
                    {
	0x86, 0x09, 0x00, 0x01, 0x40, 0x00, 0xa1, 0x17, 0x10, 0x00, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xc0, 0x80, 0x00, 0x00, 0xc0, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x20, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x21, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x22,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x23, 0x03, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x24, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x25, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x26,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x27, 0x03, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x28, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x29, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x2a,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x2b, 0x03, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x2c, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x2d, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x2e,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x2f, 0x03, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x30, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x31, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x32,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x33, 0x03, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x34, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x35, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x36,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x37, 0x03, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x38, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x39, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x3a,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x3b, 0x03, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x13, 0x01, 0x3c, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x3d, 0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x3e,
	0x03, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x3f, 0x03, 0x00, 0x00,
	0x79, 0x00
                    })
                    Return(RBUF)
                }
                PowerResource(WRST, 0x5, 0x0)
                {
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Method(_ON_, 0x0, NotSerialized)
                    {
                    }
                    Method(_OFF, 0x0, NotSerialized)
                    {
                    }
                    Method(_RST, 0x0, NotSerialized)
                    {
                    }
                }
            }
            Scope(\_SB_)
            {
                Device(WLTM)
                {
                    Name(_HID, "QCOM0AD5")
                    Name(_CID, "QCOMFFE0")
                    Alias(\_SB_.PSUB, _SUB)
                    Name(_DEP, Package(0x2)
                    {
                        \_SB_.WPSS,
                        \_SB_.SBTD
                    })
                }
            }
        }
        Device(CSW0)
        {
            Name(_HID, "QCOM0AC3")
            Name(_CID, "QCOMFFE0")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(0x2)
            {
                \_SB_.NSP0,
                \_SB_.SBTD
            })
        }
        Device(SBTD)
        {
            Name(_HID, "QCOM06E5")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(TFTP)
        {
            Name(_HID, "QCOM06DC")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(QCSK)
        {
            Name(_HID, "QCOM0AAC")
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
        }
        Scope(\_SB_.ADSP)
        {
        }
        Scope(\_SB_.AMSS)
        {
        }
        Scope(\_SB_.PILC)
        {
        }
        Scope(\_SB_.CDI_)
        {
        }
        Scope(\_SB_.RPEN)
        {
        }
        Scope(\_SB_.NSP0)
        {
            Name(_CID, "QCOMFFE8")
        }
        Scope(\_SB_.AMSS)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(SKUV, 0x4))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
            Method(_SUB, 0x0, NotSerialized)
            {
                Return(\_SB_.PSUB)
            }
        }
        Scope(\_SB_.PILC)
        {
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LEqual(SKUV, 0x4))
                {
                    Return("IDPA7280")
                }
                Else
                {
                    Return(\_SB_.PSUB)
                }
            }
        }
        Scope(\_SB_.ADSP)
        {
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LEqual(SKUV, 0x5))
                {
                    Return("IWSA7280")
                }
                Else
                {
                    Return(\_SB_.PSUB)
                }
            }
        }
        Device(LLC_)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_HID, "QCOM0A83")
            Alias(\_SB_.PSUB, _SUB)
            Alias(\_SB_.SVMJ, _HRV)
            Method(_CRS, 0x0, NotSerialized)
            {
                Return(Buffer(0x17)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x60, 0x09, 0x00, 0x00, 0x05, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x2a, 0x01, 0x00, 0x00, 0x79, 0x00
                })
            }
        }
        Device(MMU0)
        {
            Name(_HID, "QCOM0A09")
            Name(_UID, Zero)
            Alias(\_SB_.PSUB, _SUB)
            Alias(\_SB_.SVMJ, _HRV)
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Return(Buffer(0x257)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x10, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x80, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x81, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x82,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x83, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x84, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x85, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x86,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x87, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x88, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x89, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x8a,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x8b, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x8d, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x8e,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x8f, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x90, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x91, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x92,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x93, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x94, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x95, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x96,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xd5, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xd6, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xd7, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xd8,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xd9, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xda, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xdb, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xdc,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xdd, 0x00, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xde, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xdf, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xe0,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x5b, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x5c, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x5d, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x5e,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x5f, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x60, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x61, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x62,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x63, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x64, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x65, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x66,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x67, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x68, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x69, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x6a,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x6b, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x6c, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x6d, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x6e,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x6f, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x70, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x71, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x72,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x73, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x74, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x75, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x76,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x77, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x78, 0x01, 0x00, 0x00, 0x79, 0x00
                })
            }
        }
        Device(MMU1)
        {
            Name(_HID, "QCOM0A09")
            Name(_UID, One)
            Alias(\_SB_.PSUB, _SUB)
            Alias(\_SB_.SVMJ, _HRV)
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Return(Buffer(0x68)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xda, 0x03, 0x00, 0x00, 0x02, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xc6, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xc7, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xc8,
	0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xc9, 0x02, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xca, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xcb, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xcc,
	0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xcd, 0x02, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xce, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xcf, 0x02, 0x00, 0x00, 0x79, 0x00
                })
            }
        }
        Device(IMM0)
        {
            Name(_HID, "QCOM068F")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
        }
        Device(IMM1)
        {
            Name(_HID, "QCOM068F")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, One)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(GPU0)
        {
            Name(_HID, "QCOM0A36")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Name(_CLS, 0x3000000000000)
            Device(MON0)
            {
                Method(_ADR, 0x0, NotSerialized)
                {
                    Return(Zero)
                }
            }
            Name(_DEP, Package(0xa)
            {
                \_SB_.MMU0,
                \_SB_.MMU1,
                \_SB_.IMM0,
                \_SB_.IMM1,
                \_SB_.PEP0,
                \_SB_.PMIC,
                \_SB_.PILC,
                \_SB_.RPEN,
                \_SB_.TREE,
                \_SB_.SCM0
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(ABUF, Buffer(0xb8)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xe0, 0x0a, 0x00, 0x00, 0x20, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x8e, 0x08, 0x00, 0x00, 0x01, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x73, 0x00, 0x00, 0x00, 0x86, 0x09, 0x00,
	0x01, 0x00, 0x00, 0xd0, 0x03, 0x10, 0xf0, 0x03, 0x00, 0x86, 0x09, 0x00,
	0x01, 0x00, 0x00, 0xd6, 0x03, 0x00, 0xf0, 0x03, 0x00, 0x89, 0x06, 0x00,
	0x01, 0x01, 0x4c, 0x01, 0x00, 0x00, 0x86, 0x09, 0x00, 0x01, 0x00, 0x00,
	0x29, 0x0b, 0x00, 0x00, 0x01, 0x00, 0x86, 0x09, 0x00, 0x01, 0x00, 0x00,
	0x49, 0x0b, 0x00, 0x00, 0x01, 0x00, 0x86, 0x09, 0x00, 0x01, 0x00, 0x00,
	0xd9, 0x03, 0x00, 0x90, 0x00, 0x00, 0x86, 0x09, 0x00, 0x01, 0x00, 0x00,
	0xde, 0x03, 0x00, 0x00, 0x01, 0x00, 0x86, 0x09, 0x00, 0x01, 0x00, 0x00,
	0x20, 0x0c, 0xff, 0xff, 0x00, 0x00, 0x86, 0x09, 0x00, 0x01, 0x00, 0x00,
	0xa0, 0x0a, 0x00, 0x00, 0x20, 0x00, 0x89, 0x06, 0x00, 0x01, 0x01, 0xce,
	0x00, 0x00, 0x00, 0x8c, 0x20, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00,
	0x00, 0x00, 0x2c, 0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f,
	0x30, 0x00, 0x79, 0x00
                })
                Return(ABUF)
            }
            Method(RESI, 0x0, NotSerialized)
            {
                Name(AINF, Package(0x10)
                {
                    0x3,
                    Zero,
                    Package(0x3)
                    {
                        "RESOURCE",
                        "MDP_REGS",
                        "DISPLAY"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "DP_PHY_REGS",
                        "DISPLAY"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "VSYNC_INTERRUPT",
                        "DISPLAY"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GFX_REGS",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GFX_REG_CONT",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GFX_INTERRUPT",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GPU_PDC_SEQ_MEM",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GPU_PDC_REGS",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GPU_CC",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GPU_RSCC",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "GPU_RPMH_CPRF",
                        "GRAPHICS"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "VIDEO_REGS",
                        "VIDEO"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "VIDC_INTERRUPT",
                        "VIDEO"
                    },
                    Package(0x3)
                    {
                        "RESOURCE",
                        "DSI_PANEL_RESET",
                        "DISPLAY"
                    }
                })
                Return(AINF)
            }
            Method(_ROM, 0x3, NotSerialized)
            {
                Name(PCFG, Buffer(0x14a4)
                {
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76,
	0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x27, 0x31, 0x2e, 0x30, 0x27,
	0x20, 0x65, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x3d, 0x27, 0x75,
	0x74, 0x66, 0x2d, 0x38, 0x27, 0x3f, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x50, 0x61, 0x6e, 0x65, 0x6c, 0x4e, 0x61, 0x6d, 0x65, 0x3e, 0x52,
	0x36, 0x36, 0x34, 0x35, 0x31, 0x20, 0x56, 0x69, 0x73, 0x69, 0x6f, 0x6e,
	0x6f, 0x78, 0x3c, 0x2f, 0x50, 0x61, 0x6e, 0x65, 0x6c, 0x4e, 0x61, 0x6d,
	0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x50, 0x61, 0x6e, 0x65,
	0x6c, 0x44, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e,
	0x3e, 0x52, 0x36, 0x36, 0x34, 0x35, 0x31, 0x20, 0x56, 0x69, 0x73, 0x69,
	0x6f, 0x6e, 0x6f, 0x78, 0x20, 0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20,
	0x44, 0x53, 0x49, 0x20, 0x44, 0x53, 0x43, 0x20, 0x43, 0x6f, 0x6d, 0x6d,
	0x61, 0x6e, 0x64, 0x20, 0x4d, 0x6f, 0x64, 0x65, 0x20, 0x41, 0x6d, 0x6f,
	0x6c, 0x65, 0x64, 0x20, 0x50, 0x61, 0x6e, 0x65, 0x6c, 0x20, 0x28, 0x31,
	0x34, 0x34, 0x30, 0x78, 0x32, 0x35, 0x36, 0x30, 0x20, 0x32, 0x34, 0x62,
	0x70, 0x70, 0x29, 0x3c, 0x2f, 0x50, 0x61, 0x6e, 0x65, 0x6c, 0x44, 0x65,
	0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x20, 0x69, 0x64,
	0x3d, 0x27, 0x45, 0x44, 0x49, 0x44, 0x20, 0x43, 0x6f, 0x6e, 0x66, 0x69,
	0x67, 0x75, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x27, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x4d, 0x61, 0x6e, 0x75,
	0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x49, 0x44, 0x3e, 0x30, 0x78,
	0x31, 0x30, 0x34, 0x44, 0x3c, 0x2f, 0x4d, 0x61, 0x6e, 0x75, 0x66, 0x61,
	0x63, 0x74, 0x75, 0x72, 0x65, 0x49, 0x44, 0x3e, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x50, 0x72, 0x6f, 0x64, 0x75, 0x63,
	0x74, 0x43, 0x6f, 0x64, 0x65, 0x3e, 0x37, 0x32, 0x38, 0x30, 0x3c, 0x2f,
	0x50, 0x72, 0x6f, 0x64, 0x75, 0x63, 0x74, 0x43, 0x6f, 0x64, 0x65, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x53, 0x65,
	0x72, 0x69, 0x61, 0x6c, 0x4e, 0x75, 0x6d, 0x62, 0x65, 0x72, 0x3e, 0x30,
	0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31, 0x3c, 0x2f, 0x53, 0x65, 0x72,
	0x69, 0x61, 0x6c, 0x4e, 0x75, 0x6d, 0x62, 0x65, 0x72, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x57, 0x65, 0x65, 0x6b,
	0x6f, 0x66, 0x4d, 0x61, 0x6e, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72,
	0x65, 0x3e, 0x30, 0x78, 0x30, 0x31, 0x3c, 0x2f, 0x57, 0x65, 0x65, 0x6b,
	0x6f, 0x66, 0x4d, 0x61, 0x6e, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72,
	0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x59, 0x65, 0x61, 0x72, 0x6f, 0x66, 0x4d, 0x61, 0x6e, 0x75, 0x66, 0x61,
	0x63, 0x74, 0x75, 0x72, 0x65, 0x3e, 0x30, 0x78, 0x31, 0x42, 0x3c, 0x2f,
	0x59, 0x65, 0x61, 0x72, 0x6f, 0x66, 0x4d, 0x61, 0x6e, 0x75, 0x66, 0x61,
	0x63, 0x74, 0x75, 0x72, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x45, 0x44, 0x49, 0x44, 0x56, 0x65, 0x72, 0x73,
	0x69, 0x6f, 0x6e, 0x3e, 0x31, 0x3c, 0x2f, 0x45, 0x44, 0x49, 0x44, 0x56,
	0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x3c, 0x45, 0x44, 0x49, 0x44, 0x52, 0x65, 0x76,
	0x69, 0x73, 0x69, 0x6f, 0x6e, 0x3e, 0x33, 0x3c, 0x2f, 0x45, 0x44, 0x49,
	0x44, 0x52, 0x65, 0x76, 0x69, 0x73, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x56, 0x69, 0x64, 0x65,
	0x6f, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x44, 0x65, 0x66, 0x69, 0x6e, 0x69,
	0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x30, 0x78, 0x38, 0x30, 0x3c, 0x2f, 0x56,
	0x69, 0x64, 0x65, 0x6f, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x44, 0x65, 0x66,
	0x69, 0x6e, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f,
	0x6e, 0x74, 0x61, 0x6c, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x53, 0x69,
	0x7a, 0x65, 0x3e, 0x30, 0x78, 0x30, 0x37, 0x3c, 0x2f, 0x48, 0x6f, 0x72,
	0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x53, 0x63, 0x72, 0x65, 0x65,
	0x6e, 0x53, 0x69, 0x7a, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c,
	0x53, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x53, 0x69, 0x7a, 0x65, 0x3e, 0x30,
	0x78, 0x30, 0x43, 0x3c, 0x2f, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61,
	0x6c, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x53, 0x69, 0x7a, 0x65, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x69,
	0x73, 0x70, 0x6c, 0x61, 0x79, 0x54, 0x72, 0x61, 0x6e, 0x73, 0x66, 0x65,
	0x72, 0x43, 0x68, 0x61, 0x72, 0x61, 0x63, 0x74, 0x65, 0x72, 0x69, 0x73,
	0x74, 0x69, 0x63, 0x73, 0x3e, 0x30, 0x78, 0x37, 0x38, 0x3c, 0x2f, 0x44,
	0x69, 0x73, 0x70, 0x6c, 0x61, 0x79, 0x54, 0x72, 0x61, 0x6e, 0x73, 0x66,
	0x65, 0x72, 0x43, 0x68, 0x61, 0x72, 0x61, 0x63, 0x74, 0x65, 0x72, 0x69,
	0x73, 0x74, 0x69, 0x63, 0x73, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x46, 0x65, 0x61, 0x74, 0x75, 0x72, 0x65, 0x53,
	0x75, 0x70, 0x70, 0x6f, 0x72, 0x74, 0x3e, 0x30, 0x78, 0x32, 0x3c, 0x2f,
	0x46, 0x65, 0x61, 0x74, 0x75, 0x72, 0x65, 0x53, 0x75, 0x70, 0x70, 0x6f,
	0x72, 0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x52, 0x65, 0x64, 0x2e, 0x47, 0x72, 0x65, 0x65, 0x6e, 0x42, 0x69,
	0x74, 0x73, 0x3e, 0x30, 0x78, 0x41, 0x35, 0x3c, 0x2f, 0x52, 0x65, 0x64,
	0x2e, 0x47, 0x72, 0x65, 0x65, 0x6e, 0x42, 0x69, 0x74, 0x73, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x42, 0x6c, 0x75,
	0x65, 0x2e, 0x57, 0x68, 0x69, 0x74, 0x65, 0x42, 0x69, 0x74, 0x73, 0x3e,
	0x30, 0x78, 0x35, 0x38, 0x3c, 0x2f, 0x42, 0x6c, 0x75, 0x65, 0x2e, 0x57,
	0x68, 0x69, 0x74, 0x65, 0x42, 0x69, 0x74, 0x73, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x52, 0x65, 0x64, 0x58, 0x3e,
	0x30, 0x78, 0x41, 0x36, 0x3c, 0x2f, 0x52, 0x65, 0x64, 0x58, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x52, 0x65, 0x64,
	0x59, 0x3e, 0x30, 0x78, 0x35, 0x34, 0x3c, 0x2f, 0x52, 0x65, 0x64, 0x59,
	0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x47,
	0x72, 0x65, 0x65, 0x6e, 0x58, 0x3e, 0x30, 0x78, 0x33, 0x33, 0x3c, 0x2f,
	0x47, 0x72, 0x65, 0x65, 0x6e, 0x58, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x3c, 0x47, 0x72, 0x65, 0x65, 0x6e, 0x59, 0x3e,
	0x30, 0x78, 0x42, 0x33, 0x3c, 0x2f, 0x47, 0x72, 0x65, 0x65, 0x6e, 0x59,
	0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x42,
	0x6c, 0x75, 0x65, 0x58, 0x3e, 0x30, 0x78, 0x32, 0x36, 0x3c, 0x2f, 0x42,
	0x6c, 0x75, 0x65, 0x58, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x42, 0x6c, 0x75, 0x65, 0x59, 0x3e, 0x30, 0x78, 0x31,
	0x32, 0x3c, 0x2f, 0x42, 0x6c, 0x75, 0x65, 0x59, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x57, 0x68, 0x69, 0x74, 0x65,
	0x58, 0x3e, 0x30, 0x78, 0x34, 0x46, 0x3c, 0x2f, 0x57, 0x68, 0x69, 0x74,
	0x65, 0x58, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x57, 0x68, 0x69, 0x74, 0x65, 0x59, 0x3e, 0x30, 0x78, 0x35, 0x34,
	0x3c, 0x2f, 0x57, 0x68, 0x69, 0x74, 0x65, 0x59, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x45, 0x73, 0x74, 0x61, 0x62,
	0x6c, 0x69, 0x73, 0x68, 0x65, 0x64, 0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67,
	0x73, 0x49, 0x3e, 0x30, 0x78, 0x30, 0x3c, 0x2f, 0x45, 0x73, 0x74, 0x61,
	0x62, 0x6c, 0x69, 0x73, 0x68, 0x65, 0x64, 0x54, 0x69, 0x6d, 0x69, 0x6e,
	0x67, 0x73, 0x49, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x3c, 0x45, 0x73, 0x74, 0x61, 0x62, 0x6c, 0x69, 0x73, 0x68, 0x65,
	0x64, 0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x73, 0x49, 0x49, 0x3e, 0x30,
	0x78, 0x30, 0x3c, 0x2f, 0x45, 0x73, 0x74, 0x61, 0x62, 0x6c, 0x69, 0x73,
	0x68, 0x65, 0x64, 0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x73, 0x49, 0x49,
	0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x4d,
	0x61, 0x6e, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x73, 0x54,
	0x69, 0x6d, 0x69, 0x6e, 0x67, 0x3e, 0x30, 0x78, 0x30, 0x3c, 0x2f, 0x4d,
	0x61, 0x6e, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x73, 0x54,
	0x69, 0x6d, 0x69, 0x6e, 0x67, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x53, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x72, 0x64,
	0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x73, 0x31, 0x2f, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x53, 0x74, 0x61, 0x6e,
	0x64, 0x61, 0x72, 0x64, 0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x73, 0x32,
	0x2f, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x53, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x72, 0x64, 0x54, 0x69, 0x6d, 0x69,
	0x6e, 0x67, 0x73, 0x33, 0x2f, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x53, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x72, 0x64,
	0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x73, 0x34, 0x2f, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x53, 0x74, 0x61, 0x6e,
	0x64, 0x61, 0x72, 0x64, 0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x73, 0x35,
	0x2f, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x53, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x72, 0x64, 0x54, 0x69, 0x6d, 0x69,
	0x6e, 0x67, 0x73, 0x36, 0x2f, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x53, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x72, 0x64,
	0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x73, 0x37, 0x2f, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x53, 0x69, 0x67, 0x6e,
	0x61, 0x6c, 0x54, 0x69, 0x6d, 0x69, 0x6e, 0x67, 0x49, 0x6e, 0x74, 0x65,
	0x72, 0x66, 0x61, 0x63, 0x65, 0x2f, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x2f, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x3e, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x3c, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x20, 0x69, 0x64, 0x3d, 0x27,
	0x44, 0x65, 0x74, 0x61, 0x69, 0x6c, 0x65, 0x64, 0x20, 0x54, 0x69, 0x6d,
	0x69, 0x6e, 0x67, 0x27, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61,
	0x6c, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x53, 0x69, 0x7a, 0x65, 0x4d,
	0x4d, 0x3e, 0x30, 0x78, 0x34, 0x34, 0x3c, 0x2f, 0x48, 0x6f, 0x72, 0x69,
	0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6e,
	0x53, 0x69, 0x7a, 0x65, 0x4d, 0x4d, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x3c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61,
	0x6c, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x53, 0x69, 0x7a, 0x65, 0x4d,
	0x4d, 0x3e, 0x30, 0x78, 0x39, 0x33, 0x3c, 0x2f, 0x56, 0x65, 0x72, 0x74,
	0x69, 0x63, 0x61, 0x6c, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x53, 0x69,
	0x7a, 0x65, 0x4d, 0x4d, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61,
	0x6c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x53, 0x63, 0x72,
	0x65, 0x65, 0x6e, 0x53, 0x69, 0x7a, 0x65, 0x4d, 0x4d, 0x3e, 0x30, 0x78,
	0x30, 0x30, 0x3c, 0x2f, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74,
	0x61, 0x6c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x53, 0x63,
	0x72, 0x65, 0x65, 0x6e, 0x53, 0x69, 0x7a, 0x65, 0x4d, 0x4d, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x20,
	0x69, 0x64, 0x3d, 0x27, 0x41, 0x63, 0x74, 0x69, 0x76, 0x65, 0x20, 0x54,
	0x69, 0x6d, 0x69, 0x6e, 0x67, 0x27, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x3c, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c,
	0x41, 0x63, 0x74, 0x69, 0x76, 0x65, 0x3e, 0x31, 0x30, 0x38, 0x30, 0x3c,
	0x2f, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x41,
	0x63, 0x74, 0x69, 0x76, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x46,
	0x72, 0x6f, 0x6e, 0x74, 0x50, 0x6f, 0x72, 0x63, 0x68, 0x3e, 0x39, 0x36,
	0x3c, 0x2f, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c,
	0x46, 0x72, 0x6f, 0x6e, 0x74, 0x50, 0x6f, 0x72, 0x63, 0x68, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f,
	0x6e, 0x74, 0x61, 0x6c, 0x42, 0x61, 0x63, 0x6b, 0x50, 0x6f, 0x72, 0x63,
	0x68, 0x3e, 0x34, 0x30, 0x3c, 0x2f, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f,
	0x6e, 0x74, 0x61, 0x6c, 0x42, 0x61, 0x63, 0x6b, 0x50, 0x6f, 0x72, 0x63,
	0x68, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x6f, 0x72,
	0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x53, 0x79, 0x6e, 0x63, 0x50,
	0x75, 0x6c, 0x73, 0x65, 0x3e, 0x33, 0x32, 0x3c, 0x2f, 0x48, 0x6f, 0x72,
	0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x53, 0x79, 0x6e, 0x63, 0x50,
	0x75, 0x6c, 0x73, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x53, 0x79,
	0x6e, 0x63, 0x53, 0x6b, 0x65, 0x77, 0x3e, 0x30, 0x3c, 0x2f, 0x48, 0x6f,
	0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x53, 0x79, 0x6e, 0x63,
	0x53, 0x6b, 0x65, 0x77, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x4c, 0x65,
	0x66, 0x74, 0x42, 0x6f, 0x72, 0x64, 0x65, 0x72, 0x3e, 0x30, 0x3c, 0x2f,
	0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74, 0x61, 0x6c, 0x4c, 0x65,
	0x66, 0x74, 0x42, 0x6f, 0x72, 0x64, 0x65, 0x72, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x74,
	0x61, 0x6c, 0x52, 0x69, 0x67, 0x68, 0x74, 0x42, 0x6f, 0x72, 0x64, 0x65,
	0x72, 0x3e, 0x30, 0x3c, 0x2f, 0x48, 0x6f, 0x72, 0x69, 0x7a, 0x6f, 0x6e,
	0x74, 0x61, 0x6c, 0x52, 0x69, 0x67, 0x68, 0x74, 0x42, 0x6f, 0x72, 0x64,
	0x65, 0x72, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x56, 0x65,
	0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x41, 0x63, 0x74, 0x69, 0x76, 0x65,
	0x3e, 0x32, 0x33, 0x34, 0x30, 0x3c, 0x2f, 0x56, 0x65, 0x72, 0x74, 0x69,
	0x63, 0x61, 0x6c, 0x41, 0x63, 0x74, 0x69, 0x76, 0x65, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x3c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61,
	0x6c, 0x46, 0x72, 0x6f, 0x6e, 0x74, 0x50, 0x6f, 0x72, 0x63, 0x68, 0x3e,
	0x32, 0x35, 0x3c, 0x2f, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c,
	0x46, 0x72, 0x6f, 0x6e, 0x74, 0x50, 0x6f, 0x72, 0x63, 0x68, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63,
	0x61, 0x6c, 0x42, 0x61, 0x63, 0x6b, 0x50, 0x6f, 0x72, 0x63, 0x68, 0x3e,
	0x34, 0x3c, 0x2f, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x42,
	0x61, 0x63, 0x6b, 0x50, 0x6f, 0x72, 0x63, 0x68, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c,
	0x53, 0x79, 0x6e, 0x63, 0x50, 0x75, 0x6c, 0x73, 0x65, 0x3e, 0x31, 0x3c,
	0x2f, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x53, 0x79, 0x6e,
	0x63, 0x50, 0x75, 0x6c, 0x73, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x3c, 0x56, 0x65, 0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x53, 0x79,
	0x6e, 0x63, 0x53, 0x6b, 0x65, 0x77, 0x3e, 0x30, 0x3c, 0x2f, 0x56, 0x65,
	0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x53, 0x79, 0x6e, 0x63, 0x53, 0x6b,
	0x65, 0x77, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x56, 0x65,
	0x72, 0x74, 0x69, 0x63, 0x61, 0x6c, 0x54, 0x6f, 0x70, 0x42, 0x6f, 0x72,
	0x64, 0x65, 0x72, 0x3e, 0x30, 0x3c, 0x2f, 0x56, 0x65, 0x72, 0x74, 0x69,
	0x63, 0x61, 0x6c, 0x54, 0x6f, 0x70, 0x42, 0x6f, 0x72, 0x64, 0x65, 0x72,
	0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x56, 0x65, 0x72, 0x74,
	0x69, 0x63, 0x61, 0x6c, 0x42, 0x6f, 0x74, 0x74, 0x6f, 0x6d, 0x42, 0x6f,
	0x72, 0x64, 0x65, 0x72, 0x3e, 0x30, 0x3c, 0x2f, 0x56, 0x65, 0x72, 0x74,
	0x69, 0x63, 0x61, 0x6c, 0x42, 0x6f, 0x74, 0x74, 0x6f, 0x6d, 0x42, 0x6f,
	0x72, 0x64, 0x65, 0x72, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x49, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x44, 0x61, 0x74, 0x61, 0x50, 0x6f,
	0x6c, 0x61, 0x72, 0x69, 0x74, 0x79, 0x3e, 0x46, 0x61, 0x6c, 0x73, 0x65,
	0x3c, 0x2f, 0x49, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x44, 0x61, 0x74, 0x61,
	0x50, 0x6f, 0x6c, 0x61, 0x72, 0x69, 0x74, 0x79, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x49, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x56, 0x73,
	0x79, 0x6e, 0x63, 0x50, 0x6f, 0x6c, 0x61, 0x69, 0x72, 0x74, 0x79, 0x3e,
	0x46, 0x61, 0x6c, 0x73, 0x65, 0x3c, 0x2f, 0x49, 0x6e, 0x76, 0x65, 0x72,
	0x74, 0x56, 0x73, 0x79, 0x6e, 0x63, 0x50, 0x6f, 0x6c, 0x61, 0x69, 0x72,
	0x74, 0x79, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x49, 0x6e,
	0x76, 0x65, 0x72, 0x74, 0x48, 0x73, 0x79, 0x6e, 0x63, 0x50, 0x6f, 0x6c,
	0x61, 0x72, 0x69, 0x74, 0x79, 0x3e, 0x46, 0x61, 0x6c, 0x73, 0x65, 0x3c,
	0x2f, 0x49, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x48, 0x73, 0x79, 0x6e, 0x63,
	0x50, 0x6f, 0x6c, 0x61, 0x72, 0x69, 0x74, 0x79, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x42, 0x6f, 0x72, 0x64, 0x65, 0x72, 0x43, 0x6f,
	0x6c, 0x6f, 0x72, 0x3e, 0x30, 0x78, 0x30, 0x3c, 0x2f, 0x42, 0x6f, 0x72,
	0x64, 0x65, 0x72, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x2f, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x3e, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x20, 0x69, 0x64,
	0x3d, 0x27, 0x44, 0x69, 0x73, 0x70, 0x6c, 0x61, 0x79, 0x20, 0x49, 0x6e,
	0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x27, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63,
	0x65, 0x54, 0x79, 0x70, 0x65, 0x3e, 0x39, 0x3c, 0x2f, 0x49, 0x6e, 0x74,
	0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x54, 0x79, 0x70, 0x65, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66,
	0x61, 0x63, 0x65, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x46, 0x6f, 0x72, 0x6d,
	0x61, 0x74, 0x3e, 0x33, 0x3c, 0x2f, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66,
	0x61, 0x63, 0x65, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x46, 0x6f, 0x72, 0x6d,
	0x61, 0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x47, 0x72,
	0x6f, 0x75, 0x70, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x47, 0x72,
	0x6f, 0x75, 0x70, 0x20, 0x69, 0x64, 0x3d, 0x27, 0x44, 0x53, 0x49, 0x20,
	0x49, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x27, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x43, 0x68, 0x61,
	0x6e, 0x6e, 0x65, 0x6c, 0x49, 0x64, 0x3e, 0x32, 0x3c, 0x2f, 0x44, 0x53,
	0x49, 0x43, 0x68, 0x61, 0x6e, 0x6e, 0x65, 0x6c, 0x49, 0x64, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x56, 0x69, 0x72,
	0x74, 0x75, 0x61, 0x6c, 0x49, 0x64, 0x3e, 0x30, 0x3c, 0x2f, 0x44, 0x53,
	0x49, 0x56, 0x69, 0x72, 0x74, 0x75, 0x61, 0x6c, 0x49, 0x64, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x43, 0x6f, 0x6c,
	0x6f, 0x72, 0x46, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x3e, 0x33, 0x36, 0x3c,
	0x2f, 0x44, 0x53, 0x49, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x46, 0x6f, 0x72,
	0x6d, 0x61, 0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44,
	0x53, 0x49, 0x54, 0x72, 0x61, 0x66, 0x66, 0x69, 0x63, 0x4d, 0x6f, 0x64,
	0x65, 0x3e, 0x31, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x54, 0x72, 0x61, 0x66,
	0x66, 0x69, 0x63, 0x4d, 0x6f, 0x64, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x43, 0x50, 0x68, 0x79, 0x4d, 0x6f,
	0x64, 0x65, 0x3e, 0x54, 0x72, 0x75, 0x65, 0x3c, 0x2f, 0x44, 0x53, 0x49,
	0x43, 0x50, 0x68, 0x79, 0x4d, 0x6f, 0x64, 0x65, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x43, 0x6d, 0x64, 0x53, 0x77,
	0x61, 0x70, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x3e,
	0x46, 0x61, 0x6c, 0x73, 0x65, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x43, 0x6d,
	0x64, 0x53, 0x77, 0x61, 0x70, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61,
	0x63, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53,
	0x49, 0x54, 0x45, 0x43, 0x68, 0x65, 0x63, 0x6b, 0x45, 0x6e, 0x61, 0x62,
	0x6c, 0x65, 0x3e, 0x54, 0x72, 0x75, 0x65, 0x3c, 0x2f, 0x44, 0x53, 0x49,
	0x54, 0x45, 0x43, 0x68, 0x65, 0x63, 0x6b, 0x45, 0x6e, 0x61, 0x62, 0x6c,
	0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49,
	0x54, 0x45, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x44, 0x65, 0x64, 0x69, 0x63,
	0x61, 0x74, 0x65, 0x64, 0x54, 0x45, 0x50, 0x69, 0x6e, 0x3e, 0x54, 0x72,
	0x75, 0x65, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x54, 0x45, 0x55, 0x73, 0x69,
	0x6e, 0x67, 0x44, 0x65, 0x64, 0x69, 0x63, 0x61, 0x74, 0x65, 0x64, 0x54,
	0x45, 0x50, 0x69, 0x6e, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x44, 0x53, 0x49, 0x54, 0x45, 0x76, 0x53, 0x79, 0x6e, 0x63, 0x53, 0x74,
	0x61, 0x72, 0x74, 0x50, 0x6f, 0x73, 0x3e, 0x32, 0x33, 0x34, 0x30, 0x3c,
	0x2f, 0x44, 0x53, 0x49, 0x54, 0x45, 0x76, 0x53, 0x79, 0x6e, 0x63, 0x53,
	0x74, 0x61, 0x72, 0x74, 0x50, 0x6f, 0x73, 0x3e, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x54, 0x45, 0x76, 0x53, 0x79, 0x6e,
	0x63, 0x49, 0x6e, 0x69, 0x74, 0x56, 0x61, 0x6c, 0x3e, 0x32, 0x33, 0x34,
	0x30, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x54, 0x45, 0x76, 0x53, 0x79, 0x6e,
	0x63, 0x49, 0x6e, 0x69, 0x74, 0x56, 0x61, 0x6c, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43, 0x45, 0x6e,
	0x61, 0x62, 0x6c, 0x65, 0x3e, 0x54, 0x72, 0x75, 0x65, 0x3c, 0x2f, 0x44,
	0x53, 0x49, 0x44, 0x53, 0x43, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x44, 0x53,
	0x43, 0x4d, 0x61, 0x6a, 0x6f, 0x72, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f,
	0x6e, 0x3e, 0x31, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43, 0x4d,
	0x61, 0x6a, 0x6f, 0x72, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x44, 0x53,
	0x43, 0x4d, 0x69, 0x6e, 0x6f, 0x72, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f,
	0x6e, 0x3e, 0x31, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43, 0x4d,
	0x69, 0x6e, 0x6f, 0x72, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x44, 0x53,
	0x43, 0x53, 0x63, 0x72, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3e,
	0x30, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43, 0x53, 0x63, 0x72,
	0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43, 0x50, 0x72, 0x6f,
	0x66, 0x69, 0x6c, 0x65, 0x49, 0x44, 0x3e, 0x34, 0x3c, 0x2f, 0x44, 0x53,
	0x49, 0x44, 0x53, 0x43, 0x50, 0x72, 0x6f, 0x66, 0x69, 0x6c, 0x65, 0x49,
	0x44, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49,
	0x44, 0x53, 0x43, 0x53, 0x6c, 0x69, 0x63, 0x65, 0x57, 0x69, 0x64, 0x74,
	0x68, 0x3e, 0x35, 0x34, 0x30, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x44, 0x53,
	0x43, 0x53, 0x6c, 0x69, 0x63, 0x65, 0x57, 0x69, 0x64, 0x74, 0x68, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x44, 0x53,
	0x43, 0x53, 0x6c, 0x69, 0x63, 0x65, 0x48, 0x65, 0x69, 0x67, 0x68, 0x74,
	0x3e, 0x32, 0x30, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43, 0x53,
	0x6c, 0x69, 0x63, 0x65, 0x48, 0x65, 0x69, 0x67, 0x68, 0x74, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43,
	0x53, 0x6c, 0x69, 0x63, 0x65, 0x50, 0x65, 0x72, 0x50, 0x61, 0x63, 0x6b,
	0x65, 0x74, 0x3e, 0x32, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x44, 0x53, 0x43,
	0x53, 0x6c, 0x69, 0x63, 0x65, 0x50, 0x65, 0x72, 0x50, 0x61, 0x63, 0x6b,
	0x65, 0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53,
	0x49, 0x4c, 0x61, 0x6e, 0x65, 0x73, 0x3e, 0x33, 0x3c, 0x2f, 0x44, 0x53,
	0x49, 0x4c, 0x61, 0x6e, 0x65, 0x73, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x48, 0x73, 0x61, 0x48, 0x73,
	0x65, 0x41, 0x66, 0x74, 0x65, 0x72, 0x56, 0x73, 0x56, 0x65, 0x3e, 0x46,
	0x61, 0x6c, 0x73, 0x65, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x48, 0x73, 0x61,
	0x48, 0x73, 0x65, 0x41, 0x66, 0x74, 0x65, 0x72, 0x56, 0x73, 0x56, 0x65,
	0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53,
	0x49, 0x4c, 0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65, 0x72, 0x4d, 0x6f, 0x64,
	0x65, 0x49, 0x6e, 0x48, 0x46, 0x50, 0x3e, 0x46, 0x61, 0x6c, 0x73, 0x65,
	0x3c, 0x2f, 0x44, 0x53, 0x49, 0x4c, 0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65,
	0x72, 0x4d, 0x6f, 0x64, 0x65, 0x49, 0x6e, 0x48, 0x46, 0x50, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x4c,
	0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65, 0x72, 0x4d, 0x6f, 0x64, 0x65, 0x49,
	0x6e, 0x48, 0x42, 0x50, 0x3e, 0x46, 0x61, 0x6c, 0x73, 0x65, 0x3c, 0x2f,
	0x44, 0x53, 0x49, 0x4c, 0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65, 0x72, 0x4d,
	0x6f, 0x64, 0x65, 0x49, 0x6e, 0x48, 0x42, 0x50, 0x3e, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x4c, 0x6f, 0x77,
	0x50, 0x6f, 0x77, 0x65, 0x72, 0x4d, 0x6f, 0x64, 0x65, 0x49, 0x6e, 0x48,
	0x53, 0x41, 0x3e, 0x46, 0x61, 0x6c, 0x73, 0x65, 0x3c, 0x2f, 0x44, 0x53,
	0x49, 0x4c, 0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65, 0x72, 0x4d, 0x6f, 0x64,
	0x65, 0x49, 0x6e, 0x48, 0x53, 0x41, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x4c, 0x6f, 0x77, 0x50, 0x6f,
	0x77, 0x65, 0x72, 0x4d, 0x6f, 0x64, 0x65, 0x49, 0x6e, 0x42, 0x4c, 0x4c,
	0x50, 0x45, 0x4f, 0x46, 0x3e, 0x54, 0x72, 0x75, 0x65, 0x3c, 0x2f, 0x44,
	0x53, 0x49, 0x4c, 0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65, 0x72, 0x4d, 0x6f,
	0x64, 0x65, 0x49, 0x6e, 0x42, 0x4c, 0x4c, 0x50, 0x45, 0x4f, 0x46, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49,
	0x4c, 0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65, 0x72, 0x4d, 0x6f, 0x64, 0x65,
	0x49, 0x6e, 0x42, 0x4c, 0x4c, 0x50, 0x3e, 0x54, 0x72, 0x75, 0x65, 0x3c,
	0x2f, 0x44, 0x53, 0x49, 0x4c, 0x6f, 0x77, 0x50, 0x6f, 0x77, 0x65, 0x72,
	0x4d, 0x6f, 0x64, 0x65, 0x49, 0x6e, 0x42, 0x4c, 0x4c, 0x50, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x52,
	0x65, 0x66, 0x72, 0x65, 0x73, 0x68, 0x52, 0x61, 0x74, 0x65, 0x3e, 0x30,
	0x78, 0x33, 0x43, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x2f, 0x44, 0x53, 0x49,
	0x52, 0x65, 0x66, 0x72, 0x65, 0x73, 0x68, 0x52, 0x61, 0x74, 0x65, 0x3e,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x43, 0x6d,
	0x64, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x54, 0x72, 0x69, 0x67, 0x67, 0x65,
	0x72, 0x3e, 0x46, 0x61, 0x6c, 0x73, 0x65, 0x3c, 0x2f, 0x44, 0x53, 0x49,
	0x43, 0x6d, 0x64, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x54, 0x72, 0x69, 0x67,
	0x67, 0x65, 0x72, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44,
	0x53, 0x49, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x41, 0x75, 0x74, 0x6f,
	0x52, 0x65, 0x66, 0x72, 0x65, 0x73, 0x68, 0x3e, 0x54, 0x72, 0x75, 0x65,
	0x3c, 0x2f, 0x44, 0x53, 0x49, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x41,
	0x75, 0x74, 0x6f, 0x52, 0x65, 0x66, 0x72, 0x65, 0x73, 0x68, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x41, 0x75, 0x74,
	0x6f, 0x52, 0x65, 0x66, 0x72, 0x65, 0x73, 0x68, 0x46, 0x72, 0x61, 0x6d,
	0x65, 0x4e, 0x75, 0x6d, 0x44, 0x69, 0x76, 0x3e, 0x31, 0x3c, 0x2f, 0x44,
	0x53, 0x49, 0x41, 0x75, 0x74, 0x6f, 0x52, 0x65, 0x66, 0x72, 0x65, 0x73,
	0x68, 0x46, 0x72, 0x61, 0x6d, 0x65, 0x4e, 0x75, 0x6d, 0x44, 0x69, 0x76,
	0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x44, 0x53, 0x49, 0x43,
	0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x6c, 0x65, 0x72, 0x4d, 0x61, 0x70,
	0x70, 0x69, 0x6e, 0x67, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x30, 0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x44, 0x53,
	0x49, 0x43, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x6c, 0x65, 0x72, 0x4d,
	0x61, 0x70, 0x70, 0x69, 0x6e, 0x67, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x2f, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x3e, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x3c, 0x44, 0x53, 0x49, 0x49, 0x6e, 0x69, 0x74, 0x53, 0x65, 0x71,
	0x75, 0x65, 0x6e, 0x63, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x33, 0x39, 0x20, 0x62, 0x30, 0x20, 0x30, 0x30, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x33, 0x39, 0x20, 0x65, 0x62, 0x20, 0x30, 0x30, 0x20, 0x30,
	0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x66, 0x37,
	0x20, 0x30, 0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20,
	0x62, 0x30, 0x20, 0x30, 0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33,
	0x39, 0x20, 0x64, 0x38, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30,
	0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30,
	0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x35, 0x62, 0x20, 0x30,
	0x30, 0x20, 0x35, 0x62, 0x20, 0x30, 0x30, 0x20, 0x35, 0x62, 0x20, 0x30,
	0x30, 0x20, 0x35, 0x62, 0x20, 0x30, 0x30, 0x20, 0x35, 0x62, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x62, 0x30, 0x20, 0x38, 0x30,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x65, 0x36, 0x20,
	0x30, 0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x62,
	0x30, 0x20, 0x30, 0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39,
	0x20, 0x62, 0x36, 0x20, 0x36, 0x63, 0x20, 0x30, 0x30, 0x20, 0x30, 0x36,
	0x20, 0x32, 0x33, 0x20, 0x61, 0x66, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x33, 0x39, 0x20, 0x62, 0x34, 0x20, 0x32, 0x30, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x33, 0x39, 0x20, 0x63, 0x66, 0x20, 0x36, 0x34, 0x20, 0x30,
	0x62, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30,
	0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x38, 0x20, 0x30,
	0x30, 0x20, 0x30, 0x62, 0x20, 0x37, 0x37, 0x20, 0x30, 0x31, 0x20, 0x30,
	0x31, 0x20, 0x30, 0x31, 0x20, 0x30, 0x31, 0x20, 0x30, 0x31, 0x20, 0x30,
	0x31, 0x20, 0x30, 0x34, 0x20, 0x30, 0x34, 0x20, 0x30, 0x34, 0x20, 0x30,
	0x34, 0x20, 0x30, 0x34, 0x20, 0x30, 0x35, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x33, 0x39, 0x20, 0x62, 0x30, 0x20, 0x30, 0x34, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x66, 0x37, 0x20, 0x30, 0x31, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x64, 0x66, 0x20, 0x35,
	0x30, 0x20, 0x34, 0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39,
	0x20, 0x66, 0x33, 0x20, 0x35, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30,
	0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x33, 0x39, 0x20, 0x66, 0x32, 0x20, 0x31, 0x31, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x33, 0x39, 0x20, 0x66, 0x33, 0x20, 0x30, 0x31, 0x20, 0x30,
	0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x31, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x66, 0x34, 0x20, 0x30, 0x30,
	0x20, 0x30, 0x32, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20,
	0x66, 0x32, 0x20, 0x31, 0x39, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33,
	0x39, 0x20, 0x64, 0x66, 0x20, 0x35, 0x30, 0x20, 0x34, 0x32, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x33, 0x35, 0x20, 0x30, 0x30,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x32, 0x61, 0x20,
	0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x34, 0x20, 0x33, 0x37, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x33, 0x39, 0x20, 0x32, 0x62, 0x20, 0x30,
	0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x39, 0x20, 0x32, 0x33, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x30, 0x35, 0x20, 0x31, 0x31, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x66, 0x66, 0x20, 0x37, 0x38, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x30, 0x35, 0x20, 0x32, 0x39, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x2f, 0x44, 0x53, 0x49, 0x49, 0x6e, 0x69, 0x74, 0x53, 0x65, 0x71,
	0x75, 0x65, 0x6e, 0x63, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x44, 0x53, 0x49, 0x54, 0x65, 0x72, 0x6d, 0x53, 0x65, 0x71, 0x75, 0x65,
	0x6e, 0x63, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x35,
	0x20, 0x32, 0x38, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x66, 0x20,
	0x31, 0x34, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x35, 0x20, 0x31,
	0x30, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x66, 0x20, 0x37, 0x38,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x44, 0x53, 0x49, 0x54, 0x65,
	0x72, 0x6d, 0x53, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63, 0x65, 0x3e, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x3c, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x20, 0x69,
	0x64, 0x3d, 0x27, 0x42, 0x61, 0x63, 0x6b, 0x6c, 0x69, 0x67, 0x68, 0x74,
	0x20, 0x43, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x75, 0x72, 0x61, 0x74, 0x69,
	0x6f, 0x6e, 0x27, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x42,
	0x61, 0x63, 0x6b, 0x6c, 0x69, 0x67, 0x68, 0x74, 0x54, 0x79, 0x70, 0x65,
	0x3e, 0x33, 0x3c, 0x2f, 0x42, 0x61, 0x63, 0x6b, 0x6c, 0x69, 0x67, 0x68,
	0x74, 0x54, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x42, 0x61, 0x63, 0x6b, 0x6c, 0x69, 0x67, 0x68, 0x74, 0x42, 0x69,
	0x74, 0x57, 0x69, 0x64, 0x74, 0x68, 0x3e, 0x31, 0x32, 0x3c, 0x2f, 0x42,
	0x61, 0x63, 0x6b, 0x6c, 0x69, 0x67, 0x68, 0x74, 0x42, 0x69, 0x74, 0x57,
	0x69, 0x64, 0x74, 0x68, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
	0x44, 0x69, 0x73, 0x70, 0x6c, 0x61, 0x79, 0x52, 0x65, 0x73, 0x65, 0x74,
	0x49, 0x6e, 0x66, 0x6f, 0x3e, 0x30, 0x20, 0x31, 0x30, 0x20, 0x31, 0x30,
	0x30, 0x30, 0x20, 0x31, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x3c, 0x2f,
	0x44, 0x69, 0x73, 0x70, 0x6c, 0x61, 0x79, 0x52, 0x65, 0x73, 0x65, 0x74,
	0x49, 0x6e, 0x66, 0x6f, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f,
	0x47, 0x72, 0x6f, 0x75, 0x70, 0x3e, 0x20, 0x20, 0x20, 0x20, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x00
                })
                While(One)
                {
                    Name(_T_0, Zero)
                    Store(ToInteger(Arg2, ), _T_0)
                    If(LEqual(_T_0, 0x6f00))
                    {
                        Store(PCFG, Local2)
                    }
                    Else
                    {
                        Store(PCFG, Local2)
                    }
                    Break
                }
                If(LNot(LLess(Arg0, SizeOf(Local2))))
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
                Else
                {
                    Store(Arg0, Local0)
                }
                If(LGreater(Arg1, 0x1000))
                {
                    Store(0x1000, Local1)
                }
                Else
                {
                    Store(Arg1, Local1)
                }
                If(LGreater(Add(Local0, Local1, ), SizeOf(Local2)))
                {
                    Subtract(SizeOf(Local2), Local0, Local1)
                }
                CreateField(Local2, Multiply(0x8, Local0, ), Multiply(0x8, Local1, ), RBUF)
                Return(RBUF)
            }
            Method(PGRT, 0x2, NotSerialized)
            {
                Name(RBUF, Buffer(One)
                {
	0x00
                })
                Return(RBUF)
            }
            Method(PBRT, 0x2, NotSerialized)
            {
                Name(RBUF, Buffer(One)
                {
	0x00
                })
                Return(RBUF)
            }
            Method(ROE1, 0x3, NotSerialized)
            {
                Name(PCFG, Buffer(One)
                {
	0x00
                })
                Store(PCFG, Local2)
                If(LNot(LLess(Arg0, SizeOf(Local2))))
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
                Else
                {
                    Store(Arg0, Local0)
                }
                If(LGreater(Arg1, 0x1000))
                {
                    Store(0x1000, Local1)
                }
                Else
                {
                    Store(Arg1, Local1)
                }
                If(LGreater(Add(Local0, Local1, ), SizeOf(Local2)))
                {
                    Subtract(SizeOf(Local2), Local0, Local1)
                }
                CreateField(Local2, Multiply(0x8, Local0, ), Multiply(0x8, Local1, ), RBUF)
                Return(RBUF)
            }
            Method(ROE2, 0x3, NotSerialized)
            {
                Name(PCFG, Buffer(One)
                {
	0x00
                })
                Store(PCFG, Local2)
                If(LNot(LLess(Arg0, SizeOf(Local2))))
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
                Else
                {
                    Store(Arg0, Local0)
                }
                If(LGreater(Arg1, 0x1000))
                {
                    Store(0x1000, Local1)
                }
                Else
                {
                    Store(Arg1, Local1)
                }
                If(LGreater(Add(Local0, Local1, ), SizeOf(Local2)))
                {
                    Subtract(SizeOf(Local2), Local0, Local1)
                }
                CreateField(Local2, Multiply(0x8, Local0, ), Multiply(0x8, Local1, ), RBUF)
                Return(RBUF)
            }
            Method(ROE3, 0x3, NotSerialized)
            {
                Name(PCFG, Buffer(One)
                {
	0x00
                })
                Store(PCFG, Local2)
                If(LNot(LLess(Arg0, SizeOf(Local2))))
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
                Else
                {
                    Store(Arg0, Local0)
                }
                If(LGreater(Arg1, 0x1000))
                {
                    Store(0x1000, Local1)
                }
                Else
                {
                    Store(Arg1, Local1)
                }
                If(LGreater(Add(Local0, Local1, ), SizeOf(Local2)))
                {
                    Subtract(SizeOf(Local2), Local0, Local1)
                }
                CreateField(Local2, Multiply(0x8, Local0, ), Multiply(0x8, Local1, ), RBUF)
                Return(RBUF)
            }
            Method(ROE4, 0x3, NotSerialized)
            {
                Name(PCFG, Buffer(One)
                {
	0x00
                })
                Store(PCFG, Local2)
                If(LNot(LLess(Arg0, SizeOf(Local2))))
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
                Else
                {
                    Store(Arg0, Local0)
                }
                If(LGreater(Arg1, 0x1000))
                {
                    Store(0x1000, Local1)
                }
                Else
                {
                    Store(Arg1, Local1)
                }
                If(LGreater(Add(Local0, Local1, ), SizeOf(Local2)))
                {
                    Subtract(SizeOf(Local2), Local0, Local1)
                }
                CreateField(Local2, Multiply(0x8, Local0, ), Multiply(0x8, Local1, ), RBUF)
                Return(RBUF)
            }
            Method(ROE5, 0x3, NotSerialized)
            {
                Name(PCFG, Buffer(One)
                {
	0x00
                })
                Store(PCFG, Local2)
                If(LNot(LLess(Arg0, SizeOf(Local2))))
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
                Else
                {
                    Store(Arg0, Local0)
                }
                If(LGreater(Arg1, 0x1000))
                {
                    Store(0x1000, Local1)
                }
                Else
                {
                    Store(Arg1, Local1)
                }
                If(LGreater(Add(Local0, Local1, ), SizeOf(Local2)))
                {
                    Subtract(SizeOf(Local2), Local0, Local1)
                }
                CreateField(Local2, Multiply(0x8, Local0, ), Multiply(0x8, Local1, ), RBUF)
                Return(RBUF)
            }
            Method(ROE6, 0x3, NotSerialized)
            {
                Name(PCFG, Buffer(One)
                {
	0x00
                })
                Store(PCFG, Local2)
                If(LNot(LLess(Arg0, SizeOf(Local2))))
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
                Else
                {
                    Store(Arg0, Local0)
                }
                If(LGreater(Arg1, 0x1000))
                {
                    Store(0x1000, Local1)
                }
                Else
                {
                    Store(Arg1, Local1)
                }
                If(LGreater(Add(Local0, Local1, ), SizeOf(Local2)))
                {
                    Subtract(SizeOf(Local2), Local0, Local1)
                }
                CreateField(Local2, Multiply(0x8, Local0, ), Multiply(0x8, Local1, ), RBUF)
                Return(RBUF)
            }
            Name(_DOD, Package(One)
            {
                0x24321
            })
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_HRV, 0x0, NotSerialized)
            {
                Name(RESU, Zero)
                Name(TIER, Zero)
                Name(DREV, Zero)
                Name(FAMI, Zero)
                Name(PROD, Zero)
                And(\_SB_.SIDT, 0xf, TIER)
                And(ShiftRight(\_SB_.SJTG, 0x1c, ), 0xf, DREV)
                ShiftLeft(DREV, 0x4, DREV)
                And(ShiftRight(\_SB_.SJTG, 0xc, ), 0xffff, PROD)
                If(Or(LEqual(PROD, 0x193), LEqual(PROD, 0x1eb), ))
                {
                    ShiftLeft(One, 0x8, FAMI)
                }
                If(LEqual(PROD, 0x194))
                {
                    ShiftLeft(0x2, 0x8, FAMI)
                }
                If(Or(LEqual(PROD, 0x1e3), LEqual(PROD, 0x20a), ))
                {
                    ShiftLeft(0x3, 0x8, FAMI)
                }
                Or(TIER, RESU, RESU)
                Or(DREV, RESU, RESU)
                Or(FAMI, RESU, RESU)
                Return(RESU)
            }
            Device(AVS0)
            {
                Name(_ADR, 0x24321)
                Method(_CRS, 0x0, NotSerialized)
                {
                    Name(RBUF, Buffer(0x2)
                    {
	0x79, 0x00
                    })
                    Return(RBUF)
                }
                Name(_DEP, Package(0x3)
                {
                    \_SB_.MMU0,
                    \_SB_.IMM0,
                    \_SB_.VFE0
                })
            }
            Method(CHDV, 0x0, NotSerialized)
            {
                Name(CHIF, Package(0x2)
                {
                    One,
                    Package(0x7)
                    {
                        "CHILDDEV",
                        Zero,
                        0x24321,
                        "QCOM_AVStream_7280",
                        Zero,
                        "Qualcomm Camera AVStream Mini Driver",
                        Package(0x4)
                        {
                            "COMPATIBLEIDS",
                            0x2,
                            "VEN_QCOM&DEV__AVSTREAM",
                            "QCOM_AVSTREAM"
                        }
                    }
                })
                Return(CHIF)
            }
        }
        Device(SCM0)
        {
            Name(_HID, "QCOM04DD")
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
        }
        Device(TLOG)
        {
            Name(_HID, "QCOM0AE3")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
        }
        Device(TREE)
        {
            Name(_HID, "QCOM04DE")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x31)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x88,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x86,
	0x09, 0x00, 0x01, 0xef, 0xbe, 0xad, 0xde, 0xad, 0xde, 0xef, 0xbe, 0x79,
	0x00
                })
                CreateDWordField(RBUF, 0x27, TGCA)
                CreateDWordField(RBUF, 0x2b, TGCL)
                Store(\_SB_.TCMA, TGCA)
                Store(\_SB_.TCML, TGCL)
                Return(RBUF)
            }
        }
        Device(SPMI)
        {
            Name(_HID, "QCOM0A0B")
            Alias(\_SB_.PSUB, _SUB)
            Name(_CID, "PNP0CA2")
            Name(_UID, One)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0xe)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x40, 0x0c, 0x00, 0x00, 0x80, 0x02,
	0x79, 0x00
                })
                Return(RBUF)
            }
            Method(CONF, 0x0, NotSerialized)
            {
                Name(XBUF, Buffer(0x1a)
                {
	0x00, 0x01, 0x01, 0x01, 0xff, 0x00, 0x02, 0x00, 0x0a, 0x07, 0x04, 0x07,
	0x01, 0xff, 0x10, 0x01, 0x00, 0x01, 0x0c, 0x40, 0x00, 0x00, 0x02, 0x80,
	0x00, 0x00
                })
                Return(XBUF)
            }
        }
        Device(GIO0)
        {
            Name(_HID, "QCOM0A0C")
            Name(_UID, Zero)
            Alias(\_SB_.PSUB, _SUB)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x44)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x10, 0x0f, 0x00, 0x00, 0x30, 0x00,
	0x89, 0x06, 0x00, 0x09, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x09, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x09, 0x01, 0xf0,
	0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x09, 0x01, 0x2e, 0x02, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x09, 0x01, 0x28, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x01, 0x01, 0x85, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Method(OFNI, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x2)
                {
	0xaf, 0x00
                })
                Return(RBUF)
            }
            Name(GABL, Zero)
            Method(_REG, 0x2, NotSerialized)
            {
                If(LEqual(Arg0, 0x8))
                {
                    Store(Arg1, GABL)
                }
            }
            Method(_AEI, 0x0, NotSerialized)
            {
                Name(RBF0, Buffer(0x25)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00,
	0xf4, 0x01, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x79,
	0x00
                })
                Return(RBF0)
            }
            Method(_EBD, 0x0, NotSerialized)
            {
                Notify(\_SB_.GPU0, 0x92)
            }
            Method(_DSM, 0x4, NotSerialized)
            {
                If(LEqual(Arg0, Buffer(0x10)
                {
	0x40, 0x8f, 0x24, 0x4f, 0xe2, 0xd5, 0x9f, 0x49, 0x83, 0x4c, 0x27, 0x75,
	0x8e, 0xa1, 0xcd, 0x3f
                }))
                {
                    While(One)
                    {
                        Name(_T_0, Zero)
                        Store(Arg2, _T_0)
                        If(LEqual(_T_0, Zero))
                        {
                            Return(Buffer(One)
                            {
	0x03
                            })
                        }
                        Else
                        {
                            If(LEqual(_T_0, One))
                            {
                                Return(Package(One)
                                {
                                    0x100
                                })
                            }
                            Else
                            {
                                BreakPoint
                            }
                        }
                        Break
                    }
                }
                Else
                {
                    Return(Buffer(One)
                    {
	0x00
                    })
                }
            }
        }
        Device(IPCC)
        {
            Name(_HID, "QCOM06C2")
            Name(_UID, Zero)
            Alias(\_SB_.PSUB, _SUB)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x26)
                {
	0x89, 0x06, 0x00, 0x03, 0x01, 0x05, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x06, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x07,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xea, 0x02, 0x00, 0x00,
	0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(PCI1)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.PEP0,
                \_SB_.QPPX
            })
            Name(_HID, 0x80ad041)
            Name(_CID, 0x30ad041)
            Name(_UID, One)
            Name(_SEG, One)
            Name(_BBN, Zero)
            Name(_PRT, Package(0x4)
            {
                Package(0x4)
                {
                    0xffff,
                    Zero,
                    Zero,
                    0x1d2
                },
                Package(0x4)
                {
                    0xffff,
                    One,
                    Zero,
                    0x1d3
                },
                Package(0x4)
                {
                    0xffff,
                    0x2,
                    Zero,
                    0x1d6
                },
                Package(0x4)
                {
                    0xffff,
                    0x3,
                    Zero,
                    0x1d7
                }
            })
            Method(_CCA, 0x0, NotSerialized)
            {
                Return(One)
            }
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(PRP1, One))
                {
                    Return(0xf)
                }
                Else
                {
                    Return(Zero)
                }
            }
            Method(_PSC, 0x0, NotSerialized)
            {
                Return(Zero)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x1e)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x30, 0x40, 0x00, 0x00, 0xd0, 0x01,
	0x88, 0x0d, 0x00, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x02, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Name(SUPP, Zero)
            Name(CTRL, Zero)
            Method(_DSW, 0x3, NotSerialized)
            {
            }
            Method(_OSC, 0x4, NotSerialized)
            {
                If(LEqual(Arg0, Buffer(0x10)
                {
	0x5b, 0x4d, 0xdb, 0x33, 0xf7, 0x1f, 0x1c, 0x40, 0x96, 0x57, 0x74, 0x41,
	0xc0, 0x3d, 0xd7, 0x66
                }))
                {
                    CreateDWordField(Arg3, Zero, CDW1)
                    CreateDWordField(Arg3, 0x4, CDW2)
                    CreateDWordField(Arg3, 0x8, CDW3)
                    Store(CDW2, SUPP)
                    Store(CDW3, CTRL)
                    If(LNot(LEqual(And(SUPP, 0x16, ), 0x16)))
                    {
                        And(CTRL, 0x1e, CTRL)
                    }
                    And(CTRL, 0x15, CTRL)
                    If(LNot(LEqual(Arg1, One)))
                    {
                        Or(CDW1, 0x8, CDW1)
                    }
                    If(LNot(LEqual(CDW3, CTRL)))
                    {
                        Or(CDW1, 0x10, CDW1)
                    }
                    Store(CTRL, CDW3)
                    Return(Arg3)
                }
                Else
                {
                    Or(CDW1, 0x4, CDW1)
                    Return(Arg3)
                }
            }
            Method(_DSM, 0x4, NotSerialized)
            {
                If(LEqual(Arg0, Buffer(0x10)
                {
	0xd0, 0x37, 0xc9, 0xe5, 0x53, 0x35, 0x7a, 0x4d, 0x91, 0x17, 0xea, 0x4d,
	0x19, 0xc3, 0x43, 0x4d
                }))
                {
                    While(One)
                    {
                        Name(_T_0, Zero)
                        Store(ToInteger(Arg2, ), _T_0)
                        If(LEqual(_T_0, Zero))
                        {
                            Return(Buffer(0x2)
                            {
	0xff, 0x03
                            })
                        }
                        Else
                        {
                            If(LEqual(_T_0, One))
                            {
                                Return(Package(0x2)
                                {
                                    Package(One)
                                    {
                                        One
                                    },
                                    Package(0x3)
                                    {
                                        Zero,
                                        One,
                                        One
                                    }
                                })
                            }
                            Else
                            {
                                If(LEqual(_T_0, 0x2))
                                {
                                    Return(Package(One)
                                    {
                                        Package(0x4)
                                        {
                                            One,
                                            0x3,
                                            Zero,
                                            0x7
                                        }
                                    })
                                }
                                Else
                                {
                                    If(LEqual(_T_0, 0x3))
                                    {
                                        Return(Package(One)
                                        {
                                            Zero
                                        })
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_0, 0x4))
                                        {
                                            Return(Package(0x2)
                                            {
                                                Package(One)
                                                {
                                                    Zero
                                                },
                                                Package(0x4)
                                                {
                                                    One,
                                                    0x3,
                                                    Zero,
                                                    0x7
                                                }
                                            })
                                        }
                                        Else
                                        {
                                            If(LEqual(_T_0, 0x5))
                                            {
                                                Return(Package(One)
                                                {
                                                    One
                                                })
                                            }
                                            Else
                                            {
                                                If(LEqual(_T_0, 0x6))
                                                {
                                                    Return(Package(0x4)
                                                    {
                                                        Package(One)
                                                        {
                                                            Zero
                                                        },
                                                        Package(One)
                                                        {
                                                            Zero
                                                        },
                                                        Package(One)
                                                        {
                                                            Zero
                                                        },
                                                        Package(One)
                                                        {
                                                            Zero
                                                        }
                                                    })
                                                }
                                                Else
                                                {
                                                    If(LEqual(_T_0, 0x7))
                                                    {
                                                        Return(Package(One)
                                                        {
                                                            One
                                                        })
                                                    }
                                                    Else
                                                    {
                                                        If(LEqual(_T_0, 0x8))
                                                        {
                                                            Return(Package(One)
                                                            {
                                                                One
                                                            })
                                                        }
                                                        Else
                                                        {
                                                            If(LEqual(_T_0, 0x9))
                                                            {
                                                                Return(Package(0x5)
                                                                {
                                                                    0xffffffff,
                                                                    0xffffffff,
                                                                    0xffffffff,
                                                                    Zero,
                                                                    0xffffffff
                                                                })
                                                            }
                                                            Else
                                                            {
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Break
                    }
                }
            }
            Name(_S0W, 0x4)
            Name(_PR0, Package(One)
            {
                \_SB_.P1RR
            })
            Name(_PR3, Package(One)
            {
                \_SB_.P1RR
            })
            Device(RP1_)
            {
                Method(_ADR, 0x0, Serialized)
                {
                    Return(Zero)
                }
                Name(_PR0, Package(One)
                {
                    \_SB_.R1RR
                })
                Name(_PR3, Package(One)
                {
                    \_SB_.R1RR
                })
                Name(_PRR, Package(One)
                {
                    \_SB_.R1RR
                })
                Name(_S0W, 0x4)
                Name(_DSD, Package(0x2)
                {
                    Buffer(0x10)
                    {
	0xc0, 0xe2, 0x11, 0x62, 0xa3, 0x58, 0xf3, 0x4a, 0x90, 0xe1, 0x92, 0x7a,
	0x4e, 0x0c, 0x55, 0xa4
                    },
                    Package(One)
                    {
                        Package(0x2)
                        {
                            "HotPlugSupportInD3",
                            One
                        }
                    }
                })
                Method(_CRS, 0x0, NotSerialized)
                {
                    Name(RBUF, Buffer(0x25)
                    {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x13, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x79,
	0x00
                    })
                    Return(RBUF)
                }
                Method(_DSM, 0x4, NotSerialized)
                {
                    If(LEqual(Arg0, Buffer(0x10)
                    {
	0xd0, 0x37, 0xc9, 0xe5, 0x53, 0x35, 0x7a, 0x4d, 0x91, 0x17, 0xea, 0x4d,
	0x19, 0xc3, 0x43, 0x4d
                    }))
                    {
                        While(One)
                        {
                            Name(_T_0, Zero)
                            Store(ToInteger(Arg2, ), _T_0)
                            If(LEqual(_T_0, Zero))
                            {
                                Return(Buffer(0x2)
                                {
	0x01, 0x03
                                })
                            }
                            Else
                            {
                                If(LEqual(_T_0, 0x8))
                                {
                                    Return(Package(One)
                                    {
                                        One
                                    })
                                }
                                Else
                                {
                                    If(LEqual(_T_0, 0x9))
                                    {
                                        Return(Package(0x5)
                                        {
                                            0xffffffff,
                                            0xffffffff,
                                            0xffffffff,
                                            Zero,
                                            0xffffffff
                                        })
                                    }
                                    Else
                                    {
                                    }
                                }
                            }
                            Break
                        }
                    }
                }
            }
        }
        PowerResource(P1RR, 0x5, 0x0)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
            Method(_ON_, 0x0, NotSerialized)
            {
            }
            Method(_OFF, 0x0, NotSerialized)
            {
            }
        }
        PowerResource(R1RR, 0x5, 0x0)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
            Method(_ON_, 0x0, NotSerialized)
            {
            }
            Method(_OFF, 0x0, NotSerialized)
            {
            }
            Method(_RST, 0x0, NotSerialized)
            {
            }
        }
        Device(QPPX)
        {
            Name(_HID, "QCOM0A96")
            Name(_UID, Zero)
            Name(_CCA, Zero)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, Serialized)
            {
                Name(RBUF, Buffer(0x26)
                {
	0x8c, 0x21, 0x00, 0x01, 0x01, 0x01, 0x00, 0x08, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x01, 0x00, 0x02,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x01,
	0x79, 0x00
                })
                Return(RBUF)
            }
            Method(_QPG, 0x0, Serialized)
            {
                Return(Package(One)
                {
                    One
                })
            }
        }
        Device(IPC0)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.GLNK
            })
            Name(_HID, "QCOM0A0D")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(GLNK)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.IPCC,
                \_SB_.RPEN
            })
            Name(_HID, "QCOM0A84")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
        }
        Device(ARPC)
        {
            Name(_DEP, Package(0x4)
            {
                \_SB_.MMU0,
                \_SB_.GLNK,
                \_SB_.SCM0,
                \_SB_.IMM0
            })
            Name(_HID, "QCOM0A5C")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(ARPD)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.ADSP,
                \_SB_.ARPC
            })
            Name(_HID, "QCOM0A82")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(RFS0)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Name(_HID, "QCOM0A15")
            Alias(\_SB_.PSUB, _SUB)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x26)
                {
	0x86, 0x09, 0x00, 0x01, 0x88, 0x88, 0x88, 0x88, 0x99, 0x99, 0x99, 0x99,
	0x86, 0x09, 0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22,
	0x86, 0x09, 0x00, 0x01, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44,
	0x79, 0x00
                })
                CreateDWordField(RBUF, 0x4, RMTA)
                CreateDWordField(RBUF, 0x8, RMTL)
                CreateDWordField(RBUF, 0x10, RFMA)
                CreateDWordField(RBUF, 0x14, RFML)
                CreateDWordField(RBUF, 0x1c, RFAA)
                CreateDWordField(RBUF, 0x20, RFAL)
                Store(\_SB_.RMTB, RMTA)
                Store(\_SB_.RMTX, RMTL)
                Store(\_SB_.RFMB, RFMA)
                Store(\_SB_.RFMS, RFML)
                Store(\_SB_.RFAB, RFAA)
                Store(\_SB_.RFAS, RFAL)
                Return(RBUF)
            }
        }
        Scope(\_SB_.RFS0)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xb)
            }
        }
        Device(IPA_)
        {
            Name(_DEP, Package(0x6)
            {
                \_SB_.PEP0,
                \_SB_.RPEN,
                \_SB_.TREE,
                \_SB_.MMU0,
                \_SB_.GLNK,
                \_SB_.IPC0
            })
            Name(_HID, "QCOM0A6A")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Return(Buffer(0x2c)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xe4, 0x01, 0x00, 0x00, 0x06, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xae, 0x02, 0x00, 0x00, 0x86, 0x09, 0x00,
	0x01, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x03, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xd0, 0x01, 0x00, 0x00, 0x79, 0x00
                })
            }
            Device(NTAD)
            {
                Name(_ADR, One)
            }
        }
        Scope(\_SB_.IPA_)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(QDIG)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.GLNK
            })
            Name(_HID, "QCOM0A13")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(SSM_)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.GLNK,
                \_SB_.TREE
            })
            Name(_HID, "QCOM0A14")
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
        }
        Device(SYSM)
        {
            Name(_HID, "ACPI0010")
            Name(_UID, 0x100000)
            Name(_LPI, Package(0x4)
            {
                Zero,
                0x1000000,
                One,
                Package(0xa)
                {
                    0x251c,
                    0x1770,
                    One,
                    0x20,
                    Zero,
                    Zero,
                    0xb300,
                    Buffer(0x11)
                    {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                    },
                    Buffer(0x11)
                    {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                    },
                    "platform.DRIPS"
                }
            })
            Device(CLUS)
            {
                Name(_HID, "ACPI0010")
                Name(_UID, 0x10)
                Name(_LPI, Package(0x5)
                {
                    Zero,
                    0x1000000,
                    0x2,
                    Package(0xa)
                    {
                        0x170c,
                        0xbb8,
                        Zero,
                        Zero,
                        Zero,
                        Zero,
                        0x20,
                        Buffer(0x11)
                        {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                        },
                        Buffer(0x11)
                        {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                        },
                        "L3Cluster.D2"
                    },
                    Package(0xa)
                    {
                        0x1770,
                        0xce4,
                        One,
                        Zero,
                        Zero,
                        One,
                        0x40,
                        Buffer(0x11)
                        {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                        },
                        Buffer(0x11)
                        {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                        },
                        "L3Cluster.D4"
                    }
                })
                Device(CPU0)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, Zero)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver0.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver0.C2"
                        },
                        Package(0xa)
                        {
                            0x6ee,
                            0x385,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver0.C3"
                        },
                        Package(0xa)
                        {
                            0xfa1,
                            0x393,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver0.C4"
                        }
                    })
                }
                Device(CPU1)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, One)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver1.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver1.C2"
                        },
                        Package(0xa)
                        {
                            0x6ee,
                            0x385,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver1.C3"
                        },
                        Package(0xa)
                        {
                            0xfa1,
                            0x393,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver1.C4"
                        }
                    })
                }
                Device(CPU2)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, 0x2)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver2.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver2.C2"
                        },
                        Package(0xa)
                        {
                            0x6ee,
                            0x385,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver2.C3"
                        },
                        Package(0xa)
                        {
                            0xfa1,
                            0x393,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver2.C4"
                        }
                    })
                }
                Device(CPU3)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, 0x3)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver3.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver3.C2"
                        },
                        Package(0xa)
                        {
                            0x6ee,
                            0x385,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver3.C3"
                        },
                        Package(0xa)
                        {
                            0xfa1,
                            0x393,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoSilver3.C4"
                        }
                    })
                }
                Device(CPU4)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, 0x4)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold0.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold0.C2"
                        },
                        Package(0xa)
                        {
                            0xf0a,
                            0x35c,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold0.C3"
                        },
                        Package(0xa)
                        {
                            0xf6e,
                            0x38e,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold0.C4"
                        }
                    })
                }
                Device(CPU5)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, 0x5)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold1.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold1.C2"
                        },
                        Package(0xa)
                        {
                            0xf0a,
                            0x35c,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold1.C3"
                        },
                        Package(0xa)
                        {
                            0xf6e,
                            0x38e,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold1.C4"
                        }
                    })
                }
                Device(CPU6)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, 0x6)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold2.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold2.C2"
                        },
                        Package(0xa)
                        {
                            0xf0a,
                            0x35c,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold2.C3"
                        },
                        Package(0xa)
                        {
                            0xf6e,
                            0x38e,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoGold2.C4"
                        }
                    })
                }
                Device(CPU7)
                {
                    Name(_HID, "ACPI0007")
                    Name(_UID, 0x7)
                    Method(_STA, 0x0, NotSerialized)
                    {
                        Return(0xf)
                    }
                    Name(_LPI, Package(0x7)
                    {
                        Zero,
                        Zero,
                        0x4,
                        Package(0xa)
                        {
                            Zero,
                            Zero,
                            One,
                            Zero,
                            Zero,
                            Zero,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoPrime0.C1"
                        },
                        Package(0xa)
                        {
                            0x190,
                            0x64,
                            Zero,
                            Zero,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoPrime0.C2"
                        },
                        Package(0xa)
                        {
                            0xf96,
                            0x3e8,
                            One,
                            One,
                            Zero,
                            One,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x03, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoPrime0.C3"
                        },
                        Package(0xa)
                        {
                            0x118a,
                            0x5dc,
                            One,
                            One,
                            Zero,
                            0x2,
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x7f, 0x20, 0x00, 0x03, 0x04, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            Buffer(0x11)
                            {
	0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79, 0x00
                            },
                            "KryoPrime0.C4"
                        }
                    })
                }
            }
        }
        Device(QDCI)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.GLNK
            })
            Name(_HID, "QCOM0A12")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(GPS_)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.GLNK
            })
            Name(_HID, "QCOM0A6C")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
        }
        Scope(\_SB_.GPS_)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(SKUV, 0x4))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(QGP0)
        {
            Name(_HID, "QCOM0A88")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, Serialized)
            {
                Name(RBUF, Buffer(0x20)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0x90, 0x00, 0x00, 0x00, 0x05, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x14, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x01, 0x01, 0x15, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(QGP1)
        {
            Name(_HID, "QCOM0A88")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, One)
            Name(_CCA, Zero)
            Method(_CRS, 0x0, Serialized)
            {
                Name(RBUF, Buffer(0x20)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xa0, 0x00, 0x00, 0x00, 0x05, 0x00,
	0x89, 0x06, 0x00, 0x01, 0x01, 0x37, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x01, 0x01, 0x38, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(QWPP)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_HID, "QCOM0A79")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xb)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Return(Buffer(0x1a)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x60, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x68, 0x09, 0x00, 0x00, 0x07, 0x00,
	0x79, 0x00
                })
            }
        }
        Device(SOCP)
        {
            Name(_HID, "QCOM06DD")
            Alias(\_SB_.PSUB, _SUB)
            Alias(\_SB_.STOR, STOR)
        }
        Device(QDSS)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.PEP0,
                \_SB_.MMU0
            })
            Name(_HID, "QCOM0A56")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xb)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Return(Buffer(0x38)
                {
	0x89, 0x06, 0x00, 0x03, 0x01, 0x2e, 0x01, 0x00, 0x00, 0x86, 0x09, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0xa0, 0x04, 0x00, 0x86, 0x09, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x01, 0x86, 0x09, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xa0, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x43, 0x00, 0x00, 0x00, 0x79, 0x00
                })
            }
        }
        Device(QCDB)
        {
            Name(_HID, "QCOM06DE")
            Method(_SUB, 0x0, NotSerialized)
            {
                Return("AGN00000")
            }
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(RMNT)
        {
            Name(_HID, "QCOM0A95")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(MBRG)
        {
            Name(_HID, "QCOM0A07")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(RMAT)
        {
            Name(_HID, "QCOM0A08")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(DPLB)
        {
            Name(_HID, "QCOM0A70")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(CCID)
        {
            Name(_HID, "QCOM0AA2")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(DSBY)
        {
            Name(_HID, "QCOM06CD")
            Alias(\_SB_.PSUB, _SUB)
        }
        Scope(\_SB_.RMNT)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Scope(\_SB_.MBRG)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Scope(\_SB_.RMAT)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Scope(\_SB_.DPLB)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Scope(\_SB_.CCID)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Scope(\_SB_.DSBY)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
        }
        Device(SSVC)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.IPC0,
                \_SB_.QDIG
            })
            Name(_HID, "QCOM06DB")
            Alias(\_SB_.PSUB, _SUB)
            Name(_CID, "ACPIQCOM06DB")
            Name(_UID, Zero)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Name(HWNL, One)
        Device(HWN0)
        {
            Name(_HID, "QCOM0A68")
            Name(_UID, Zero)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.HWNL, Zero))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(Zero)
                }
            }
            Method(HWNL, 0x0, NotSerialized)
            {
                Name(CFG0, Package(0x10)
                {
                    0x2,
                    0x3,
                    0x19b,
                    0x14,
                    Zero,
                    Zero,
                    One,
                    One,
                    0x2,
                    0x2,
                    One,
                    One,
                    One,
                    0x3,
                    0x6,
                    One
                })
                Return(CFG0)
            }
        }
        Device(CAMP)
        {
            Name(_DEP, Package(0x5)
            {
                \_SB_.PEP0,
                \_SB_.PMIC,
                \_SB_.PML0,
                \_SB_.ARPC,
                \_SB_.NSP0
            })
            Name(_HID, "QCOM0A32")
            Name(_UID, 0x1b)
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return("IDP07280")
                }
                Else
                {
                    Return("IDP17280")
                }
            }
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x4d)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xc4, 0x0a, 0x00, 0x10, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0xf0, 0xc9, 0x0a, 0x00, 0x80, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0xa0, 0xc4, 0x0a, 0x00, 0x10, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0xb0, 0xc4, 0x0a, 0x00, 0x10, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xec, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x2f, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xeb,
	0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(CAMS)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.MPCS
            })
            Name(_HID, "QCOM0A26")
            Name(_UID, 0x15)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return(0xf)
                }
                Else
                {
                    Return(Zero)
                }
            }
            Name(PGID, Buffer(0xa)
            {
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x43, 0x41, 0x4d, 0x53, 0x00
            })
            Name(DBUF, Buffer(DBFL)
            {
            })
            CreateByteField(DBUF, Zero, STAT)
            CreateByteField(DBUF, 0x2, DVAL)
            CreateField(DBUF, 0x18, 0xa0, DEID)
            Method(_S1D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S2D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S3D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_PS0, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(Zero, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
            Method(_PS3, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(0x3, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
        }
        Device(CAMF)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.MPCS
            })
            Name(_HID, "QCOM0A06")
            Name(_UID, 0x1a)
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return("IDP07280")
                }
                Else
                {
                    Return("IDP17280")
                }
            }
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Name(PGID, Buffer(0xa)
            {
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x43, 0x41, 0x4d, 0x46, 0x00
            })
            Name(DBUF, Buffer(DBFL)
            {
            })
            CreateByteField(DBUF, Zero, STAT)
            CreateByteField(DBUF, 0x2, DVAL)
            CreateField(DBUF, 0x18, 0xa0, DEID)
            Method(_S1D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S2D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S3D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_PS0, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(Zero, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
            Method(_PS3, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(0x3, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
        }
        Device(CAMI)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.MPCS
            })
            Name(_HID, "QCOM0A99")
            Name(_UID, 0x1c)
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return("IDP07280")
                }
                Else
                {
                    Return("IDP17280")
                }
            }
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
            Name(PGID, Buffer(0xa)
            {
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x43, 0x41, 0x4d, 0x49, 0x00
            })
            Name(DBUF, Buffer(DBFL)
            {
            })
            CreateByteField(DBUF, Zero, STAT)
            CreateByteField(DBUF, 0x2, DVAL)
            CreateField(DBUF, 0x18, 0xa0, DEID)
            Method(_S1D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S2D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S3D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_PS0, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(Zero, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
            Method(_PS3, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(0x3, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
        }
        Device(CAMT)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.MPCS
            })
            Name(_HID, "QCOM0ACE")
            Name(_UID, 0x1d)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return(0xf)
                }
                Else
                {
                    Return(Zero)
                }
            }
            Name(PGID, Buffer(0xa)
            {
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x43, 0x41, 0x4d, 0x54, 0x00
            })
            Name(DBUF, Buffer(DBFL)
            {
            })
            CreateByteField(DBUF, Zero, STAT)
            CreateByteField(DBUF, 0x2, DVAL)
            CreateField(DBUF, 0x18, 0xa0, DEID)
            Method(_S1D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S2D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S3D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_PS0, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(Zero, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
            Method(_PS3, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(0x3, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
        }
        Device(CAMU)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.MPCS
            })
            Name(_HID, "QCOM0ACF")
            Name(_UID, 0x1e)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return(0xf)
                }
                Else
                {
                    Return(Zero)
                }
            }
            Name(PGID, Buffer(0xa)
            {
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x43, 0x41, 0x4d, 0x55, 0x00
            })
            Name(DBUF, Buffer(DBFL)
            {
            })
            CreateByteField(DBUF, Zero, STAT)
            CreateByteField(DBUF, 0x2, DVAL)
            CreateField(DBUF, 0x18, 0xa0, DEID)
            Method(_S1D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S2D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S3D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_PS0, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(Zero, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
            Method(_PS3, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(0x3, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
        }
        Device(FLSH)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.CAMP
            })
            Name(_HID, "QCOM0A27")
            Name(_UID, 0x19)
            Method(_SUB, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.SKUV, One))
                {
                    Return("IDP07280")
                }
                Else
                {
                    Return("IDP17280")
                }
            }
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x2)
                {
	0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(MPCS)
        {
            Name(_DEP, Package(One)
            {
                \_SB_.CAMP
            })
            Name(_HID, "QCOM0A98")
            Name(_UID, 0x18)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x6b)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xce, 0x0a, 0x00, 0x20, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x20, 0xce, 0x0a, 0x00, 0x20, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xce, 0x0a, 0x00, 0x20, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x60, 0xce, 0x0a, 0x00, 0x20, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x80, 0xce, 0x0a, 0x00, 0x20, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xfd, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xfe, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xff,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xe0, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0x9a, 0x00, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(JPGE)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.CAMP,
                \_SB_.MMU0
            })
            Name(_HID, "QCOM0A33")
            Name(_UID, 0x17)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x2c)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0xe0, 0xc4, 0x0a, 0x00, 0x40, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x20, 0xc5, 0x0a, 0x00, 0x40, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xfa, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xfb, 0x01, 0x00, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(VFE0)
        {
            Name(_DEP, Package(0x3)
            {
                \_SB_.MMU0,
                \_SB_.PEP0,
                \_SB_.CAMP
            })
            Name(_HID, "QCOM0A25")
            Name(_UID, 0x16)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x116)
                {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xc0, 0x0a, 0x00, 0x00, 0x02, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x80, 0xc4, 0x0a, 0x00, 0x02, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x82, 0xc4, 0x0a, 0x00, 0x02, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x84, 0xc4, 0x0a, 0x00, 0x02, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x86, 0xc4, 0x0a, 0x00, 0x02, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0xb0, 0xc6, 0x0a, 0x00, 0x10, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x00, 0x00, 0xf0, 0xc6, 0x0a, 0x00, 0x80, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x00, 0x00, 0x70, 0xc8, 0x0a, 0x00, 0xa0, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x40, 0xcc, 0x0a, 0x00, 0x50, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0xb0, 0xcc, 0x0a, 0x00, 0x50, 0x00, 0x00,
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x30, 0x84, 0x00, 0x00, 0x50, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xed, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xee, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xe3,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x99, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xef, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xf1, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xf3,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xa1, 0x02, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xf5, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0x88, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xfc,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xf0, 0x01, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x03, 0x01, 0xf2, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x03, 0x01, 0xa0, 0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0xf4,
	0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x03, 0x01, 0x87, 0x01, 0x00, 0x00,
	0x79, 0x00
                })
                Return(RBUF)
            }
        }
        Device(SEN2)
        {
            Name(_DEP, Package(0x3)
            {
                \_SB_.IPC0,
                \_SB_.ADSP,
                \_SB_.ARPC
            })
            Name(_HID, "QCOM0A93")
            Alias(\_SB_.PSUB, _SUB)
            Name(_CID, "QCOM0A67")
            Name(_PLD, Package(One)
            {
                Buffer(0x14)
                {
	0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
                }
            })
        }
        Name(HPDB, Zero)
        Name(HPDS, Buffer(One)
        {
	0x00
        })
        Name(DPPN, 0xd)
        Name(CCST, Buffer(One)
        {
	0x02
        })
        Name(PORT, Buffer(One)
        {
	0x02
        })
        Name(HIRQ, Buffer(One)
        {
	0x00
        })
        Name(USBC, Buffer(One)
        {
	0x0b
        })
        Name(MUXC, Buffer(One)
        {
	0x00
        })
        Device(URS0)
        {
            Name(_HID, "QCOM0A8B")
            Name(_CID, "PNP0CA1")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Name(_CCA, Zero)
            Name(_DEP, Package(0x2)
            {
                \_SB_.PEP0,
                \_SB_.UCS0
            })
            Name(_CRS, Buffer(0xe)
            {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0x60, 0x0a, 0xff, 0xff, 0x0f, 0x00,
	0x79, 0x00
            })
            Device(USB0)
            {
                Name(_ADR, Zero)
                Name(_S0W, 0x3)
                Name(_CRS, Buffer(0x2f)
                {
	0x89, 0x06, 0x00, 0x09, 0x01, 0xa5, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x19, 0x01, 0xa2, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00, 0x19, 0x01, 0x11,
	0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x1b, 0x01, 0x0f, 0x02, 0x00, 0x00,
	0x89, 0x06, 0x00, 0x1b, 0x01, 0x0e, 0x02, 0x00, 0x00, 0x79, 0x00
                })
                Device(RHUB)
                {
                    Name(_ADR, Zero)
                    Device(PRT1)
                    {
                        Name(_ADR, One)
                        Name(_UPC, Package(0x4)
                        {
                            One,
                            0x9,
                            Zero,
                            Zero
                        })
                        Name(_PLD, Package(One)
                        {
                            Buffer(0x14)
                            {
	0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69, 0x0c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
                            }
                        })
                    }
                }
                Method(_DSM, 0x4, NotSerialized)
                {
                    While(One)
                    {
                        Name(_T_0, Buffer(One)
                        {
	0x00
                        })
                        CopyObject(ToBuffer(Arg0, ), _T_0)
                        If(LEqual(_T_0, Buffer(0x10)
                        {
	0x85, 0xe3, 0x2e, 0xce, 0xe6, 0x00, 0xcb, 0x48, 0x9f, 0x05, 0x2e, 0xdb,
	0x92, 0x7c, 0x48, 0x99
                        }))
                        {
                            While(One)
                            {
                                Name(_T_1, Zero)
                                Store(ToInteger(Arg2, ), _T_1)
                                If(LEqual(_T_1, Zero))
                                {
                                    While(One)
                                    {
                                        Name(_T_2, Zero)
                                        Store(ToInteger(Arg1, ), _T_2)
                                        If(LEqual(_T_2, Zero))
                                        {
                                            Return(Buffer(One)
                                            {
	0x1d
                                            })
                                            Break
                                        }
                                        Else
                                        {
                                            Return(Buffer(One)
                                            {
	0x01
                                            })
                                            Break
                                        }
                                        Break
                                    }
                                    Return(Buffer(One)
                                    {
	0x00
                                    })
                                    Break
                                }
                                Else
                                {
                                    If(LEqual(_T_1, 0x2))
                                    {
                                        Return(Zero)
                                        Break
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_1, 0x3))
                                        {
                                            Return(Zero)
                                            Break
                                        }
                                        Else
                                        {
                                            If(LEqual(_T_1, 0x4))
                                            {
                                                Return(0x2)
                                                Break
                                            }
                                            Else
                                            {
                                                Return(Buffer(One)
                                                {
	0x00
                                                })
                                                Break
                                            }
                                        }
                                    }
                                }
                                Break
                            }
                        }
                        Else
                        {
                            Return(Buffer(One)
                            {
	0x00
                            })
                            Break
                        }
                        Break
                    }
                }
                Method(PHYC, 0x0, NotSerialized)
                {
                    Name(CFG0, Package(Zero)
                    {
                    })
                    Return(CFG0)
                }
            }
            Device(UFN0)
            {
                Name(_ADR, One)
                Name(_S0W, 0x3)
                Device(RHUB)
                {
                    Name(_ADR, Zero)
                    Device(PRT1)
                    {
                        Name(_ADR, One)
                        Name(_UPC, Package(0x4)
                        {
                            One,
                            0x9,
                            Zero,
                            Zero
                        })
                        Name(_PLD, Package(One)
                        {
                            Buffer(0x14)
                            {
	0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69, 0x0c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
                            }
                        })
                    }
                }
                Name(_CRS, Buffer(0x14)
                {
	0x89, 0x06, 0x00, 0x09, 0x01, 0xa5, 0x00, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x19, 0x01, 0xa2, 0x00, 0x00, 0x00, 0x79, 0x00
                })
                Method(_DSM, 0x4, NotSerialized)
                {
                    While(One)
                    {
                        Name(_T_0, Buffer(One)
                        {
	0x00
                        })
                        CopyObject(ToBuffer(Arg0, ), _T_0)
                        If(LEqual(_T_0, Buffer(0x10)
                        {
	0xeb, 0xcf, 0x56, 0xfe, 0xd5, 0x49, 0x78, 0x43, 0xa8, 0xa2, 0x29, 0x78,
	0xdb, 0xe5, 0x4a, 0xd2
                        }))
                        {
                            While(One)
                            {
                                Name(_T_1, Zero)
                                Store(ToInteger(Arg2, ), _T_1)
                                If(LEqual(_T_1, Zero))
                                {
                                    While(One)
                                    {
                                        Name(_T_2, Zero)
                                        Store(ToInteger(Arg1, ), _T_2)
                                        If(LEqual(_T_2, Zero))
                                        {
                                            Return(Buffer(One)
                                            {
	0x03
                                            })
                                            Break
                                        }
                                        Else
                                        {
                                            Return(Buffer(One)
                                            {
	0x01
                                            })
                                            Break
                                        }
                                        Break
                                    }
                                    Return(Buffer(One)
                                    {
	0x00
                                    })
                                    Break
                                }
                                Else
                                {
                                    If(LEqual(_T_1, One))
                                    {
                                        Return(0x20)
                                        Break
                                    }
                                    Else
                                    {
                                        Return(Buffer(One)
                                        {
	0x00
                                        })
                                        Break
                                    }
                                }
                                Break
                            }
                        }
                        Else
                        {
                            If(LEqual(_T_0, Buffer(0x10)
                            {
	0x9f, 0x29, 0xde, 0x18, 0x76, 0x94, 0xc9, 0x4f, 0xb4, 0x3b, 0x8a, 0xeb,
	0x71, 0x3e, 0xd7, 0x51
                            }))
                            {
                                While(One)
                                {
                                    Name(_T_3, Zero)
                                    Store(ToInteger(Arg2, ), _T_3)
                                    If(LEqual(_T_3, Zero))
                                    {
                                        While(One)
                                        {
                                            Name(_T_4, Zero)
                                            Store(ToInteger(Arg1, ), _T_4)
                                            If(LEqual(_T_4, Zero))
                                            {
                                                Return(Buffer(One)
                                                {
	0x03
                                                })
                                                Break
                                            }
                                            Else
                                            {
                                                Return(Buffer(One)
                                                {
	0x01
                                                })
                                                Break
                                            }
                                            Break
                                        }
                                        Return(Buffer(One)
                                        {
	0x00
                                        })
                                        Break
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_3, One))
                                        {
                                            Return(0x39)
                                            Break
                                        }
                                        Else
                                        {
                                            Return(Buffer(One)
                                            {
	0x00
                                            })
                                            Break
                                        }
                                    }
                                    Break
                                }
                            }
                            Else
                            {
                                Return(Buffer(One)
                                {
	0x00
                                })
                                Break
                            }
                        }
                        Break
                    }
                }
                Method(PHYC, 0x0, NotSerialized)
                {
                    Name(CFG0, Package(Zero)
                    {
                    })
                    Return(CFG0)
                }
            }
        }
        Device(USB1)
        {
            Name(_HID, "QCOM0AA1")
            Name(_CID, "ACPI\\PNP0D15")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, One)
            Name(_CCA, Zero)
            Method(_STA, 0x0, NotSerialized)
            {
                Return(Zero)
            }
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Name(_S0W, 0x3)
            Name(_ADR, Zero)
            Name(_CRS, Buffer(0x32)
            {
	0x86, 0x09, 0x00, 0x01, 0x00, 0x00, 0xc0, 0x08, 0xff, 0xff, 0x0f, 0x00,
	0x89, 0x06, 0x00, 0x09, 0x01, 0x12, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00,
	0x19, 0x01, 0x11, 0x01, 0x00, 0x00, 0x89, 0x06, 0x00, 0x1b, 0x01, 0x0d,
	0x02, 0x00, 0x00, 0x89, 0x06, 0x00, 0x1b, 0x01, 0x0c, 0x02, 0x00, 0x00,
	0x79, 0x00
            })
            Device(RHUB)
            {
                Name(_ADR, Zero)
                Device(PRT1)
                {
                    Name(_ADR, One)
                    Name(_UPC, Package(0x4)
                    {
                        One,
                        0x6,
                        Zero,
                        Zero
                    })
                    Name(_PLD, Package(One)
                    {
                        Buffer(0x14)
                        {
	0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69, 0x0c, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
                        }
                    })
                }
            }
            Method(_DSM, 0x4, NotSerialized)
            {
                While(One)
                {
                    Name(_T_0, Buffer(One)
                    {
	0x00
                    })
                    CopyObject(ToBuffer(Arg0, ), _T_0)
                    If(LEqual(_T_0, Buffer(0x10)
                    {
	0x85, 0xe3, 0x2e, 0xce, 0xe6, 0x00, 0xcb, 0x48, 0x9f, 0x05, 0x2e, 0xdb,
	0x92, 0x7c, 0x48, 0x99
                    }))
                    {
                        While(One)
                        {
                            Name(_T_1, Zero)
                            Store(ToInteger(Arg2, ), _T_1)
                            If(LEqual(_T_1, Zero))
                            {
                                While(One)
                                {
                                    Name(_T_2, Zero)
                                    Store(ToInteger(Arg1, ), _T_2)
                                    If(LEqual(_T_2, Zero))
                                    {
                                        Return(Buffer(One)
                                        {
	0x1d
                                        })
                                        Break
                                    }
                                    Else
                                    {
                                        Return(Buffer(One)
                                        {
	0x01
                                        })
                                        Break
                                    }
                                    Break
                                }
                                Return(Buffer(One)
                                {
	0x00
                                })
                                Break
                            }
                            Else
                            {
                                If(LEqual(_T_1, 0x2))
                                {
                                    Return(Zero)
                                    Break
                                }
                                Else
                                {
                                    If(LEqual(_T_1, 0x3))
                                    {
                                        Return(Zero)
                                        Break
                                    }
                                    Else
                                    {
                                        If(LEqual(_T_1, 0x4))
                                        {
                                            Return(0x2)
                                            Break
                                        }
                                        Else
                                        {
                                            Return(Buffer(One)
                                            {
	0x00
                                            })
                                            Break
                                        }
                                    }
                                }
                            }
                            Break
                        }
                    }
                    Else
                    {
                        Return(Buffer(One)
                        {
	0x00
                        })
                        Break
                    }
                    Break
                }
            }
            Method(PHYC, 0x0, NotSerialized)
            {
                Name(CFG0, Package(Zero)
                {
                })
                Return(CFG0)
            }
        }
        Device(UCS0)
        {
            Name(_HID, "QCOM0AA4")
            Name(_DEP, Package(One)
            {
                \_SB_.PEP0
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x25)
                {
	0x8c, 0x20, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x23,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x79,
	0x00
                })
                Return(RBUF)
            }
            Method(MUXV, 0x0, NotSerialized)
            {
                Return(\_SB_.MUXC)
            }
            Method(CCVL, 0x0, NotSerialized)
            {
                Return(\_SB_.CCST)
            }
            Method(DPVL, 0x0, NotSerialized)
            {
                Return(\_SB_.DPPN)
            }
            Method(HPDM, 0x0, NotSerialized)
            {
                Return(\_SB_.HPDS)
            }
            Method(HPDI, 0x0, NotSerialized)
            {
                Return(\_SB_.HIRQ)
            }
        }
        Device(AGR0)
        {
            Name(_HID, "ACPI000C")
            Name(_PUR, Package(0x2)
            {
                One,
                Zero
            })
            Method(_OST, 0x3, NotSerialized)
            {
                Store(Arg2, \_SB_.PEP0.ROST)
            }
        }
        ThermalZone(TZ0_)
        {
            Name(_HID, "QCOM0A58")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
            Name(TTSP, One)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ0_.TTSP)
            }
        }
        ThermalZone(TZ1_)
        {
            Name(_HID, "QCOM0A58")
            Name(_UID, One)
            Name(_TZD, Package(One)
            {
                \_SB_.PEP0
            })
            Name(TPSV, 0xec4)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ1_.TPSV)
            }
            Name(_MTL, 0x14)
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ1_.TTC1)
            }
            Name(TTC2, One)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ1_.TTC2)
            }
            Name(TTSP, One)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ1_.TTSP)
            }
            Name(_TZP, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
        }
        ThermalZone(TZ2_)
        {
            Name(_HID, "QCOM0A59")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
            Name(TTSP, One)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ2_.TTSP)
            }
        }
        ThermalZone(TZ3_)
        {
            Name(_HID, "QCOM0A59")
            Name(_UID, One)
            Name(_TZD, Package(One)
            {
                \_SB_.PEP0
            })
            Name(TPSV, 0xec4)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ3_.TPSV)
            }
            Name(_MTL, 0x14)
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ3_.TTC1)
            }
            Name(TTC2, One)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ3_.TTC2)
            }
            Name(TTSP, One)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ3_.TTSP)
            }
            Name(_TZP, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
        }
        ThermalZone(TZ4_)
        {
            Name(_HID, "QCOM0AD4")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
            Name(TTSP, One)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ4_.TTSP)
            }
        }
        ThermalZone(TZ5_)
        {
            Name(_HID, "QCOM0AD4")
            Name(_UID, One)
            Name(_TZD, Package(One)
            {
                \_SB_.PEP0
            })
            Name(TPSV, 0xec4)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ5_.TPSV)
            }
            Name(_MTL, 0x14)
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ5_.TTC1)
            }
            Name(TTC2, One)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ5_.TTC2)
            }
            Name(TTSP, One)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ5_.TTSP)
            }
            Name(_TZP, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
        }
        ThermalZone(TZ6_)
        {
            Name(_HID, "QCOM0A91")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.GPU0
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ6_.TPSV)
            }
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ6_.TTC1)
            }
            Name(TTC2, 0x2)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ6_.TTC2)
            }
            Name(TTSP, 0x2)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ6_.TTSP)
            }
            Name(_TZP, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
        }
        ThermalZone(TZ7_)
        {
            Name(_HID, "QCOM0A51")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
            Name(TTSP, 0x32)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ7_.TTSP)
            }
        }
        ThermalZone(TZ9_)
        {
            Name(_HID, "QCOM0A4C")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
            Name(TTSP, 0x32)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ9_.TTSP)
            }
        }
        ThermalZone(TZ10)
        {
            Name(_HID, "QCOM0A92")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MJCT
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ10.TPSV)
            }
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ10.TTC1)
            }
            Name(TTC2, 0x2)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ10.TTC2)
            }
            Name(TTSP, 0xa)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ10.TTSP)
            }
            Name(_TZP, Zero)
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SJTG, 0x1eb0e1), LEqual(SKUV, 0x4)), LEqual(SKUV, 0x6)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
        }
        ThermalZone(TZ11)
        {
            Name(_HID, "QCOM0ABF")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.CSW0
            })
            Name(TPSV, 0xec4)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ11.TPSV)
            }
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ11.TTC1)
            }
            Name(TTC2, One)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ11.TTC2)
            }
            Name(TTSP, 0x32)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ11.TTSP)
            }
            Name(_TZP, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
        }
        ThermalZone(TZ12)
        {
            Name(_HID, "QCOM0A4B")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
            Name(TTSP, 0x32)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ12.TTSP)
            }
        }
        ThermalZone(TZ13)
        {
            Name(_HID, "QCOM0A57")
            Name(_UID, Zero)
            Name(_TZD, Package(0x4)
            {
                \_SB_.WLTM,
                \_SB_.CSW0,
                \_SB_.GPU0,
                _SB_.MBCL
            })
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(0x2)
                {
                    \_SB_.PEP0,
                    \_SB_.BCL1
                })
            }
        }
        ThermalZone(TZ15)
        {
            Name(_HID, "QCOM0AC8")
            Name(_UID, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x25)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0xc0,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x79,
	0x00
                })
                Return(RBUF)
            }
            Name(_TZD, Package(One)
            {
                \_SB_.PEP0
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ15.TPSV)
            }
            Name(TCRT, 0xf28)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ15.TCRT)
            }
            Name(_MTL, 0x14)
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ15.TTC1)
            }
            Name(TTC2, 0x14)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ15.TTC2)
            }
            Name(_TSP, One)
            Name(_TZP, Zero)
            Method(_DSM, 0x4, NotSerialized)
            {
                While(One)
                {
                    Name(_T_0, Buffer(One)
                    {
	0x00
                    })
                    CopyObject(ToBuffer(Arg0, ), _T_0)
                    If(LEqual(_T_0, Buffer(0x10)
                    {
	0x4b, 0x2c, 0xd4, 0xc2, 0x5e, 0xe2, 0x1c, 0x47, 0x8a, 0x4e, 0x29, 0x0a,
	0xac, 0x3a, 0x29, 0xa3
                    }))
                    {
                        While(One)
                        {
                            Name(_T_1, Zero)
                            Store(Arg2, _T_1)
                            If(LEqual(_T_1, Zero))
                            {
                                While(One)
                                {
                                    Name(_T_2, Zero)
                                    Store(Arg1, _T_2)
                                    If(LEqual(_T_2, Zero))
                                    {
                                        Return(Buffer(One)
                                        {
	0x03
                                        })
                                    }
                                    Break
                                }
                                Return(Buffer(One)
                                {
	0x00
                                })
                            }
                            Else
                            {
                                If(LEqual(_T_1, One))
                                {
                                    Store(DerefOf(Index(Arg3, Zero, )), \_SB_.TZ15.TPSV)
                                    Store(DerefOf(Index(Arg3, One, )), \_SB_.TZ15.TCRT)
                                    Store(DerefOf(Index(Arg3, 0x2, )), \_SB_.TZ15.TTC2)
                                    Store(Zero, \_SB_.TZ15.TTC1)
                                    Notify(\_SB_.TZ15, 0x81)
                                    Return(\_SB_.TZ15.TPSV)
                                }
                                Else
                                {
                                    Return(Zero)
                                }
                            }
                            Break
                        }
                    }
                    Else
                    {
                        Return(Zero)
                    }
                    Break
                }
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(0x2)
                {
                    \_SB_.PEP0,
                    \_SB_.PMIC
                })
            }
        }
        ThermalZone(TZ16)
        {
            Name(_HID, "QCOM0AC9")
            Name(_UID, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x25)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x09, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x79,
	0x00
                })
                Return(RBUF)
            }
            Name(_TZD, Package(0x2)
            {
                \_SB_.WLTM,
                \_SB_.MJCT
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ16.TPSV)
            }
            Name(TCRT, 0xf28)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ16.TCRT)
            }
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ16.TTC1)
            }
            Name(TTC2, 0x14)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ16.TTC2)
            }
            Name(_TSP, One)
            Name(_TZP, Zero)
            Method(_DSM, 0x4, NotSerialized)
            {
                While(One)
                {
                    Name(_T_0, Buffer(One)
                    {
	0x00
                    })
                    CopyObject(ToBuffer(Arg0, ), _T_0)
                    If(LEqual(_T_0, Buffer(0x10)
                    {
	0x4b, 0x2c, 0xd4, 0xc2, 0x5e, 0xe2, 0x1c, 0x47, 0x8a, 0x4e, 0x29, 0x0a,
	0xac, 0x3a, 0x29, 0xa3
                    }))
                    {
                        While(One)
                        {
                            Name(_T_1, Zero)
                            Store(Arg2, _T_1)
                            If(LEqual(_T_1, Zero))
                            {
                                While(One)
                                {
                                    Name(_T_2, Zero)
                                    Store(Arg1, _T_2)
                                    If(LEqual(_T_2, Zero))
                                    {
                                        Return(Buffer(One)
                                        {
	0x03
                                        })
                                    }
                                    Break
                                }
                                Return(Buffer(One)
                                {
	0x00
                                })
                            }
                            Else
                            {
                                If(LEqual(_T_1, One))
                                {
                                    Store(DerefOf(Index(Arg3, Zero, )), \_SB_.TZ16.TPSV)
                                    Store(DerefOf(Index(Arg3, One, )), \_SB_.TZ16.TCRT)
                                    Store(DerefOf(Index(Arg3, 0x2, )), \_SB_.TZ16.TTC2)
                                    Store(Zero, \_SB_.TZ16.TTC1)
                                    Notify(\_SB_.TZ16, 0x81)
                                    Return(\_SB_.TZ16.TPSV)
                                }
                                Else
                                {
                                    Return(Zero)
                                }
                            }
                            Break
                        }
                    }
                    Else
                    {
                        Return(Zero)
                    }
                    Break
                }
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(0x2)
                {
                    \_SB_.PEP0,
                    \_SB_.PMIC
                })
            }
        }
        ThermalZone(TZ18)
        {
            Name(_HID, "QCOM0ACB")
            Name(_UID, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x25)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x09, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x80,
	0x01, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x79,
	0x00
                })
                Return(RBUF)
            }
            Name(_TZD, Package(0x3)
            {
                \_SB_.MBS0,
                \_SB_.MBS1,
                \_SB_.MBS2
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ18.TPSV)
            }
            Name(TCRT, 0xf28)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ18.TCRT)
            }
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ18.TTC1)
            }
            Name(TTC2, 0x14)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ18.TTC2)
            }
            Name(_TSP, One)
            Name(_TZP, Zero)
            Method(_DSM, 0x4, NotSerialized)
            {
                While(One)
                {
                    Name(_T_0, Buffer(One)
                    {
	0x00
                    })
                    CopyObject(ToBuffer(Arg0, ), _T_0)
                    If(LEqual(_T_0, Buffer(0x10)
                    {
	0x4b, 0x2c, 0xd4, 0xc2, 0x5e, 0xe2, 0x1c, 0x47, 0x8a, 0x4e, 0x29, 0x0a,
	0xac, 0x3a, 0x29, 0xa3
                    }))
                    {
                        While(One)
                        {
                            Name(_T_1, Zero)
                            Store(Arg2, _T_1)
                            If(LEqual(_T_1, Zero))
                            {
                                While(One)
                                {
                                    Name(_T_2, Zero)
                                    Store(Arg1, _T_2)
                                    If(LEqual(_T_2, Zero))
                                    {
                                        Return(Buffer(One)
                                        {
	0x03
                                        })
                                    }
                                    Break
                                }
                                Return(Buffer(One)
                                {
	0x00
                                })
                            }
                            Else
                            {
                                If(LEqual(_T_1, One))
                                {
                                    Store(DerefOf(Index(Arg3, Zero, )), \_SB_.TZ18.TPSV)
                                    Store(DerefOf(Index(Arg3, One, )), \_SB_.TZ18.TCRT)
                                    Store(DerefOf(Index(Arg3, 0x2, )), \_SB_.TZ18.TTC2)
                                    Store(Zero, \_SB_.TZ18.TTC1)
                                    Notify(\_SB_.TZ18, 0x81)
                                    Return(\_SB_.TZ18.TPSV)
                                }
                                Else
                                {
                                    Return(Zero)
                                }
                            }
                            Break
                        }
                    }
                    Else
                    {
                        Return(Zero)
                    }
                    Break
                }
            }
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SJTG, 0x1eb0e1), LEqual(SKUV, 0x4)), LEqual(SKUV, 0x6)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(0x2)
                {
                    \_SB_.PEP0,
                    \_SB_.PMIC
                })
            }
        }
        ThermalZone(TZ99)
        {
            Name(_HID, "QCOM0A5A")
            Name(_UID, Zero)
            Name(_TZD, Package(0xd)
            {
                \_SB_.SYSM.CLUS.CPU0,
                \_SB_.SYSM.CLUS.CPU1,
                \_SB_.SYSM.CLUS.CPU2,
                \_SB_.SYSM.CLUS.CPU3,
                \_SB_.SYSM.CLUS.CPU4,
                \_SB_.SYSM.CLUS.CPU5,
                \_SB_.SYSM.CLUS.CPU6,
                \_SB_.SYSM.CLUS.CPU7,
                \_SB_.PEP0,
                \_SB_.WLTM,
                \_SB_.CSW0,
                \_SB_.GPU0,
                \_SB_.MJCT
            })
            Name(TPSV, 0xec4)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ99.TPSV)
            }
            Name(TCRT, 0xf28)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ99.TCRT)
            }
            Name(_MTL, 0x14)
            Name(TTC1, 0x4)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ99.TTC1)
            }
            Name(TTC2, 0x3)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ99.TTC2)
            }
            Name(TTSP, 0xa)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ99.TTSP)
            }
            Name(_TZP, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.PEP0
                })
            }
        }
        Device(MPA_)
        {
            Name(_HID, "QCOM04B4")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MPA1)
        {
            Name(_HID, "QCOM04B5")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBJ0)
        {
            Name(_HID, "QCOM04B6")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBJ1)
        {
            Name(_HID, "QCOM04B7")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBJ2)
        {
            Name(_HID, "QCOM04B8")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBJ3)
        {
            Name(_HID, "QCOM04B9")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBS0)
        {
            Name(_HID, "QCOM04BA")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBS1)
        {
            Name(_HID, "QCOM04BB")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBS2)
        {
            Name(_HID, "QCOM04BC")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MSKN)
        {
            Name(_HID, "QCOM04BE")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MJCT)
        {
            Name(_HID, "QCOM04BF")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(MBCL)
        {
            Name(_HID, "QCOM06D4")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(One)
            {
                \_SB_.IPC0
            })
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        ThermalZone(TZ51)
        {
            Name(_HID, "QCOM04C0")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MPA_
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ51.TPSV)
            }
            Name(TCRT, 0xf5a)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ51.TCRT)
            }
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ51.TTC1)
            }
            Name(TTC2, 0x2)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ51.TTC2)
            }
            Name(TTSP, 0xa)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ51.TTSP)
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MPA_
                })
            }
        }
        ThermalZone(TZ52)
        {
            Name(_HID, "QCOM04C1")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MPA1
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ52.TPSV)
            }
            Name(TCRT, 0xf5a)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ52.TCRT)
            }
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ52.TTC1)
            }
            Name(TTC2, 0x2)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ52.TTC2)
            }
            Name(TTSP, 0xa)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ52.TTSP)
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MPA1
                })
            }
        }
        ThermalZone(TZ53)
        {
            Name(_HID, "QCOM04C2")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MBJ0
            })
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MBJ0
                })
            }
        }
        ThermalZone(TZ54)
        {
            Name(_HID, "QCOM04C3")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MBJ1
            })
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MBJ1
                })
            }
        }
        ThermalZone(TZ55)
        {
            Name(_HID, "QCOM04C4")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MBJ2
            })
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MBJ2
                })
            }
        }
        ThermalZone(TZ56)
        {
            Name(_HID, "QCOM04C5")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MBJ3
            })
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MBJ3
                })
            }
        }
        ThermalZone(TZ57)
        {
            Name(_HID, "QCOM04C6")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MBS0
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ57.TPSV)
            }
            Name(TCRT, 0xf5a)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ57.TCRT)
            }
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ57.TTC1)
            }
            Name(TTC2, 0x2)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ57.TTC2)
            }
            Name(TTSP, 0xa)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ57.TTSP)
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MBS0
                })
            }
        }
        ThermalZone(TZ58)
        {
            Name(_HID, "QCOM04C7")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MBS1
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ58.TPSV)
            }
            Name(TCRT, 0xf5a)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ58.TCRT)
            }
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ58.TTC1)
            }
            Name(TTC2, 0x2)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ58.TTC2)
            }
            Name(TTSP, 0xa)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ58.TTSP)
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MBS1
                })
            }
        }
        ThermalZone(TZ59)
        {
            Name(_HID, "QCOM04C8")
            Name(_UID, Zero)
            Name(_TZD, Package(One)
            {
                \_SB_.MBS2
            })
            Name(TPSV, 0xe60)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ59.TPSV)
            }
            Name(TCRT, 0xf5a)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ59.TCRT)
            }
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ59.TTC1)
            }
            Name(TTC2, 0x2)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ59.TTC2)
            }
            Name(TTSP, 0xa)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ59.TTSP)
            }
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(One)
                {
                    \_SB_.MBS2
                })
            }
        }
        ThermalZone(TZ31)
        {
            Name(_HID, "QCOM0A5F")
            Name(_UID, Zero)
            Name(TTC1, One)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ31.TTC1)
            }
            Name(TTC2, 0x5)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ31.TTC2)
            }
            Name(TTSP, 0x1e)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ31.TTSP)
            }
            Name(_TZP, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(0x2)
                {
                    \_SB_.PEP0,
                    \_SB_.ADC1
                })
            }
        }
        ThermalZone(TZ32)
        {
            Name(_HID, "QCOM0A61")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(0x2)
                {
                    \_SB_.PEP0,
                    \_SB_.ADC1
                })
            }
            Name(_TZD, Package(0x5)
            {
                \_SB_.SYSM.CLUS.CPU4,
                \_SB_.SYSM.CLUS.CPU5,
                \_SB_.SYSM.CLUS.CPU6,
                \_SB_.SYSM.CLUS.CPU7,
                \_SB_.GPU0
            })
            Name(TPSV, 0xe2e)
            Method(_PSV, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ32.TPSV)
            }
            Name(TCRT, 0xef6)
            Method(_CRT, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ32.TCRT)
            }
            Name(_MTL, 0x14)
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ32.TTC1)
            }
            Name(TTC2, 0x14)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ32.TTC2)
            }
            Name(TTSP, 0x28)
            Name(_TZP, Zero)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ32.TTSP)
            }
        }
        ThermalZone(TZ33)
        {
            Name(_HID, "QCOM0A63")
            Name(_UID, Zero)
            Method(_DEP, 0x0, NotSerialized)
            {
                Return(Package(0x2)
                {
                    \_SB_.PEP0,
                    \_SB_.ADC1
                })
            }
            Name(_MTL, 0x14)
            Name(TTC1, Zero)
            Method(_TC1, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ33.TTC1)
            }
            Name(TTC2, 0x14)
            Method(_TC2, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ33.TTC2)
            }
            Name(TTSP, 0x1e)
            Name(_TZP, Zero)
            Method(_TSP, 0x0, NotSerialized)
            {
                Return(\_SB_.TZ33.TTSP)
            }
        }
        Name(HWNH, Zero)
        Device(HWN1)
        {
            Name(_HID, "QCOM0A69")
            Name(_UID, One)
            Alias(\_SB_.PSUB, _SUB)
            Method(_STA, 0x0, NotSerialized)
            {
                If(LEqual(\_SB_.HWNH, Zero))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(Zero)
                }
            }
            Name(_DEP, Package(One)
            {
                \_SB_.PMIC
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x25)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00,
	0x0e, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x32, 0x00, 0x79,
	0x00
                })
                Return(RBUF)
            }
            Method(HAPI, 0x0, NotSerialized)
            {
                Name(CFG0, Package(0x3)
                {
                    One,
                    One,
                    One
                })
                Return(CFG0)
            }
            Method(HAPC, 0x0, NotSerialized)
            {
                Name(CFG0, Package(0x16)
                {
                    Zero,
                    0x984,
                    Zero,
                    One,
                    One,
                    One,
                    One,
                    Zero,
                    0x4,
                    One,
                    0x3,
                    0x14,
                    One,
                    0x3,
                    Zero,
                    Zero,
                    0x6,
                    Zero,
                    Zero,
                    0x535,
                    0x3,
                    One
                })
                Return(CFG0)
            }
        }
        Device(TSC1)
        {
            Name(_HID, "STFT556A")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(0x3)
            {
                \_SB_.GIO0,
                \_SB_.IC14,
                \_SB_.PEP0
            })
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x41)
                {
	0x8e, 0x19, 0x00, 0x02, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x06, 0x00,
	0x80, 0x1a, 0x06, 0x00, 0x49, 0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x49,
	0x43, 0x31, 0x34, 0x00, 0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23,
	0x00, 0x00, 0x00, 0x51, 0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x47, 0x49,
	0x4f, 0x30, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Name(PGID, Buffer(0xa)
            {
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x54, 0x53, 0x43, 0x31, 0x00
            })
            Name(DBUF, Buffer(DBFL)
            {
            })
            CreateByteField(DBUF, Zero, STAT)
            CreateByteField(DBUF, 0x2, DVAL)
            CreateField(DBUF, 0x18, 0xa0, DEID)
            Method(_S1D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S2D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_S3D, 0x0, NotSerialized)
            {
                Return(0x3)
            }
            Method(_PS0, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(Zero, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
            Method(_PS3, 0x0, NotSerialized)
            {
                Store(Buffer(ESNL)
                {
                }, DEID)
                Store(0x3, DVAL)
                Store(PGID, DEID)
                If(\_SB_.ABD_.AVBL)
                {
                    Store(DBUF, \_SB_.PEP0.FLD0)
                }
            }
        }
        Device(BTNS)
        {
            Name(_HID, "ACPI0011")
            Alias(\_SB_.PSUB, _SUB)
            Name(_UID, Zero)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(RBUF, Buffer(0x6b)
                {
	0x8c, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x15, 0x00, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x07,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c,
	0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0xc6, 0x00,
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x8c, 0x20,
	0x00, 0x01, 0x00, 0x01, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x06, 0x00, 0x5c,
	0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x79, 0x00
                })
                Return(RBUF)
            }
            Name(_DSD, Package(0x2)
            {
                Buffer(0x10)
                {
	0x25, 0xd6, 0x6b, 0xfa, 0xe8, 0x9c, 0x0d, 0x47, 0xa2, 0xc7, 0xb3, 0xca,
	0x36, 0xc4, 0x28, 0x2e
                },
                Package(0x4)
                {
                    Package(0x5)
                    {
                        Zero,
                        One,
                        Zero,
                        One,
                        0xd
                    },
                    Package(0x5)
                    {
                        One,
                        Zero,
                        One,
                        One,
                        0x81
                    },
                    Package(0x5)
                    {
                        One,
                        One,
                        One,
                        0xc,
                        0xe9
                    },
                    Package(0x5)
                    {
                        One,
                        0x2,
                        One,
                        0xc,
                        0xea
                    }
                }
            })
        }
        Device(NRCX)
        {
            Name(_HID, "QCOM0AD6")
            Alias(\_SB_.PSUB, _SUB)
        }
        Device(PSAU)
        {
            Name(_HID, "QCOM0AE1")
            Alias(\_SB_.PSUB, _SUB)
        }
        Scope(\_SB_.NRCX)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Scope(\_SB_.PSAU)
        {
            Method(_STA, 0x0, NotSerialized)
            {
                If(LOr(LOr(LEqual(\_SB_.SKUV, 0x4), LEqual(\_SB_.SKUV, 0x6)), LEqual(\_SB_.SKUV, 0x7)))
                {
                    Return(Zero)
                }
                Else
                {
                    Return(0xf)
                }
            }
        }
        Device(BTH0)
        {
            Name(_HID, "QCOM0A6B")
            Alias(\_SB_.PSUB, _SUB)
            Name(_DEP, Package(0x3)
            {
                \_SB_.PEP0,
                \_SB_.PMIC,
                \_SB_.UAR8
            })
            Name(_PRW, Package(0x2)
            {
                Zero,
                Zero
            })
            Name(_S4W, 0x2)
            Name(_S0W, 0x2)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(PBUF, Buffer(0x45)
                {
	0x8e, 0x1d, 0x00, 0x01, 0x00, 0x03, 0x02, 0x35, 0x00, 0x01, 0x0a, 0x00,
	0x00, 0xc2, 0x01, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0xc0, 0x5c, 0x5f,
	0x53, 0x42, 0x2e, 0x55, 0x41, 0x52, 0x38, 0x00, 0x8c, 0x20, 0x00, 0x01,
	0x01, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x19, 0x00, 0x23, 0x00, 0x00, 0x00, 0x55, 0x00, 0x5c, 0x5f, 0x53,
	0x42, 0x2e, 0x47, 0x49, 0x4f, 0x30, 0x00, 0x79, 0x00
                })
                Return(PBUF)
            }
            Method(_STA, 0x0, NotSerialized)
            {
                Return(0xf)
            }
        }
        Device(ADC1)
        {
            Name(_DEP, Package(0x2)
            {
                \_SB_.SPMI,
                \_SB_.PMIC
            })
            Name(_HID, "QCOM0A11")
            Name(_UID, Zero)
            Alias(\_SB_.PSUB, _SUB)
            Method(_CRS, 0x0, NotSerialized)
            {
                Name(INTB, Buffer(0x4a)
                {
	0x8c, 0x21, 0x00, 0x01, 0x00, 0x01, 0x00, 0x11, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x01, 0x00, 0x20,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x02,
	0x8c, 0x21, 0x00, 0x01, 0x00, 0x01, 0x00, 0x11, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x17, 0x00, 0x00, 0x19, 0x00, 0x23, 0x00, 0x01, 0x00, 0x28,
	0x00, 0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x50, 0x4d, 0x30, 0x31, 0x00, 0x02,
	0x79, 0x00
                })
                Name(NAM_, Buffer(0xa)
                {
	0x5c, 0x5f, 0x53, 0x42, 0x2e, 0x53, 0x50, 0x4d, 0x49, 0x00
                })
                Name(VUSR, Buffer(0xc)
                {
	0x8e, 0x13, 0x00, 0x01, 0x00, 0xc1, 0x02, 0x00, 0x31, 0x01, 0x00, 0x00
                })
                Name(VBTM, Buffer(0xc)
                {
	0x8e, 0x13, 0x00, 0x01, 0x00, 0xc1, 0x02, 0x00, 0x34, 0x01, 0x00, 0x00
                })
                Concatenate(VUSR, NAM_, Local1)
                Concatenate(VBTM, NAM_, Local2)
                Concatenate(Local1, Local2, Local3)
                Concatenate(Local3, INTB, Local0)
                Return(Local0)
            }
        }
    }
}
