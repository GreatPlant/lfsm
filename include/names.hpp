#ifndef NAMES_HPP_
#define NAMES_HPP_

#include <cstdint>

#define STATE(str)	str = State<name(#str)>
#define STATE_A(str, act)	str = State<name(#str), act>
#define EVENT(str)	str = Event<name(#str)>


constexpr unsigned int name (const char* n){

	  unsigned int  res = 0;

      for (uint_fast32_t i = 0; n[i] != '\0'; i++) {

		char data = n[i];

	    for (std::uint_fast32_t j = sizeof (char) * 8; j > 0; j--) {

	      res = ((res ^ data) & 1) ? (res >> 1) ^ 0x8C : (res >> 1);
	      data >>= 1;
	    }
	  }
	  return res;
};

#endif /* NAMES_HPP_ */
