add_executable(geogenerator main.cpp)

target_link_libraries(geogenerator PUBLIC geo)
target_include_directories(geogenerator PUBLIC ${PROJECT_SOURCE_DIR}/geogenerator)