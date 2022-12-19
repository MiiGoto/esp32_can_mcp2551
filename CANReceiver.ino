#include <esp32_can.h>

// 受け取ったものの表示処理関数
void printFrame(CAN_FRAME *message)
{
  Serial.print(message->id, HEX);
  if (message->extended) Serial.print(" X ");
  else Serial.print(" S ");   
  Serial.print(message->length, DEC);
  for (int i = 0; i < message->length; i++) {
    Serial.print(message->data.byte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

// CANメッセージ受け取り時のコールバック関数
void gotHundred(CAN_FRAME *frame)
{
  Serial.print("Got special frame!  ");
  printFrame(frame);
}

void setup() {
  Serial.begin(115200);

  Serial.println("Initializing ...");

  CAN0.begin(500000);

  Serial.println("Ready ...!");

  CAN0.watchFor(0x100, 0xF00); //setup a special filter
  CAN0.watchFor(); //then let everything else through anyway
  CAN0.setCallback(0, gotHundred); //callback on that first special filter
}

void loop() {
  byte i = 0;
  CAN_FRAME message;
  if (CAN0.read(message)) {

    printFrame(&message);
  }
}
