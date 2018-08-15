#!/bin/bash
cd str/str

mv apps/include/Controller.h apps/include/Controller.h.bak
mv apps/src/Controller.cpp apps/src/Controller.cpp.bak
cp apps/test/MockController.h apps/include/Controller.h
cp apps/test/MockController.cpp apps/src/Controller.cpp

cd ../
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Coverage ..
cmake --build .
ctest -VV

cd ../str
mv -f apps/include/Controller.h.bak apps/include/Controller.h
mv -f apps/src/Controller.cpp.bak apps/src/Controller.cpp

