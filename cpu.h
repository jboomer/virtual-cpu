#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include <QObject>

namespace vCPU{

    class CPU : public QObject {
            Q_OBJECT

        private:
			RAM *memory;

			uint8_t pc;
			uint8_t reg_a;
			uint8_t reg_b;
			uint8_t reg_c;
			uint8_t acc;
            const uint8_t instr_addr;
            const uint8_t addr_ceil;

			bool m_halt;
			bool m_overflow;
			bool m_underflow;

			void halt();
			void add();
			void store();
			void loadA();
			void loadB();
			void putA();
			void putB();
            void print();

            uint8_t fetch();
			void decode(const uint8_t& op);
				
		public:
			CPU(RAM *mem);
			~CPU();
			void run();

        signals:
            void output(int output);
            void process_cmd(int opcode);
	};
}

#endif
