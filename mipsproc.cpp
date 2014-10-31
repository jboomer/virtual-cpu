#include "mipsproc.h"


//TODO: get opCode(), get rs etc. in private helper functies

namespace vCPU{
    MIPSproc::MIPSproc(RAM *mem)
    {
        memory = mem;
        regs = new uint32_t[32];
        ir = 0;
        pc = 0; //start address
        npc = 0; //next address

    }

    MIPSproc::~MIPSproc()
    {
        delete(memory);
    }

    void MIPSproc::run()
    {
        //while(not end of instructions)
        //{
        //  fetch()
        //  decode()
        //  execute()
        //  mem_acces()
        //  mem_writeback()
        //}
    }

    void MIPSproc::fetch(){
        pc = npc;
        for (int i = 0; i < 4; i++)
        {
            (ir >> (i * 8)) = memory->read(pc + i); // LSB eerst?
        }
        npc = pc + 4; //Gets overwritten for jumps and branches
    }

    void MIPSproc::decode()
    {
        switch(opCode())
        {
        case(OC_ALU):
            // R - type
            ALUSrcA = regs[r_rs()];
            ALUSrcB = regs[r_rt()];
            break;

        case(OC_ADDI):
        case(OC_ADDIU):
        case(OC_ANDI):
        case(OC_ORI):
            // Immediate ALU instructions
            ALUSrcA = regs[i_rs()];
            ALUSrcA = i_imm();

        default:
            break;
        }
    }

    void MIPSproc::execute()
    {
        //TODO: Alle acties in functies zetten
        emit process_cmd(ir);

        switch(opCode())
        {
        case(OP_ALU):
            switch(r_func()){
            case(FUNCT_ADD):
                //TODO: Overflow
                regs[r_rd()] = ALUSrcA + ALUSrcB;
                break;
            }

            break;
        case(OC_J):
            pc = npc;
            npc = (pc & 0xf0000000) | ((ir & 0x3ffffff) << 2);
            break;
        case(OC_JAL):
            regs[31] = pc + 4;
            pc = npc;
            npc = (pc & 0xf0000000) | ((ir & 0x3fffffff) << 2);
            break;
        default:
            break;
        }
    }

    void MIPSproc::mem_acces()
    {
        switch(opCode())
        {
        case(OC_LBU):
            regs[i_rt()] = memory->read(regs[i_rs() + i_imm()]);
        case(OC_LW):
            for (int i = 0; i < 4; i++)
            {
                regs[i_rt()] = memory->read(regs[i_rs()] + i_imm() + i);
            }
        default:
            break;
        }
    }

    void MIPSproc::mem_writeback()
    {
        switch(opCode())
        {
        case(OP_SB):
            memory->write(regs[i_rs()] + i_imm(), regs[i_rt()] & 0xff);
            break;
        case(OP_SW):
            for (int i = 0; i < 4; i++)
            {
                memory->write(regs[i_rs()] + i_imm() + i, (regs[i_rt()] >> i) & 0xff);
            }
            break;
        default:
            break;
        }
    }

    int MIPSproc::opCode()
    {
        return ((ir >> OP) & 0x3f);
    }

    int MIPSproc::r_rs()
    {
        return ((ir >> R_RS) & 0x1f);
    }

    int MIPSproc::r_rt()
    {
        return ((ir >> R_RT) & 0x1f);
    }

    int MIPSproc::r_rd()
    {
        return ((ir >> R_RD) & 0x1f);
    }

    int MIPSproc::r_shamt()
    {
        return ((ir >> R_SHAMT) & 0x1f);
    }

    int MIPSproc::i_rs()
    {
        return ((ir >> I_RS) & 0x1f);
    }

    int MIPSproc::i_rt()
    {
        return ((ir >> I_RT) & 0x1f);
    }

    int MIPSproc::i_imm()
    {
        return ((ir >> I_IMM) & 0xffff);
    }

    int MIPSproc::j_addr()
    {
        return ((ir >> J_ADDR) & 0x3ffffff);
    }
}
