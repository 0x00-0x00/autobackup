cmake_minimum_required(VERSION 3.6)
project(autobackup)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/arguments.c
        src/arguments.h
        autobackup.c src/datacopy.c src/datacopy.h src/require.c src/require.h src/verbose.c src/verbose.h src/time_measure.c src/time_measure.h src/push.c src/push.h src/helper.c src/helper.h)

add_executable(autobackup ${SOURCE_FILES})