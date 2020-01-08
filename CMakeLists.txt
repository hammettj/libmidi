cmake_minimum_required(VERSION 3.10)
project(libmidi
	VERSION 0.1.0
	LANGUAGES C
)
set(CMAKE_C_STANDARD 11)


# library
add_library(libmidi
	src/midi.c
)
target_include_directories(libmidi PUBLIC
	include
)

# example program
add_executable(example
	read_midi.c
)
target_include_directories(example PUBLIC
	include
)
target_link_libraries(example
	libmidi
)
