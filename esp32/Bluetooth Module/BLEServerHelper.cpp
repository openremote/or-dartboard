#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <iostream>
#include "BLEServerHelper.h"
#include "BLEMyCallbacks.h"
#include <Arduino.h>
#include "TTGOScreenMagic.h"


void DartboardBLEServer::init(std::string name)
{
  BLEDevice::init("Dartboard 1");
  m_pServer = BLEDevice::createServer();
  m_pServer->setCallbacks(new MyBLEServerCallbacks());

  m_pService = m_pServer->createService(SERVICE_UUID);

  m_pHitCharacteristic = m_pService->createCharacteristic(
                           HIT_CHAR_UUID,
                           BLECharacteristic::PROPERTY_READ |
                           BLECharacteristic::PROPERTY_NOTIFY);
  m_pPrimaryLineCharacteristic = m_pService->createCharacteristic(
                                   PRIMARY_LINE_CHAR_UUID,  
                                   BLECharacteristic::PROPERTY_WRITE);
  m_pSecondaryLineCharacteristic = m_pService->createCharacteristic(
                                     SECONDARY_LINE_CHAR_UUID,
                                     BLECharacteristic::PROPERTY_WRITE);
  m_pEnableCharacteristic = m_pService->createCharacteristic(
                              ENABLE_CHAR_UUID,
                              BLECharacteristic::PROPERTY_WRITE);

  m_pHitCharacteristic->addDescriptor(new BLE2902());

  MyBLECharacteristicCallback* callbacks = new MyBLECharacteristicCallback();

  m_pHitCharacteristic->setCallbacks(callbacks);
  m_pPrimaryLineCharacteristic->setCallbacks(callbacks);
  m_pSecondaryLineCharacteristic->setCallbacks(callbacks);
  m_pEnableCharacteristic->setCallbacks(callbacks);
};

void DartboardBLEServer::startAdvertising()
{
  m_pService->start();
  m_pAdvertising = BLEDevice::getAdvertising();
  m_pAdvertising->addServiceUUID(SERVICE_UUID);
  m_pAdvertising->setScanResponse(true);
  m_pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  m_pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
};

void DartboardBLEServer::setHits(uint8_t *hits, uint8_t len)
{
  // 2 brackets, amount of hits * 2 (max two digits per hit), plus len amount of commas - 1
  char value[2 + (len * 2) + len - 1];
  int length = 0;

  // Starting bracket
  length += sprintf(value + length, "[");

  for (int i = 0; i < len; i++) {
    length += sprintf(value + length, "%d", (char *)hits[i]);
    if (i != len - 1) {
      length += sprintf(value + length, ",");
    }
  }
  length += sprintf(value + length, "]");

  // Set value of hits to characteristic & notify
  m_pHitCharacteristic->setValue(value);
  m_pHitCharacteristic->notify(true);
}
