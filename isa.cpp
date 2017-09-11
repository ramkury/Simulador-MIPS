#include "isa.h"
#include "control.h"
#include <cstdio>

int32_t mem[MEM_SIZE] = { 0 };
int32_t gpr[32] = { 0 };
int32_t ri = 0;
uint32_t pc = TEXT_START;
uint32_t hi = 0;
uint32_t lo = 0;

uint8_t op, rs, rt, rd, shamt, funct;

std::map<uint8_t, instruction> map_opcodes = {
        {0x00, &i_ext},      {0x23, &i_lw},       {0x20, &i_lb},       {0x24, &i_lbu},
        {0x21, &i_lh},       {0x25, &i_lhu},      {0x0F, &i_lui},      {0x2B, &i_sw},
        {0x28, &i_sb},       {0x29, &i_sh},       {0x04, &i_beq},      {0x05, &i_bne},
        {0x06, &i_blez},     {0x07, &i_bgtz},     {0x08, &i_addi},     {0x0A, &i_slti},
        {0x0B, &i_sltiu},    {0x0C, &i_andi},     {0x0D, &i_ori},      {0x0E, &i_xori},
        {0x02, &i_j},        {0x03, &i_jal}
};

std::map<uint8_t, instruction> map_funct = {
        {0x20, &f_add},      {0x22, &f_sub},      {0x18, &f_mult},     {0x1A, &f_div},
        {0x24, &f_and},      {0x25, &f_or},       {0x26, &f_xor},      {0x27, &f_nor},
        {0x2A, &f_slt},      {0x08, &f_jr},       {0x00, &f_sll},      {0x02, &f_srl},
        {0x03, &f_sra},      {0x0C, &f_syscall},  {0x10, &f_mfhi},     {0x12, &f_mflo}
};


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

void i_ext() {

}

void i_lw() {
    gpr[rt] = lw(gpr_u[rs], get_immediate());
}

void i_lb() {
    gpr[rt] = lb(gpr_u[rs], get_immediate());
}

void i_lbu() {
    gpr[rt] = lbu(gpr_u[rs], get_immediate());
}

void i_lh() {
    gpr[rt] = lh(gpr_u[rs], get_immediate());
}

void i_lhu() {
    gpr[rt] = lhu(gpr_u[rs], get_immediate());
}

void i_lui() {
    gpr[rt] = get_immediate() << 16;
}

void i_sw() {
    sw(gpr_u[rs], get_immediate(), gpr[rt]);
}

void i_sb() {
    sb(gpr_u[rs], get_immediate(), static_cast<int8_t>(gpr[rt] & 0xFF));
}

void i_sh() {
    sh(gpr_u[rs], get_immediate(), static_cast<int16_t>(gpr[rt] & 0xFFFF));
}

void i_beq() {
    if (gpr[rs] == gpr[rt]) {
        branch();
    }
}

void i_bne() {
    if (gpr[rs] != gpr[rt]) {
        branch();
    }
}

void i_blez() {
    if (gpr[rs] <= 0) {
        branch();
    }
}

void i_bgtz() {
    if (gpr[rs] > 0) {
        branch();
    }
}

void i_addi() {
    gpr[rt] = gpr[rs] + get_immediate();
}

void i_slti() {
    gpr[rt] = (gpr[rs] < get_immediate());
}

void i_sltiu() {
    int32_t imm = get_immediate();
    gpr[rt] = (gpr_u[rs] < static_cast<uint32_t>(imm));
}

void i_andi() {
    gpr[rt] = gpr[rs] & ri & 0xFFFF;
}

void i_ori() {
    gpr[rt] = gpr[rs] | (ri & 0xFFFF);
}

void i_xori() {
    gpr[rt] = gpr[rs] ^ (ri & 0xFFFF);
}

void i_j() {

}

void i_jal() {

}

void f_add() {

}

void f_sub() {

}

void f_mult() {

}

void f_div() {

}

void f_and() {

}

void f_or() {

}

void f_xor() {

}

void f_nor() {

}

void f_slt() {

}

void f_jr() {

}

void f_sll() {

}

void f_srl() {

}

void f_sra() {

}

void f_mfhi() {

}

void f_mflo() {

}

void f_syscall() {

}

int16_t get_immediate() {
    return static_cast<int16_t>(ri & 0xFFFF);
}

void branch() {
    int32_t s_offset = get_immediate() << 2;
    pc += s_offset;
}
