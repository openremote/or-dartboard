#include <stdio.h>
#include <stdlib.h>
#include <Wire.h>
#include "BLEServerHelper.h"
#include "TTGOScreenMagic.h"
#include "MatrixScanner.h"

uint8_t matrixPoints[8][  8] = {
  // 0,     1,        2,      3,       4,       5,       6,       7
  {(19 * 2), (19 * 1), (19 * 3), (3 * 3), (3 * 1), (3 * 2), (0 * 0), (0 * 0)}, // 0
  {(7 * 2), (7 * 1), (7 * 3), (17 * 3), (17 * 1), (17 * 2), (18 * 2), (1 * 2)}, // 1
  {(16 * 2), (16 * 1), (16 * 3), (2 * 3), (2 * 1), (2 * 2), (5 * 2), (20 * 2)}, // 2
  {(8 * 2), (8 * 1), (8 * 3), (15 * 3), (15 * 1), (15 * 2), (5 * 1), (20 * 1)}, // 3
  {(11 * 2), (11 * 1), (11 * 3), (10 * 3), (10 * 1), (10 * 2), (5 * 3), (20 * 3)}, // 4
  {(14 * 2), (14 * 1), (14 * 3), (6 * 3), (6 * 1), (6 * 2), (18 * 3), (1 * 3)}, // 5
  {(9 * 2), (9 * 1), (9 * 3), (13 * 2), (13 * 1), (13 * 2), (25 * 1), (50 * 1)}, // 6
  {(12 * 2), (12 * 1), (12 * 3), (4 * 3), (4 * 1), (4 * 2), (18 * 1), (1 * 1)} // 7
};

// Amount of throws before we override the first throw
#define MAX_THROWS 3

// Current known hits
uint8_t hits[MAX_THROWS];

// Amount of darts thrown
int throws = 0;

// The bluetooth server
DartboardBLEServer* server = new DartboardBLEServer();

void setup() {
  // Initialize serial
  Serial.begin(115200);

  Serial.println("Configuring MCP23017");
  MatrixScanner::init();

  Serial.println("Start bluetooth server");

  // Initialize bluetooth & start advertising
  server->init("Dartboard 2");
  server->startAdvertising();
  server->setHits(hits, 0);

  // Write initial screen
  TTGOScreenManager::init();
  TTGOScreenManager::drawText(PRIMARY_LINE, "BLESSED\nv0.1");
  TTGOScreenManager::drawText(SECONDARY_LINE, "Connect to\nget started");
}

void loop() {
  struct Hit hit;

  if (MatrixScanner::scan(hit)) {
    // Lookup points by row & column indexes
    uint8_t points = matrixPoints[hit.row][hit.col];

    // Get hit index by wrapping throws by the amount of throws we register
    uint8_t hitIndex = throws % MAX_THROWS;

    // Set hit at current index to points
    hits[hitIndex] = points;

    // Count throw
    throws++;

    // Update bluetooth hits by sending hits plus the amount of throws filled
    server->setHits((uint8_t *)hits, hitIndex + 1);

    // Delay to prevent registering a hit twice.
    delay(500);
  }
}
