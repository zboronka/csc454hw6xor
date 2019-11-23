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
#include "machine.hpp"
#include "event.hpp"
#include "colors.hpp"

using namespace devsim;

int main() {
	Port<int>* in = new Port<int>();
	Port<int>* out = new Port<int>();

	Machine* press = new Machine(devsim::SECOND,0);
	Machine* drill = new Machine(devsim::SECOND*2,1);

	Pipe netin = Pipe(in, press->input, nullptr, press);
	Pipe netout = Pipe(drill->output, out, drill, nullptr);
	std::vector<Pipe>* pipes = new std::vector<Pipe>();
	pipes->push_back(netin);
	pipes->push_back(netout);
	{pipes->push_back(Pipe(press->output, drill->input, press, drill));}

	std::vector<Event>* pqueue = new std::vector<Event>();

	std::unordered_map<long long,int> trajectory;
	std::regex input("\\((\\d*\\.\\d*|\\d*),(\\d*)\\)");
	std::smatch matches;

	std::string command;
	for(std::cin >> command; command != "run"; std::cin >> command) {
		auto words_begin = std::sregex_iterator(command.begin(), command.end(), input);
		auto words_end = std::sregex_iterator();
		for(std::sregex_iterator i = words_begin; i != words_end; i++) {
			long long time = (long long)devsim::SECOND*atof((*i)[1].str().c_str());
			pqueue->push_back(Event(EXT, TotalTime(time, 0), press));
			make_heap(pqueue->begin(), pqueue->end(), Event::compare);
			trajectory[time] = atoi((*i)[2].str().c_str());
		}
	}

	while(!pqueue->empty()) {
		Event e = pqueue->front();
		pqueue->erase(pqueue->begin());
		make_heap(pqueue->begin(), pqueue->end(), Event::compare);

		if(trajectory.find(e.time.get_real()) != trajectory.end() && e.target == press && e.delta == EXT) {
			in->set(trajectory[e.time.get_real()]);
			netin.pipe();
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
				pqueue->push_back(Event(EXT, e.time, pipe.output_machine));
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
			std::cout << out->get() << std::endl << std::endl;
		}
	}

	delete in;
	delete out;
	delete pipes;
	delete drill;
	delete press;
	delete pqueue;
}
