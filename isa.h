#pragma once

#include <cstdint>

#define MEM_SIZE 4096
#define DATA_START 0x00002000
#define TEXT_START 0x00000000

extern int32_t mem[MEM_SIZE];
extern int32_t GPR[32];

// lê um inteiro alinhado - endereços múltiplos de 4
int32_t lw(uint32_t address, int16_t kte);
// lê meia palavra, 16 bits - retorna inteiro com sinal
int32_t lh(uint32_t address, int16_t kte);
// lê um byte - retorna inteiro com sinal
int32_t lb(uint32_t address, int16_t kte);
// escreve um inteiro alinhado na memória - endereços múltiplos de 4
void sw(uint32_t address, int16_t kte, int32_t dado);
// escreve meia palavra, 16 bits - endereços múltiplos de 2
void sh(uint32_t address, int16_t kte, int16_t dado);
// escreve um byte na memória
void sb(uint32_t address, int16_t kte, int8_t dado);
