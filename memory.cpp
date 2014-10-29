#include "memory.h"

#define MAX_ADDR 255

namespace vCPU{
    Memory::Memory(){
	    m_memspace = new uint8_t[MAX_ADDR];
    }
    Memory::~Memory(){
        delete m_memspace;
    }
    const uint8_t& Memory::read(uint8_t pos){
        return m_memspace[pos];
    }

    void RAM::write(uint8_t pos, uint8_t value){
        m_memspace[pos] = value;
    }
}
