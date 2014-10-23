#ifndef CPU_MEMORY
#define CPU_MEMORY

#include <stdint.h>

#define MAX_ADDR 255

namespace vCPU{
  class Memory{
		protected:
	  	uint8_t *m_memspace;
		public:
	    Memory();
	    ~Memory();
			const uint8_t& read(uint8_t pos);
  };

	class RAM: public Memory{
		public:
			void write(uint8_t pos, uint8_t val);
	};
}


#endif
