#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Min & max pin ids of port A pins
#define PORTA_MIN 0
#define PORTA_MAX 7

// Min & max pin ids of port B pins
#define PORTB_MIN 8
#define PORTB_MAX 15

// Port A & port B
#define REGISTER_A 0
#define REGISTER_B 1

struct Hit {
  uint8_t row, col;
};


class MatrixScanner { //constructor destructor maken?
  public:
    static void init();
    static bool scan(Hit& out);
    static void setScanEnabled(bool enabled);

  private:
    static bool shouldScan;
};
