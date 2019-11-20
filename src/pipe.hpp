#ifndef PIPE_HPP
#define PIPE_HPP

#include <cstring>

#include "port.hpp"
#include "mooremachine.hpp"

namespace devsim {
	class Pipe {
		private:
			class PipeConcept {
				public:
					virtual bool pipe() = 0;
			};

			template <typename T>
			class PipeModel : public PipeConcept {
				private:
					Port<T>* input_port;
					Port<T>* output_port;
				public:
					PipeModel(Port<T>* in, Port<T>* out) : 
						input_port(in),
						output_port(out) {}
					PipeModel() : 
						input_port(nullptr),
						output_port(nullptr) {}
					bool pipe() {
						if(input_port->available()) {
							output_port->set(input_port->get());
							return true;
						} 
						return false;
					}
			};

			PipeConcept* p;
		public:
			MooreMachine* input_machine;
			MooreMachine* output_machine;

			template <typename T>
			Pipe(Port<T>* in, Port<T>* out, MooreMachine* imach, MooreMachine* omach) :
				p(new PipeModel<T>(in, out)),
				input_machine(imach),
				output_machine(omach) { in->link(); out->link(); }
			~Pipe() { delete p; }
			Pipe(const Pipe& other);
			Pipe& operator=(const Pipe& other);

			bool pipe() { return p->pipe(); }
	};
}

#endif
