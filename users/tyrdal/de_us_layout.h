#pragma once

#include "quantum.h"

enum userspace_custom_keycodes {
    CU_FIRST = SAFE_RANGE,  // start of the customizable number SAFE_RANGE - First name
    CU_LAST,                // Last name
    CU_MAIL,                // email address

#ifdef GERMAN_ENABLE
    CU_COMM,    // , | <
    CU_DOT,     // . | >
    CU_SLSH,    // / | ?
    CU_SCLN,    // ; | :
    CU_GRV,     // ` | ~
    CU_2,       // 2 | @
    CU_3,       // 3 | #
    CU_6,       // 6 | ^
    CU_7,       // 7 | &
    CU_8,       // 8 | *
    CU_9,       // 9 | (
    CU_0,       // 0 | )
    CU_EQL,     // = | +
    CU_LBRC,    // [ | {
    CU_RBRC,    // ] | }
    CU_LCURL,   // { | [
    CU_RCURL,   // } | ]
    CU_BSLS,    // \ | |
    CU_QUOT,    // ' | "
    CU_DQUO,    // " | ' -> inverse of us since i need " more often
    CU_DSLSH,   // / | \ -> slash and backslash
    CU_EXLM,    // !
    CU_HASH,    // #
    CU_TILD,    // ~
    CU_PERC,    // %
    CU_CIRC,    // ^
    CU_AMPR,    // &
    CU_PIPE,    // |
    CU_DLR,     // $
    CU_DQUO_S,  // "
    CU_AT,      // @
    CU_UNDS,    // _
    CU_LT,      // <
    CU_GT,      // >
    CU_COLN,    // :
    CU_QUES,    // ?
    CU_GRV_S,   // `
    CU_SCLN_S,  // ;
    CU_LP_S,    // (
    CU_RP_S,    // )
    CU_LCL_S,   // {
    CU_RCL_S,   // ]
    CU_LBC_S,   // [
    CU_RBC_S,   // ]
    CU_DOT_S,   // .
    CU_COM_S,   // ,
    CU_PARAG,   // §
    CU_P4,      // numpad 4 | left
    CU_P5,      // numpad 5 | down
    CU_P6,      // numpad 6 | right
    CU_P8,      // numpad 8 | up
#endif
    NEW_SAFE_RANGE
};

#ifdef GERMAN_ENABLE

// Those are identical in de and us and are only provided to have a consistent look in the keymap
#    define CU_1 KC_1
#    define CU_4 KC_4
#    define CU_5 KC_5
#    define CU_MINS KC_SLSH
#    define CU_SZ KC_MINUS
#    define CU_EURO ALGR(KC_E)
#    define CU_DEG S(KC_GRAVE)

void send_custom_keycode(uint16_t* kc, bool pressed, bool shift_pressed, uint16_t normal, uint16_t shifted);
#endif

extern uint8_t def_layer;  // current default layer
