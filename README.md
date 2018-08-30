# etrobocon2018
[![Build Status](https://travis-ci.org/KatLab-MiyazakiUniv/etrobocon2018.svg?branch=master)](https://travis-ci.org/KatLab-MiyazakiUniv/etrobocon2018) [![CircleCI](https://circleci.com/gh/KatLab-MiyazakiUniv/etrobocon2018/tree/master.svg?style=svg)](https://circleci.com/gh/KatLab-MiyazakiUniv/etrobocon2018/tree/master) [![codecov](https://codecov.io/gh/KatLab-MiyazakiUniv/etrobocon2018/branch/master/graph/badge.svg)](https://codecov.io/gh/KatLab-MiyazakiUniv/etrobocon2018)

[![CodeFactor](https://www.codefactor.io/repository/github/katlab-miyazakiuniv/etrobocon2018/badge)](https://www.codefactor.io/repository/github/katlab-miyazakiuniv/etrobocon2018)
[![document](https://img.shields.io/badge/Document-auto%20build-blue.svg)](https://katlab-miyazakiuniv.github.io/etrobocon2018/)

ようこそ

このページは[片山研究所モデルベース開発推進事業部](http://earth.cs.miyazaki-u.ac.jp "http://earth.cs.miyazaki-u.ac.jp")が開発している、ETロボコン2018デベロッパー部門アドバンスドコースのソースコードのリポジトリです。

## Make方法

makeには、[ETrobo-Docker](https://github.com/korosuke613/ETrobo-Docker)を利用しています。


`etrobocon2018/str`ディレクトリ内で、以下を実行してください。

```bash
docker run --rm -it -v $PWD:/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker makeSpecial
```

makeが成功すると、`etrobocon2018/str`ディレクトリ内に、２つの実行ファイル`app_left`, `app_right`が生成されます。

```bash
-> % ls
Makefile.inc   app.cpp        app_left       apps
makeLeft.sh    makeSpecial.sh app.cfg        app.h
app_right      ev3-api        makeRight.sh
```

`app_left`が、Lコースの走行プログラムです。`app_right`が、Rコースの走行プログラムです。

### Rコースのみビルドしたい場合
Rコースのみビルドしたい場合は以下を実行してください。

```bash
docker run --rm -it -v $PWD:/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker makeRight
```

### Lコースのみビルドしたい場合
Lコースのみビルドしたい場合は以下を実行してください。

```bash
docker run --rm -it -v $PWD:/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker makeLeft
```
