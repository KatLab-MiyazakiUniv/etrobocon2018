/**
 *  @file   AIAnswerBlock.cpp
 *  @brief  AIアンサーのブロックを並べる
 *  @author T.N.Revolution
 */
#ifndef AI_ANSWER_BLOCK_H
#define AI_ANSWER_BLOCK_H
#include "Lifter.h"
#include "Navigator.h"

class AIAnswerBlock {
 private:
  Navigator navigator;
  std::int16_t target_brightness;
  Lifter lifter;
  // Distinguisher distingish_color;

 public:
  AIAnswerBlock(Controller& controller, Walker& walker, std::int16_t brightness)
    : navigator(controller, walker), target_brightness(brightness), lifter(controller)
  {
  }
  //! リフターを使ってブロックを放って後ろを向く
  void throwBlock(bool angle_direction = false);
  //! アナログ数字が0，デジタル数字が0
  void block00();
  //! アナログ数字が0，デジタル数字が1
  void block01();
  //! アナログ数字が0，デジタル数字が2
  void block02();
  //! アナログ数字が0，デジタル数字が3
  void block03();
  //! アナログ数字が0，デジタル数字が4
  void block04();
  //! アナログ数字が0，デジタル数字が5
  void block05();
  //! アナログ数字が0，デジタル数字が6
  void block06();
  //! アナログ数字が0，デジタル数字が7
  void block07();

  //! アナログ数字が1，デジタル数字が0
  void block10();
  //! アナログ数字が1，デジタル数字が1
  void block11();
  //! アナログ数字が1，デジタル数字が2
  void block12();
  //! アナログ数字が1，デジタル数字が3
  void block13();
  //! アナログ数字が1，デジタル数字が4
  void block14();
  //! アナログ数字が1，デジタル数字が5
  void block15();
  //! アナログ数字が1，デジタル数字が6
  void block16();
  //! アナログ数字が1，デジタル数字が7
  void block17();

  //! アナログ数字が2，デジタル数字が0
  void block20();
  //! アナログ数字が2，デジタル数字が1
  void block21();
  //! アナログ数字が2，デジタル数字が2
  void block22();
  //! アナログ数字が2，デジタル数字が3
  void block23();
  //! アナログ数字が2，デジタル数字が4
  void block24();
  //! アナログ数字が2，デジタル数字が5
  void block25();
  //! アナログ数字が2，デジタル数字が6
  void block26();
  //! アナログ数字が2，デジタル数字が7
  void block27();

  //! アナログ数字が3，デジタル数字が0
  void block30();
  //! アナログ数字が3，デジタル数字が1
  void block31();
  //! アナログ数字が3，デジタル数字が2
  void block32();
  //! アナログ数字が3，デジタル数字が3
  void block33();
  //! アナログ数字が3，デジタル数字が4
  void block34();
  //! アナログ数字が3，デジタル数字が5
  void block35();
  //! アナログ数字が3，デジタル数字が6
  void block36();
  //! アナログ数字が3，デジタル数字が7
  void block37();

  //! アナログ数字が4，デジタル数字が0
  void block40();
  //! アナログ数字が4，デジタル数字が1
  void block41();
  //! アナログ数字が4，デジタル数字が2
  void block42();
  //! アナログ数字が4，デジタル数字が3
  void block43();
  //! アナログ数字が4，デジタル数字が4
  void block44();
  //! アナログ数字が4，デジタル数字が5
  void block45();
  //! アナログ数字が4，デジタル数字が6
  void block46();
  //! アナログ数字が4，デジタル数字が7
  void block47();

  //! アナログ数字が5，デジタル数字が0
  void block50();
  //! アナログ数字が5，デジタル数字が1
  void block51();
  //! アナログ数字が5，デジタル数字が2
  void block52();
  //! アナログ数字が5，デジタル数字が3
  void block53();
  //! アナログ数字が5，デジタル数字が4
  void block54();
  //! アナログ数字が5，デジタル数字が5
  void block55();
  //! アナログ数字が5，デジタル数字が6
  void block56();
  //! アナログ数字が5，デジタル数字が7
  void block57();

  //! アナログ数字が6，デジタル数字が0
  void block60();
  //! アナログ数字が6，デジタル数字が1
  void block61();
  //! アナログ数字が6，デジタル数字が2
  void block62();
  //! アナログ数字が6，デジタル数字が3
  void block63();
  //! アナログ数字が6，デジタル数字が4
  void block64();
  //! アナログ数字が6，デジタル数字が5
  void block65();
  //! アナログ数字が6，デジタル数字が6
  void block66();
  //! アナログ数字が6，デジタル数字が7
  void block67();

  //! アナログ数字が7，デジタル数字が0
  void block70();
  //! アナログ数字が7，デジタル数字が1
  void block71();
  //! アナログ数字が7，デジタル数字が2
  void block72();
  //! アナログ数字が7，デジタル数字が3
  void block73();
  //! アナログ数字が7，デジタル数字が4
  void block74();
  //! アナログ数字が7，デジタル数字が5
  void block75();
  //! アナログ数字が7，デジタル数字が6
  void block76();
  //! アナログ数字が7，デジタル数字が7
  void block77();
};

#endif
