#ifndef SIMULADOR_MIPS_ISA_H
#define SIMULADOR_MIPS_ISA_H

#include <cstdint>
#include <map>

#define MEM_SIZE    4096
#define DATA_START  0x00002000
#define TEXT_START  0x00000000

#define sp (mem[29])
#define ra (mem[31])

typedef void (*instruction)();

static const char * gpr_names[] = {
        "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
        "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

extern int32_t mem[MEM_SIZE];
extern int32_t gpr[32];
extern int32_t ri;
extern uint32_t pc, hi, lo;
extern uint8_t op, rs, rt, rd, shamt, funct;
extern std::map<uint8_t, instruction> map_opcodes;
extern std::map<uint8_t, instruction> map_funct;

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


//OPCODES
void i_ext();
void i_lw();
void i_lb();
void i_lbu();
void i_lh();
void i_lhu();
void i_lui();
void i_sw();
void i_sb();
void i_sh();
void i_beq();
void i_bne();
void i_blez();
void i_bgtz();
void i_addi();
void i_slti();
void i_sltiu();
void i_andi();
void i_ori();
void i_xori();
void i_j();
void i_jal();

// FUNCT
void f_add();
void f_sub();
void f_mult();
void f_div();
void f_and();
void f_or();
void f_xor();
void f_nor();
void f_slt();
void f_jr();
void f_sll();
void f_srl();
void f_sra();
void f_mfhi();
void f_mflo();
void f_syscall();

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

// funções auxiliares
uint32_t cvt_word_address(uint32_t address);
uint32_t cvt_half_address(uint32_t address);
/**
 * Combina os campos rd, shamt e funct para obter o valor imediato
 * usado nas instruções do tipo I
 * @return Valor imediato
 */
uint16_t get_immediate();


#endif //SIMULADOR_MIPS_ISA_H
