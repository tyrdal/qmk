#include "de_us_layout.h"
#include "action_util.h"
#include "keymap_german.h"
#ifdef CONSOLE_ENABLE
#    include "xprintf.h"
#endif

#ifdef __clang__
#    pragma clang diagnostic ignored "-Wunknown-attributes"  // clangd does not know PROGMEM
#endif

uint8_t def_layer;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t* record) { return true; }
//__attribute__((weak)) void autoshift_press_user_keymap(uint16_t keycode, bool shifted, keyrecord_t* record);
//__attribute__((weak)) void autoshift_release_user_keymap(uint16_t keycode, bool shifted, keyrecord_t* record);

#ifdef GERMAN_ENABLE
#    ifndef AUTO_SHIFT_ENABLE
#        define MAP_CUSTOM_KEYCODE(pressed, shift_pressed, osm_shift_pressed, normal, shifted) \
            {                                                                                  \
                static uint16_t kc;                                                            \
                send_custom_keycode(&kc, pressed, shift_pressed, normal, shifted);             \
            }

void send_custom_keycode(uint16_t* kc, bool pressed, bool shift_pressed, bool osm_shift_pressed, uint16_t normal, uint16_t shifted) {
    if (pressed) {
        if (shift_pressed) {
            del_mods(MOD_MASK_SHIFT);
            *kc = shifted;
        } else if (osm_shift_pressed) {
            del_one_shot_mods(MOD_MASK_SHIFT);
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
#    endif

void send_custom_symbol(bool pressed, bool shift_pressed, uint16_t kc) {
    if (pressed) {
        if (shift_pressed) {
            del_mods(MOD_MASK_SHIFT);
        }
        register_code16(kc);
        if (shift_pressed) {
            register_code(KC_LSHIFT);
        }
    } else {
        unregister_code16(kc);
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    bool is_shift_pressed = get_mods() & MOD_MASK_SHIFT;
#ifndef AUTO_SHIFT_ENABLE
    bool is_osm_shift_pressed = get_oneshot_mods() & MOD_MASK_SHIFT;
#endif
    bool pressed = record->event.pressed;

    // uint8_t mods      = get_mods();
    // uint8_t osm_mods  = get_oneshot_mods();
    // uint8_t weak_mods = get_oneshot_mods();

    // TODO handle one shot and weak mods for custom codes

    // if (!record->event.pressed) {
    //     xprintf("Mods %d %d OSM %d %d Weak %d %d\n", mods, (int)is_shift_pressed, osm_mods, (int)(osm_mods & MOD_MASK_SHIFT), weak_mods, (int)(weak_mods & weak_mods & MOD_MASK_SHIFT));
    // }

    switch (keycode) {
        case CU_FIRST:
            if (record->event.pressed) {
                SEND_STRING("Ren");
                tap_code(KC_EQUAL);
                tap_code(KC_E);
            }
            break;
        case CU_LAST:
            if (record->event.pressed) {
                SEND_STRING("M;hring");
            }
            break;
        case CU_MAIL:
            if (record->event.pressed) {
                SEND_STRING("rene");
                tap_code16(S(KC_SLASH));
                SEND_STRING("moehring");
                tap_code16(ALGR(KC_Q));
                SEND_STRING("gmx.de");
            }
            break;

#ifdef GERMAN_ENABLE
#    ifndef AUTO_SHIFT_ENABLE
        case CU_2:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_2, RALT(KC_Q));
            break;
        case CU_3:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_3, KC_NONUS_HASH);
            break;
        case CU_6:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_6, CU_CIRC);
            break;
        case CU_7:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_7, S(KC_6));
            break;
        case CU_8:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_8, S(KC_RIGHT_BRACKET));
            break;
        case CU_9:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_9, S(KC_8));
            break;
        case CU_0:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_0, S(KC_9));
            break;
        case CU_COMM:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_COMMA, KC_NONUS_BACKSLASH);
            break;
        case CU_DOT:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_DOT, S(KC_NONUS_BACKSLASH));
            break;
        case CU_SLSH:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_KP_SLASH, S(KC_MINUS));
            break;
        case CU_DSLSH:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, KC_KP_SLASH, ALGR(KC_MINUS));
        case CU_SCLN:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, S(KC_COMMA), S(KC_DOT));
            break;
        case CU_QUOT:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, S(KC_NONUS_HASH), S(KC_2));
            break;
        case CU_DQUO:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, S(KC_2), S(KC_NONUS_HASH));
            break;
        case CU_GRV:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, CU_GRV_S, S(KC_RIGHT_BRACKET));
            break;
        case CU_EQL:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, S(KC_0), S(KC_KP_PLUS));
            break;
        case CU_LBRC:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, RALT(KC_8), RALT(KC_7));
            break;
        case CU_RBRC:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, RALT(KC_9), RALT(KC_0));
            break;
        case CU_BSLS:
            MAP_CUSTOM_KEYCODE(pressed, is_shift_pressed, is_osm_shift_pressed, RALT(KC_MINUS), RALT(KC_NONUS_BACKSLASH));
            break;
