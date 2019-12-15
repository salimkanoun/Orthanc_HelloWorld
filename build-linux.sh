#!/bin/bash

set -e

if [ ! -f "salimPlugin.cpp" ]; then
  echo "This script must be executed in the dep-check-proj folder!" 1>&2;
  exit -1
else

  echo ""
  echo "----------------------------------------"
  echo "--> Removing the build folder..."
  echo "----------------------------------------"

  if [ -d "linux-build" ]; then
    rm -rf ./linux-build
  fi

  echo "----------------------------------------"
  echo "--> Creating the build folder..."
  echo "----------------------------------------"

  mkdir ./linux-build

  cd linux-build

  echo ""
  echo "----------------------------------------"
  echo "--> Configuring the project..."
  echo "----------------------------------------"
  echo ""

  # a relative path for DCMAKE_TOOLCHAIN_FILE does NOT work. it SEEMS to, but
  # it fails later down the configuration

  currentDir=$(pwd)
  currentDirAbs=$(realpath "$currentDir")

  cmake \
    -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=$currentDirAbs/../../../vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DVCPKG_TARGET_TRIPLET=x64-linux \
    -DCMAKE_BUILD_TYPE=Debug \
    ..

  echo ""
  echo ""
  echo "----------------------------------------"
  echo "--> Building the program..."
  echo "----------------------------------------"
  echo ""
  cmake --build .

  echo ""
  echo ""
  echo ""
  echo "----------------------------------------"
  echo "--> Displaying the program dependencies..."
  echo "----------------------------------------"
  echo ""

  ldd ./libsalimPlugin.so

  cd ..

fi
