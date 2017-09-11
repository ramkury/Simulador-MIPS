#include <cstdio>
#include <fstream>
#include "control.h"
#include "isa.h"

void dump_mem(int start, int end, char format) {

    int i;
    const char * chosen_format;
    switch (tolower(format)) {
        case 'd':
            printf("\nMemória (formato decimal):\n");
            chosen_format = " %d ";
            break;
        case 'h':
            printf("\nMemória (formato hexadecimal):\n");
            chosen_format = " %X ";
            break;
        default:
            return;
    }

    for(i = start / 4; i < end / 4; ++i) {
        printf(chosen_format, mem[i]);
    }

    printf("\n");

}

void load_file(int start_addr, const char *filename) {
    std::ifstream f(filename);
    if (f.is_open()) {
        for (int i = start_addr; !f.eof(); i++) {
            f.read((char *)&mem[i], 4);
        }
    }
}

void dump_reg(char format) {
    const char * chosen_format;
    switch (tolower(format)) {
        case 'd':
            printf("\nDump de registradores (formato decimal):");
            chosen_format = "$%s=%d\t";
            break;
        case 'h':
            printf("\nDump de registradores (formato hexadecimal):");
            chosen_format = "$%s=%.8X\t";
            break;
        default:
            return;
    }

    for (int i = 0; i < 32; ++i) {
        if (i % 4 == 0) {
            printf("\n");
        }
        printf(chosen_format, gpr_names[i], gpr[i]);
    }

    printf("\n");
    printf(chosen_format, "pc", pc);
    printf(chosen_format, "hi", hi);
    printf(chosen_format, "lo", lo);
    printf("\n");
}

void fetch() {
    ri = ((uint32_t *)mem)[pc];
    pc += 4;
}

void decode() {
    op = (ri >> 26) & 0x3F;
    rs = (ri >> 21) & 0x1F;
    rt = (ri >> 16) & 0x1F;
    rd = (ri >> 11) & 0x1F;
    shamt = (ri << 21) >> 27;
    funct = ri & 0x3F;
}

void execute() {

}

void step() {
    fetch();
    decode();
    execute();
}

void run() {
    pc = 0;
    sp = 0x3FFC;
    while (pc < DATA_START) {
        step();
    }
}
