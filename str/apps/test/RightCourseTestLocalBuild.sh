#!/bin/bash
cd ../../

mv apps/include/Controller.h apps/include/Controller.h.bak
mv apps/src/Controller.cpp apps/src/Controller.cpp.bak
cp apps/test/MockController.h apps/include/Controller.h
cp apps/test/MockController.cpp apps/src/Controller.cpp

cd apps/test
g++-8 -g -O0 RightCourseTest.cpp ../src/*.cpp gtest_main.o gtest-all.o -I../include -I/Users/Futa/googletest/googletest/include

cd ../../
mv -f apps/include/Controller.h.bak apps/include/Controller.h
mv -f apps/src/Controller.cpp.bak apps/src/Controller.cpp

