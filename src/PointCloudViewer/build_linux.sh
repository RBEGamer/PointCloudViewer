#!/bin/sh
cd PointCloudViewer/build

cmake ..
make clean
make
chmod +x ./PCV
./PCV

cd ../..
