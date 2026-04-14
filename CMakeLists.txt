cmake_minimum_required(VERSION 3.3)
project(ReadHEPMC)

# Find Geant4 — specify components as needed
find_package(Geant4 REQUIRED ui_all vis_all)

# Include Geant4's CMake helper macros and settings
include(${Geant4_USE_FILE})

# Add your sources
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(ReadHEPMC ${sources} ${headers})
target_link_libraries(ReadHEPMC ${Geant4_LIBRARIES})
