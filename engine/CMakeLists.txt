target_compile_options(Engine PRIVATE -Wall -Wextra -Wpedantic)

target_compile_features(Engine PRIVATE c_std_23)

target_sources(Engine PRIVATE
	src/math_a.c
	src/engine2d.c
	src/camera.c
)

target_include_directories(Engine PRIVATE
	${SDL_PATH}/include
	include
)

target_link_directories(Engine PRIVATE
	${SDL_PATH}/lib
	)

target_link_libraries(Engine
	${DEPENDENCIES}
	${LIBRARIES}
)
