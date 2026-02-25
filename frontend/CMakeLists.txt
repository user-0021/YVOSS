cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME app)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} "main.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist)
set(DEST_DIR "${CMAKE_SOURCE_DIR}/../staticfile")


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory "${DEST_DIR}"
	COMMAND sh -c "cp *.js *.wasm ${DEST_DIR}"
	COMMENT ">>> Copying all generated assets to ${DEST_DIR}..."
)