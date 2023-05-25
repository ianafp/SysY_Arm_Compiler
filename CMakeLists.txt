cmake_minimum_required(VERSION 3.13)
project(compiler)

# settings
# set to OFF to enable C mode
set(CPP_MODE ON)
if(CPP_MODE)
  set(FB_EXT ".cpp")
else()
  set(FB_EXT ".c")
endif()
message(STATUS "Flex/Bison generated source file extension: ${FB_EXT}")
add_compile_options(-g)
# enable all warnings
if(MSVC)
  add_compile_options(/W3)
else()
  # disable warnings caused by old version of Flex
  add_compile_options(-Wall -Wno-register)
endif()

# options about libraries and includes
set(LIB_DIR "$ENV{CDE_LIBRARY_PATH}/native" CACHE STRING "directory of libraries")
set(INC_DIR "$ENV{CDE_INCLUDE_PATH}" CACHE STRING "directory of includes")
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty)
set(GLOG_DIR ${THIRD_PARTY_DIR}/glog-master)
set(GLOG_SOURCE_DIR ${THIRD_PARTY_DIR}/glog-master/src)
set(THIRD_PARTY_BINIRY_DIR ${PROJECT_BINARY_DIR}/thirdparty)
set(GLOG_BINIRY_DIR ${THIRD_PARTY_BINIRY_DIR}/glog-master)
message(STATUS "Library directory: ${LIB_DIR}")
message(STATUS "Include directory: ${INC_DIR}")

# find Flex/Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# generate lexer/parser
file(GLOB_RECURSE L_SOURCES "src/parser/*.l")
file(GLOB_RECURSE Y_SOURCES "src/parser/*.y")
if(NOT (L_SOURCES STREQUAL "" AND Y_SOURCES STREQUAL ""))
  string(REGEX REPLACE ".*/(.*)\\.l" "${CMAKE_CURRENT_BINARY_DIR}/\\1.lex${FB_EXT}" L_OUTPUTS "${L_SOURCES}")
  string(REGEX REPLACE ".*/(.*)\\.y" "${CMAKE_CURRENT_BINARY_DIR}/\\1.tab${FB_EXT}" Y_OUTPUTS "${Y_SOURCES}")
  flex_target(Lexer ${L_SOURCES} ${L_OUTPUTS})
  bison_target(Parser ${Y_SOURCES} ${Y_OUTPUTS})
  add_flex_bison_dependency(Lexer Parser)
endif()

# project link directories
link_directories(${LIB_DIR})

