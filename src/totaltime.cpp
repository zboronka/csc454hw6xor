#include "totaltime.hpp"

namespace devsim {
	bool operator<(TotalTime const& a, TotalTime const& b) {
		return a.real_time == b.real_time ? a.discrete_time < b.discrete_time : a.real_time < b.real_time;
	}

	bool operator<=(TotalTime const& a, TotalTime const& b) {
		return a == b || a < b;
	}

	bool operator>(TotalTime const& a, TotalTime const& b) {
		return a.real_time == b.real_time ? a.discrete_time > b.discrete_time : a.real_time > b.real_time;
	}

	bool operator>=(TotalTime const& a, TotalTime const& b) {
		return a==b || a > b;
	}

	bool operator==(TotalTime const& a, TotalTime const& b) {
		return a.real_time == b.real_time && a.discrete_time == b.discrete_time;
	}

	bool operator!=(TotalTime const& a, TotalTime const& b) {
		return !(a==b);
	}

	std::ostream& operator<<(std::ostream &strm, TotalTime const& a) {
		return strm << "(" << (long double)a.real_time/SECOND << ", " << a.discrete_time << ")";
	}

	TotalTime TotalTime::advance(TotalTime b) {
		return b.real_time == 0 ? TotalTime(real_time, discrete_time + b.discrete_time) : TotalTime(real_time + b.real_time, 0);
	}

	TotalTime TotalTime::advance(long long b) {
		return TotalTime(real_time + b, 0);
	}

	long long TotalTime::length(TotalTime b) {
		return b.real_time - real_time;
	}
}
