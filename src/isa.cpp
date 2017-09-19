#include "../include/isa.h"
#include "../include/control.h"
#include <cstdio>

int32_t mem[MEM_SIZE] = { 0 };
int32_t gpr[32] = { 0 };
uint32_t * const gpr_u = reinterpret_cast<uint32_t * const>(gpr);
int32_t ri = 0;
uint32_t pc = TEXT_START;
int32_t hi = 0;
int32_t lo = 0;

uint8_t op, rs, rt, rd, shamt, funct;
int16_t k16;
uint32_t k26;

std::map<uint8_t, instruction> map_opcodes = {
        {0x00, &i_ext},      {0x23, &i_lw},       {0x20, &i_lb},       {0x24, &i_lbu},
        {0x21, &i_lh},       {0x25, &i_lhu},      {0x0F, &i_lui},      {0x2B, &i_sw},
        {0x28, &i_sb},       {0x29, &i_sh},       {0x04, &i_beq},      {0x05, &i_bne},
        {0x06, &i_blez},     {0x07, &i_bgtz},     {0x08, &i_addi},     {0x0A, &i_slti},
        {0x0B, &i_sltiu},    {0x0C, &i_andi},     {0x0D, &i_ori},      {0x0E, &i_xori},
        {0x02, &i_j},        {0x03, &i_jal},      {0x09, &i_addi}
};

std::map<uint8_t, instruction> map_funct = {
        {0x20, &f_add},      {0x22, &f_sub},      {0x18, &f_mult},     {0x1A, &f_div},
        {0x24, &f_and},      {0x25, &f_or},       {0x26, &f_xor},      {0x27, &f_nor},
        {0x2A, &f_slt},      {0x08, &f_jr},       {0x00, &f_sll},      {0x02, &f_srl},
        {0x03, &f_sra},      {0x0C, &f_syscall},  {0x10, &f_mfhi},     {0x12, &f_mflo},
        {0x21, &f_add} // ADDU se comporta da mesma maneira que ADD
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
    auto it = map_funct.find(funct);
    if (it == map_funct.end()) {
        printf("Código funct 0x%.6X não foi implementado!\n", funct);
    } else {
        (*(it->second))();
    }
}

void i_lw() {
    gpr[rt] = lw(gpr_u[rs], k16);
}

void i_lb() {
    gpr[rt] = lb(gpr_u[rs], k16);
}

void i_lbu() {
    gpr[rt] = lbu(gpr_u[rs], k16);
}

void i_lh() {
    gpr[rt] = lh(gpr_u[rs], k16);
}

void i_lhu() {
    gpr[rt] = lhu(gpr_u[rs], k16);
}

void i_lui() {
    gpr[rt] = k16 << 16;
}

void i_sw() {
    sw(gpr_u[rs], k16, gpr[rt]);
}

void i_sb() {
    sb(gpr_u[rs], k16, static_cast<int8_t>(gpr[rt] & 0xFF));
}

void i_sh() {
    sh(gpr_u[rs], k16, static_cast<int16_t>(gpr[rt] & 0xFFFF));
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
    gpr[rt] = gpr[rs] + k16;
}

void i_slti() {
    gpr[rt] = (gpr[rs] < k16);
}

void i_sltiu() {
    int32_t imm = k16;
    gpr[rt] = (gpr_u[rs] < static_cast<uint32_t>(imm));
}

void i_andi() {
    gpr[rt] = gpr[rs] & k16;
}

void i_ori() {
    gpr[rt] = gpr[rs] | k16;
}

void i_xori() {
    gpr[rt] = gpr[rs] ^ k16;
}

void i_j() {
    jump(k26);
}

void i_jal() {
    ra = pc;
    jump(k26);
}

void f_add() {
    gpr[rd] = gpr[rs] + gpr[rt];
}

void f_sub() {
    gpr[rd] = gpr[rs] - gpr[rt];
}

void f_mult() {
    int64_t prod = gpr[rs] * gpr[rt];
    hi = static_cast<int32_t>(prod >> 32);
    lo = static_cast<int32_t>(prod & 0xFFFFFFFF);
}

void f_div() {
    if (gpr[rt] != 0) {
        lo = gpr[rs] / gpr[rt];
        hi = gpr[rs] % gpr[rt];
    }
}

void f_and() {
    gpr[rd] = gpr[rs] & gpr[rt];
}

void f_or() {
    gpr[rd] = gpr[rs] | gpr[rt];
}

void f_xor() {
    gpr[rd] = gpr[rs] ^ gpr[rt];
}

void f_nor() {
    gpr[rd] = ~(gpr[rs] ^ gpr[rt]);
}

void f_slt() {
    gpr[rd] = gpr[rs] < gpr[rt];
}

void f_jr() {
    if (gpr[rs] % 4 != 0) {
        throw TS_except_alignment_word;
    }
    pc = gpr_u[rs];
}

void f_sll() {
    gpr_u[rd] = gpr_u[rt] << shamt;
}

void f_srl() {
    gpr_u[rd] = gpr_u[rt] >> shamt;
}

void f_sra() {
    gpr[rd] = gpr[rt] >> shamt;
}

void f_mfhi() {
    gpr[rd] = hi;
}

void f_mflo() {
    gpr[rd] = lo;
}

void f_syscall() {
    switch (v0) {
        case 1: // Print integer
            printf("%d", a0);
            break;
        case 4: { // Print string
            auto s = reinterpret_cast<char *>(mem) + a0;
            printf("%s", s);
            break;
        }
        case 10: // Terminate
            throw TS_except_syscall_exit;
        default:
            throw TS_except_syscall_undefined;
    }
}

void branch() {
    int32_t s_offset = k16 << 2;
    pc += s_offset;
}

void jump(int32_t address) {
    static const uint32_t mask = 0x0FFFFFFF;
    auto dest = address << 2;
    dest &= mask;
    pc &= ~mask;
    pc |= dest;
}
