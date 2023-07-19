target_compile_options(main PRIVATE
	-Wall
	-Wextra
	-Wpedantic
)

target_compile_features(main PRIVATE
	c_std_23
)

target_sources(main PRIVATE
	src/main.c
)

target_include_directories(main PRIVATE
	../engine/include
	include
)

target_link_libraries(main
	engine
)
