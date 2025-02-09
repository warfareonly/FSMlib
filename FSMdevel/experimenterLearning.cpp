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
#include "commons.h"

#define PTRandSTR(f) f, #f

#define COMPUTATION_TIME(com) \
	auto start = chrono::system_clock::now(); \
	com; \
	auto end = chrono::system_clock::now(); \
	chrono::duration<double> elapsed_seconds = end - start; 

static unique_ptr<DFSM> fsm;
static FILE * outFile;

static bool showConjecture(const unique_ptr<DFSM>& conjecture) {
	auto fn = conjecture->writeDOTfile(DATA_PATH + "tmp/");
	//char c;	cin >> c;
	remove(OUTPUT_GV);
	rename(fn.c_str(), OUTPUT_GV);
	return true;
}

static bool showAndStop(const unique_ptr<DFSM>& conjecture) {
	showConjecture(conjecture);
	unique_ptr<Teacher> teacher = make_unique<TeacherRL>(fsm);
	auto ce = teacher->equivalenceQuery(conjecture);
	return !ce.empty();
}

static void printCSV(const unique_ptr<Teacher>& teacher, const unique_ptr<DFSM>& model, 
		double sec, const string& description, shared_ptr<BlackBox> bb = nullptr) {
	fprintf(outFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%f\t%d\t%d\t%f\t%s\n", FSMmodel::areIsomorphic(fsm, model), fsm->getType(),
		fsm->getNumberOfStates(), fsm->getNumberOfInputs(), fsm->getNumberOfOutputs(), teacher->getAppliedResetCount(),
		teacher->getOutputQueryCount(), teacher->getEquivalenceQueryCount(), teacher->getQueriedSymbolsCount(), 
		teacher->getExplorationSize(), double(teacher->getExplorationSize()) / teacher->getQueriedSymbolsCount(),
		(bb ? bb->getAppliedResetCount() : 0), (bb ? bb->getQueriedSymbolsCount() : 0), sec, description.c_str());
	fflush(outFile);
	printf(".");
}

static vector<string> descriptions;
static vector<function<unique_ptr<DFSM>(const unique_ptr<Teacher>&)>> algorithms;

static void loadAlgorithms(state_t minExtraStates, state_t maxExtraStates, seq_len_t maxDistLen, bool isEQallowed, 
		unsigned int mask, unsigned int startId) {
	if (mask & 1) { // L*
		vector<pair<function<void(const sequence_in_t& ce, ObservationTable& ot, const unique_ptr<Teacher>& teacher)>, string>>	ceFunc;
		ceFunc.emplace_back(PTRandSTR(addAllPrefixesToS));
		ceFunc.emplace_back(PTRandSTR(addAllSuffixesAfterLastStateToE));
		ceFunc.emplace_back(PTRandSTR(addSuffix1by1ToE));
		ceFunc.emplace_back(PTRandSTR(addSuffixAfterLastStateToE));
		ceFunc.emplace_back(PTRandSTR(addSuffixToE_binarySearch));
		for (size_t i = 0; i < ceFunc.size(); i++) {
			descriptions.emplace_back("L*\t" + ceFunc[i].second + "\t" + to_string(descriptions.size() + startId) + "\t");
			algorithms.emplace_back(bind(Lstar, placeholders::_1, ceFunc[i].first, nullptr, (i == 2), (i > 2)));
		}
	}
	if (mask & 2) { // OP
		vector<pair<OP_CEprocessing, string>> opCeFunc;
		opCeFunc.emplace_back(PTRandSTR(AllGlobally));
		opCeFunc.emplace_back(PTRandSTR(OneGlobally));
		opCeFunc.emplace_back(PTRandSTR(OneLocally));
		for (size_t i = 0; i < opCeFunc.size(); i++) {
			descriptions.emplace_back("OP\t" + opCeFunc[i].second + "\t" + to_string(descriptions.size() + startId) + "\t");
			algorithms.emplace_back(bind(ObservationPackAlgorithm, placeholders::_1, opCeFunc[i].first, nullptr));
		}
	}
	if (mask & 4) { // DT
		descriptions.emplace_back("DT\t\t" + to_string(descriptions.size() + startId) + "\t");
		algorithms.emplace_back(bind(DiscriminationTreeAlgorithm, placeholders::_1, nullptr));
	}
	if (mask & 8) { // TTT
		descriptions.emplace_back("TTT\t\t" + to_string(descriptions.size() + startId) + "\t");
		algorithms.emplace_back(bind(TTT, placeholders::_1, nullptr));
	}
	if (mask & 16) { // Quotient
		descriptions.emplace_back("Quotient\t\t" + to_string(descriptions.size() + startId) + "\t");
		algorithms.emplace_back(bind(QuotientAlgorithm, placeholders::_1, nullptr));
	}
	if (mask & 32) { // GoodSplit
		descriptions.emplace_back("GoodSplit\tmaxDistLen:" + to_string(maxDistLen) + 
			(isEQallowed ? "+EQ" : "") + "\t" + to_string(descriptions.size() + startId) + "\t");
		algorithms.emplace_back(bind(GoodSplit, placeholders::_1, maxDistLen, nullptr, isEQallowed));
	}
	if (mask & 64) { // Hlearner
		for (state_t i = minExtraStates; i <= maxExtraStates; i++) {
			descriptions.emplace_back("Hlearner\tExtraStates:" + to_string(i) + 
				(isEQallowed ? "+EQ" : "") + "\t" + to_string(descriptions.size() + startId) + "\t");
			algorithms.emplace_back(bind(Hlearner, placeholders::_1, i, nullptr, isEQallowed));
		}
	}
	if (mask & 128) { // SPYlearner
		for (state_t i = minExtraStates; i <= maxExtraStates; i++) {
			descriptions.emplace_back("SPYlearner\tExtraStates:" + to_string(i) +
				(isEQallowed ? "+EQ" : "") + "\t" + to_string(descriptions.size() + startId) + "\t");
			algorithms.emplace_back(bind(SPYlearner, placeholders::_1, i, nullptr, isEQallowed));
		}
	}
	if (mask & 256) { // Slearner
		for (state_t i = minExtraStates; i <= maxExtraStates; i++) {
			descriptions.emplace_back("Slearner\tExtraStates:" + to_string(i) +
				(isEQallowed ? "+EQ" : "") + "\t" + to_string(descriptions.size() + startId) + "\t");
			algorithms.emplace_back(bind(Slearner, placeholders::_1, i, nullptr, isEQallowed));
		}
	}
}

