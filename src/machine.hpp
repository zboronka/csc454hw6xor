#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "mooremachine.hpp"
#include "totaltime.hpp"
#include "port.hpp"

class Machine: public devsim::MooreMachine {
	private:
		int p = 0;

		long long s = 0;
		long long t = 0;
	public:
		devsim::Port<int>* input = nullptr;
		devsim::Port<int>* output = nullptr;

		Machine(long long t, int priority) : t(t), 
		                                     input(new devsim::Port<int>()),
		                                     output(new devsim::Port<int>()) { this->set_priority(priority); }
		~Machine() { delete input; delete output; }
		Machine(const Machine& other);
		Machine& operator=(const Machine& other);

		long long ta() { return p > 0 ? s : -1; }

		void lambda() { output->set(1); }

		void delta_int(devsim::TotalTime);
		void delta_ext(devsim::TotalTime); 
		void delta_con(devsim::TotalTime);
};

#endif
