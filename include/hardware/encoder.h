#pragma once

/** GPIO setup; call once early in setup(). No-op on boards without an encoder. */
void encoderInit();
/** Detents moved since the last call: -1, 0, or +1 (call once per loop iteration). */
int encoderPollRotation();
