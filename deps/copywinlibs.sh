#!/bin/bash

if [ '!' -f mmm.nsi ]; then
    echo 'Please run this from the root source directory.' >&2
    exit 1
fi

if [ '!' -d build ]; then
    echo 'To use this script, build in a subdirectory called "build".' >&2
    exit 1
fi

cp /cygdrive/c/MinGW/bin/libgcc_s_dw2-1.dll                     build
cp /cygdrive/c/MinGW/bin/mingwm10.dll                           build
cp /cygdrive/c/MinGW/bin/libstdc++-6.dll                        build
cp /cygdrive/c/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtCore4.dll     build
cp /cygdrive/c/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtGui4.dll      build
