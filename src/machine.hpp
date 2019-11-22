#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "mooremachine.hpp"
#include "port.hpp"

class Machine: public devsim::MooreMachine {
	private:
		int p = 0;

		long long s = 0;
		long long t = 0;
	public:
		devsim::Port<int>* input = nullptr;
		devsim::Port<int>* output = nullptr;

		Machine(long long t, int priority) { this->t = t; this->set_priority(priority); }
		~Machine() { delete input; delete output; }
		Machine(const Machine& other);
		Machine& operator=(const Machine& other);

		long long ta() { return p > 0 ? s : -1; }

		void lambda() { output->set(1); }

		void delta_int() { p -= 1; s = t; }
		void delta_ext(long long e) { s = p == 0 ? t : s - e; p += input->get(); } 
		void delta_con() { p += input->get() - 1; s = t; }

		std::string insertion() const { return "" + p; }
};

#endif
