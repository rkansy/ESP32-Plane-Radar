#pragma once

/** GPIO + interrupt setup; call once early in setup(). No-op on boards without an encoder. */
void encoderInit();
/** Net detents moved since the last call (may be >1 if loop() was busy); 0 if none. */
int encoderPollRotation();
