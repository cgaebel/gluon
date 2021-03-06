cmake_minimum_required(VERSION 2.6)
project(Gluon)

#Project options, to provide a selective build process
#Note that some of these are mutually exclusive or just
#do not make a whole lot of sense combined.
option(WITH_KDE "Build with KDE Development Platform Support" ON)
option(BUILD_GLUON_AUDIO "Build Gluon Audio Library" ON)
option(BUILD_GLUON_INPUT "Build Gluon Input Library" ON)
option(BUILD_GLUON_GRAPHICS "Build Gluon Graphics Library" ON)
option(BUILD_GLUON_ENGINE "Build Gluon Engine Library" ON)
option(BUILD_GLUON_PLAYER "Build Gluon Player Application" ON)
option(BUILD_PLASMOID "Build Gluon Player Plasmoid" ON)
option(BUILD_GLUON_CREATOR "Build Gluon Creator Application" ON)
option(INSTALL_EXAMPLES "Install the game examples for Gluon Player" ON)
option(BUILD_GLUON_TESTS "Build the Gluon test suite" OFF)

if(CMAKE_INSTALL_PREFIX STREQUAL "/usr")
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" ON)
else()
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" OFF)
endif()

set(GLUON_BUILD_ALL TRUE
    CACHE INTERNAL "Build all of Gluon"
)

SET(CMAKE_CXX_FLAGS "-Wall")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

##### Gluon Libraries #####

####### Gluon Core ########
add_subdirectory(core)
####### Gluon Audio #######
if(BUILD_GLUON_AUDIO)
    add_subdirectory(audio)
endif()
####### Gluon Input #######
if(BUILD_GLUON_INPUT)
    add_subdirectory(input)
endif()
###### Gluon Graphics #####
if(BUILD_GLUON_GRAPHICS)
    add_subdirectory(graphics)
endif()
###### Gluon Engine #######
if(BUILD_GLUON_ENGINE)
    add_subdirectory(engine)
endif()

######## KDE Parts ########
if(WITH_KDE)
    set(BUILD_PLASMOID ON)
    set(BUILD_GLUON_CREATOR ON)
endif(WITH_KDE)
if(BUILD_PLASMOID OR BUILD_GLUON_CREATOR)
    find_package(KDE4)
    if(NOT KDE4_FOUND)
        set(BUILD_PLASMOID OFF)
        set(BUILD_GLUON_CREATOR OFF)
        set(KDE_FAILED TRUE)
    endif(NOT KDE4_FOUND)
endif(BUILD_PLASMOID OR BUILD_GLUON_CREATOR)

###### Gluon Creator ######
if(BUILD_GLUON_CREATOR)
    add_subdirectory(creator)
endif(BUILD_GLUON_CREATOR)

###### Gluon Player ######
# Checks must be done here because it does its own checks only when cmake was not called here ...
if(BUILD_GLUON_PLAYER)
    add_subdirectory(player)
else(BUILD_GLUON_PLAYER)
    set(INSTALL_EXAMPLES OFF)
    set(BUILD_PLASMOID OFF)
endif(BUILD_GLUON_PLAYER)

if(BUILD_GLUON_TESTS)
    add_subdirectory(core_test)
endif(BUILD_GLUON_TESTS)

message(STATUS)
message(STATUS "========== Gluon Build Information ==========")
message(STATUS "Build Version: ${GLUON_VERSION_STRING} (${GLUON_VERSION_NAME})")
message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Install the *.cmake files into CMake root (INSTALL_CMAKE_FILES): ${INSTALL_CMAKE_FILES}")
message(STATUS "Install the game examples for Gluon Player (INSTALL_EXAMPLES): ${INSTALL_EXAMPLES}")
message(STATUS "Enable KDE Development Platform support (WITH_KDE): ${WITH_KDE}")
message(STATUS "Build Gluon Audio Library (BUILD_GLUON_AUDIO): ${BUILD_GLUON_AUDIO}")
message(STATUS "Build Gluon Input Library (BUILD_GLUON_INPUT): ${BUILD_GLUON_INPUT}")
message(STATUS "Build Gluon Graphics Library (BUILD_GLUON_GRAPHICS): ${BUILD_GLUON_GRAPHICS}")
message(STATUS "Build Gluon Engine Library (BUILD_GLUON_ENGINE): ${BUILD_GLUON_ENGINE}")
if(BUILD_GLUON_ENGINE)
    message(STATUS "    Build Components dependant on Gluon Audio (BUILD_AUDIO_COMPONENTS): ${BUILD_AUDIO_COMPONENTS}")
    message(STATUS "    Build Assets dependant on Gluon Audio (BUILD_AUDIO_ASSETS): ${BUILD_AUDIO_ASSETS}")
    message(STATUS "    Build Components dependant on Gluon Graphics (BUILD_GRAPHICS_COMPONENTS): ${BUILD_GRAPHICS_COMPONENTS}")
    message(STATUS "    Build Assets dependant on Gluon Graphics (BUILD_GRAPHICS_ASSETS): ${BUILD_GRAPHICS_ASSETS}")
    message(STATUS "    Build Components dependant on Gluon Input (BUILD_INPUT_COMPONENTS): ${BUILD_INPUT_COMPONENTS}")
    message(STATUS "    Build Assets dependant on Gluon Input (BUILD_INPUT_ASSETS): ${BUILD_INPUT_ASSETS}")
    message(STATUS "    Build Components related to physics (BUILD_PHYSICS_COMPONENTS): ${BUILD_PHYSICS_COMPONENTS}")
    message(STATUS "    Build Assets related to physics (BUILD_PHYSICS_ASSETS): ${BUILD_PHYSICS_ASSETS}")
    message(STATUS "    Build other Components (BUILD_OTHER_COMPONENTS): ${BUILD_OTHER_COMPONENTS}")
    message(STATUS "    Build other Assets (BUILD_OTHER_ASSETS): ${BUILD_OTHER_ASSETS}")
