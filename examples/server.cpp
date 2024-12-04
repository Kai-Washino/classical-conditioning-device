#include <M5Unified.h>
#include <WiFi.h>
#include <WebServer.h>
#include "wifi_config.h"

#define CYCLES 15

WebServer server(80);
bool isConditioning;

void handleRoot() {
  server.send(200, "text/plain", "M5StickC is ready to receive commands");
}

void handleBuzz() {
  // 音を鳴らす
  tone(GPIO_NUM_2, 600, 1000); // ピンに音を500ミリ秒間出力
  server.send(200, "text/plain", "Buzzing now");
}

void handleConditioning() {
  server.send(200, "text/plain", "条件づけ開始");
  isConditioning = true;
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.delay(500);  // Serial出力用のウエイト

  // 画面上にログを表示する
  M5.setLogDisplayIndex(0);
  M5.Display.setTextScroll(true);

  // WiFi接続の開始
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("Connecting to WiFi...");
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 1);
  M5.Lcd.print(WiFi.localIP());
  // サーバーのルートとハンドラを設定
  server.on("/", handleRoot);
  server.on("/buzz", handleBuzz);
  server.on("/conditioning", handleConditioning);

  // サーバーを開始
  server.begin();  

  isConditioning = false;
}

void loop() {
  // サーバーのリクエストを処理
  server.handleClient();
  if (isConditioning) {
    for (int i = 0; i < CYCLES; i++) {      
      tone(GPIO_NUM_2, 600, 1000);  // 600Hzを1000ms(1秒)      
      M5.Log.printf("Cycle: %d\n", i);
      delay(100000);      
    }
  }  
}
