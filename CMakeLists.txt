cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
include(ExternalProject)
project(fggrid)
set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
if(NOT MPI_FOUND)
    ExternalProject_Add(mpi_project
            URL https://download.open-mpi.org/release/open-mpi/v5.0/openmpi-5.0.5.tar.gz
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/mpi
            CONFIGURE_COMMAND <path_to_mpi>/configure --prefix=${CMAKE_CURRENT_BINARY_DIR}/mpi
            BUILD_COMMAND make
            INSTALL_COMMAND make install
    )
    set(MPI_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/mpi/lib)
    set(MPI_INCLUDE_PATH ${CMAKE_CURRENT_BINARY_DIR}/mpi/include)

    add_dependencies(fggrid mpi_project)
else()
    message(STATUS "MPI found")
endif()
include_directories(${MPI_INCLUDE_PATH})

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


add_executable(fggrid run_fggrid.cpp)
target_link_libraries(fggrid PUBLIC MPI::MPI_CXX)
add_executable(visualizer MACOSX_BUNDLE visualizer.cpp)
target_link_libraries(visualizer PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
        TARGETS visualizer
        MODULES ${VTK_LIBRARIES}
)