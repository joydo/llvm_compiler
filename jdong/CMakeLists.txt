cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(JdongCompiler LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

# ---- cxxopts library ----
CPMAddPackage(
  NAME cxxopts
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES Off" "CXXOPTS_BUILD_TESTS Off"
)

# ---- self-building CommonLibrary library ----
CPMAddPackage(NAME CommonLibrary SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- LLVM Infrastructure library ----
set(LLVM_BIN_PATH "/Users/joy/Compilers/llvm_dev/llvm_compiler_related/llvm_install/bin")
set(LLVM_HEADER_DIR "/Users/joy/Compilers/llvm_dev/llvm_compiler_related/llvm_install/include")
execute_process(COMMAND bash -c "${LLVM_BIN_PATH}/llvm-config --cxxflags" OUTPUT_VARIABLE LLVM_CXXFLAGS)
execute_process(COMMAND bash -c "${LLVM_BIN_PATH}/llvm-config --ldflags" OUTPUT_VARIABLE LLVM_LDFLAGS)
execute_process(COMMAND bash -c "${LLVM_BIN_PATH}/llvm-config --libs" OUTPUT_VARIABLE LLVM_LIBS)
execute_process(COMMAND bash -c "${LLVM_BIN_PATH}/llvm-config --system-libs" OUTPUT_VARIABLE LLVM_SYSTEM_LIBS)
execute_process(COMMAND bash -c "${LLVM_BIN_PATH}/llvm-config --libdir" OUTPUT_VARIABLE LLVM_LIBS_DIR)
string(STRIP ${LLVM_CXXFLAGS} LLVM_CXXFLAGS)
string(STRIP ${LLVM_LDFLAGS} LLVM_LDFLAGS)
string(STRIP ${LLVM_LIBS} LLVM_LIBS)
string(STRIP ${LLVM_SYSTEM_LIBS} LLVM_SYSTEM_LIBS)
string(STRIP ${LLVM_LIBS_DIR} LLVM_LIBS_DIR)
set(COMPILE_FLAGS "${LLVM_CXXFLAGS}")
set(LINKER_FLAGS "${LLVM_LIBS}")

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

# ---- add dependencies for cppast ----
add_subdirectory(/Users/joy/Compilers/llvm_dev/llvm_exploit_related/jd_llvm_compiler_/third_party/cppast /Users/joy/Compilers/llvm_dev/llvm_exploit_related/jd_llvm_compiler_/third_library_libs/cppast)

add_executable(JdongCompiler ${sources})
target_include_directories(JdongCompiler PUBLIC ${LLVM_HEADER_DIR})
#target_link_directories(JdongCompiler PUBLIC ${LLVM_LIBS_DIR})

set_target_properties(JdongCompiler PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "${COMPILE_FLAGS}" COMPILE_FLAGS "-fexceptions" COMPILE_FLAGS "-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk" LINK_DIRECTORIES "${LLVM_LIBS_DIR}" LINK_FLAGS "${LINKER_FLAGS}" OUTPUT_NAME "jdCompiler")

target_link_libraries(JdongCompiler CommonLibrary::CommonLibrary cxxopts cppast)
