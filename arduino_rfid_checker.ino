#include <SPI.h>
#include <MFRC522.h>
#include <string.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);
  rfid.PCD_AntennaOff();
  rfid.PCD_AntennaOn();

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  static uint32_t rebootTimer = millis();
  if (millis() - rebootTimer >= 1000) {
    rebootTimer = millis();
    digitalWrite(RST_PIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(RST_PIN, LOW);
    rfid.PCD_Init();
  }

  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;
  String s,a = "";

  for (uint8_t i = 0; i < 4; i++) {
  a = String(rfid.uid.uidByte[i], HEX);
  a.toUpperCase();
  s += "0x" + a + ", ";
  }

  if(s == "0xFF, 0xFF, 0xFF, 0xFF, ")
    Serial.print("0");
  else if(s == "0x11, 0x11, 0x11, 011, " || s == "0x22, 0x22, 0x22, 0x22, ")
    Serial.print("1");
}
