/* Copyright (c) Michal Soucha, 2016
*
* This file is part of FSMlib
*
* FSMlib is free software: you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation, either version 3 of the License, or (at your option) any later
* version.
*
* FSMlib is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
* A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* FSMlib. If not, see <http://www.gnu.org/licenses/>.
*/

#define DBG_MEMORY_LEAK 0
#if DBG_MEMORY_LEAK
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif
#ifndef PARALLEL_COMPUTING
//#define PARALLEL_COMPUTING // un/comment this if CUDA is enabled/disabled
#endif // !PARALLEL_COMPUTING

#include "commons.h"
#include<iostream>

unique_ptr<DFSM> fsm;
static bool debug_mode = false;

#define COMPUTATION_TIME(com) \
	auto start = chrono::system_clock::now(); \
	com; \
	auto end = chrono::system_clock::now(); \
	chrono::duration<double> elapsed_seconds = end - start;\
	if (debug_mode) std::cerr << "time_elapsed:\t" << elapsed_seconds.count() << "s" << std::endl;

static void printTS(sequence_set_t& TS) {
	FSMlib::PrefixSet ps;
	seq_len_t len(0);
	int test_id = 0;
	for (const auto& cSeq : TS) {
		len += cSeq.size();
		ps.insert(cSeq);
		printf("tc_%d:\t%s\n", test_id, FSMmodel::getInSequenceAsString(cSeq).c_str());
		test_id += 1;
	}
	if (debug_mode) std::cerr << "total_resets:\t" << TS.size() << std::endl;
	if (debug_mode) std::cerr << "total_length:\t" << len << std::endl;
	//auto syms = ps.getNumberOfSymbols();
	//printf("%d,%d,%d,%f,%d,%f\n", TS.size(), len, TS.size()+len, double(len)/TS.size(), syms, double(syms)/len);
}

static void print_help() {
	std::cout << "FSMlib -f [path to the FSM file in Soucha's format] " << std::endl;
	std::cout << "  Optional parameters:" << std::endl;
	std::cout << "\t-es [0-9]+               // Number of extra states (Default: 0)" << std::endl;
	std::cout << "\t-m {w,wp,hsi,h,spy,spyh} // Testing method (Default: w method)" << std::endl;
	//std::cout << "\t-is_dot                  // FSM is a .dot file (Default: kiss)" << std::endl;
}

int main(int argc, char** argv) {

	int ES = 0;
	string method = "w";
	string fileName = "fsm.in";
	bool use_cin = true;

	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-f") == 0) {//number of extra states
				fileName = string(argv[i+1]);
				use_cin = false;
			}
			else if (strcmp(argv[i], "-es") == 0) {//number of extra states
				ES = atoi(argv[i+1]);
			}
			else if (strcmp(argv[i], "-m") == 0) {//testing method
				method = string(argv[i+1]);
			}
			else if (strcmp(argv[i], "-debug") == 0) {//debug mode
				debug_mode = true;
			}
			else if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "-h") == 0) {//help menu
				print_help();
				return 0;
			}

		}
	}
	
	if (use_cin) {
		fsm = FSMmodel::loadFSM_from_cin();
	}
	else {
		fsm = FSMmodel::loadFSM(fileName);
		if (debug_mode) std::cerr << "fsm_name:\t" << fileName << std::endl;
	}

	if (debug_mode) std::cerr << "ctt:\t" << method << std::endl;
	if (debug_mode) std::cerr << "es:\t" << ES << std::endl;

	if (method.compare("w") == 0) {// generate tests using the w method
		COMPUTATION_TIME(auto TS = W_method(fsm, ES););  printTS(TS);
	}
	else if (method.compare("wp") == 0) {// generate tests using the wp method
		COMPUTATION_TIME(auto TS = Wp_method(fsm, ES););  printTS(TS);
	}
	else if (method.compare("hsi") == 0) {// generate tests using the hsi method
		COMPUTATION_TIME(auto TS = HSI_method(fsm, ES););  printTS(TS);
	}
	else if (method.compare("h") == 0) {// generate tests using the h method
		COMPUTATION_TIME(auto TS = H_method(fsm, ES););  printTS(TS);
	}
	else if (method.compare("spy") == 0) {// generate tests using the spy method
		COMPUTATION_TIME(auto TS = SPY_method(fsm, ES););  printTS(TS);
	}
	else if (method.compare("spyh") == 0) {// generate tests using the spyh method
		COMPUTATION_TIME(auto TS = SPYH_method(fsm, ES););  printTS(TS);
	}
	// else if (method.compare("s") == 0) {// generate tests using the s method
	// 	COMPUTATION_TIME(auto TS = S_method(fsm, ES););  printTS(TS);
	// }
	// else {
	// 	auto st = getSplittingTree(fsm, true);
	// 	auto hsiST = getHarmonizedStateIdentifiersFromSplittingTree(fsm, st);
	// 	if (method.compare("hsi_st") == 0) {// generate tests using the hsi method using splitting tree 
	// 		COMPUTATION_TIME(auto TS = HSI_method(fsm, ES, hsiST););  printTS(TS);
	// 	}
	// 	else if (method.compare("spy_st") == 0) {// generate tests using the spy method using splitting tree 
	// 		COMPUTATION_TIME(auto TS = SPY_method(fsm, ES, hsiST););  printTS(TS);
	// 	}

	// }
	return 0;
}