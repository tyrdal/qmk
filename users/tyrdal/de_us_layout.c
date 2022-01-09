#include "de_us_layout.h"
#include "action.h"
#include "action_util.h"
#include "config.h"
#include "debug.h"
#include "keycode.h"
#include "keycode_legacy.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "timer.h"
#include "xprintf.h"

#ifdef __clang__
#    pragma clang diagnostic ignored "-Wunknown-attributes"  // clangd does not know PROGMEM
#endif

uint8_t def_layer = 0;
// TODO check if this actually works
__attribute__((constructor)) void init_def_layer(void) {
    def_layer = eeconfig_read_default_layer();
#ifdef CONSOLE_ENABLE
    xprintf("%s %d", "Initial default layer: ", def_layer);
#endif
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t* record) { return true; }

#ifdef GERMAN_ENABLE
#    define MAP_CUSTOM_KEYCODE(pressed, shift_pressed, normal, shifted)        \
        {                                                                      \
            static uint16_t kc;                                                \
            send_custom_keycode(&kc, pressed, shift_pressed, normal, shifted); \
        }

inline void send_custom_keycode(uint16_t* kc, bool pressed, bool shift_pressed, uint16_t normal, uint16_t shifted) {
    if (pressed) {
        if (shift_pressed) {
            del_mods(MOD_MASK_SHIFT);
            *kc = shifted;
        } else {
            *kc = normal;
        }
        register_code16(*kc);
        if (shift_pressed) {
            register_code(KC_LSHIFT);
        }
    } else {
        unregister_code16(*kc);
    }
}

#    define SPACE_CADET_CODE(x)                             \
        {                                                   \
            static uint16_t timer;                          \
            if (record->event.pressed) {                    \
                timer = timer_read();                       \
                register_code(KC_LEFT_SHIFT);               \
            } else {                                        \
                unregister_code(KC_LEFT_SHIFT);             \
                if (timer_elapsed(timer) <= TAPPING_TERM) { \
                    tap_code16(x);                          \
                }                                           \
            }                                               \
        }
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    bool is_shift_pressed = get_mods() & MOD_MASK_SHIFT;
    bool pressed          = record->event.pressed;

    switch (keycode) {
            // leader based key codes
        case CU_FIRST:
            if (record->event.pressed) {
                SEND_STRING("René");
            }
            break;
        case CU_LAST:
            if (record->event.pressed) {
                SEND_STRING("Möhring");
            }
            break;
        case CU_MAIL:
            if (record->event.pressed) {
                SEND_STRING("rene_moehring@gmx.de");
            }
            break;
        case CU_AE:
            if (record->event.pressed) {
                send_string(is_shift_pressed ? "Ä" : "ä");
            }
            break;
        case CU_UE:
            if (record->event.pressed) {
                send_string(is_shift_pressed ? "Ü" : "ü");
            }
            break;
        case CU_OE:
            if (record->event.pressed) {
                send_string(is_shift_pressed ? "Ö" : "ö");
            }
            break;
        case CU_EACUT:
            if (record->event.pressed) {
                send_string(is_shift_pressed ? "É" : "é");
            }
            break;
        case CU_SZ:
            if (record->event.pressed) {
                SEND_STRING("ß");
            }
            break;
        case CU_EURO:
            if (record->event.pressed) {
                SEND_STRING("€");
            }
            break;
        case CU_DEG:
            if (record->event.pressed) {
                SEND_STRING("°");
            }
            break;

#ifdef GERMAN_ENABLE
        case CU_2:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_2, RALT(KC_Q));
            break;
        case CU_3:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_3, KC_NONUS_HASH);
            break;
        case CU_6:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_6, CU_CIRC);
            break;
        case CU_7:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_7, S(KC_6));
            break;
        case CU_8:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_8, S(KC_RIGHT_BRACKET));
            break;
        case CU_9:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_9, S(KC_8));
            break;
        case CU_0:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_0, S(KC_9));
            break;
        case CU_COMM:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_COMMA, KC_NONUS_BACKSLASH);
            break;
        case CU_DOT:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_DOT, S(KC_NONUS_BACKSLASH));
            break;
        case CU_SLSH:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_KP_SLASH, S(KC_MINUS));
            break;
        case CU_SCLN:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_COMMA), S(KC_DOT));
            break;
        case CU_QUOT:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_NONUS_HASH), S(KC_2));
            break;
        case CU_GRV:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, CU_GRV_S, S(KC_RIGHT_BRACKET));
            break;
        case CU_EQL:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_0), S(KC_KP_PLUS));
            break;
        case CU_LBRC:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, RALT(KC_8), RALT(KC_7));
            break;
        case CU_RBRC:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, RALT(KC_9), RALT(KC_0));
            break;
        case CU_BSLS:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, RALT(KC_MINUS), RALT(KC_NONUS_BACKSLASH));
            break;
        // Custom Symbolics
        case CU_EXLM:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_1), S(KC_1));
            break;
        case CU_HASH:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_NONUS_HASH, KC_NONUS_HASH);
            break;
        case CU_TILD:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, RALT(KC_RIGHT_BRACKET), RALT(KC_RIGHT_BRACKET));
            break;
        case CU_PERC:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_5), S(KC_5));
            break;
        case CU_CIRC:  // DEAD
            SEND_STRING("^");
            break;
        case CU_AMPR:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_6), S(KC_6));
            break;
        case CU_PIPE:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, RALT(KC_NONUS_BACKSLASH), RALT(KC_NONUS_BACKSLASH));
            break;
        case CU_DLR:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_4), S(KC_4));
            break;
        case CU_DQUO:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_2), S(KC_2));
            break;
        case CU_AT:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, RALT(KC_Q), RALT(KC_Q));
            break;
        case CU_UNDS:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_SLASH), S(KC_SLASH));
            break;
        case CU_LT:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_NONUS_BACKSLASH, KC_NONUS_BACKSLASH);
            break;
        case CU_GT:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_NONUS_BACKSLASH), S(KC_NONUS_BACKSLASH));
            break;
        case CU_COLN:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_DOT), S(KC_DOT));
            break;
        case CU_QUES:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_MINUS), S(KC_MINUS));
            break;
        case CU_GRV_S:  // DEAD
            SEND_STRING("`");
            break;
        case CU_SCLN_S:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_COMMA), S(KC_COMMA));
            break;
        case CU_DOT_S:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_DOT, KC_DOT);
            break;
        case CU_COM_S:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_COMMA, KC_COMMA);
            break;
        case CU_PO:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_8), S(KC_8));
            break;
        case CU_PC:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, S(KC_9), S(KC_9));
            break;
        // space cadet shift
        case CU_LSPO:
            SPACE_CADET_CODE(S(KC_8));
            break;
        case CU_RSPC:
            SPACE_CADET_CODE(S(KC_9));
            break;
        // numpad  - arrow keys when shifted
        case CU_P4:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_KP_4, KC_LEFT);
            break;
        case CU_P5:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_KP_5, KC_DOWN);
            break;
        case CU_P6:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_KP_6, KC_RIGHT);
            break;
        case CU_P8:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, KC_KP_8, KC_UP);
            break;
#endif
    };
    return process_record_keymap(keycode, record);
}
