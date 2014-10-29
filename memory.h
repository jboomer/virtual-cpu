#ifndef CPU_MEMORY
#define CPU_MEMORY

#include <stdint.h>


namespace vCPU{
    /*
     *32b memory
     */
    class Memory{
		protected:
        uint32_t *m_memspace;
		public:
	    Memory();
	    ~Memory();
            const uint32_t& read(uint8_t pos);
    };

    class RAM: public Memory{
		public:
            void write(uint8_t pos, uint32_t val);
	};
}


#endif
