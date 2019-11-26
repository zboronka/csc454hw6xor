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

		protected:
			TotalTime lastdelta;

		public:
			virtual long long ta() = 0;

			virtual void lambda() = 0;

			virtual void delta_int(TotalTime) = 0;
			virtual void delta_ext(TotalTime) = 0;
			virtual void delta_con(TotalTime) = 0;

			MooreMachine() : internal(nullptr), lastdelta(TotalTime()) {}
			~MooreMachine();
			MooreMachine(const MooreMachine& other);
			MooreMachine& operator=(const MooreMachine& other);

			Event* get_internal() { return internal; }
			void set_internal(Event* internal);

			int get_priority() const { return priority; }
			void set_priority(int priority) { this->priority = priority; }

			virtual std::string insertion() const { return std::to_string(priority); }
			friend std::ostream& operator<<(std::ostream&, MooreMachine const&);
			friend bool operator<(MooreMachine const&, MooreMachine const&);
			friend bool operator>(MooreMachine const&, MooreMachine const&);
			friend bool operator==(MooreMachine const&, MooreMachine const&);
	};
}

#endif
