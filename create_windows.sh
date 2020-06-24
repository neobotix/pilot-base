#!/bin/bash

VERSION=$(cat VERSION)
ARCH=$(uname -m)
DIST=$(cat ~/DIST)
DST=pilot-base-$VERSION-$ARCH-$DIST

export PATH=$PATH:$PWD/dependencies/codegen/usr/bin
export VNX_INTERFACE_DIR=${VNX_INTERFACE_DIR:-$PWD/dependencies/vnx/usr/interface}
./codegen.sh || exit 1

rm -rf $DST
mkdir -m 755 -p $DST/usr
mkdir -p $ARCH

./install.sh -DCMAKE_INSTALL_PREFIX:PATH=$PWD/$DST/usr || exit 1

7za a ${DST}.7z ${DST} || exit 1
mv ${DST}.7z $ARCH/
rm -rf $DST

