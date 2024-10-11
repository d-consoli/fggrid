cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(fggrid)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER /usr/bin/mpic++)

find_package(OpenMP REQUIRED)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH} ${CMAKE_SOURCE_DIR}/include)


find_package(VTK COMPONENTS
        CommonColor
        CommonDataModel
        InteractionWidgets
        CommonCore
        FiltersSources
        FiltersCore
        FiltersGeometry
        FiltersModeling
        InteractionStyle
        RenderingContextOpenGL2
        RenderingCore
        RenderingFreeType
        RenderingGL2PSOpenGL2
        RenderingOpenGL2
        RenderingAnnotation
)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "FGGrid: Unable to find the VTK build folder.")
endif()
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

add_subdirectory(test)
add_library(FgGrid src/FgTree.cpp src/FgGeometry.cpp src/FgCell.cpp src/FgVertex.cpp src/misc.cpp)
add_library(FgVisualizer src/FgVisualizer.cpp src/misc.cpp)

target_link_libraries(FgGrid PUBLIC ${MPI_LIBRARIES} OpenMP::OpenMP_CXX)
target_link_libraries(FgVisualizer PUBLIC OpenMP::OpenMP_CXX ${VTK_LIBRARIES})

if(MPI_COMPILE_FLAGS)
    set_target_properties(FgGrid PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(FgGrid PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

vtk_module_autoinit(
        TARGETS FgVisualizer
        MODULES ${VTK_LIBRARIES}
)
