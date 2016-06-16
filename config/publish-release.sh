#!/bin/bash

mkdir zpd
cp -R lib zpd/lib
cp -R cpd zpd/cpd
cp -R xpd zpd/xpd
cp README.md zpd/readme.txt
cp LICENSE.txt zpd/license.txt
cd zpd
ls
echo $TRAVIS_OS_NAME
echo $ZPD_ARCH
echo $TRAVIS_TAG
echo zpd_$TRAVIS_OS_NAME_$ZPD_ARCH_$TRAVIS_TAG
zip -r zpd_$TRAVIS_OS_NAME_$ZPD_ARCH_$TRAVIS_TAG.zip zpd
