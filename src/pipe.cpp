#include "pipe.hpp"

namespace devsim {
	Pipe::Pipe(const Pipe& other) {
		input_machine = other.input_machine;
		output_machine = other.output_machine;

		p = new PipeModel<int>();
		memcpy(p, other.p, sizeof(PipeModel<int>));
	}

	Pipe& Pipe::operator=(const Pipe& other) {
		if(this != &other) {
			delete p;
			input_machine = other.input_machine;
			output_machine = other.output_machine;
			memcpy(other.p, p, sizeof(PipeModel<int>));
		}

		return *this;
	}
}
