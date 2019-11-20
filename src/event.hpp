#ifndef EVENT_HPP
#define EVENT_HPP

#include "totaltime.hpp"
#include "mooremachine.hpp"
#include "colors.hpp"

namespace devsim {
	enum Delta { EXT, INT, CON };

	class MooreMachine;
	class Event {
		public:
			TotalTime time;
			MooreMachine* target;
			Delta delta;
			Event(Delta, TotalTime, MooreMachine*);
			Event() : time(TotalTime()), target(nullptr), delta(EXT) {}

			static bool compare(Event const&, Event const&);
			friend bool operator==(Event const&, Event const&);
			friend std::ostream& operator<<(std::ostream&, Event const&);
	};
}

#endif
