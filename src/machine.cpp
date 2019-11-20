#include "machine.hpp"

Machine::Machine(const Machine& other) {
	p = other.p;
	s = other.s;
	t = other.t;

	if(other.input != nullptr) {
		input = new Port<int>();
		memcpy(input, other.input, sizeof(Port<int>));
	}
	else {
		input = nullptr;
	}

	if(other.output != nullptr) {
		output = new Port<int>();
		memcpy(output, other.output, sizeof(Port<int>));
	}
	else {
		output = nullptr;
	}
}

Machine& Machine::operator=(const Machine& other) {
	if(this != &other) {
		p = other.p;
		s = other.s;
		t = other.t;

		if(input != nullptr) {
			delete input;
		}
		else {
			input = new Port<int>();
		}

		if(output != nullptr) {
			delete output;
		}
		else {
			output = new Port<int>();
		}

		if(other.input != nullptr) {
			memcpy(input, other.input, sizeof(Port<int>));
		}
		else {
			input = nullptr;
		}

		if(other.output != nullptr) {
			memcpy(output, other.output, sizeof(Port<int>));
		}
		else {
			output = nullptr;
		}
	}

	return *this;
}
