cmake_minimum_required(VERSION 2.8)

project(estudo_02)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
# Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
# Find SDL

file(GLOB my_source_files "*.h" "*.cpp")
add_executable(estudo02 ${my_source_files} )     

target_link_libraries(estudo02 ${ITK_LIBRARIES} ${VTK_LIBRARIES})