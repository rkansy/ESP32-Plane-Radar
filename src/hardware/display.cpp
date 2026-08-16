#include "hardware/display.h"

#include "config.h"
#include "hardware/display_font.h"

LGFX tft;

#if defined(BOARD_CROWPANEL_146)
namespace {
/** Reset the panel and power up its rails/backlight before LovyanGFX init. */
void boardPowerInit() {
  pinMode(config::kDisplayPinRst, OUTPUT);
  digitalWrite(config::kDisplayPinRst, HIGH);
  delay(10);
  digitalWrite(config::kDisplayPinRst, LOW);
  delay(10);
  digitalWrite(config::kDisplayPinRst, HIGH);

  pinMode(config::kDisplayPwr1Pin, OUTPUT);
  pinMode(config::kDisplayPwr2Pin, OUTPUT);
  digitalWrite(config::kDisplayPwr1Pin, HIGH);
  digitalWrite(config::kDisplayPwr2Pin, HIGH);

  pinMode(config::kDisplayBacklightPin, OUTPUT);
  digitalWrite(config::kDisplayBacklightPin, HIGH);
}
}  // namespace
#endif

void displayInit() {
#if defined(BOARD_CROWPANEL_146)
  boardPowerInit();
#endif
  tft.init();
#if defined(BOARD_CROWPANEL_146)
  tft.initDMA();
#endif
  tft.setRotation(0);
  tft.setBrightness(255);
  tft.setTextWrap(false);
  displayFontInit();
}
