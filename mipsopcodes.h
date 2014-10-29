#ifndef MIPS_H
#define MIPS_H

//Shift positions
#define OP 26

#define R_RS 21
#define R_RT 16
#define R_RD 11
#define R_SHAMT 6
#define R_FUNC 0

#define I_RD 21
#define I_RS 16
#define I_IMM 0

#define J_ADDR 0

//Opcodes

// "I" type
#define OC_ADDI 0x08
#define OC_ADDIU 0x09
#define OC_ANDI 0x0c
#define OC_BEQ 0x04
#define OC_BNE 0x05
#define OC_LBU 0x24
#define OC_LHU 0x25
#define OC_LUI 0x0f
#define OC_LW 0x23
#define OC_ORI 0x0d
#define OC_SB 0x28
#define OC_SH 0x29
#define OC_SLTI 0x0a
#define OC_SLTIU 0x0b
#define OC_SW 0x2b

// "J" type
#define OC_J 0x02
#define OC_JAL 0x03

//"R" type
#define OC_ALU 0x00
#define OC_MFC0 0x10
#define FUNCT_ADD 0x20
#define FUNCT_ADDU 0x21
#define FUNCT_AND 0x24
#define FUNCT_DIV 0x1a
#define FUNCT_DIVU 0x1b
#define FUNCT_JR 0x08
#define FUNCT_MFHI 0x10
#define FUNCT_MFLO 0x12
#define FUNCT_MULT 0x18
#define FUNCT_MULTU 0x19
#define FUNCT_NOR 0x27
#define FUNCT_XOR 0x26
#define FUNCT_OR 0x25
#define FUNCT_SLT 0x2a
#define FUNCT_SLTU 0x2b
#define FUNCT_SLL 0x00
#define FUNCT_SRL 0x02
#define FUNCT_SRA 0x03
#define FUNCT_SUB 0x22
#define FUNCT_SUBU 0x23

#endif // MIPS_H
