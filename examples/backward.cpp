#include <M5Unified.h>

#define BEEP_INTERVAL 5000

int cycle;

void setup(void) {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.delay(500);  // Serial出力用のウエイト

  // 画面上にログを表示する
  M5.setLogDisplayIndex(0);
  M5.Display.setTextScroll(true);
  cycle = 0;
}

void loop(void) {
  M5.delay(1);
  M5.update();
  if(M5.BtnB.wasPressed()){
    // 真ん中のボタンを押して離した
    M5.Log.println("BtnB");
    unsigned long previousMillis = millis();

    while (true) {
      // 現在の時刻を取得
      unsigned long currentMillis = millis();

      // ビープ音を鳴らす条件をチェック
      if (currentMillis - previousMillis >= BEEP_INTERVAL) {
        // BEEP_INTERVALが経過したら音を鳴らす
        previousMillis = currentMillis;  // 次のビープ音のために時刻を更新
        tone(GPIO_NUM_2, 600, 1000);  // GPIO 26に600Hzのトーンを1000ms鳴らす
        M5.Log.printf("Beep: %d\n", cycle++); 
      }

      // ボタンの状態を更新
      M5.update();

      // BtnBがもう一度押されたらループを抜ける
      if (M5.BtnB.wasPressed()) {
        M5.Log.println("BtnB pressed again, exiting loop");
        break;  // whileループを抜ける
      }
    }    
    M5.Log.println("Done");
  }
}