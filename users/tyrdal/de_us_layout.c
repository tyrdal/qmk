#include "de_us_layout.h"
#include "action.h"
#include "debug.h"
#include "keycode.h"
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
//__attribute__((weak)) void timer_timeout_keymap(void) {}

// These indicate if left and right shift are physically pressed
static bool shift = false;

// Interrupt and times for space cadet shift ( shift / parenthesis)
bool sc_shift = false;
// uint16_t shift_timer = 0;
//
// void handle_sc_shift(uint16_t keycode, bool pressed) {
//     if (pressed) {
//         sc_shift    = true;
//         shift_timer = timer_read();
//     } else {
//         sc_shift = false;
//         if (timer_elapsed(shift_timer) < TAPPING_TERM && sc_shift) {
//             register_code16(keycode);
//         }
//     }
// }

inline bool is_shift(void) { return shift || sc_shift; }

static void send_custom_string(const char* normal, const char* shifted) {
    if (is_shift()) {
        send_string(shifted);
    } else {
        send_string(normal);
    }
}

static void send_custom_keycode(uint16_t normal, uint16_t shifted) {
    if (is_shift()) {
        register_code16(normal);
        unregister_code16(normal);
    } else {
        register_code16(shifted);
        unregister_code16(shifted);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
            // detemine if shift is pressed
        case KC_S:
        case KC_RSFT:
            shift = record->event.pressed;
            break;
            // TODO send correct parens
        case KC_LSPO:
        case KC_RSPC:
            sc_shift = record->event.pressed;
            break;

            // leader based key codes
        case CU_FIRST:
            send_string("René");
            break;
        case CU_LAST:
            send_string("Möhring");
            break;
        case CU_MAIL:
            send_string("rene_moehring@gmx.de");
            break;
        case CU_AE:
            if (record->event.pressed) {
                send_custom_string("ä", "Ä");
            }
            break;
        case CU_UE:
            if (record->event.pressed) {
                send_custom_string("ü", "Ü");
            }
            break;
        case CU_OE:
            if (record->event.pressed) {
                send_custom_string("ö", "Ö");
            }
            break;
        case CU_EACUT:
            if (record->event.pressed) {
                send_custom_string("é", "É");
            }
            break;
        case CU_SZ:
            send_string("ß");
            break;
        case CU_EURO:
            send_string("€");
            break;
        case CU_DEG:
            send_string("°");
            break;

#ifdef GERMAN_ENABLE
        case CU_2:
            if (record->event.pressed) {
                send_custom_keycode(KC_2, RALT(KC_Q));
            }
            break;
        case CU_3:
            if (record->event.pressed) {
                send_custom_keycode(KC_3, KC_NUHS);
            }
            break;
        case CU_6:
            if (record->event.pressed) {
                send_custom_keycode(KC_6, KC_GRV);
                register_code(KC_SPACE);  // needed cause it is a dead key
                unregister_code(KC_SPACE);
            }
            break;
        case CU_7:
            if (record->event.pressed) {
                send_custom_keycode(KC_7, KC_6);
            }
            break;
        case CU_8:
            if (record->event.pressed) {
                send_custom_keycode(KC_8, KC_RBRC);
            }
            break;
        case CU_9:
            if (record->event.pressed) {
                send_custom_keycode(KC_9, KC_8);
            }
            break;
        case CU_0:
            if (record->event.pressed) {
                send_custom_keycode(KC_0, KC_9);
            }
            break;
        case CU_COMM:
            if (record->event.pressed) {
                if (is_shift()) {
                    send_string("<");
                } else {
                    register_code(KC_COMM);
                    unregister_code(KC_COMM);
                }
            }
            break;
        case CU_DOT:
            if (record->event.pressed) {
                send_custom_keycode(KC_DOT, KC_NUBS);
            }
            break;
        case CU_SLSH:
            if (record->event.pressed) {
                send_custom_keycode(KC_PSLS, KC_MINS);
            }
            break;
        case CU_SCLN:
            if (record->event.pressed) {
                send_custom_keycode(S(KC_COMM), KC_DOT);
            }
            break;
        case CU_QUOT:
            if (record->event.pressed) {
                send_custom_keycode(S(KC_NUHS), KC_2);
            }
            break;
        case CU_GRV:
            if (record->event.pressed) {
                if (is_shift()) {
                    send_string("~");
                } else {
                    register_code16(S(KC_EQL));
                    unregister_code16(S(KC_EQL));
                    // dead key needs space afterwards
                    register_code(KC_SPACE);
                    unregister_code(KC_SPACE);
                }
            }
            break;
        case CU_EQL:
            if (record->event.pressed) {
                send_custom_keycode(S(KC_0), KC_PPLS);
            }
            break;
        case CU_LBRC:
            if (record->event.pressed) {
                send_custom_string("[", "{");
            }
            break;
        case CU_RBRC:
            if (record->event.pressed) {
                send_custom_string("]", "}");
            }
            break;
        case CU_BSLS:
            if (record->event.pressed) {
                send_custom_string("\\", "|");
            }
            break;
        case CU_EXLM:
            send_string("!");
            break;
        case CU_HASH:
            send_string("#");
            break;
        case CU_TILD:
            send_string("~");
            break;
        case CU_PERC:
            send_string("%");
            break;
        case CU_CIRC:
            send_string("^");
            break;
        case CU_AMPR:
            send_string("&");
            break;
        case CU_PIPE:
            send_string("|");
            break;
        case CU_DLR:
            send_string("$");
            break;
        case CU_DQUO:
            send_string("\"");
            break;
        case CU_AT:
            send_string("@");
            break;
        case CU_UNDS:
            send_string("_");
            break;
        case CU_LT:
            send_string("<");
            break;
        case CU_GT:
            send_string(">");
            break;
        case CU_COLN:
            send_string(":");
            break;
        case CU_QUES:
            send_string("?");
            break;
        case CU_PDOT:
            send_string(".");
            break;
        case CU_PCMM:
            send_string(",");
            break;
#endif
    };
    return process_record_keymap(keycode, record);
}
