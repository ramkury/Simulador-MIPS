#ifndef SIMULADOR_MIPS_ISA_H
#define SIMULADOR_MIPS_ISA_H

#include <cstdint>
#include <map>

#define MEM_SIZE    4096
#define DATA_START  0x00002000
#define TEXT_START  0x00000000

#define sp   (gpr[29])
#define ra   (gpr[31])
#define zero (gpr[0])
#define v0   (gpr[2])
#define a0   (gpr[4])
#define a1   (gpr[5])

typedef void (*instruction)();

static const char * gpr_names[] = {
        "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
        "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

extern int32_t mem[MEM_SIZE];
extern int32_t gpr[32];
extern uint32_t * const gpr_u;
extern int32_t ri, hi, lo;
extern uint32_t pc;
// Campos da instrução
extern uint8_t op, rs, rt, rd, shamt, funct;
extern int16_t k16;
extern uint32_t k26;
extern std::map<uint8_t, instruction> map_opcodes;
extern std::map<uint8_t, instruction> map_funct;

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
 * Multiplica por 4 os 16 últimos bits de ri
 * e adiciona o resultado (com sinal estendido) ao PC
 */
void branch();

/**
 * Desloca 2 bits para a esquerda os 26 últimos bits de address
 * e concatena o resultado aos 4 bits mais significativos do PC
 */
void jump(int32_t address);

#endif //SIMULADOR_MIPS_ISA_H
