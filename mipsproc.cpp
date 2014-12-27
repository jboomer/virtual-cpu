#include "mipsproc.h"
#include "mipsopcodes.h"

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
        while(!m_halt){
            fetch();
            decode();
            execute();
            mem_acces();
            mem_writeback();
        }
    }

    void MIPSproc::fetch(){
        pc = npc;
        ir = 0;

        for (int i = 0; i < 4; i++)
        {
            ir |= (memory->read(pc + i)) << (i * 8); // MSB eerst?
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
				//TODO: Overflow
        emit process_cmd(ir);

        switch(opCode())
        {
        case(OC_MFC0): //?
        case(OC_ALU):
            switch(r_func()){
            case FUNCT_ADD:
                regs[r_rd()] = ALUSrcA + ALUSrcB;
                break;
            case FUNCT_ADDU:
            case FUNCT_AND:
                regs[r_rd()] = ALUSrcA & ALUSrcB;
            break;
            case FUNCT_DIVU:
            case FUNCT_DIV:
                lo = ALUSrcA / ALUSrcB;
                hi = ALUSrcA % ALUSrcB;
                break;
            case FUNCT_JR:
                npc = ALUSrcA;
                break;
            case FUNCT_MFHI:
                regs[r_rd()] = hi;
                break;
            case FUNCT_MFLO:
                regs[r_rd()] = lo;
                break;
            case FUNCT_MULTU:
            case FUNCT_MULT:
                lo = ALUSrcA * ALUSrcB;
                break;
            case FUNCT_NOR:
								regs[r_rd()] = ~(ALUSrcA | ALUSrcB);
                break;
            case FUNCT_OR:
                regs[r_rd()] = ALUSrcA | ALUSrcB;
                break;
            case FUNCT_SLL:
                regs[r_rd()] = ALUSrcB << r_shamt();
                break;
            case FUNCT_SLTU:
            case FUNCT_SLT:
                regs[r_rd()] = (ALUSrcA < ALUSrcB) ? 1 : 0;
                break;
            case FUNCT_SRA:
                regs[r_rd()] = ALUSrcB >> r_shamt();
            case FUNCT_SRL:
                regs[r_rd()] = ALUSrcB >> ALUSrcA;
                break;
            case FUNCT_SUBU:
            case FUNCT_SUB:
                regs[r_rd()] = ALUSrcA - ALUSrcB;
                break;
            case FUNCT_XOR:
                regs[r_rd()] =  ALUSrcA ^ ALUSrcB;
                break;
            default:
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
        case(OC_SB):
            memory->write(regs[i_rs()] + i_imm(), regs[i_rt()] & 0xff);
            break;
        case(OC_SW):
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

    int MIPSproc::r_func()
    {
        return ((ir >> R_FUNC) & 0x3f);
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
