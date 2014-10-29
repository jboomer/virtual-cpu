#include "mipsproc.h"

namespace vCPU{
    MIPSproc::MIPSproc(RAM *mem)
    {
        memory = mem;
        regs = new uint32_t[32];
        ir = 0;
        pc = 0; //start address
    }

    MIPSproc::~MIPSproc()
    {
        delete(memory);
    }

    void MIPSproc::fetch(){
        ir = memory->read(pc);
        npc = pc + 1;
    }

    void MIPSproc::decode(const uint32_t &instr)
    {

    }
}
