#ifndef _PLATFORM_UTILS_H_
#define _PLATFORM_UTILS_H_

#define SMMU_BASE 0x15000000

#define SMMU_CTX_BANK_SIZE 0x1000

#define SMMU_CTX_BANK_0_OFFSET 0x80000
#define SMMU_CTX_BANK_SCTLR_OFFSET 0x0
#define SMMU_CTX_BANK_TTBR0_0_OFFSET 0x20
#define SMMU_CTX_BANK_TTBR0_1_OFFSET 0x24
#define SMMU_CTX_BANK_TTBR1_0_OFFSET 0x28
#define SMMU_CTX_BANK_TTBR1_1_OFFSET 0x2C
#define SMMU_CTX_BANK_MAIR0_OFFSET 0x38
#define SMMU_CTX_BANK_MAIR1_OFFSET 0x3C
#define SMMU_CTX_BANK_TTBCR_OFFSET 0x30

#define SMMU_NON_CCA_SCTLR 0xE0
#define SMMU_CCA_SCTLR 0x9F00E0

#define UFS_CTX_BANK 1

#define APSS_WDT_BASE 0x17C10000
#define APSS_WDT_ENABLE_OFFSET 0x8

#endif /* _PLATFORM_UTILS_H_ */