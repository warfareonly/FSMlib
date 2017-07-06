/* Copyright (c) Michal Soucha, 2017
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
#include "stdafx.h"
#include "../TestUtils.h"

using namespace FSMlearning;

//#define OUTPUT_GV string(string(DATA_PATH) + "tmp/output.gv").c_str()

extern bool showConjecture(const unique_ptr<DFSM>& conjecture);

namespace FSMlibTest
{
	TEST_CLASS(SlearnerTests)
	{
	public:
		unique_ptr<DFSM> fsm;

		// TODO: incomplete machines

		TEST_METHOD(TestSlearner_DFSM)
		{
			fsm = make_unique<DFSM>();
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFSM_R4_ADS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFSM_R4_SCSet.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFSM_R5_PDS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFSM_R5_SVS.fsm");
		}

		TEST_METHOD(TestSlearner_Mealy)
		{
			fsm = make_unique<Mealy>();
			/*
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R100.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R100_1.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R100_PDS_l99.fsm", 97);
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R10_PDS.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R4_HS.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R4_PDS.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R4_SS.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Mealy_R6_ADS.fsm");
			/*/
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Mealy_R4_ADS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Mealy_R4_HS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Mealy_R4_PDS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Mealy_R4_SCSet.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Mealy_R4_SS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Mealy_R4_SVS.fsm");
			//*/
		}

		TEST_METHOD(TestSlearner_Moore)
		{
			fsm = make_unique<Moore>();
			/*
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R100.fsm");
			//testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R100_PDS.fsm", 15);// too hard
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R100_PDS_l99.fsm", 1);//97
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R10_PDS.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R10_PDS_E.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R4_HS.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R4_PDS.fsm");
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R4_SS.fsm", 1);//2
			testSlearner(DATA_PATH + SEQUENCES_DIR + "Moore_R6_ADS.fsm");
			/*/
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Moore_R4_ADS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Moore_R4_HS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Moore_R4_PDS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Moore_R4_SCSet.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Moore_R4_SS.fsm", 2);
			testSlearner(DATA_PATH + EXAMPLES_DIR + "Moore_R5_SVS.fsm");
			//*/
		}

		TEST_METHOD(TestSlearner_DFA)
		{
			fsm = make_unique<DFA>();
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFA_R4_ADS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFA_R4_HS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFA_R4_PDS.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFA_R4_SCSet.fsm");
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFA_R4_SS.fsm");//2
			testSlearner(DATA_PATH + EXAMPLES_DIR + "DFA_R5_SVS.fsm");
		}

		void runTestSlearner(const unique_ptr<Teacher>& teacher, string teacherName, string filename, state_t maxExtraStates) {
			auto model = Slearner(teacher, maxExtraStates, showConjecture, true);
			DEBUG_MSG("Reset: %d,\tOQ: %d,\tsymbols: %d,\tEQ: %d,\tExtraStates: %d,\t%s\t%s%s\n", teacher->getAppliedResetCount(),
				teacher->getOutputQueryCount(), teacher->getQueriedSymbolsCount(), teacher->getEquivalenceQueryCount(), maxExtraStates,
				teacherName.c_str(), filename.c_str(), (FSMmodel::areIsomorphic(fsm, model) ? "" : "\tNOT LEARNED"));
			ARE_EQUAL(true, FSMmodel::areIsomorphic(fsm, model), "Learned model is different to the specification.");
		}

		void testSlearner(string filename, state_t maxExtraStates = 1) {
			fsm->load(filename);

			for (state_t es = 0; es <= maxExtraStates; es++) {
				unique_ptr<Teacher> teacher = make_unique<TeacherDFSM>(fsm, true);
				runTestSlearner(teacher, "TeacherDFSM", filename, es);
			}

			for (state_t es = 0; es <= maxExtraStates; es++) {
				unique_ptr<Teacher> teacher = make_unique<TeacherRL>(fsm);
				runTestSlearner(teacher, "TeacherRL", filename, es);
			}

			for (state_t es = 0; es <= maxExtraStates; es++) {
				shared_ptr<BlackBox> bb = make_shared<BlackBoxDFSM>(fsm, true);
				unique_ptr<Teacher> teacher = make_unique<TeacherBB>(bb, bind(FSMtesting::HSI_method, placeholders::_1, placeholders::_2,
					bind(FSMsequence::getHarmonizedStateIdentifiersFromSplittingTree, placeholders::_1,
					bind(FSMsequence::getSplittingTree, placeholders::_1, true, false), false)), 3);
				runTestSlearner(teacher, "BlackBoxDFSM, TeacherBB:HSI_method (3 extra states)", filename, es);
			}
		}
	};
}
