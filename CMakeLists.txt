cmake_minimum_required(VERSION 3.24)
project(regex_lab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++-14)

execute_process(COMMAND uname -s
        TIMEOUT 1
        OUTPUT_VARIABLE OS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(COMMAND uname -m
        TIMEOUT 1
        OUTPUT_VARIABLE MACHINE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(model)
include_directories(homework)

add_executable(regex_lab_test
        tests/test.cpp
        homework/lib_char.h
        model/parse_tree.h
        model/NFA.h
        model/DFA.h
        model/consts.h
        model/COE.h
        homework/DFA-accept/accept.h
        homework/expression-parser/to_polish.h
        homework/expression-parser/parser.h
        homework/ParseTree-to-eNFA/converter.h
        homework/subset-construction/subset_construction.h
        homework/DFA-minimization/minimization.h
)

target_link_libraries(regex_lab_test
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/DFA-minimization.a
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/expression-parser.a
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/ParseTree-to-eNFA.a
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/subset-construction.a
)

add_executable(regex_lab_std_test
        tests/std_test_all.cpp
        homework/lib_char.h
        model/parse_tree.h
        model/NFA.h
        model/DFA.h
        model/consts.h
        model/COE.h
        homework/DFA-accept/accept.h
        homework/expression-parser/to_polish.h
        homework/expression-parser/parser.h
        homework/ParseTree-to-eNFA/converter.h
        homework/subset-construction/subset_construction.h
        homework/DFA-minimization/minimization.h
)

target_link_libraries(regex_lab_std_test
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/DFA-minimization.a
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/expression-parser.a
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/ParseTree-to-eNFA.a
        ${CMAKE_SOURCE_DIR}/lib_char/${OS}-${MACHINE}/subset-construction.a
)

add_executable(CYK_algorithm
        tests/CYK_test.cpp
        model/parse_tree.h
        model/CFG.h
        homework/CYK-algorithm/CYK.h
)

# cmake -G "Unix Makefiles" -S . -B build && cd build && make all