static void compareLearningAlgorithms(const string fnName, state_t maxExtraStates, seq_len_t maxDistLen, bool isEQallowed, unsigned int mask) {
	if (mask & 1) { // TeacherDFSM
		for (size_t i = 0; i < algorithms.size(); i++) {
			unique_ptr<Teacher> teacher = make_unique<TeacherDFSM>(fsm, true, true);
			COMPUTATION_TIME(auto model = algorithms[i](teacher));
			printCSV(teacher, model, elapsed_seconds.count(), descriptions[i] + "TeacherDFSM\t\t" + fnName);
		}
	}
	printf(" ");
	if (mask & 2) { // TeacherRL
		for (size_t i = 0; i < algorithms.size(); i++) {
			unique_ptr<Teacher> teacher = make_unique<TeacherRL>(fsm, true);
			COMPUTATION_TIME(auto model = algorithms[i](teacher));
			printCSV(teacher, model, elapsed_seconds.count(), descriptions[i] + "TeacherRL\t\t" + fnName);
		}
	}
	printf(" ");
	if (mask & 4) { // TeacherBB
		for (size_t i = 0; i < algorithms.size(); i++) {
			shared_ptr<BlackBox> bb = make_shared<BlackBoxDFSM>(fsm, true);
			unique_ptr<Teacher> teacher = make_unique<TeacherBB>(bb, FSMtesting::S_method, maxExtraStates + 1);
			COMPUTATION_TIME(auto model = algorithms[i](teacher));
			printCSV(teacher, model, elapsed_seconds.count(), descriptions[i] +
				"TeacherBB:SPY_method(ExtraStates:" + to_string(maxExtraStates + 1) + ")\tBlackBoxDFSM\t" + fnName, bb);
		}
	}
}

