#! /bin/sh

OS=$(uname)
BUILD_TEMP=$(pwd)/build

mkdir -p $BUILD_TEMP/include
mkdir -p $BUILD_TEMP/lib
mkdir -p $BUILD_TEMP/soil

if [ "$OS" = "Darwin" ] ; then

  # Build GLEW
  (cd src/third-party/glew && GLEW_DEST=$BUILD_TEMP SYSTEM=Darwin make install)
  (cd src/third-party/glew && GLEW_DEST=$BUILD_TEMP SYSTEM=Darwin make distclean)

  # Build GLFW
  (cd src/third-party/glfw && make cocoa)
  (cd src/third-party/glfw && PREFIX=$BUILD_TEMP make cocoa-install)
  (cd src/third-party/glfw && make cocoa-clean)

  # Some cleanup
  rm $BUILD_TEMP/lib/libGLEW.1.7*
  rm $BUILD_TEMP/lib/libGLEW.dylib

elif [ "$OS" = "Linux" ] ; then

  # Build GLEW
  (cd src/third-party/glew && GLEW_DEST=$BUILD_TEMP SYSTEM=linux make install)
  (cd src/third-party/glew && GLEW_DEST=$BUILD_TEMP SYSTEM=linux make distclean)

  # Build GLFW
  (cd src/third-party/glfw && make x11)
  (cd src/third-party/glfw && PREFIX=$BUILD_TEMP make x11-install)
  (cd src/third-party/glfw && make x11-dist-clean)

  # Some cleanup
  mv $BUILD_TEMP/lib64/libGLEW.a $BUILD_TEMP/lib
  rm -r $BUILD_TEMP/lib64

fi

