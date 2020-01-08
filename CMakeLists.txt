cmake_minimum_required(VERSION 3.10)
project(libmidi
	VERSION 0.1.0
	LANGUAGES C
)
set(CMAKE_C_STANDARD 11)

add_library(libmidi
	src/midi.c
)
target_include_directories(libmidi PUBLIC
	include
)
