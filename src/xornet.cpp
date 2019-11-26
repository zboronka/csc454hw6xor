#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include <regex>

#include "port.hpp"
#include "pipe.hpp"
#include "totaltime.hpp"
#include "xor.hpp"
#include "memory.hpp"
#include "event.hpp"
#include "colors.hpp"

using namespace devsim;

struct xorinput {
	bool x1;
	bool x2;
};

std::ostream& operator<<(std::ostream& strm, xorinput const& x) {
	return strm << "x1: " << (x.x1 ? "true" : "false") << " x2: " << (x.x2 ? "true" : "false");
}

int main() {
	Port<bool>* in1 = new Port<bool>();
	Port<bool>* in2 = new Port<bool>();
	Port<bool>* out = new Port<bool>();

	Xor* xor1 = new Xor(0);
	Xor* xor2 = new Xor(1);
	Memory* memory = new Memory(2);

	Pipe netin1 = Pipe(in1, xor1->x1, nullptr, xor1);
	Pipe netin2 = Pipe(in2, xor1->x2, nullptr, xor1);
	Pipe netout = Pipe(xor2->output, out, xor2, nullptr);
	std::vector<Pipe>* pipes = new std::vector<Pipe>();
	pipes->push_back(netin1);
	pipes->push_back(netin2);
	pipes->push_back(netout);
	{
		pipes->push_back(Pipe(xor1->output, xor2->x1, xor1, xor2));
		pipes->push_back(Pipe(xor2->output, memory->input, xor2, memory));
		pipes->push_back(Pipe(memory->output, xor2->x2, memory, xor2));
	}

	std::vector<Event>* pqueue = new std::vector<Event>();

	std::unordered_map<long long,xorinput> trajectory;
	std::regex input("\\((\\d*\\.\\d*|\\d*),(true|false),(true|false)\\)");
	std::smatch matches;

	std::string command;
	for(std::cin >> command; command != "run"; std::cin >> command) {
		auto words_begin = std::sregex_iterator(command.begin(), command.end(), input);
		auto words_end = std::sregex_iterator();
		for(std::sregex_iterator i = words_begin; i != words_end; i++) {
			long long time = (long long)devsim::SECOND*atof((*i)[1].str().c_str());
			pqueue->push_back(Event(EXT, TotalTime(time, 0), xor1));
			make_heap(pqueue->begin(), pqueue->end(), Event::compare);
			xorinput x;
			x.x1 = (*i)[2].str().compare("true") == 0;
			x.x2 = (*i)[3].str().compare("true") == 0;
			trajectory[time] = x;
		}
	}

	// Make every model start ticking at time 0
	{
		pqueue->push_back(Event(EXT, TotalTime(0, 0), xor1));
		pqueue->push_back(Event(EXT, TotalTime(0, 0), xor2));
		pqueue->push_back(Event(EXT, TotalTime(0, 0), memory));
		make_heap(pqueue->begin(), pqueue->end(), Event::compare);
	}

	while(!pqueue->empty()) {
		Event e = pqueue->front();
		pqueue->erase(pqueue->begin());
		make_heap(pqueue->begin(), pqueue->end(), Event::compare);

		if(trajectory.find(e.time.get_real()) != trajectory.end() && e.target == xor1 && e.delta == EXT) {
			in1->set(trajectory[e.time.get_real()].x1);
			in2->set(trajectory[e.time.get_real()].x2);
			netin1.pipe();
			netin2.pipe();
			std::cout << colors::INPUT << "NETWORK IN" << colors::RESET << std::endl;
			std::cout << "Current time: " << e.time << std::endl;
			std::cout << trajectory[e.time.get_real()] << std::endl << std::endl;
		}

		if(!pqueue->empty() && e.time == pqueue->front().time && e.target == pqueue->front().target) {
			pqueue->erase(pqueue->begin());
			pqueue->push_back(Event(CON, e.time, e.target));
			make_heap(pqueue->begin(), pqueue->end(), Event::compare);
			continue;
		}

		std::cout << e << std::endl << std::endl;

		switch(e.delta) {
			case EXT:
				e.target->delta_ext(e.time);
				if(e.target->get_internal() != nullptr) {
					for(auto i = pqueue->begin(); i < pqueue->end(); i++) {
						if(*e.target->get_internal()==*i) {
							pqueue->erase(i);
							make_heap(pqueue->begin(), pqueue->end(), Event::compare);
						}
					}
				}
				break;
			case INT:
				e.target->lambda();
				e.target->delta_int(e.time);
				break;
			case CON:
				e.target->lambda();
				e.target->delta_con(e.time);
			default:
				break;
		}

		for(Pipe pipe : *pipes) {
			if(pipe.pipe() && pipe.output_machine != nullptr) {
				if(pipe.output_machine->get_priority() < e.target->get_priority()) {
					pqueue->push_back(Event(EXT, e.time.advance(TotalTime(0,1)), pipe.output_machine));
				}
				else {
					pqueue->push_back(Event(EXT, e.time, pipe.output_machine));
				}
				make_heap(pqueue->begin(), pqueue->end(), Event::compare);
			}
		}

		if(e.target->ta() > 0) {
			e.target->set_internal(new Event(INT, e.time.advance(e.target->ta()), e.target));
			pqueue->push_back(*e.target->get_internal());
			make_heap(pqueue->begin(), pqueue->end(), Event::compare);
		}

		if(out->available()) {
			std::cout << colors::OUTPUT << "NETWORK OUT" << colors::RESET << std::endl;
			std::cout << "Current time: " << e.time << std::endl;
			std::cout << (out->get() ? "true" : "false") << std::endl << std::endl;
		}

		if(e.time.get_real() > devsim::SECOND*10) {
			break;
		}
	}

	delete in1;
	delete in2;
	delete out;
	delete pipes;
	delete xor1;
	delete xor2;
	delete memory;
	delete pqueue;
}
