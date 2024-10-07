cmake_minimum_required(VERSION 3.26)
project(regex_lab)

set(CMAKE_CXX_STANDARD 17)

include_directories(model)
include_directories(homework)

add_executable(regex_lab_test_all
        tests/all.cpp
        model/parse_tree.h
        model/NFA.h
        model/DFA.h
        model/consts.h
        model/COE.h
        homework/DFA-accept/accept.h
        homework/expression-parser/parser.h
        homework/ParseTree-to-eNFA/converter.h
        homework/subset-construction/subset_construction.h
        homework/DFA-minimization/minimization.h
        homework/expression-parser/to_polish.h
        homework/ParseTree-to-eNFA/merge_NFA.h
        homework/DFA-to-expression/converter.h)

add_executable(regex_lab_solution_all
        tests/all.cpp
        model/parse_tree.h
        model/NFA.h
        model/DFA.h
        model/consts.h
        model/COE.h
        homework/DFA-accept/accept.h
)

target_link_libraries(regex_lab_solution_all
        ${CMAKE_SOURCE_DIR}/lib_char/Darwin-arm64/DFA-minimization.a
        ${CMAKE_SOURCE_DIR}/lib_char/Darwin-arm64/DFA-to-expression.a
        ${CMAKE_SOURCE_DIR}/lib_char/Darwin-arm64/expression-parser.a
        ${CMAKE_SOURCE_DIR}/lib_char/Darwin-arm64/ParseTree-to-eNFA.a
        ${CMAKE_SOURCE_DIR}/lib_char/Darwin-arm64/subset-construction.a
)