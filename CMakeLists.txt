cmake_minimum_required(VERSION 3.9)
project(sonar_scanner_example)

set(CMAKE_CXX_STANDARD 17)
target_sources(app PRIVATE model.cpp model_chatgpt.cpp)
