#ifndef TOTALTIME_HPP
#define TOTALTIME_HPP

#include <ostream>

namespace devsim {
	static const long long SECOND = 1000000000;

	class TotalTime {
		private:
			long long real_time;
			int discrete_time;
		public:
			TotalTime(long long real_time, int discrete_time) { this->real_time = real_time; this->discrete_time = discrete_time; }
			TotalTime() : real_time(0), discrete_time(0) {}

			friend bool operator<(TotalTime const& a, TotalTime const& b);
			friend bool operator<=(TotalTime const& a, TotalTime const& b);
			friend bool operator>(TotalTime const& a, TotalTime const& b);
			friend bool operator>=(TotalTime const& a, TotalTime const& b);
			friend bool operator==(TotalTime const& a, TotalTime const& b);
			friend bool operator!=(TotalTime const& a, TotalTime const& b);
			friend std::ostream& operator<<(std::ostream&, TotalTime const&);

			TotalTime advance(TotalTime);
			TotalTime advance(long long);
			long long length(TotalTime);
			long long get_real() { return real_time; }
			int get_discrete() { return discrete_time; }
	};
}

#endif
