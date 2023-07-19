target_compile_options(engine PRIVATE
	-Wall
	-Wextra
	-Wpedantic
)

target_compile_features(engine PRIVATE
	c_std_23
)

target_sources(engine PRIVATE
	src/library.c
	src/engine2d.c
	src/camera.c
)

target_include_directories(engine PRIVATE
	../${SDL_PATH}/include
	include
)

target_link_directories(engine PRIVATE
	../${SDL_PATH}/lib
)

target_link_libraries(engine
	${DEPENDENCIES}
	${LIBRARIES}
)
