#ifndef __DTB_PARSER_H__
#define __DTB_PARSER_H__
#include "uart.h"
#include "string.h"

#define PADDING         0x00000000
#define FDT_BEGIN_NODE  0x00000001
#define FDT_END_NODE    0x00000002
#define FDT_PROP        0x00000003
#define FDT_NOP         0x00000004
#define FDT_END         0x00000009
#define DT_ADDR         0x200000



struct fdt_header {
    unsigned int magic; // This field shall contain the value 0xd00dfeed (big-endian).
    unsigned int totalsize;
    unsigned int off_dt_struct;   // offset of the structure block from the beginning of the header.
    unsigned int off_dt_strings;  // offset of the strings block from the beginning of the header.
    unsigned int off_mem_rsvmap;  // offset of the mem.res. block from the beginning of the header.
    unsigned int version;
    unsigned int last_comp_version;
    unsigned int boot_cpuid_phys;
    unsigned int size_dt_strings; // length in bytes of the strings block section
    unsigned int size_dt_struct;  // length in bytes of the structure block section
};

unsigned int convert_big_to_small_endian(unsigned int num);
void print_dt_info();
void parse_dt();



#endif
