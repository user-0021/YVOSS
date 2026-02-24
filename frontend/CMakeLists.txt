cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME app)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} "main.cpp")

set(DEST_DIR "${CMAKE_SOURCE_DIR}/../static")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

	COMMAND ${CMAKE_COMMAND} -E make_directory "${DEST_DIR}"
	COMMAND ${CMAKE_COMMAND} -E copy 
		"${CMAKE_CURRENT_BINARY_DIR}/kros_app.js" 
		"${DEST_DIR}/main.js"
					
	# WASMファイルのコピー（生成される場合のみ）
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_CURRENT_BINARY_DIR}/kros_app.wasm" 
		"${DEST_DIR}/main.wasm"
					
	COMMENT ">>> Generated files are being deployed to ${DEST_DIR}..."
)