cmake_minimum_required(VERSION 3.5)
project(Darwinet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.cpp
        src/fcb/Active.cpp
        src/fcb/Active.h
        src/fcb/BackEnd.cpp
        src/fcb/BackEnd.h
        src/fcb/Core.cpp
        src/fcb/Core.h
        src/fcb/FrontEnd.cpp
        src/fcb/FrontEnd.h src/miv/Value.cpp src/miv/Value.h src/miv/Instance.cpp src/miv/Instance.h src/miv/Model.cpp src/miv/Model.h)
add_executable(Darwinet ${SOURCE_FILES})