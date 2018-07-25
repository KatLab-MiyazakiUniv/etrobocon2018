cd ..
mv src/apps/include/EtRobocon2018.h src/apps/include/EtRobocon2018.h.bak
cat src/apps/include/EtRobocon2018.h.bak | sed "s/\\/\\/#define IS_RIGHT_COURSE/#define IS_RIGHT_COURSE/" > src/apps/include/EtRobocon2018.h
make app=src side=right
cp src/apps/include/EtRobocon2018.h.bak src/apps/include/EtRobocon2018.h
rm -f src/apps/include/EtRobocon2018.h.bak
mv app src/app_right