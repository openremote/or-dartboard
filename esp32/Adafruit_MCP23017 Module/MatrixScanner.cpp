#include "MatrixScanner.h"
#include "Adafruit_MCP23017_blessed.h"

bool MatrixScanner::shouldScan;

Adafruit_MCP23017 mcp;

/**
   Initiliases the Matrix scanner
*/
void MatrixScanner::init() {
  // Initialize MCP23017
  Wire.setClock(100000); // set i2c frequency to 1mHz (works for us)
  mcp.begin(&Wire); // use default address 0

  // Setup port B as inputs for columns
  for (int i = PORTB_MIN; i <= PORTB_MAX; i++) {
    mcp.pinMode(i, INPUT);
    mcp.pullUp(i, HIGH);
  }

  for (int i = PORTA_MIN; i <= PORTA_MAX; i++) {
    mcp.pinMode(i, OUTPUT);
    mcp.digitalWrite(i, HIGH);
  }
};

void MatrixScanner::setScanEnabled(bool enabled) {
  MatrixScanner::shouldScan = enabled;
}


bool MatrixScanner::scan(Hit& out) {
  if (!MatrixScanner::shouldScan) {
    return false;
  }
  
  // Loop over all rows
  for (int a = 0; a < 8; a++) {

    // Write byte with 1 bit low, the row we want to test
    // Select the a'th bit (by shifting), invert using xor because only that bit should be low
    // 0b1 => 0b00010000 => 0b11101111
    mcp.writeGPIO(REGISTER_A, 0b1 << a ^ 0xFF);

    // Read back from the column (REGISTER_B) input
    uint8_t data = mcp.readGPIO(REGISTER_B);

    // If the data was not 0xFF, it means one of the colums was pulled low
    if (data != 0xFF) {

      // Invert to turn the single low bit into a single high bit
      // 0b11111101 => 0b00000010
      uint8_t value = data ^ 0xFF;

      // Efficient way to retrieve which bit (which column) is set (which means it was pulled low)
      // https://stackoverflow.com/questions/47319974/most-efficient-way-to-find-the-index-of-the-only-1-bit-in-a-char-variable-in
      // 0b00000100 => 6
      uint8_t b = (0xFAC688 / value / value / value) & 0x7;

      struct Hit hit;
      hit.row = a;
      hit.col = b;
      out = hit;
      return true;
    }
  }

  return false;
}
