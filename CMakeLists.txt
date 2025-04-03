cmake_minimum_required(VERSION 3.15)
project(SequencesBinding)

set(Python3_ROOT_DIR "C:\\Users\\ilya\\AppData\\Local\\Programs\\Python\\Python313")

set(pybind11_DIR "C:\\Users\\ilya\\AppData\\Local\\Programs\\Python\\Python313\\Lib\\site-packages\\pybind11\\share\\cmake\\pybind11")

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

find_package(pybind11 REQUIRED)
set(PYBIND11_FINDPYTHON ON)
pybind11_add_module(sequences 
    cpp/ArraySequence.cpp 
    cpp/ListSequence.cpp 
    cpp/DynamicArray.cpp 
    cpp/LinkedList.cpp 
    cpp/sequence_bindings.cpp)



