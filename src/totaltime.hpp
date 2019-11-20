#ifndef TOTALTIME_HPP
#define TOTALTIME_HPP

#include <ostream>

namespace devsim {
	class TotalTime {
		private:
			double real_time;
			int discrete_time;
		public:
			TotalTime(double real_time, int discrete_time) { this->real_time = real_time; this->discrete_time = discrete_time; }
			TotalTime() : real_time(0), discrete_time(0) {}

			friend bool operator<(TotalTime const& a, TotalTime const& b);
			friend bool operator<=(TotalTime const& a, TotalTime const& b);
			friend bool operator>(TotalTime const& a, TotalTime const& b);
			friend bool operator>=(TotalTime const& a, TotalTime const& b);
			friend bool operator==(TotalTime const& a, TotalTime const& b);
			friend bool operator!=(TotalTime const& a, TotalTime const& b);
			friend std::ostream& operator<<(std::ostream&, TotalTime const&);

			TotalTime advance(TotalTime);
			TotalTime advance(double);
			double length(TotalTime);
			double get_real() { return real_time; }
			int get_discrete() { return discrete_time; }
	};
}

#endif
