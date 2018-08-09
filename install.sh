#!/bin/bash
cd str/str

mv apps/include/Worker.h apps/include/Worker.h.bak
mv apps/src/Worker.cpp apps/src/Worker.cpp.bak
cp apps/test/Worker.h apps/include/Worker.h
cp apps/test/Worker.cpp apps/src/Worker.cpp

cd ../
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Coverage ..
cmake --build .
ctest -VV

cd ../str
mv -f apps/include/Worker.h.bak apps/include/Worker.h
mv -f apps/src/Worker.cpp.bak apps/src/Worker.cpp

