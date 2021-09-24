file(GLOB SRC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(id STATIC ${SRC_FILES})

target_include_directories(id PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})