#    endif
        // Custom Symbolics
        case CU_EXLM:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_1));
            break;
        case CU_HASH:
            send_custom_symbol(pressed, is_shift_pressed, KC_NONUS_HASH);
            break;
        case CU_TILD:
            send_custom_symbol(pressed, is_shift_pressed, ALGR(KC_RIGHT_BRACKET));
            break;
        case CU_PERC:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_5));
            break;
        case CU_CIRC:  // DEAD
            if (pressed) {
                if (is_shift_pressed) {
                    del_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_GRAVE);
                tap_code(KC_SPACE);
                if (is_shift_pressed) {
                    register_code(KC_LSHIFT);
                }
            }
            break;
        case CU_AMPR:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_6));
            break;
        case CU_PIPE:
            send_custom_symbol(pressed, is_shift_pressed, ALGR(KC_NONUS_BACKSLASH));
            break;
        case CU_DLR:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_4));
            break;
        case CU_DQUO_S:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_2));
            break;
        case CU_AT:
            send_custom_symbol(pressed, is_shift_pressed, ALGR(KC_Q));
            break;
        case CU_UNDS:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_SLASH));
            break;
        case CU_LT:
            send_custom_symbol(pressed, is_shift_pressed, KC_NONUS_BACKSLASH);
            break;
        case CU_GT:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_NONUS_BACKSLASH));
            break;
        case CU_COLN:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_DOT));
            break;
        case CU_QUES:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_MINUS));
            break;
        case CU_GRV_S:  // DEAD
            if (pressed) {
                tap_code16(S(KC_EQUAL));
                tap_code(KC_SPACE);
            }
            break;
        case CU_SCLN_S:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_COMMA));
            break;
        case CU_DOT_S:
            send_custom_symbol(pressed, is_shift_pressed, KC_DOT);
            break;
        case CU_COM_S:
            send_custom_symbol(pressed, is_shift_pressed, KC_COMMA);
            break;
        case CU_LP:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_8));
            break;
        case CU_RP:
            send_custom_symbol(pressed, is_shift_pressed, S(KC_9));
            break;
#endif
    };
    return process_record_keymap(keycode, record);
}

#ifdef AUTO_SHIFT_ENABLE
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
#    ifdef GERMAN_ENABLE
        case CU_COMM:
        case CU_DOT:
        case CU_SLSH:
        case CU_DSLSH:
        case CU_SCLN:
        case CU_GRV:
        case CU_2:
        case CU_3:
        case CU_6:
        case CU_7:
        case CU_8:
        case CU_9:
        case CU_0:
        case CU_EQL:
        case CU_LBRC:
        case CU_RBRC:
        case CU_LCURL:
        case CU_RCURL:
        case CU_BSLS:
        case CU_QUOT:
        case CU_DQUO:
        case CU_P4:
        case CU_P5:
        case CU_P6:
        case CU_P8:
