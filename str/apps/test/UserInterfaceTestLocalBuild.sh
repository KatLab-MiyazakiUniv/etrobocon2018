#!/bin/bash
cd ../../

mv apps/include/Worker.h apps/include/Worker.h.bak
mv apps/src/Worker.cpp apps/src/Worker.cpp.bak
cp apps/test/MockWorker.h apps/include/Worker.h
cp apps/test/MockWorker.cpp apps/src/Worker.cpp

cd apps/test
g++-8 -g -O0 UserInterfaceTest.cpp ../src/UserInterface.cpp ../src/FirstCode.cpp gtest_main.o gtest-all.o -I../include -I/Users/Futa/googletest/googletest/include

cd ../../
mv -f apps/include/Worker.h.bak apps/include/Worker.h
mv -f apps/src/Worker.cpp.bak apps/src/Worker.cpp

