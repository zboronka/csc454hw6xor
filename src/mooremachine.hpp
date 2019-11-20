#ifndef MOOREMACHINE_HPP
#define MOOREMACHINE_HPP

#include <cstring>

#include "event.hpp"

namespace devsim {
	class Event;
	class MooreMachine {
		private:
			Event* internal;
			int priority;

		public:
			virtual double ta() = 0;

			virtual void lambda() = 0;

			virtual void delta_int() = 0;
			virtual void delta_ext(double) = 0;
			virtual void delta_con() = 0;

			MooreMachine() : internal(nullptr) {}
			~MooreMachine();
			MooreMachine(const MooreMachine& other);
			MooreMachine& operator=(const MooreMachine& other);

			Event* get_internal() { return internal; }
			void set_internal(Event* internal);

			int get_priority() { return priority; }
			void set_priority(int priority) { this->priority = priority; }

			virtual std::string insertion() const = 0;
			friend std::ostream& operator<<(std::ostream&, MooreMachine const&);
			friend bool operator<(MooreMachine const&, MooreMachine const&);
			friend bool operator>(MooreMachine const&, MooreMachine const&);
			friend bool operator==(MooreMachine const&, MooreMachine const&);
	};
}

#endif
