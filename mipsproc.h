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

            // Hidden registers
            uint32_t pc; //Program counter
            uint32_t npc; //Next program counter
            uint32_t ir; //Instruction register
            uint32_t hi; //HIGH register
            uint32_t lo; //LOW register

            uint32_t ALUSrcA;
            uint32_t ALUSrcB;
            uint8_t ALUOp;

            // Flags
            bool m_halt;
            bool m_overflow;
            bool m_underflow;

            // Instruction pipeline
            void fetch();
            void decode();
            void execute();
            void mem_acces();
            void mem_writeback();

            // Actions


            // Helper functions
            int opCode();
            int r_rs();
            int r_rt();
            int r_rd();
            int r_shamt();
            int r_func();
            int i_rs();
            int i_rt();
            int i_imm();
            int j_addr();

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
