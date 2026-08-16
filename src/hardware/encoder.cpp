#include "hardware/encoder.h"

#include "config.h"

#if defined(BOARD_CROWPANEL_146)

#include <Arduino.h>

namespace {
// Written only from the ISR; read/cleared from encoderPollRotation() with
// interrupts briefly disabled, so plain volatiles are sufficient here.
volatile int s_last_a = HIGH;
volatile int32_t s_accum = 0;

// Interrupt-driven: loop() can be busy for a while (HTTP fetch, full redraw),
// so polling digitalRead() from loop() alone misses fast rotations.
void IRAM_ATTR onEncoderAChange() {
  const int a = digitalRead(config::kEncoderAPin);
  if (a == s_last_a) {
    return;
  }
  if (s_last_a == HIGH && a == LOW) {
    s_accum += (digitalRead(config::kEncoderBPin) == HIGH) ? -1 : 1;
  }
  s_last_a = a;
}
}  // namespace

void encoderInit() {
  pinMode(config::kEncoderAPin, INPUT_PULLUP);
  pinMode(config::kEncoderBPin, INPUT_PULLUP);
  pinMode(config::kEncoderSwPin, INPUT_PULLUP);
  s_last_a = digitalRead(config::kEncoderAPin);
  attachInterrupt(digitalPinToInterrupt(static_cast<uint8_t>(config::kEncoderAPin)),
                  onEncoderAChange, CHANGE);
}

int encoderPollRotation() {
  noInterrupts();
  const int32_t accum = s_accum;
  s_accum = 0;
  interrupts();
  return static_cast<int>(accum);
}

#else

void encoderInit() {}

int encoderPollRotation() { return 0; }

#endif  // BOARD_CROWPANEL_146
