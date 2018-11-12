#!/bin/bash
cd ../../

mv apps/include/Controller.h apps/include/Controller.h.bak
mv apps/src/Controller.cpp apps/src/Controller.cpp.bak
cp apps/test/MockController.h apps/include/Controller.h
cp apps/test/MockController.cpp apps/src/Controller.cpp

cd apps/test
g++-8 -g BlockSolverTest.cpp \
    ../src/BlockSolver.cpp \
    ../src/BlockStrategy.cpp \
    ../src/Distinguisher.cpp \
    ../src/LineTracerWalker.cpp ../src/SpeedControl.cpp \
    ../src/TurnControl.cpp ../src/InitialPositionCodeDecoder.cpp \
    ../src/LPF.cpp ../src/Pid.cpp ../src/Lifter.cpp ../src/Navigator.cpp \
    ../src/WheelOdometry.cpp  ../src/BlockArea.cpp ./MockController.cpp \
    ../src/Walker.cpp \
    ../src/MotorAngle.cpp \
    gtest_main.o gtest-all.o -I../include -I/Users/Futa/googletest/googletest/include

cd ../../
mv -f apps/include/Controller.h.bak apps/include/Controller.h
mv -f apps/src/Controller.cpp.bak apps/src/Controller.cpp

