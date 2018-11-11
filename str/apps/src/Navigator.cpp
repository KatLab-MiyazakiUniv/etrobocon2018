/**
 *  @file Navigator.cpp
 *  @brief 走行制御と回転制御を実行するクラス
 *  @author T.Miyaji
 */
#include "Navigator.h"

/**
 *  [Navigator::reset]
 *  @brief 座標とエンコーダの値を初期化する
 */
void Navigator::reset()
{
  walker.reset();
  odometry.reset();
}

/**
 *  [Navigator::spin]
 *  @brief 指定した角度まで走行体を回転させる
 *  @param angle     回転角度 [deg]
 *  @param clockwise 時計回りに回転させるか(デフォルトは、反時計回り)
 *  @param pwm       モータパワー
 */
void Navigator::spin(float angle, bool clockwise, std::int8_t pwm)
{
  // 測定角度の初期化
  reset();
  angle = (angle < 0) ? -angle : angle;

  while(odometry.getRotationAngle(walker.get_count_L(), walker.get_count_R()) < angle) {
    // 時計回りのときは-pwmを渡す
    walker.run(0, clockwise ? -pwm : pwm);
    controller.tslpTsk(4);
  }

  // 回転停止
  walker.run(0, 0);
  reset();
}

/**
 *  [Navigator::move]
 *  @brief 指定した距離まで走行体を移動させる
 *  @param distance 距離 [mm]
 *  @param pwm      モータパワー
 */
void Navigator::move(float distance, std::int8_t pwm)
{
  // 測定距離の初期化
  reset();
  float radius = 0.0f;

  while(radius < distance) {
    walker.run(pwm, 0);
    odometry.update(walker.get_count_L(), walker.get_count_R());
    radius = odometry.getCoordinate().radius;
    controller.tslpTsk(4);
  }

  // 移動停止
  walker.run(0, 0);
  reset();
}

/**
 *  [Navigator::back]
 *  @brief 指定した距離まで走行体を後退させる
 *  @param distance 距離 [mm]
 *  @param pwm      モータパワー
 */
void Navigator::back(float distance, std::int8_t pwm)
{
  // 測定距離の初期化
  reset();
  float radius = 0.0f;

  while(radius < distance) {
    walker.run(-pwm, 0);
    odometry.update(walker.get_count_L(), walker.get_count_R());
    radius = -odometry.getCoordinate().radius;
    controller.tslpTsk(4);
  }
}

/**
 *  [Navigator::moveWhileDetecting]
 *  @param distance 距離 [mm]
 *  @param black    黒色の輝度値
 *  @param pwm      モータパワー
 */
void Navigator::moveWhileDetecting(float distance, std::int16_t black, std::int8_t pwm)
{
  // 測定距離の初期化
  reset();
  controller.ledSetColorGreen();
  while(odometry.update(walker.get_count_L(), walker.get_count_R()).radius < distance) {
    walker.run(pwm, 0);
    if(binarization(black) == false)
      controller.ledSetColorOrange();
    else
      controller.ledSetColorGreen();
    controller.tslpTsk(4);
  }

  walker.run(0, 0);
  reset();
}

/**
 *  [Navigator::getBrightness]
 *  @brief 光センサの値を所得する
 *  @return 光センサの値
 */
std::int16_t Navigator::getBrightness()
{
  return controller.getBrightness();
}

/**
 *  [Navigator::getNearbyBrightness]
 *  @brief 現在位置の周辺における光センサ値を取得する
 *  @param  distance 距離 [mm]
 *  @return          光センサの値
 */
std::int8_t Navigator::getNearbyBrightness(float distance)
{
  auto center = getBrightness();

  // distanceだけ前に移動した点のセンサ値を取る
  move(distance, 10);
  auto front_value = getBrightness();
  back(distance, 10);

  // distanceだけ後ろに移動した点のセンサ値を取る
  back(distance, 10);
  auto back_value = getBrightness();
  move(distance, 10);

  return std::min({ front_value, center, back_value });
}

/**
 *  [Navigator::binarization]
 *  @brief 2値化処理を実行する
 *  @param  black 黒色の輝度値
 *  @return       黒のときfalse, 白のときtrue
 */
bool Navigator::binarization(std::int16_t black)
{
  auto brightness = getBrightness();
  return (brightness < black) ? false : true;
}

/**
 *  [Navigator::moveOnLine]
 *  @brief 指定した距離だけライントレースする
 *  @param distance 距離 [mm]
 *  @param target   黒色と白色の境界の輝度値
 *  @param pwm      モータパワー
 */
void Navigator::moveOnLine(float distance, std::int16_t target, std::int8_t pwm)
{
  // 測定距離の初期化
  reset();
  float radius = 0.0f;

  // ライントレースで用いるPID値のセット
  line_tracer.speedControl.setPid(2.0, 0.8, 0.1, pwm);
  line_tracer.turnControl.setPid(1.1, 0.1, 0.2, target);

  while(radius < distance) {
    odometry.update(walker.get_count_L(), walker.get_count_R());
    radius = odometry.getCoordinate().radius;
    line_tracer.runLine(walker.get_count_L(), walker.get_count_R(), getBrightness());
    if(line_tracer.getForward() < 0)
      walker.run(0, 0);
    else
      walker.run(line_tracer.getForward(), line_tracer.getTurn());
    controller.tslpTsk(4);
  }

  walker.run(0, 0);
  reset();
}

void Navigator::moveToColor(float distance, std::int16_t target_brightness, Color target_color,
                            std::int8_t speed)
{
  reset();  // 距離の初期化
  float radius = 0.0f;
  // ライントレースで用いるPID値のセット
  line_tracer.speedControl.setPid(2.0, 0.8, 0.1, speed);
  line_tracer.turnControl.setPid(1.1, 0.1, 0.2, target_brightness);
  // 距離を超過するか目的の色を見つけるまでループ
  while(radius < distance) {
    color = distinguisher.getColor();
    odometry.update(walker.get_count_L(), walker.get_count_R());
    radius = odometry.getCoordinate().radius;
    line_tracer.runLine(walker.get_count_L(), walker.get_count_R(), getBrightness());
    walker.run(line_tracer.getForward(), line_tracer.getTurn());
    controller.printDisplay(5, "color: %d", color);
    if(color == target_color) {
      controller.speakerPlayTone(NOTE_A5, 300);
      break;
    }
    controller.tslpTsk(4);  // 4msec周期
  }

  color = Color::NONE;
  walker.run(0, 0);
  reset();
}