# project include directories
include_directories(src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${INC_DIR})
set(COMPILER_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
include_directories(${COMPILER_SRC_INCLUDE_DIR})
# all of C/C++ source files
file(GLOB_RECURSE C_SOURCES "src/*.c" "src/*/*.c" "src/*/*/*.c")
file(GLOB_RECURSE CXX_SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")
file(GLOB_RECURSE CC_SOURCES "src/*.cc" "src/*/*.cc" "src/*/*/*.cc")
set(SOURCES ${C_SOURCES} ${CXX_SOURCES} ${CC_SOURCES}
            ${FLEX_Lexer_OUTPUTS} ${BISON_Parser_OUTPUT_SOURCE})



# add glog
add_subdirectory(${GLOG_DIR})
include_directories(${GLOG_BINIRY_DIR})
include_directories(${GLOG_SOURCE_DIR})
# include_directories(${GLOG_DIR}/build ${GLOG_DIR}/src)
# executable
add_executable(compiler ${SOURCES})
target_link_libraries(compiler glog)
# add command
add_custom_target(
  run 

  ${CMAKE_BINARY_DIR}/${PROJECT_NAME} test ${CMAKE_SOURCE_DIR}/debug/hello.c -o ${CMAKE_SOURCE_DIR}/debug/hello.ll

)
add_custom_target(
  zx_test 
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe test ${CMAKE_SOURCE_DIR}/debug/zx_test.c -o ${CMAKE_SOURCE_DIR}/debug/zx_test.ll

)

add_custom_target(
  llvm 
  
  clang -S -emit-llvm ../debug/hello.c
)

add_custom_target(
  bc
  
  llvm-as ${CMAKE_SOURCE_DIR}/debug/hello.ll -o hello.bc
)

add_custom_target(
  quicksort

  ${CMAKE_BINARY_DIR}/${PROJECT_NAME} test ${CMAKE_SOURCE_DIR}/debug/quick_sort.c -o ${CMAKE_SOURCE_DIR}/debug/quick_sort.ll

)

add_custom_target(
  advisor

  ${CMAKE_BINARY_DIR}/${PROJECT_NAME} test ${CMAKE_SOURCE_DIR}/debug/advisor.c -o ${CMAKE_SOURCE_DIR}/debug/advisor.ll

)

add_custom_target(
  matrix_mul

  ${CMAKE_BINARY_DIR}/${PROJECT_NAME} test ${CMAKE_SOURCE_DIR}/debug/matrix_mul.c -o ${CMAKE_SOURCE_DIR}/debug/matrix_mul.ll
)

add_custom_target(
  build_quicksort
  COMMAND llc -march=x86-64 ${CMAKE_SOURCE_DIR}/debug/quick_sort.ll -o ${CMAKE_SOURCE_DIR}/debug/quick_sort.s
  COMMAND as ${CMAKE_SOURCE_DIR}/debug/quick_sort.s -o ${CMAKE_SOURCE_DIR}/debug/quick_sort.o
  COMMAND clang -Wall -Werror ${CMAKE_SOURCE_DIR}/debug/quick_sort.o -o ${CMAKE_SOURCE_DIR}/debug/quick_sort -I/root/compiler/sysy-runtime-lib-master/src -L/root/compiler/sysy-runtime-lib-master/build -lsysy -O1
  COMMENT "quicksort Linked"
)

add_custom_target(
  build_advisor
  COMMAND llc -march=x86-64 ${CMAKE_SOURCE_DIR}/debug/advisor.ll -o ${CMAKE_SOURCE_DIR}/debug/advisor.s
  COMMAND as ${CMAKE_SOURCE_DIR}/debug/advisor.s -o ${CMAKE_SOURCE_DIR}/debug/advisor.o
  COMMAND clang -Wall -Werror ${CMAKE_SOURCE_DIR}/debug/advisor.o -o ${CMAKE_SOURCE_DIR}/debug/advisor -I/root/compiler/sysy-runtime-lib-master/src -L/root/compiler/sysy-runtime-lib-master/build -lsysy -O1
  COMMENT "advisor Linked"
)

add_custom_target(
  build_matrix_mul
  COMMAND llc -march=x86-64 ${CMAKE_SOURCE_DIR}/debug/matrix_mul.ll -o ${CMAKE_SOURCE_DIR}/debug/matrix_mul.s
  COMMAND as ${CMAKE_SOURCE_DIR}/debug/matrix_mul.s -o ${CMAKE_SOURCE_DIR}/debug/matrix_mul.o
  COMMAND clang -Wall -Werror ${CMAKE_SOURCE_DIR}/debug/matrix_mul.o -o ${CMAKE_SOURCE_DIR}/debug/matrix_mul -I/root/compiler/sysy-runtime-lib-master/src -L/root/compiler/sysy-runtime-lib-master/build -lsysy -O1
  COMMENT "matrix_mul Linked"
)

add_custom_target(
  test_quicksort
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME} test ${CMAKE_SOURCE_DIR}/debug/matrix_mul.c -o ${CMAKE_SOURCE_DIR}/debug/matrix_mul.ll
  COMMAND llc -march=x86-64 ${CMAKE_SOURCE_DIR}/debug/quick_sort.ll -o ${CMAKE_SOURCE_DIR}/debug/quick_sort.s
  COMMAND as ${CMAKE_SOURCE_DIR}/debug/quick_sort.s -o ${CMAKE_SOURCE_DIR}/debug/quick_sort.o
  COMMAND clang -Wall -Werror ${CMAKE_SOURCE_DIR}/debug/quick_sort.o -o ${CMAKE_SOURCE_DIR}/debug/quick_sort -I/root/compiler/sysy-runtime-lib-master/src -L/root/compiler/sysy-runtime-lib-master/build -lsysy -O1
  COMMENT "quicksort Linked"
  COMMAND ${CMAKE_SOURCE_DIR}/tester/quicksort/quicksort-linux-amd64 ${CMAKE_SOURCE_DIR}/debug/quick_sort
  COMMENT "quicksort Tested"
)

add_custom_target(
  test_matrix_mul
  COMMAND ${CMAKE_SOURCE_DIR}/tester/matrix/matrix-linux-amd64 ${CMAKE_SOURCE_DIR}/debug/matrix_mul
  COMMENT "matrix_mul Tested"
)

add_custom_target(
  test_advisor
  COMMAND ${CMAKE_SOURCE_DIR}/tester/advisor/advisor-linux-amd64 ${CMAKE_SOURCE_DIR}/debug/advisor
  COMMENT "advisor Tested"
)
# add_dependencies(run ${PROJECT_NAME})

set_target_properties(compiler PROPERTIES C_STANDARD 11 CXX_STANDARD 17)
target_link_libraries(compiler pthread dl)