#    endif
            return true;
    }

    return false;
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t* record) {
    switch (keycode) {
#    ifdef GERMAN_ENABLE
        case CU_2:
            register_code16(!shifted ? KC_2 : RALT(KC_Q));
            break;
        case CU_3:
            register_code16(!shifted ? KC_3 : KC_NONUS_HASH);
            break;
        case CU_6:
            register_code16(!shifted ? KC_6 : CU_CIRC);
            break;
        case CU_7:
            register_code16(!shifted ? KC_7 : S(KC_6));
            break;
        case CU_8:
            register_code16(!shifted ? KC_8 : S(KC_RIGHT_BRACKET));
            break;
        case CU_9:
            register_code16(!shifted ? KC_9 : S(KC_8));
            break;
        case CU_0:
            register_code16(!shifted ? KC_0 : S(KC_9));
            break;
        case CU_COMM:
            register_code16(!shifted ? KC_COMMA : KC_NONUS_BACKSLASH);
            break;
        case CU_DOT:
            register_code16(!shifted ? KC_DOT : S(KC_NONUS_BACKSLASH));
            break;
        case CU_SLSH:
            register_code16(!shifted ? KC_KP_SLASH : S(KC_MINUS));
            break;
        case CU_DSLSH:
            register_code16(!shifted ? KC_KP_SLASH : ALGR(KC_MINUS));
            break;
        case CU_SCLN:
            register_code16(!shifted ? S(KC_COMMA) : S(KC_DOT));
            break;
        case CU_QUOT:
            register_code16(!shifted ? S(KC_NONUS_HASH) : S(KC_2));
            break;
        case CU_DQUO:
            register_code16(!shifted ? S(KC_2) : S(KC_NONUS_HASH));
            break;
        case CU_GRV:
            register_code16(!shifted ? CU_GRV_S : S(KC_RIGHT_BRACKET));
            break;
        case CU_EQL:
            register_code16(!shifted ? S(KC_0) : S(KC_KP_PLUS));
            break;
        case CU_LBRC:
            register_code16(!shifted ? RALT(KC_8) : RALT(KC_7));
            break;
        case CU_RBRC:
            register_code16(!shifted ? RALT(KC_9) : RALT(KC_0));
            break;
        case CU_LCURL:
            register_code16(!shifted ? RALT(KC_7) : RALT(KC_8));
            break;
        case CU_RCURL:
            register_code16(!shifted ? RALT(KC_0) : RALT(KC_9));
            break;
        case CU_BSLS:
            register_code16(!shifted ? RALT(KC_MINUS) : RALT(KC_NONUS_BACKSLASH));
            break;
        case CU_P4:
            register_code16(!shifted ? KC_KP_4 : KC_LEFT);
            break;
        case CU_P5:
            register_code16(!shifted ? KC_KP_5 : KC_DOWN);
            break;
        case CU_P6:
            register_code16(!shifted ? KC_KP_6 : KC_RIGHT);
            break;
        case CU_P8:
            register_code16(!shifted ? KC_KP_8 : KC_UP);
            break;
#    endif
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t* record) {
    switch (keycode) {
#    ifdef GERMAN_ENABLE
        case CU_2:
            unregister_code16(!shifted ? KC_2 : RALT(KC_Q));
            break;
        case CU_3:
            unregister_code16(!shifted ? KC_3 : KC_NONUS_HASH);
            break;
        case CU_6:
            unregister_code16(!shifted ? KC_6 : CU_CIRC);
            break;
        case CU_7:
            unregister_code16(!shifted ? KC_7 : S(KC_6));
            break;
        case CU_8:
            unregister_code16(!shifted ? KC_8 : S(KC_RIGHT_BRACKET));
            break;
        case CU_9:
            unregister_code16(!shifted ? KC_9 : S(KC_8));
            break;
        case CU_0:
            unregister_code16(!shifted ? KC_0 : S(KC_9));
            break;
        case CU_COMM:
            unregister_code16(!shifted ? KC_COMMA : KC_NONUS_BACKSLASH);
            break;
        case CU_DOT:
            unregister_code16(!shifted ? KC_DOT : S(KC_NONUS_BACKSLASH));
            break;
        case CU_SLSH:
            unregister_code16(!shifted ? KC_KP_SLASH : S(KC_MINUS));
            break;
        case CU_DSLSH:
            unregister_code16(!shifted ? KC_KP_SLASH : ALGR(KC_MINUS));
            break;
        case CU_SCLN:
            unregister_code16(!shifted ? S(KC_COMMA) : S(KC_DOT));
            break;
        case CU_QUOT:
            unregister_code16(!shifted ? S(KC_NONUS_HASH) : S(KC_2));
            break;
        case CU_DQUO:
            unregister_code16(!shifted ? S(KC_2) : S(KC_NONUS_HASH));
            break;
        case CU_GRV:
            unregister_code16(!shifted ? CU_GRV_S : S(KC_RIGHT_BRACKET));
            break;
        case CU_EQL:
            unregister_code16(!shifted ? S(KC_0) : S(KC_KP_PLUS));
            break;
        case CU_LBRC:
            unregister_code16(!shifted ? RALT(KC_8) : RALT(KC_7));
            break;
        case CU_RBRC:
            unregister_code16(!shifted ? RALT(KC_9) : RALT(KC_0));
            break;
        case CU_LCURL:
            unregister_code16(!shifted ? RALT(KC_7) : RALT(KC_8));
            break;
        case CU_RCURL:
            unregister_code16(!shifted ? RALT(KC_0) : RALT(KC_9));
            break;
        case CU_BSLS:
            unregister_code16(!shifted ? RALT(KC_MINUS) : RALT(KC_NONUS_BACKSLASH));
            break;
        case CU_P4:
            unregister_code16(!shifted ? KC_KP_4 : KC_LEFT);
            break;
        case CU_P5:
            unregister_code16(!shifted ? KC_KP_5 : KC_DOWN);
            break;
        case CU_P6:
            unregister_code16(!shifted ? KC_KP_6 : KC_RIGHT);
            break;
        case CU_P8:
            unregister_code16(!shifted ? KC_KP_8 : KC_UP);
            break;
#    endif
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}
#endif
