cmake_minimum_required(VERSION 3.10)
project(libmidi
	VERSION 0.1.0
	LANGUAGES C
)
set(CMAKE_C_STANDARD 11)


# library
add_library(midi
	src/midi.c
	src/byte_buffer.c
)
target_include_directories(midi PUBLIC
	include
)
install(TARGETS midi
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
install(FILES include/midi.h
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/libmidi
)

# example program
add_executable(example
	read_midi.c
)
target_include_directories(example PUBLIC
	include
)
target_link_libraries(example
	midi
)
