#include <M5Unified.h>

#define CYCLES 15

void setup(void) {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.delay(500);  // Serial出力用のウエイト

  // 画面上にログを表示する
  M5.setLogDisplayIndex(0);
  M5.Display.setTextScroll(true);
}

void loop(void) {
  M5.delay(1);
  M5.update();
  if (M5.BtnB.wasPressed()) {
    // 右側のボタンを押して離した        
    tone(GPIO_NUM_2, 600, 1000);  // 600Hzを1000ms(1秒)
    M5.Log.println("BtnB TONE(600Hz)");   
  }
  if(M5.BtnA.wasPressed()){
    // 真ん中のボタンを押して離した
    M5.Log.println("BtnA");
    for (int i = 0; i < CYCLES; i++) {      
      tone(GPIO_NUM_2, 600, 1000);  // 600Hzを1000ms(1秒)      
      delay(100000);
      M5.Log.printf("Cycle: %d\n", i);
    }
    M5.Log.println("Done");
  }
}