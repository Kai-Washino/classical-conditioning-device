#include <M5Unified.h>
#include <WiFi.h>
#include <WebServer.h>
#include "wifi_config.h"

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "M5StickC is ready to receive commands");
}

void handleBuzz() {
  // 音を鳴らす
  tone(GPIO_NUM_2, 600, 1000); // ピンに音を500ミリ秒間出力
  server.send(200, "text/plain", "Buzzing now");
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

  // サーバーを開始
  server.begin();  
}

void loop() {
  // サーバーのリクエストを処理
  server.handleClient();
}
