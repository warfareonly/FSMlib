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
#pragma once

#include "../Sequences/FSMsequence.h"

namespace FSMtesting {
	//<-- Resettable machines -->// 

	/**
	* Designs a test suite in which all transitions are confirmed
	* using appended Preset Distinguishing Sequence.
	* 
	* Source:
	* MastersThesis (soucha2015checking) 
	* Soucha, M. 
	* Checking Experiment Design Methods 
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	* @return true if a test suite is designed, false if there is no PDS or negative extraStates
	*/
	FSMLIB_API bool PDS_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);

	/**
	* Designs a test suite in which all transitions are confirmed
	* using appended Adaptive Distinguishing Sequence.
	*
	* Source:
	* MastersThesis (soucha2015checking) 
	* Soucha, M. 
	* Checking Experiment Design Methods 
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	* @return true if a test suite is designed, false if there is no ADS or negative extraStates
	*/
	FSMLIB_API bool ADS_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);
	
	/**
	* Designs a test suite in which all states are confirmed
	* using Verifying Set of State Verifying Sequences of each state
	* and all last transitions are confirmed
	* using appended State Verifying Sequence of the end state, or
	* using its State Characterizing Set if the state has no SVS.
	* SCSet is also in place of SVS in VSet if such SVS does not exist.
	*
	* Source:
	* MastersThesis (soucha2015checking) 
	* Soucha, M. 
	* Checking Experiment Design Methods 
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	* @return the number of states without SVS, or NULL_STATE if extraStates is negative
	*/
	FSMLIB_API state_t SVS_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);
	
	/**
	* Designs a test suite in which all states and transitions are confirmed
	* using appended Characterizing Set.
	*
	* Sources:
	* Article (vasilevskii1973failure) 
	* Vasilevskii, M. 
	* Failure diagnosis of automata 
	* Cybernetics and Systems Analysis, Springer, 1973, 9, 653-665 
	*
	* Article (chow1978testing)
	* Chow, T. S. 
	* Testing software design modeled by finite-state machines 
	* Software Engineering, IEEE Transactions on, IEEE, 1978, 178-187
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences, 
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API void W_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);
	
	/**
	* Designs a test suite in which all transitions are confirmed
	* using appended State Characterizing Set of the end state
	* and all states are confirmed using Characterizing Set
	* that consists of all used SCSets.
	*
	* Source:
	* Article (fujiwara1991test)
	* Fujiwara, S.; Khendek, F.; Amalou, M.; Ghedamsi, A. & others
	* Test selection based on finite state models 
	* Software Engineering, IEEE Transactions on, IEEE, 1991, 17, 591-603
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API void Wp_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);
	
	/**
	* Designs a test suite in which all states and transitions are confirmed
	* using appended Harmonized State Identifier of the related state.
	*
	* Source:
	* InProceedings (petrenko1991checking) 
	* Petrenko, A. 
	* Checking experiments with protocol machines 
	* Proceedings of the IFIP TC6/WG6. 1 Fourth International Workshop on Protocol Test Systems IV, 1991, 83-94
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API void HSI_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);

	/**
	* Designs a test suite in which all state pairs are distinguished and thus confirmed
	* using a separating sequence that is chosen adaptively to minimize the length of TS.
	* Transitions are confirmed in the same manner, i.e. end states are distinguished from all states.
	*
	* Source:
	* InCollection (dorofeeva2005improved)
	* Dorofeeva, R.; El-Fakih, K. & Yevtushenko, N. 
	* An improved conformance testing method 
	* Formal Techniques for Networked and Distributed Systems-FORTE 2005, Springer, 2005, 204-218
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API void H_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);

	/**
	* Designs a test suite in which all states and transitions are confirmed
	* using Harmonized State Identifiers that are appended to already confirmed states
	*
	* Source:
	* Article (simao2012reducing)
	* Simao, A.; Petrenko, A. & Yevtushenko, N.
	* On reducing test length for fsms with extra states 
	* Software Testing, Verification and Reliability, Wiley Online Library, 2012, 22, 435-454
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API void SPY_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);

	/// TODO
	/**
	*
	* Source:
	* InProceedings (petrenko1992test) 
	* Petrenko, A. & Yevtushenko, N. 
	* Test suite generation from a fsm with a given type of implementation errors 
	* Proceedings of the IFIP TC6/WG6. 1 Twelth International Symposium on Protocol Specification, Testing and Verification XII, 1992, 229-243
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	//FSMLIB_API void FF_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);
	
	/**
	*
	* Source:
	* Article (petrenko2005testing) 
	* Petrenko, A. & Yevtushenko, N. 
	* Testing from partial deterministic FSM specifications 
	* Computers, IEEE Transactions on, IEEE, 2005, 54, 1154-1165
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	//FSMLIB_API void SC_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);
	
	/**
	*
	* Source:
	* Article (simao2009fault) 
	* Sim�o, A. & Petrenko, A. 
	* Fault coverage-driven incremental test generation 
	* The Computer Journal, Br Computer Soc, 2009, bxp073 
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many states shall be considered relatively to the number of states,
	*/
	//FSMLIB_API void P_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);

	/// Attempts
	//FSMLIB_API void GSPY_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);// is it correct?
	//FSMLIB_API void SPYH_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);// is it correct?
	
	/**
	* Designs a checking sequence by appending an adaptive distinguishing sequence
	* such that each transition and state is verified by ADS in resulting CS.
	* In the process of design, if an unverified transition is too far from the current state,
	* reset is applied and thus a test suite of several sequences can be produced.
	*
	* Source:
	* MastersThesis (soucha2015checking)
	* Soucha, M.
	* Checking Experiment Design Methods
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API bool Mra_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);
	
	/**
	*
	* Source:
	* MastersThesis (soucha2015checking)
	* Soucha, M.
	* Checking Experiment Design Methods
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API bool Mrstar_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0, std::string fileName = "");
	
	/**
	*
	* Source:
	* MastersThesis (soucha2015checking)
	* Soucha, M.
	* Checking Experiment Design Methods
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param TS - Test Suite to fill up with test sequences,
	*		 TS will be empty if extraStates is negative
	* @param extraStates - how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0
	*/
	FSMLIB_API bool Mrg_method(DFSM* fsm, sequence_set_t & TS, int extraStates = 0);

	//<-- Checking sequence methods -->//

	/// TODO
	/**
	*
	* Source:
	* Article (hsieh1971checking) 
	* Hsieh, E. 
	* Checking Experiments for Sequential Machines 
	* Computers, IEEE Transactions on, IEEE, 1971, 100, 1152-1166
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a ADS
	* @param extraStates - NOT SUPPORTED YET(how many extra states shall be considered,
	*		default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e.there is an ADS, otherwise false
	*/
	//FSMLIB_API bool HrADS_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	*
	* Essential source:
	* InProceedings (hennie1964fault) 
	* Hennie, F. 
	* Fault detecting experiments for sequential circuits 
	* Switching Circuit Theory and Logical Design, 1964 Proceedings of the Fifth Annual Symposium on, 1964, 95-110
	*
	* Further sources: gonenc1970method, ural1997minimizing, hierons2006optimizing,... (see soucha2015checking)
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a PDS
	* @param extraStates - NOT SUPPORTED YET(how many extra states shall be considered,
	*		default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e.there is an PDS, otherwise false
	*/
	//FSMLIB_API bool D_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	*
	* Similar to the D-method but it uses ADS instead of PDS.
	*
	* Sources:
	* Article (boute1974distinguishing) 
	* Boute, R. 
	* Distinguishing sets for optimal state identification in checking experiments 
	* Computers, IEEE Transactions on, IEEE, 1974, 100, 874-877 
	*
	* InProceedings (hierons2009checking) 
	* Hierons, R. M.; Jourdan, G.-V.; Ural, H. & Yenigun, H. 
	* Checking sequence construction using adaptive and preset distinguishing sequences 
	* Software Engineering and Formal Methods, 2009 Seventh IEEE International Conference on, 2009, 157-166
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a ADS
	* @param extraStates - NOT SUPPORTED YET(how many extra states shall be considered,
	*		default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e.there is an ADS, otherwise false
	*/
	//FSMLIB_API bool AD_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	*
	* Source:
	* InProceedings (hennie1964fault) 
	* Hennie, F. 
	* Fault detecting experiments for sequential circuits 
	* Switching Circuit Theory and Logical Design, 1964 Proceedings of the Fifth Annual Symposium on, 1964, 95-110
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence
	* @param extraStates - NOT SUPPORTED YET(how many extra states shall be considered,
	*		default is no extra state, needs to be positive or 0)
	*/
	//FSMLIB_API void DW_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	*
	* Source:
	* InCollection (porto2013generation) 
	* Porto, F. R.; Endo, A. T. & Simao, A. 
	* Generation of Checking Sequences Using Identification Sets 
	* Formal Methods and Software Engineering, Springer, 2013, 115-130
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence
	* @param extraStates - NOT SUPPORTED YET(how many extra states shall be considered,
	*		default is no extra state, needs to be positive or 0)
	*/
	//FSMLIB_API void DWp_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	*
	* Sources:
	* Article (sabnani1985new) 
	* Sabnani, K. & Dahbura, A. 
	* A new technique for generating protocol test 
	* ACM SIGCOMM Computer Communication Review, ACM, 1985, 15, 36-43
	*
	* Article (chan1989improved) 
	* Chan, W. Y.; Vuong, C. & Otp, M. 
	* An improved protocol test generation procedure based on UIOs 
	* ACM SIGCOMM Computer Communication Review, ACM, 1989, 19, 283-294
	*
	* and many others... see soucha2015checking
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence
	* @param extraStates - NOT SUPPORTED YET(how many extra states shall be considered,
	*		default is no extra state, needs to be positive or 0)
	* @return 
	*/
	//FSMLIB_API int UIO_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	*
	* Source:
	* InProceedings (vuong1990novel) 
	* Vuong, S. T. & Ko, K. C. 
	* A novel approach to protocol test sequence generation 
	* Global Telecommunications Conference, 1990, and Exhibition. 'Communications: Connecting the Future', GLOBECOM'90., IEEE, 1990, 1880-1884 
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence
	* @param extraStates - NOT SUPPORTED YET(how many extra states shall be considered,
	*		default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, otherwise false
	*/
	//FSMLIB_API bool CSP_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);

	/**
	* Designs a checking sequence by appending an adaptive distinguishing sequence
	* to confirmed states so another state/transition is verified.
	*
	* Sources:
	* InCollection (simao2008generating)
	* Sim�o, A. & Petrenko, A.
	* Generating checking sequences for partial reduced finite state machines
	* Testing of Software and Communicating Systems, Springer, 2008, 153-168
	*
	* InProceedings (simao2009checking)
	* Sim�o, A. & Petrenko, A.
	* Checking sequence generation using state distinguishing subsequences
	* Software Testing, Verification and Validation Workshops, 2009. ICSTW'09. International Conference on, 2009, 48-56
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a ADS
	* @param extraStates - NOT SUPPORTED YET (how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e. there is an ADS, otherwise false
	*/
	FSMLIB_API bool C_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	*
	*
	* Sources:
	* Article (kapus2010better) 
	* Kapus-Kolar, M. 
	* A better procedure and a stronger state-recognition pattern for checking sequence construction 
	* Jo�ef Stefan Institute Technical Report, 2010, 10574
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a ADS
	* @param extraStates - NOT SUPPORTED YET (how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e. there is an ADS, otherwise false
	*/
	//FSMLIB_API bool K_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);

	// Attempts
	//FSMLIB_API void MHSI_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);// is it correct?

	/**
	* Designs a checking sequence by appending an adaptive distinguishing sequence
	* such that each transition and state is verified by ADS in resulting CS.
	*
	* Source:
	* MastersThesis (soucha2015checking) 
	* Soucha, M. 
	* Checking Experiment Design Methods 
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a ADS
	* @param extraStates - NOT SUPPORTED YET (how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e. there is an ADS, otherwise false
	*/
	FSMLIB_API bool Ma_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
	
	/**
	* Designs a checking sequence by appending an adaptive distinguishing sequence
	* such that each transition and state is verified by ADS in resulting CS.
	*
	* Source:
	* MastersThesis (soucha2015checking)
	* Soucha, M.
	* Checking Experiment Design Methods
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a ADS
	* @param extraStates - NOT SUPPORTED YET (how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e. there is an ADS, otherwise false
	*/
	FSMLIB_API bool Mstar_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0, std::string fileName = "");
	
	/**
	* Designs a checking sequence by appending an adaptive distinguishing sequence
	* such that each transition and state is verified by ADS in resulting CS.
	*
	* Source:
	* MastersThesis (soucha2015checking)
	* Soucha, M.
	* Checking Experiment Design Methods
	* Czech Technical Univerzity in Prague, 2015
	*
	* @param fsm - Deterministic FSM
	* @param CS - Checking Sequence if given DFSM has a ADS
	* @param extraStates - NOT SUPPORTED YET (how many extra states shall be considered,
	*		 default is no extra state, needs to be positive or 0)
	* @return true if a checking sequence is designed, i.e. there is an ADS, otherwise false
	*/
	FSMLIB_API bool Mg_method(DFSM* fsm, sequence_in_t & CS, int extraStates = 0);
}
