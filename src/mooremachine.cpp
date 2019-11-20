#include "mooremachine.hpp"

namespace devsim {
	MooreMachine::~MooreMachine() {
		if(internal != nullptr) {
			delete internal;
		}
	}

	MooreMachine::MooreMachine(const MooreMachine& other) {
		priority = other.priority;

		if(other.internal != nullptr) {
			internal = new Event();
			memcpy(internal, other.internal, sizeof(Event));
		}
		else {
			internal = nullptr;
		}
	}

	MooreMachine& MooreMachine::operator=(const MooreMachine& other) {
		if(this != &other) {
			priority = other.priority;
			if(internal != nullptr) {
				delete internal;
			}
			else {
				internal = new Event();
			}

			if(other.internal != nullptr) {
				memcpy(internal, other.internal, sizeof(Event));
			}
			else {
				internal = nullptr;
			}
		}

		return *this;
	}

	void MooreMachine::set_internal(Event* internal) {
		if(this->internal != nullptr) {
			delete this->internal;
		}

		this->internal = internal;
	}

	std::ostream& operator<<(std::ostream& strm, MooreMachine const& m) {
		return strm << m.insertion();
	}

	bool operator<(MooreMachine const& a, MooreMachine const& b) {
		return a.priority < b.priority;
	}

	bool operator>(MooreMachine const& a, MooreMachine const& b) {
		return a.priority > b.priority;
	}
	bool operator==(MooreMachine const& a, MooreMachine const& b) {
		return a.priority == b.priority;
	}
}
