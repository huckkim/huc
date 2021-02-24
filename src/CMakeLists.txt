add_subdirectory(Rings)
add_subdirectory(Fields)
add_subdirectory(Modules)

add_executable(huc main.cc)

target_link_libraries(huc IntegerLib)