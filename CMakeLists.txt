###############################################################################
# Multi Minecraft Manager (MMM)
# Copyright (c) Frank "SeySayux" Erens <seysayux@gmail.com>
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
#    1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
#
#    2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
#
#    3. This notice may not be removed or altered from any source
#    distribution.
###############################################################################

cmake_minimum_required(VERSION 2.6)
project(MMM)

# For some reason (most likely because it's a fuckup) cmake can't find Qt on
# my system, so I'm setting it here explicitly.
# If you installed Qt in its default location, this shouldn't harm you. In case
# you didn't, feel free to remove/adjust these lines.
# TODO: make it work on my system without these lines.
if(WIN32)
    set(QT_QMAKE_EXECUTABLE 
            "C:\\QtSDK\\Desktop\\Qt\\4.8.0\\mingw\\bin\\qmake.exe")
endif(WIN32)

if(CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-g -std=c++03 -Wno-long-long -pedantic -Wall -Werror)
endif(CMAKE_COMPILER_IS_GNUCC)
  
set(PROGNAME mmm)

if(APPLE)
set(MACOSX_BUNDLE_ICON_FILE ${CMAKE_SOURCE_DIR}/icon/mmm.icns)
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "0.3 pre (c) 2012 Frank \"SeySayux\" Erens")
set(MACOSX_BUNDLE_VERSION "Version 0.3 pre (c) 2012 Frank \"SeySayux\" Erens" )
set(MACOSX_BUNDLE_LONG_VERSION_STRING 
        "Version 0.3 pre (c) 2012 Frank \"SeySayux\" Erens")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "Multi Minecraft Manager")
set(MACOSX_BUNDLE_BUNDLE_NAME "Multi Minecraft Manager")
else(APPLE)
endif(APPLE)


find_package(Qt4 REQUIRED)

set(MMM_SRC 
    src/main.cpp 
    src/os.cpp 
    src/gui.cpp 
    src/qstd.cpp 
    src/instance.cpp)
    
set(MMM_HDR 
    src/gui.h
    src/instance.h)
    
set(MMM_UI )

set(MMM_RSC resources.qrc)

qt4_wrap_cpp(MMM_HDR_MOC ${MMM_HDR})
qt4_wrap_ui(MMM_UI_HDR ${MMM_UI})
qt4_add_resources(MMM_RSC_RCC ${MMM_RSC})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# This is just so I can type "make and run"
add_custom_target(and)

if(APPLE)
    add_executable(${PROGNAME} MACOSX_BUNDLE ${MMM_SRC} 
            ${MMM_HDR_MOC} ${MMM_RSC_RCC} 
            ${MMM_UI_HDR} )

    # Copying the icon
    add_custom_command(TARGET ${PROGNAME} POST_BUILD
            COMMAND mkdir -p 
            ${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.app/Contents/Resources
            COMMAND cp ${MACOSX_BUNDLE_ICON_FILE} 
            ${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.app/Contents/Resources
            COMMAND rm -rf
            ${CMAKE_CURRENT_BINARY_DIR}/${MACOSX_BUNDLE_BUNDLE_NAME}.app
            COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.app
            ${CMAKE_CURRENT_BINARY_DIR}/${MACOSX_BUNDLE_BUNDLE_NAME}.app)

    # Running from command line
    add_custom_target(run COMMAND open
            ${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.app
            DEPENDS ${PROGNAME})
elseif(WIN32)
    if(MINGW)
        # resource compilation for MinGW
        add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/winicon.o
                COMMAND windres.exe -I${CMAKE_CURRENT_SOURCE_DIR} 
                -i${CMAKE_CURRENT_SOURCE_DIR}/icon/winicon.rc 
                -o ${CMAKE_CURRENT_BINARY_DIR}/winicon.o )
        SET(MMM_SRC ${MMM_SRC} 
                ${CMAKE_CURRENT_BINARY_DIR}/winicon.o)
    else(MINGW)
        set(MMM_SRC ${MMM_SRC} icon/winicon.rc)
    endif(MINGW)
    

    add_executable(${PROGNAME} WIN32 ${MMM_SRC} 
            ${MMM_HDR_MOC} ${MMM_RSC_RCC} 
            ${MMM_UI_HDR} )

    add_custom_target(run COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.exe
            DEPENDS ${PROGNAME})
else(APPLE)
    add_executable(${PROGNAME} ${MMM_SRC} 
            ${MMM_HDR_MOC} ${MMM_RSC_RCC} 
            ${MMM_UI_HDR} )
endif(APPLE)

target_link_libraries(${PROGNAME} ${QT_LIBRARIES})

