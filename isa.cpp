#include "isa.h"

int32_t mem[MEM_SIZE] = { 0 };
int32_t GPR[32] = { 0 };

int32_t lw(uint32_t address, int16_t kte) {
    uint32_t addr = (address + kte) >> 2;
    return mem[addr];
}

int32_t lh(uint32_t address, int16_t kte) {
    int16_t * m = (int16_t *)mem;
    uint32_t addr = (address + kte) >> 1;
    return m[addr];
}

int32_t lb(uint32_t address, int16_t kte) {
    int8_t * m = (int8_t *)mem;
    uint32_t addr = (address + kte);
    return m[addr];
}

void sw(uint32_t address, int16_t kte, int32_t dado) {
    uint32_t addr = (address + kte) >> 2;
    mem[addr] = dado;
}

void sh(uint32_t address, int16_t kte, int16_t dado) {
    int16_t * m = (int16_t *)mem;
    uint32_t addr = (address + kte) >> 1;
    m[addr] = dado;
}

void sb(uint32_t address, int16_t kte, int8_t dado) {
    int8_t * m = (int8_t *)mem;
    uint32_t addr = (address + kte);
    m[addr] = dado;
}

