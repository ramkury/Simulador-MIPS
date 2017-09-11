#include <cstdio>
#include <fstream>
#include "control.h"
#include "isa.h"

void print_memory() {
    int i;
    printf("\nMemoria (hex):\n");
    printf("Início da área de código (0x%.8X)\n", TEXT_START);
    for(i = TEXT_START / 4; i < DATA_START / 4; ++i) {
        printf(" %X ", mem[i]);
    }
    printf("\nInício da área de dados (0x%.8X)\n", DATA_START);
    for(i = DATA_START / 4; i < MEM_SIZE; ++i) {
        printf(" %X ", mem[i]);
    }
    printf("\n");
}

void read_to_memory(int start_addr, const char * filename) {
    std::ifstream f(filename);
    if (f.is_open()) {
        for (int i = start_addr; !f.eof(); i++)
        {
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
    printf("\n");
}

void fetch() {
    ri = ((uint32_t *)mem)[pc];
    pc += 4;
}

void decode() {

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
