#ifndef PORT_HPP
#define PORT_HPP

namespace devsim {
	template <class T>
	class Port {
		private:
			T payload;
			int links;
			int accesses;
		public:
			void set(T t) { payload = t; accesses = 0; }
			T get() { if(accesses < links) { accesses++; return payload; } throw "PortNotOpenException"; }
			bool available() { return accesses < links; }
			void link() { links++; accesses++; }
	};
}

#endif
