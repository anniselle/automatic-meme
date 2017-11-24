cmake_minimum_required (VERSION 2.9)

set(FULL_NAME automatic-meme)
set(SHORT_NAME ameme)
set(SOURCES
	${CMAKE_SOURCE_DIR}/mainWindow/mainWindow.cc)
set(LIBS gdi32)

project (${FULL_NAME})

include_directories(include/)
add_executable(${SHORT_NAME} ${SOURCES})
target_link_libraries(${SHORT_NAME} ${LIBS})