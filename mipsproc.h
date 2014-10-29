#ifndef MIPSPROC_H
#define MIPSPROC_H

#include "memory.h"
#include <stdint.h>
#include <QObject>

namespace vCPU{

    /*
     * class CPU : A prototype class for a general CPU with Qt signals
     * with 32-bit registers
     */
    class MIPSproc : public QObject {
            Q_OBJECT

        private:
            RAM *memory;

            // General purpose registers
            uint32_t *regs;

            //Special registers
            uint32_t pc; //Program counter
            uint32_t npc; //Next program counter
            uint32_t ir; //Instruction register
            uint32_t hi; //HIGH register
            uint32_t lo; //LOW register


            //Flags
            bool m_halt;
            bool m_overflow;
            bool m_underflow;

            void fetch();
            void decode(const uint32_t& instr);

        public:
            MIPSproc(RAM *mem);
            ~MIPSproc();
            void run();

        signals:
            void output(int output);
            void process_cmd(int opcode);
    };
}

#endif
