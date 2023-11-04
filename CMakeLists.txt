cmake_minimum_required(VERSION 3.23)
project(feup_aed1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(feup_aed1
        src/slot.cpp
        src/slot.h
        src/student.cpp
        src/student.h
        src/ClassUC.cpp
        src/ClassUC.h
        src/DataManager.h
        src/DataManager.cpp
        src/main.cpp
        src/Menu.cpp
        src/Menu.h
        src/Request.cpp
        src/Request.h
        src/RequestManager.cpp
        src/RequestManager.h
)

