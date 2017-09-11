#include "isa.h"

int32_t mem[MEM_SIZE] = { 0 };
int32_t gpr[32] = { 0 };
uint32_t pc = TEXT_START;
uint32_t ri = 0;
uint32_t hi = 0;
uint32_t lo = 0;

int32_t lw(uint32_t address, int16_t kte) {
    uint32_t addr = (address + kte) >> 2;
    return mem[addr];
}

int32_t lh(uint32_t address, int16_t kte) {
    auto m = (int16_t *)mem;
    uint32_t addr = (address + kte) >> 1;
    return m[addr];
}

int32_t lhu(uint32_t address, int16_t kte) {
    return 0xFFFF & lh(address, kte);
}

int32_t lb(uint32_t address, int16_t kte) {
    auto m = (int8_t *)mem;
    uint32_t addr = (address + kte);
    return m[addr];
}

int32_t lbu(uint32_t address, int16_t kte) {
    return 0xFF & lb(address, kte);
}

void sw(uint32_t address, int16_t kte, int32_t dado) {
    uint32_t addr = (address + kte) >> 2;
    mem[addr] = dado;
}

void sh(uint32_t address, int16_t kte, int16_t dado) {
    auto m = (int16_t *)mem;
    uint32_t addr = (address + kte) >> 1;
    m[addr] = dado;
}

void sb(uint32_t address, int16_t kte, int8_t dado) {
    auto m = (int8_t *)mem;
    uint32_t addr = (address + kte);
    m[addr] = dado;
}
