#ifndef SIMULADOR_MIPS_ISA_H
#define SIMULADOR_MIPS_ISA_H

#include <cstdint>

#define MEM_SIZE    4096
#define DATA_START  0x00002000
#define TEXT_START  0x00000000

#define sp (mem[29])
#define ra (mem[31])

static const char * gpr_names[] = {
        "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
        "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

extern int32_t mem[MEM_SIZE];
extern int32_t gpr[32];
extern uint32_t pc, ri;

enum OPCODES { // lembrem que so sao considerados os 6 primeiros bits dessas constantes
    EXT=0x00,   LW=0x23,    LB=0x20,    LBU=0x24,
    LH=0x21,    LHU=0x25,   LUI=0x0F,   SW=0x2B,
    SB=0x28,    SH=0x29,    BEQ=0x04,   BNE=0x05,
    BLEZ=0x06,  BGTZ=0x07,  ADDI=0x08,  SLTI=0x0A,
    SLTIU=0x0B, ANDI=0x0C,  ORI=0x0D,   XORI=0x0E,
    J=0x02,     JAL=0x03
};

enum FUNCT	{
    ADD=0x20,   SUB=0x22,   MULT=0x18,  DIV=0x1A,
    AND=0x24,   OR=0x25,    XOR=0x26,   NOR=0x27,
    SLT=0x2A,   JR=0x08,    SLL=0x00,   SRL=0x02,
    SRA=0x03,   MFHI=0x10,	MFLO=0x12,  SYSCALL=0x0c
};

// lê um inteiro alinhado - endereços múltiplos de 4
int32_t lw(uint32_t address, int16_t kte);
// lê meia palavra, 16 bits - retorna inteiro com sinal
int32_t lh(uint32_t address, int16_t kte);
// lê meia palavra, 16 bits - retorna inteiro sem sinal
int32_t lhu(uint32_t address, int16_t kte);
// lê um byte - retorna inteiro com sinal
int32_t lb(uint32_t address, int16_t kte);
// lê um byte - retorna inteiro sem sinal
int32_t lbu(uint32_t address, int16_t kte);
// escreve um inteiro alinhado na memória - endereços múltiplos de 4
void sw(uint32_t address, int16_t kte, int32_t dado);
// escreve meia palavra, 16 bits - endereços múltiplos de 2
void sh(uint32_t address, int16_t kte, int16_t dado);
// escreve um byte na memória
void sb(uint32_t address, int16_t kte, int8_t dado);

#endif //SIMULADOR_MIPS_ISA_H
