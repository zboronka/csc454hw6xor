#include "memory.hpp"

Memory::Memory(const Memory& other) {
	q1 = other.q1;
	q2 = other.q2;

	if(other.input != nullptr) {
		input = new devsim::Port<bool>();
		memcpy(input, other.input, sizeof(devsim::Port<bool>));
	}
	else {
		input = nullptr;
	}
	
	if(other.output != nullptr) {
		output = new devsim::Port<bool>();
		memcpy(output, other.output, sizeof(devsim::Port<bool>));
	}
	else {
		output = nullptr;
	}
}

Memory& Memory::operator=(const Memory& other) {
	if(this != &other) {
		q1 = other.q1;
		q2 = other.q2;

		if(input != nullptr) {
			delete input;
		}
		else {
			input = new devsim::Port<bool>();
		}

		if(output != nullptr) {
			delete output;
		}
		else {
			output = new devsim::Port<bool>();
		}

		if(other.input != nullptr) {
			memcpy(input, other.input, sizeof(devsim::Port<bool>));
		}
		else {
			input = nullptr;
		}

		if(other.output != nullptr) {
			memcpy(output, other.output, sizeof(devsim::Port<bool>));
		}
		else {
			output = nullptr;
		}
	}

	return *this;
}

std::string Memory::insertion() const { 
	std::ostringstream convert;
	convert << this->get_priority() << " q1: " << (q1 ? "true" : "false") << " q2: " << (q2 ? "true" : "false");
	return convert.str(); 
}

void Memory::delta_int(devsim::TotalTime now) {
	q1 = q2;
	if(input->available()) {
		q2 = input->get();
	}

	lastdelta = now;
}

void Memory::delta_ext(devsim::TotalTime now) { 
	lastdelta = now; 
} 

void Memory::delta_con(devsim::TotalTime now) {
	q1 = q2;
	if(input->available()) {
		q2 = input->get();
	}

	lastdelta = now;
}
