#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "../include/control.h"
#include "../include/isa.h"

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
    ri = ((uint32_t *)mem)[pc / 4];
    pc += 4;
}

void decode() {
    op    = static_cast<uint8_t>((ri >> 26) & 0x3F);
    rs    = static_cast<uint8_t>((ri >> 21) & 0x1F);
    rt    = static_cast<uint8_t>((ri >> 16) & 0x1F);
    rd    = static_cast<uint8_t>((ri >> 11) & 0x1F);
    shamt = static_cast<uint8_t>((ri >>  6) & 0x1F);
    funct = static_cast<uint8_t>(ri & 0x3F);
    k16   = static_cast<int16_t>(ri & 0xFFFF);
    k26   = static_cast<uint32_t>(ri & 0x3FFFFFF);
}

void execute() {
    zero = 0;
    auto it = map_opcodes.find(op);
    if (it == map_opcodes.end()) {
        printf("Opcode 0x%.6X não implementado!\n", op);
    } else {
        (*(it->second))();
    }
}

void step() {
    fetch();
    decode();
    execute();
}

void run() {
    pc = 0;
    sp = 0x3FFC;
    try {
        while (pc < DATA_START) {
            step();
        }
    } catch (TS_except e) {
        switch(e) {
            case TS_except_syscall_exit:
                printf("\nExecução do programa encerrada por syscall.\n");
                exit(0);
            case TS_except_syscall_undefined:
                printf("\nFoi utilizado um syscall não definido (código %d).\n", v0);
                break;
            case TS_except_alignment_word:
                printf("\nAcesso a palavra não alinhada (endereço não múltiplo de 4).\n");
                break;
            case TS_except_alignment_halfword:
                printf("\nAcesso a meia palavra não alinhada (endereço não múltiplo de 2).\n");
                break;
        }
        dump_reg('h');
        exit(e);
    }
    printf("Erro! PC excedeu a área de código!\n");
    exit(-2);
}
