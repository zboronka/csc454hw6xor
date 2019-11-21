#include "machine.hpp"

Machine::Machine(const Machine& other) {
	p = other.p;
	s = other.s;
	t = other.t;

	if(other.input != nullptr) {
		input = new devsim::Port<int>();
		memcpy(input, other.input, sizeof(devsim::Port<int>));
	}
	else {
		input = nullptr;
	}

	if(other.output != nullptr) {
		output = new devsim::Port<int>();
		memcpy(output, other.output, sizeof(devsim::Port<int>));
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
			input = new devsim::Port<int>();
		}

		if(output != nullptr) {
			delete output;
		}
		else {
			output = new devsim::Port<int>();
		}

		if(other.input != nullptr) {
			memcpy(input, other.input, sizeof(devsim::Port<int>));
		}
		else {
			input = nullptr;
		}

		if(other.output != nullptr) {
			memcpy(output, other.output, sizeof(devsim::Port<int>));
		}
		else {
			output = nullptr;
		}
	}

	return *this;
}
