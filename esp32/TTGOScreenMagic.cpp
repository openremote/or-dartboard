/**
 * TTGOScreenMagic: Manages the output onto the TTGO screen on the ESP32.
 * @file TTGOScreenMagic.cpp
 * @author Nik Robben
 * @version 1.0 10/1/2021
 */

#include "TTGOScreenMagic.h"

TFT_eSPI tft = TFT_eSPI(135, 240);

std::string TTGOScreenManager::primaryLine;

std::string TTGOScreenManager::secondaryLine;

/**
 * Initiliases the TFT-scren through SPI and sets basic configuration.
 */
void TTGOScreenManager::init(){
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
//    tft.setTextWrap(true, true);
    tft.setTextDatum(MC_DATUM);
};

/**
 * Draws text on the given line
 */
void TTGOScreenManager::drawText(uint8_t line, std::string text){

    if(line == PRIMARY_LINE) {
      TTGOScreenManager::primaryLine = text;
    } else {
      TTGOScreenManager::secondaryLine = text;
    }

    // Clear screen
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(4);
    tft.setCursor(0, 0);

    // Draw two strings
    tft.setTextColor(TFT_RED);
    tft.println(TTGOScreenManager::primaryLine.c_str());
//    tft.drawString(TTGOScreenManager::primaryLine.c_str(), tft.width() / 2, tft.height() / 2 - 40 );
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.print(TTGOScreenManager::secondaryLine.c_str());
//    tft.drawString(TTGOScreenManager::secondaryLine.c_str(), tft.width() / 2, tft.height() / 2 + 20);
};
