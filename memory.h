#ifndef CPU_MEMORY
#define CPU_MEMORY

#include <stdint.h>


namespace vCPU{
    /*
     *32b memory
     */
    class Memory{
		protected:
        uint8_t *m_memspace;
		public:
	    Memory();
	    ~Memory();
            const uint8_t& read(uint32_t pos);
    };

    class RAM: public Memory{
		public:
            void write(uint32_t pos, uint8_t val);
	};
}


#endif
