#include "cpu.h"
#include "opcodes.h"

namespace vCPU{
CPU::CPU(RAM *mem) : instr_addr(0xff), addr_ceil(0xfe){
		memory = mem;
		m_halt = true;
        pc = 0;
	}
	
	CPU::~CPU(){
		delete(memory);		
	}

	void CPU::run(){
		m_halt = false;
		while(!m_halt){
			memory->write(instr_addr, fetch());
			decode(memory->read(instr_addr));
		}	
	}
	
    uint8_t CPU::fetch(){
		uint8_t opcode = 0;
		opcode =  memory->read(pc++);
		if (pc > addr_ceil){
			halt();
		}
		return opcode;
	}

	void CPU::decode(const uint8_t& opcode){
		if (m_halt) return;
        emit process_cmd(opcode);
		switch(opcode & 0xff){
			case(HALT) : {
				halt();
				break;
			}
			case(ADD) : {
				add();
				break;
			}
			case(STORE) : {
				store();
				break;
			}
			case(PRINT) : {
				print();
				break;
			}
            case(LOADA) : {
				loadA();
				break;
			}
			case(LOADB) : {
				loadB();
				break;
			}
			case(PUTA) : {
				putA();
				break;
			}
			case(PUTB) : {
				putB();
				break;
			}
			default : {
				break;
			}
		}
	}

	void CPU::halt(){
		m_halt = true;	
	}

	void CPU::add(){
		acc = reg_a + reg_b;
	}

	void CPU::store(){
		/* Stores the accumulator value in target location */
		reg_c = memory->read(pc++);
		memory->write(reg_c, acc);
	}

    void CPU::print(){
		//PC is now pointing at location of mem addr to load
		reg_c = memory->read(pc++);
		reg_a = memory->read(reg_c);
        emit output((int)reg_a);
	}

	void CPU::loadA(){
		/* Loads target address location in reg_a */
		reg_c = memory->read(pc++);
		reg_a = memory->read(reg_c);
	}

	void CPU::loadB(){
		/* Loads target address location in reg_b */
		reg_c = memory->read(pc++);
		reg_b = memory->read(reg_c);
	}

	void CPU::putA(){
		reg_a = memory->read(pc++);
	}

	void CPU::putB(){
		reg_b= memory->read(pc++);
	}
}
