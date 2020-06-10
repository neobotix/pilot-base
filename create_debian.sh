#!/bin/bash

VERSION=$(cat VERSION)
ARCH=$(uname -m)
DIST=$(cat ~/DIST)
DST=pilot-base-$VERSION-$ARCH-$DIST

./codegen.sh || exit 1

rm -rf $DST
mkdir -m 755 -p $DST/DEBIAN
mkdir -m 755 -p $DST/usr
mkdir -p $ARCH

echo "Version: $VERSION" >> $DST/DEBIAN/control
cat debian/control >> $DST/DEBIAN/control

./install.sh -DCMAKE_INSTALL_PREFIX:PATH=$PWD/$DST/usr || exit 1

fakeroot dpkg-deb --build $DST || exit 1

mv ${DST}.deb $ARCH/

rm -rf $DST

