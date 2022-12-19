#include <esp32_can.h>
void setup() {
  Serial.begin(115200);

  Serial.println("Initializing ...");

  CAN0.begin(500000);

  Serial.println("Ready ...!");
  CAN_FRAME txFrame;  // 送信用のフレーム。以下その設定
  txFrame.rtr = 0;
  txFrame.id = 0x123;
  txFrame.extended = false;
  txFrame.length = 4;
  txFrame.data.uint8[0] = 0x10;
  txFrame.data.uint8[1] = 0x1A;
  txFrame.data.uint8[2] = 0xFF;
  txFrame.data.uint8[3] = 0x5D;
  CAN0.sendFrame(txFrame);  // 送信処理
}

void loop() {
  //Serial.println("loop now");
  
  byte i = 0;
  CAN_FRAME message;
   
  if (CAN0.read(message)) {

    // 受信するごとにリターンメッセージを送信する
    // メッセージ ID とデータバイトを単純に増やし、適切な送信であることを示す
    // 注意：これはネットワーク上のトラフィックを2倍にします（上記のフィルタを通過することが条件です）
    /*
    message.id++;
    for (i = 0; i < message.length; i++) {
      message.data.uint8[i]++;
    }
    */
    //CAN.sendFrame(message);
    
  //or, just plain send traffic periodically //または、定期的にトラフィックを送信する
  
    delayMicroseconds(200);
    message.id++;
    message.length = 8;
    for(i=0;i<message.length;i++) {
     message.data.uint8[i]++;
    }
    CAN0.sendFrame(message);
  
}
