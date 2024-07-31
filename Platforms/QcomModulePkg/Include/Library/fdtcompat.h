#ifndef FDT_COMPAT_H
#define FDT_COMPAT_H

struct fdt_entry_node {
        fdt64_t address;
        fdt64_t size;
        struct fdt_entry_node *next;
};

#endif