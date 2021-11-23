set(PROJECT_NAME FSMlib)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../FSMvis.html"
    "ReadMe.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "FSMlib.h"
    "PrefixSet.h"
    "stdafx.h"
    "targetver.h"
    "UnionFind.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Learning
    "Learning/BlackBox.h"
    "Learning/BlackBoxDFSM.h"
    "Learning/FSMlearning.h"
    "Learning/Teacher.h"
    "Learning/TeacherBB.h"
    "Learning/TeacherDFSM.h"
    "Learning/TeacherRL.h"
)
source_group("Header Files\\Learning" FILES ${Header_Files__Learning})

set(Header_Files__Model
    "Model/DFA.h"
    "Model/DFSM.h"
    "Model/FSM.h"
    "Model/FSMmodel.h"
    "Model/FSMtypes.h"
    "Model/Mealy.h"
    "Model/Moore.h"
)
source_group("Header Files\\Model" FILES ${Header_Files__Model})

set(Header_Files__Sequences
    "Sequences/FSMsequence.h"
)
source_group("Header Files\\Sequences" FILES ${Header_Files__Sequences})

set(Header_Files__Testing
    "Testing/FaultCoverageChecker.h"
    "Testing/FSMtesting.h"
)
source_group("Header Files\\Testing" FILES ${Header_Files__Testing})

set(Source_Files
    "dllmain.cpp"
    "FSMlib.cpp"
    "PrefixSet.cpp"
    "stdafx.cpp"
    "UnionFind.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Learning
    "Learning/BlackBoxDFSM.cpp"
    "Learning/DiscriminationTreeAlgorithm.cpp"
    "Learning/GoodSplit.cpp"
    "Learning/H-learner.cpp"
    "Learning/Lstar.cpp"
    "Learning/ObservationPackAlgorithm.cpp"
    "Learning/QuotientAlgorithm.cpp"
    "Learning/S-learner.cpp"
    "Learning/SPY-learner.cpp"
    "Learning/TeacherBB.cpp"
    "Learning/TeacherDFSM.cpp"
    "Learning/TeacherRL.cpp"
    "Learning/TTT.cpp"
)
source_group("Source Files\\Learning" FILES ${Source_Files__Learning})

set(Source_Files__Model
    "Model/DFA.cpp"
    "Model/DFSM.cpp"
    "Model/FSMmodel.cpp"
    "Model/Mealy.cpp"
    "Model/Moore.cpp"
)
source_group("Source Files\\Model" FILES ${Source_Files__Model})

set(Source_Files__Sequences
    "Sequences/AdaptiveDistinguishingSequence.cpp"
    "Sequences/CharacterizingSequences.cpp"
    "Sequences/FSMcovers.cpp"
    "Sequences/HomingSequence.cpp"
    "Sequences/PresetDistinguishingSequence.cpp"
    "Sequences/SplittingTree.cpp"
    "Sequences/StateVerifyingSequence.cpp"
    "Sequences/SynchronizingSequence.cpp"
)
source_group("Source Files\\Sequences" FILES ${Source_Files__Sequences})

set(Source_Files__Testing
    "Testing/ADS-method.cpp"
    "Testing/C-method.cpp"
    "Testing/FaultCoverageChecker.cpp"
    "Testing/H-method.cpp"
    "Testing/HSI-method.cpp"
    "Testing/Ma-method.cpp"
    "Testing/Mg-method.cpp"
    "Testing/PDS-method.cpp"
    "Testing/S-method.cpp"
    "Testing/SPY-method.cpp"
    "Testing/SPYH-method.cpp"
    "Testing/SVS-method.cpp"
    "Testing/W-method.cpp"
    "Testing/Wp-method.cpp"
)
source_group("Source Files\\Testing" FILES ${Source_Files__Testing})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Header_Files__Learning}
    ${Header_Files__Model}
    ${Header_Files__Sequences}
    ${Header_Files__Testing}
    ${Source_Files}
    ${Source_Files__Learning}
    ${Source_Files__Model}
    ${Source_Files__Sequences}
    ${Source_Files__Testing}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

# use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE FSMlib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Mixed Platforms")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Mixed Platforms")
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    endif()
    source_file_compile_options(dllmain.cpp ${FILE_CL_OPTIONS})
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Mixed Platforms")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

