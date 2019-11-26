#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <sstream>

#include "mooremachine.hpp"
#include "totaltime.hpp"
#include "port.hpp"

class Memory : public devsim::MooreMachine {
	private:
		bool q1 = false;
		bool q2 = false;

	public:
		devsim::Port<bool>* input = nullptr;
		devsim::Port<bool>* output = nullptr;

		Memory(int priority) : 
			input(new devsim::Port<bool>()), 
			output(new devsim::Port<bool>()) { this->set_priority(priority); }
		~Memory() { delete input; delete output; }
		Memory(const Memory& other);
		Memory& operator=(const Memory& other);

		std::string insertion() const;

		long long ta() { return devsim::SECOND; }

		void lambda() { output->set(q1); }

		void delta_int(devsim::TotalTime);
		void delta_ext(devsim::TotalTime); 
		void delta_con(devsim::TotalTime);
};

#endif
