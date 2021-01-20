#include "BLEMyCallbacks.h"
// #include <BLELedLight.h>
#include "TTGOScreenMagic.h"
#include "BLEServerHelper.h"
#include "MatrixScanner.h"

void MyBLECharacteristicCallback::onWrite(BLECharacteristic *pCharacteristic) {
  std::string value = pCharacteristic->getValue();

  std::string uuid = pCharacteristic->getUUID().toString();

  if (uuid == ENABLE_CHAR_UUID) {
    if(value == "true") {
      MatrixScanner::setScanEnabled(true);
    } else if (value == "false") {
      MatrixScanner::setScanEnabled(false);
    } else {
      Serial.print("Unsupported enable value: ");
      Serial.println(value.c_str());
    }
  } else if (uuid == PRIMARY_LINE_CHAR_UUID) {
    TTGOScreenManager::drawText(PRIMARY_LINE, value);
  } else if (uuid == SECONDARY_LINE_CHAR_UUID) {
    TTGOScreenManager::drawText(SECONDARY_LINE, value);
  } else {
    Serial.println("Unknown write");
  }

};

// void MyBLECharacteristicCallback::onNotify(BLECharacteristic *pCharacteristic){
//     pCharacteristic->notify(true);
// };

void MyBLEServerCallbacks::onConnect(BLEServer* pServer) {
  Serial.println("Connected via Bluetooth");
  TTGOScreenManager::drawText(PRIMARY_LINE, "Connected");
  TTGOScreenManager::drawText(SECONDARY_LINE, "Waiting for game to start...");
};

void MyBLEServerCallbacks::onDisconnect(BLEServer* pServer) {
  Serial.println("Disconnected from Bluetooth");
  TTGOScreenManager::drawText(PRIMARY_LINE, "Disconnected");
  TTGOScreenManager::drawText(SECONDARY_LINE, "Connect to\nget started");
};
