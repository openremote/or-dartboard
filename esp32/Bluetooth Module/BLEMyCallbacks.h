#include <BLECharacteristic.h>
#include <BLEServer.h>

class MyBLECharacteristicCallback : public BLECharacteristicCallbacks{
public:
        virtual void onWrite(BLECharacteristic *pCharacteristic);
        // virtual void onNotify(BLECharacteristic* pCharacteristic);

};

class MyBLEServerCallbacks : public BLEServerCallbacks{
public:
        virtual void onConnect(BLEServer* pServer);
        virtual void onDisconnect(BLEServer* pServer);
};
