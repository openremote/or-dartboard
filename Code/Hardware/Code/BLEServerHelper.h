#include <BLECharacteristic.h>
#include<BLEAdvertising.h>
#include<BLEServer.h>
#include <BLEService.h>
#include <esp_gatts_api.h>

#define SERVICE_UUID "425c30ce-755e-46cd-9695-db70cddf2476"

#define HIT_CHAR_UUID "b09add57-76ea-448c-a722-780cc9120044"
#define PRIMARY_LINE_CHAR_UUID "339da5bb-3672-4dbf-b215-7dfbc13035bf"
#define SECONDARY_LINE_CHAR_UUID "8951b238-c390-4501-8b6d-593a6e1610d4"
#define ENABLE_CHAR_UUID "d5d1aac6-6453-4304-b02e-907c29d70ce9"

class DartboardBLEServer{
public:
        void init(std::string name);
        //constructor destructor maken??
        void startAdvertising();    
        void setHits(uint8_t *hits, uint8_t len);

private:
        BLEServer* m_pServer;
        BLEService* m_pService;
        BLEAdvertising* m_pAdvertising;
        BLECharacteristic* m_pHitCharacteristic;
        BLECharacteristic* m_pPrimaryLineCharacteristic;
        BLECharacteristic* m_pSecondaryLineCharacteristic;
        BLECharacteristic* m_pEnableCharacteristic;
};
