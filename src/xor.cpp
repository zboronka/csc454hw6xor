#include "xor.hpp"

Xor::Xor(const Xor& other) {
	state = other.state;

	if(other.x1 != nullptr) {
		x1 = new devsim::Port<bool>();
		memcpy(x1, other.x1, sizeof(devsim::Port<bool>));
	}
	else {
		x1 = nullptr;
	}

	if(other.x2 != nullptr) {
		x2 = new devsim::Port<bool>();
		memcpy(x2, other.x2, sizeof(devsim::Port<bool>));
	}
	else {
		x2 = nullptr;
	}
	
	if(other.output != nullptr) {
		output = new devsim::Port<bool>();
		memcpy(output, other.output, sizeof(devsim::Port<bool>));
	}
	else {
		output = nullptr;
	}
}

Xor& Xor::operator=(const Xor& other) {
	if(this != &other) {
		state = other.state;

		if(x1 != nullptr) {
			delete x1;
		}
		else {
			x1 = new devsim::Port<bool>();
		}

		if(x2 != nullptr) {
			delete x2;
		}
		else {
			x2 = new devsim::Port<bool>();
		}

		if(output != nullptr) {
			delete output;
		}
		else {
			output = new devsim::Port<bool>();
		}

		if(other.x1 != nullptr) {
			memcpy(x1, other.x1, sizeof(devsim::Port<bool>));
		}
		else {
			x1 = nullptr;
		}

		if(other.x2 != nullptr) {
			memcpy(x2, other.x2, sizeof(devsim::Port<bool>));
		}
		else {
			x2 = nullptr;
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

std::string Xor::insertion() const { 
	std::ostringstream convert;
	convert << this->get_priority() << " " << (state ? "true" : "false");
	return convert.str(); 
}

void Xor::lambda() {
	output->set(state);
}

void Xor::delta_int(devsim::TotalTime now) {
	if(x1->available() && x2->available()) {
		state = x1->get() ^ x2->get();
	}

	lastdelta = now;
}

void Xor::delta_ext(devsim::TotalTime now) { 
	lastdelta = now; 
} 

void Xor::delta_con(devsim::TotalTime now) {
	if(x1->available() && x2->available()) {
		state = x1->get() ^ x2->get();
	}

	lastdelta = now;
}