endif()
message(STATUS "Build Gluon Player Library and Qt Application (BUILD_GLUON_PLAYER): ${BUILD_GLUON_PLAYER}")
message(STATUS "Build Gluon Player Plasmoid (BUILD_PLASMOID): ${BUILD_PLASMOID}")
message(STATUS "Build Gluon Creator Application (BUILD_GLUON_CREATOR): ${BUILD_GLUON_CREATOR}")
message(STATUS "Build Gluon Tests (BUILD_GLUON_TESTS): ${BUILD_GLUON_TESTS}")
message(STATUS)
message(STATUS "To change any of these options, override them using -D{OPTION_NAME} on the commandline.")
message(STATUS "To build and install Gluon, run \"make\" and \"make install\"")
message(STATUS)
if(KDE_FAILED OR ATTICA_FAILED OR PLAYER_FAILED)
    message(STATUS)
    message(STATUS "WARNING!")
endif(KDE_FAILED OR ATTICA_FAILED OR PLAYER_FAILED)
if(KDE_FAILED)
    message(STATUS)
    message(STATUS "Gluon Creator and/or Plasmoid was/were disabled because KDE could not be found.")
    message(STATUS)
endif(KDE_FAILED)


if(INSTALL_CMAKE_FILES)
    install(
        FILES
        core/cmake/FindGluon.cmake
        core/cmake/FindGluonCore.cmake
        audio/cmake/FindGluonAudio.cmake
        audio/cmake/FindOggVorbis.cmake
        audio/cmake/FindSndFile.cmake
        graphics/cmake/FindGluonGraphics.cmake
        graphics/cmake/FindOpenGLES2.cmake
        input/cmake/FindGluonInput.cmake
        engine/cmake/FindGluonEngine.cmake
        creator/lib/cmake/FindGluonCreator.cmake
        DESTINATION
        ${CMAKE_ROOT}/Modules
        OPTIONAL
    )
else()
    install(
        FILES
        core/cmake/FindGluon.cmake
        core/cmake/FindGluonCore.cmake
        audio/cmake/FindGluonAudio.cmake
        audio/cmake/FindOggVorbis.cmake
        audio/cmake/FindSndFile.cmake
        graphics/cmake/FindGluonGraphics.cmake
        graphics/cmake/FindOpenGLES2.cmake
        input/cmake/FindGluonInput.cmake
        engine/cmake/FindGluonEngine.cmake
        creator/lib/cmake/FindGluonCreator.cmake
        DESTINATION
        ${SHARE_INSTALL_DIR}/gluon/cmake
        OPTIONAL
    )
endif()

#Packaging options
set(CPACK_SET_DESTDIR ON)
set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_PACKAGE_NAME "Gluon")
set(CPACK_PACKAGE_FILE_NAME "Gluon-${GLUON_VERSION_STRING}")
set(CPACK_PACKAGE_VERSION "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt4-gui (>= 4.6), libqt4-opengl (>= 4.6), libopenal1, libsndfile1, libvorbis0a, libgles2")
set(CPACK_PACKAGE_CONTACT "Arjen Hiemstra <ahiemstra@heimr.nl>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An open framework to create, distribute and play games")
set(CPACK_DEBIAN_PACKAGE_SECTION "Games")
include(InstallRequiredSystemLibraries)
include(CPack)
