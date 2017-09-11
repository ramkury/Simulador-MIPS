#include "isa.h"
#include "control.h"

int32_t mem[MEM_SIZE] = { 0 };
int32_t gpr[32] = { 0 };
uint32_t pc = TEXT_START;
uint32_t ri = 0;
uint32_t hi = 0;
uint32_t lo = 0;

int32_t lw(uint32_t address, int16_t kte) {
    auto addr = cvt_word_address(address + kte);
    return mem[addr];
}

int32_t lh(uint32_t address, int16_t kte) {
    auto addr = cvt_half_address(address + kte);
    return ((int16_t *)mem)[addr];
}

int32_t lhu(uint32_t address, int16_t kte) {
    return 0xFFFF & lh(address, kte);
}

int32_t lb(uint32_t address, int16_t kte) {
    uint32_t addr = (address + kte);
    return ((int8_t *)mem)[addr];
}

int32_t lbu(uint32_t address, int16_t kte) {
    return 0xFF & lb(address, kte);
}

void sw(uint32_t address, int16_t kte, int32_t dado) {
    auto addr = cvt_word_address(address + kte);
    mem[addr] = dado;
}

void sh(uint32_t address, int16_t kte, int16_t dado) {
    auto addr = cvt_half_address(address + kte);
    ((int16_t *)mem)[addr] = dado;
}

void sb(uint32_t address, int16_t kte, int8_t dado) {
    uint32_t addr = (address + kte);
    ((int8_t *)mem)[addr] = dado;
}

uint32_t cvt_word_address(uint32_t address) {
    if (address % 4 != 0) {
        throw TS_except_alignment_word;
    }
    return address / 4;
}

uint32_t cvt_half_address(uint32_t address) {
    if (address % 2 != 0) {
        throw TS_except_alignment_halfword;
    }
    return address / 2;
}
