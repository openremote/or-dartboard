#include <TFT_eSPI.h>
#include <SPI.h>

#define PRIMARY_LINE 0
#define SECONDARY_LINE 1

class TTGOScreenManager { //constructor destructor maken?
  public:
    static void init();
    static void drawText(uint8_t line, std::string text);

  private:
    static std::string primaryLine;
    static std::string secondaryLine;
};