void testDirLearning(int argc, char** argv) {
	string outFilename = "";
	auto dir = string(argv[2]);
	state_t maxExtraStates = 2, minExtraStates = 0;
	seq_len_t maxDistLen = 2;
	bool isEQallowed = true;
	unsigned int machineTypeMask = (unsigned int)(-1);// all
	state_t statesRestrictionLess = NULL_STATE, statesRestrictionGreater = NULL_STATE;
	input_t inputsRestrictionLess = STOUT_INPUT, inputsRestrictionGreater = STOUT_INPUT;
	unsigned int algorithmMask = (unsigned int)(-1);//all
	unsigned int teacherMask = 1;//TEACHER_DFSM
	unsigned int algStartIdx = 0;
	string startFN = "", endFN = "", theFN = "";
	for (int i = 3; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			outFilename = string(argv[++i]);
		}
		else if (strcmp(argv[i], "-es") == 0) {
			maxExtraStates = state_t(atoi(argv[++i]));
		}
		else if (strcmp(argv[i], "-mines") == 0) {
			minExtraStates = state_t(atoi(argv[++i]));
		}
		else if (strcmp(argv[i], "-dl") == 0) {
			maxDistLen = seq_len_t(atoi(argv[++i]));
		}
		else if (strcmp(argv[i], "-eq") == 0) {
			isEQallowed = bool(atoi(argv[++i]) != 0);
		}
		else if (strcmp(argv[i], "-m") == 0) {//machine type
			machineTypeMask = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-s") == 0) {//states
			statesRestrictionLess = state_t(atoi(argv[++i]));
			statesRestrictionGreater = statesRestrictionLess - 1;
			statesRestrictionLess++;
		}
		else if (strcmp(argv[i],"-sl") == 0) {//states
			statesRestrictionLess = state_t(atoi(argv[++i]));
		}
		else if (strcmp(argv[i], "-sg") == 0) {//states
			statesRestrictionGreater = state_t(atoi(argv[++i]));
		}
		else if (strcmp(argv[i], "-i") == 0) {//inputs
			inputsRestrictionLess = input_t(atoi(argv[++i]));
			inputsRestrictionGreater = inputsRestrictionLess - 1;
			inputsRestrictionLess++;
		}
		else if (strcmp(argv[i], "-il") == 0) {//inputs
			inputsRestrictionLess = input_t(atoi(argv[++i]));
		}
		else if (strcmp(argv[i], "-ig") == 0) {//inputs
			inputsRestrictionGreater = input_t(atoi(argv[++i]));
		}
		else if (strcmp(argv[i], "-a") == 0) {//algorithm
			algorithmMask = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-ai") == 0) {//algorithm start index
			algStartIdx = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-t") == 0) {//teacher
			teacherMask = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-f") == 0) {// filename to process
			theFN = string(argv[++i]);
		}
		else if (strcmp(argv[i], "-fstart") == 0) {// filename to start
			startFN = string(argv[++i]);
		}
		else if (strcmp(argv[i], "-fend") == 0) {// filename to end
			endFN = string(argv[++i]);
		}
	}
	if (outFilename.empty()) outFilename = dir + "_resultsLearning.csv";
#ifdef _WIN32
	if (fopen_s(&outFile, outFilename.c_str(), "w") != 0) {
#else
	  outFile = fopen(outFilename.c_str(), "w");
	  if (!outFile) {
#endif
		cerr << "Unable to open file " << outFilename << " for results!" << endl;
		return;
	}
	fprintf(outFile, "Correct\tFSMtype\tStates\tInputs\tOutputs\tResets\tOQs\tEQs\tsymbols\tExploration\tEE\t"
		"BBresets\tBBsymbols\tseconds\tAlgorithm\tCEprocessing\tAlgId\tTeacher\tBB\tfileName\n");
	loadAlgorithms(minExtraStates, maxExtraStates, maxDistLen, isEQallowed, algorithmMask, algStartIdx);
	if (theFN == "") {
		path dirPath(dir);
		directory_iterator endDir;
		for (directory_iterator it(dirPath); it != endDir; ++it) {
			if (is_regular_file(it->status())) {
				path fn(it->path());
				if (fn.extension().compare(".fsm") == 0) {
					if ((startFN != "") && (fn.filename() == startFN)) startFN = "";
					if ((endFN != "") && (fn.filename() == endFN)) break;
					if (startFN == "") {
						fsm = FSMmodel::loadFSM(fn.string());
						if ((fsm) && (machineTypeMask & (1 << fsm->getType())) &&
							((statesRestrictionLess == NULL_STATE) || (fsm->getNumberOfStates() < statesRestrictionLess)) &&
							((statesRestrictionGreater == NULL_STATE) || (statesRestrictionGreater < fsm->getNumberOfStates())) &&
							((inputsRestrictionLess == STOUT_INPUT) || (fsm->getNumberOfInputs() < inputsRestrictionLess)) &&
							((inputsRestrictionGreater == STOUT_INPUT) || (inputsRestrictionGreater < fsm->getNumberOfInputs()))) {
							compareLearningAlgorithms(fn.filename(), maxExtraStates, maxDistLen, isEQallowed, teacherMask);
							printf("%s tested\n", fn.filename().c_str());
						}
					}
				}
			}
		}
	}
	else {
		fsm = FSMmodel::loadFSM(dir + theFN);
		if ((fsm) && (machineTypeMask & (1 << fsm->getType())) &&
			((statesRestrictionLess == NULL_STATE) || (fsm->getNumberOfStates() < statesRestrictionLess)) &&
			((statesRestrictionGreater == NULL_STATE) || (statesRestrictionGreater < fsm->getNumberOfStates())) &&
			((inputsRestrictionLess == STOUT_INPUT) || (fsm->getNumberOfInputs() < inputsRestrictionLess)) &&
			((inputsRestrictionGreater == STOUT_INPUT) || (inputsRestrictionGreater < fsm->getNumberOfInputs()))) {
			compareLearningAlgorithms(theFN, maxExtraStates, maxDistLen, isEQallowed, teacherMask);
			printf("%s tested\n", theFN.c_str());
		}
	}
	fclose(outFile);
	printf("complete.\n");
}

