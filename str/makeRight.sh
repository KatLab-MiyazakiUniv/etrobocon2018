cd ..
mv product/apps/include/EtRobocon2018.h product/apps/include/EtRobocon2018.h.bak
cat product/apps/include/EtRobocon2018.h.bak | sed "s/\\/\\/#define IS_RIGHT_COURSE/#define IS_RIGHT_COURSE/" > product/apps/include/EtRobocon2018.h
make app=product side=right
cp product/apps/include/EtRobocon2018.h.bak product/apps/include/EtRobocon2018.h
rm -f product/apps/include/EtRobocon2018.h.bak
mv app product/app_right