#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "control.h"
#include "isa.h"

AddressException::AddressException(std::string& message) : message(message) {}

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
    op = static_cast<uint8_t>((ri >> 26) & 0x3F);
    rs = static_cast<uint8_t>((ri >> 21) & 0x1F);
    rt = static_cast<uint8_t>((ri >> 16) & 0x1F);
    rd = static_cast<uint8_t>((ri >> 11) & 0x1F);
    shamt = static_cast<uint8_t>((ri << 21) >> 27);
    funct = static_cast<uint8_t>(ri & 0x3F);
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
        if (e == TS_except_syscall_exit) {
            printf("\nExecução do programa encerrada por syscall.\n");
            exit(0);
        }
        printf("Erro! Pressione qualquer tecla para dump de registradores:\n");
        getchar();
        dump_reg('h');
        printf("Pressione qualquer tecla para dump de memória e encerrar o programa.\n");
        throw;
    }
}
