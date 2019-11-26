#ifndef XOR_HPP
#define XOR_HPP

#include <sstream>

#include "mooremachine.hpp"
#include "totaltime.hpp"
#include "port.hpp"
#include "colors.hpp"

class Xor: public devsim::MooreMachine {
	private:
		bool state = false;

	public:
		devsim::Port<bool>* x1 = nullptr;
		devsim::Port<bool>* x2 = nullptr;
		devsim::Port<bool>* output = nullptr;

		Xor(int priority) : 
			x1(new devsim::Port<bool>()), 
			x2(new devsim::Port<bool>()), 
			output(new devsim::Port<bool>()) { this->set_priority(priority); }
		~Xor() { delete x1; delete x2; delete output; }
		Xor(const Xor& other);
		Xor& operator=(const Xor& other);

		std::string insertion() const;

		long long ta() { return devsim::SECOND; }

		void lambda();
		void delta_int(devsim::TotalTime);
		void delta_ext(devsim::TotalTime); 
		void delta_con(devsim::TotalTime);
};

#endif
