#pragma once

#include "quantum.h"
#include "keymap_german.h"
#include "quantum_keycodes.h"

enum userspace_custom_keycodes {
    CU_DUMMY = SAFE_RANGE,  // start of the customizable number SAFE_RANGE

#ifdef GERMAN_ENABLE
    CU_LSFT,  // LSFT | (
    CU_RSFT,  // LSFT | )
    CU_COMM,  // , | <
    CU_DOT,   // . | >
    CU_SLSH,  // / | ?
    CU_SCLN,  // ; | :
    CU_QUOT,  // ' | Enable deadkey layer
    CU_GRV,   // ` | ~
    CU_CIRC,  // ^
    CU_2,     // 2 | @
    CU_3,     // 3 | #
    CU_6,     // 6 | ^
    CU_7,     // 7 | &
    CU_8,     // 8 | *
    CU_9,     // 9 | (
    CU_0,     // 0 | )
    CU_EQL,   // = | +
    CU_LBRC,  // [ | {
    CU_RBRC,  // ] | }
    CU_BSLS,  // \ | |
    CU_Z,     // Z | Y in conjunction with ctrl
    CU_Y,     // Y | Z in conjunction wiht ctrl
    CU_ESCT,  // Toggle escape of grv and circ on/off
#endif
};
