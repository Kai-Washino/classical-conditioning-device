#include <M5Unified.h>

#define ODOR_PIN 0

void setup(void) {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.delay(500);  // Serial出力用のウエイト

  // 画面上にログを表示する
  M5.setLogDisplayIndex(0);
  M5.Display.setTextScroll(true);

  pinMode(ODOR_PIN, OUTPUT);
}

void loop(void) {
  M5.delay(1);
  M5.update();

  if (M5.BtnA.wasPressed()) {
    // 真ん中のボタンを押して離した
    digitalWrite(ODOR_PIN, LOW);
    tone(GPIO_NUM_2, 600, 1000);  // 600Hzを1000ms(1秒)
    M5.Log.println("BtnA TONE(600Hz)");
    delay(1000);
    digitalWrite(ODOR_PIN, HIGH);
    delay(30000);
    digitalWrite(ODOR_PIN, LOW);
  }
}