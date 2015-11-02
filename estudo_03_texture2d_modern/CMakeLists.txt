cmake_minimum_required(VERSION 2.8)

project(estudo_03)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
# Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
# Find SDL

file(GLOB my_source_files "*.h" "*.cpp")
add_executable(estudo03 ${my_source_files} )     

target_link_libraries(estudo03 ${ITK_LIBRARIES} ${VTK_LIBRARIES})