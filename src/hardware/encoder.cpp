#include "hardware/encoder.h"

#include "config.h"

#if defined(BOARD_CROWPANEL_146)

#include <Arduino.h>

namespace {
int s_last_a = HIGH;
unsigned long s_last_read_ms = 0;
}  // namespace

void encoderInit() {
  pinMode(config::kEncoderAPin, INPUT_PULLUP);
  pinMode(config::kEncoderBPin, INPUT_PULLUP);
  pinMode(config::kEncoderSwPin, INPUT_PULLUP);
  s_last_a = digitalRead(config::kEncoderAPin);
}

int encoderPollRotation() {
  const unsigned long now = millis();
  if (now - s_last_read_ms < config::kEncoderDebounceMs) {
    return 0;
  }

  const int a = digitalRead(config::kEncoderAPin);
  if (a == s_last_a) {
    return 0;
  }
  s_last_read_ms = now;

  // Quadrature: on A's falling edge, B's level gives direction.
  int delta = 0;
  if (s_last_a == HIGH && a == LOW) {
    delta = (digitalRead(config::kEncoderBPin) == HIGH) ? -1 : 1;
  }
  s_last_a = a;
  return delta;
}

#else

void encoderInit() {}

int encoderPollRotation() { return 0; }

#endif  // BOARD_CROWPANEL_146
