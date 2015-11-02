cmake_minimum_required(VERSION 2.8)

project(RealTimeVolumeRendering)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
# Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
#adiciona os subdiretórios
add_subdirectory(estudo_01_texture2d_oldschool)
add_subdirectory(estudo_02_texture3d_oldschool)
add_subdirectory(estudo_03_texture2d_modern)
add_subdirectory(estudo_04_texture3d_modern)


