set(PROJECT_NAME FSMdevel)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "commons.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "experimenterLearning.cpp"
    "experimenterTesting.cpp"
    "FSMgenerator.cpp"
    "HSIdesignComparison.cpp"
    "MachinesAnalysis.cpp"
    "main.cpp"
    "oldFunctions.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

# use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE FSMdevel)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION "TRUE"
)
################################################################################
# Compile definitions
################################################################################
# if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Mixed Platforms")
#     target_compile_definitions(${PROJECT_NAME} PRIVATE
#         "$<$<CONFIG:Debug>:"
#             "_DEBUG"
#         ">"
#         "$<$<CONFIG:Release>:"
#             "NDEBUG"
#         ">"
#         "WIN32;"
#         "_CONSOLE;"
#         "_LIB;"
#         "UNICODE;"
#         "_UNICODE"
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
#     target_compile_definitions(${PROJECT_NAME} PRIVATE
#         "$<$<CONFIG:Debug>:"
#             "_DEBUG"
#         ">"
#         "$<$<CONFIG:Release>:"
#             "NDEBUG"
#         ">"
#         "WIN32;"
#         "_CONSOLE;"
#         "_LIB;"
#         "UNICODE;"
#         "_UNICODE"
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#     target_compile_definitions(${PROJECT_NAME} PRIVATE
#         "$<$<CONFIG:Debug>:"
#             "_DEBUG"
#         ">"
#         "$<$<CONFIG:Release>:"
#             "NDEBUG"
#         ">"
#         "WIN32;"
#         "_CONSOLE;"
#         "_LIB;"
#         "UNICODE;"
#         "_UNICODE"
#     )
# endif()

################################################################################
# Compile and link options
################################################################################
# if(MSVC)
#     if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Mixed Platforms")
#         target_compile_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /Od
#             >
#             $<$<CONFIG:Release>:
#                 /O2;
#                 /Oi;
#                 /Gy
#             >
#             /sdl;
#             /W3;
#             ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
#             ${DEFAULT_CXX_EXCEPTION_HANDLING};
#             /Y-
#         )
#     elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
#         target_compile_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /Od
#             >
#             $<$<CONFIG:Release>:
#                 /O2;
#                 /Oi;
#                 /Gy
#             >
#             /sdl;
#             /W3;
#             ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
#             ${DEFAULT_CXX_EXCEPTION_HANDLING};
#             /Y-
#         )
#     elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#         target_compile_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /Od;
#                 /RTC1
#             >
#             $<$<CONFIG:Release>:
#                 /O2;
#                 /Oi;
#                 /Gy
#             >
#             /sdl;
#             /W3;
#             ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
#             ${DEFAULT_CXX_EXCEPTION_HANDLING};
#             /Y-
#         )
#     endif()
#     if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Mixed Platforms")
#         target_link_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /INCREMENTAL
#             >
#             $<$<CONFIG:Release>:
#                 /OPT:REF;
#                 /OPT:ICF;
#                 /INCREMENTAL:NO
#             >
#             /DEBUG;
#             /SUBSYSTEM:CONSOLE
#         )
#     elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
#         target_link_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /INCREMENTAL
#             >
#             $<$<CONFIG:Release>:
#                 /OPT:REF;
#                 /OPT:ICF;
#                 /INCREMENTAL:NO
#             >
#             /DEBUG;
#             /SUBSYSTEM:CONSOLE
#         )
#     elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#         target_link_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /INCREMENTAL
#             >
#             $<$<CONFIG:Release>:
#                 /OPT:REF;
#                 /OPT:ICF;
#                 /INCREMENTAL:NO
#             >
#             /DEBUG;
#             /SUBSYSTEM:CONSOLE
#         )
#     endif()
# endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE FSMlib)
