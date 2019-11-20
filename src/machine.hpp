#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "mooremachine.hpp"
#include "port.hpp"

using namespace devsim;

class Machine: public MooreMachine {
	private:
		int p = 0;

		double s = 0;
		double t = 0;
	public:
		Port<int>* input = nullptr;
		Port<int>* output = nullptr;

		Machine(double t, int priority) { this->t = t; this->set_priority(priority); }
		~Machine() { delete input; delete output; }
		Machine(const Machine& other);
		Machine& operator=(const Machine& other);

		double ta() { return p > 0 ? s : -1; }

		void lambda() { output->set(1); }

		void delta_int() { p -= 1; s = t; }
		void delta_ext(double e) { s = p == 0 ? t : s - e; p += input->get(); } 
		void delta_con() { p += input->get() - 1; s = t; }

		std::string insertion() const { return "hhhh"; }
};

#endif
