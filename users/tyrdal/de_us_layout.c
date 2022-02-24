#include "de_us_layout.h"
#include "action_util.h"
#include "keymap_german.h"
#ifdef CONSOLE_ENABLE
#    include "xprintf.h"
#endif

#ifdef __clang__
#    pragma clang diagnostic ignored "-Wunknown-attributes"  // clangd does not know PROGMEM
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t* record) { return true; }

#ifdef GERMAN_ENABLE
typedef struct symbol_key_codes_t {
    uint16_t custom_code;
    uint16_t symbol_code;
} symbol_key_codes_t;

// clang-format off
symbol_key_codes_t symbol_codes[] = {
  {CU_EXLM,   S(KC_1)},
  {CU_HASH,   KC_NONUS_HASH},
  {CU_TILD,   ALGR(KC_RIGHT_BRACKET)},
  {CU_PERC,   S(KC_5)},
  {CU_AMPR,   S(KC_6)},
  {CU_PIPE,   ALGR(KC_NONUS_BACKSLASH)},
  {CU_DLR,    S(KC_4)},
  {CU_DQUO_S, S(KC_2)},
  {CU_AT,     ALGR(KC_Q)},
  {CU_UNDS,   S(KC_SLASH)},
  {CU_LT,     KC_NONUS_BACKSLASH},
  {CU_GT,     S(KC_NONUS_BACKSLASH)},
  {CU_COLN,   S(KC_DOT)},
  {CU_QUES,   S(KC_MINUS)},
  {CU_SCLN_S, S(KC_COMMA)},
  {CU_DOT_S,  KC_DOT},
  {CU_COM_S,  KC_COMMA},
  {CU_LP,     S(KC_8)},
  {CU_RP,     S(KC_9)},
};
uint8_t NUM_SYMBOL_CODES = sizeof(symbol_codes) / sizeof(symbol_key_codes_t);
// clang-format on

#    ifndef AUTO_SHIFT_ENABLE
typedef struct special_key_codes_t {
    uint16_t custom_code;
    uint16_t normal_code;
    uint16_t shifted_code;
    uint16_t current_code;
} special_key_codes_t;

// clang-format off
special_key_codes_t special_codes[] = {
  {CU_2,     KC_2,             RALT(KC_Q)},
  {CU_3,     KC_3,             KC_NONUS_HASH},
  {CU_6,     KC_6,             CU_CIRC},
  {CU_7,     KC_7,             S(KC_6)},
  {CU_8,     KC_8,             S(KC_RIGHT_BRACKET)},
  {CU_9,     KC_9,             S(KC_8)},
  {CU_0,     KC_0,             S(KC_9)},
  {CU_COMM,  KC_COMMA,         KC_NONUS_BACKSLASH},
  {CU_DOT,   KC_DOT,           S(KC_NONUS_BACKSLASH)},
  {CU_SLSH,  KC_KP_SLASH,      S(KC_MINUS)},
  {CU_DSLSH, KC_KP_SLASH,      ALGR(KC_MINUS)},
  {CU_SCLN,  S(KC_COMMA),      S(KC_DOT)},
  {CU_QUOT,  S(KC_NONUS_HASH), S(KC_2)},
  {CU_DQUO,  S(KC_2),          S(KC_NONUS_HASH)},
  {CU_GRV,   CU_GRV_S,         S(KC_RIGHT_BRACKET)},
  {CU_EQL,   S(KC_0),          S(KC_KP_PLUS)},
  {CU_LBRC,  RALT(KC_8),       RALT(KC_7)},
  {CU_RBRC,  RALT(KC_9),       RALT(KC_0)},
  {CU_BSLS,  RALT(KC_MINUS),   RALT(KC_NONUS_BACKSLASH) }
};
uint8_t NUM_SPECIAL_CODES = sizeof(special_codes) / sizeof(special_key_codes_t);
// clang-format on
#    endif
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    uint8_t mods     = get_mods();
    uint8_t osm_mods = get_oneshot_mods();
    bool    pressed  = record->event.pressed;

#ifdef CONSOLE_ENABLE
    // if (!record->event.pressed) {
    //     xprintf("Mods %d %d OSM %d %d\n", get_mods(), (int)get_mods() & MOD_MASK_SHIFT,
    //     get_oneshot_mods(), (int)(get_oneshot_mods() & MOD_MASK_SHIFT));
    // }
#endif

#ifdef GERMAN_ENABLE
    // Symbols (without dead keys involved)
    for (uint16_t i = 0; i < NUM_SYMBOL_CODES; ++i) {
        if (keycode == symbol_codes[i].custom_code) {
            if (pressed) {
                register_code16(symbol_codes[i].symbol_code);
            } else {
                unregister_code16(symbol_codes[i].symbol_code);
            }
            return process_record_keymap(keycode, record);
        }
    }

#    ifndef AUTO_SHIFT_ENABLE
    // Special Codes (not found on either us or de layout)
    for (uint16_t i = 0; i < NUM_SPECIAL_CODES; ++i) {
        if (keycode == special_codes[i].custom_code) {
            if (pressed) {
                if ((mods | osm_mods) & MOD_MASK_SHIFT) {
                    special_codes[i].current_code = shifted;
                } else {
                    special_codes[i].current_code = normal;
                }
                register_code16(special_codes[i].current_code);
            } else {
                unregister_code16(special_codes[i].current_code);
            }
            return process_record_keymap(keycode, record);
        }
    }
#    endif
#endif

    // Modifiers are disabled for keycodes using SEND_STRING
    // do not forget to set them back afterwards
    clear_mods();
    clear_oneshot_mods();
    switch (keycode) {
            // Strings on keypress
        case CU_FIRST:
            if (pressed) {
                SEND_STRING("Ren" SS_TAP(X_EQUAL) SS_TAP(X_E));
            }
            break;
        case CU_LAST:
            if (pressed) {
                SEND_STRING("M;hring");
            }
            break;
        case CU_MAIL:
            if (pressed) {
                SEND_STRING("rene" SS_LSFT(SS_TAP(X_SLASH)) "moehring" SS_ALGR(SS_TAP(X_Q)) "gmx.de");
            }
            break;

#ifdef GERMAN_ENABLE
            // Custom Symbols ( with dead keys involved)
        case CU_CIRC:
            if (pressed) {
                SEND_STRING(SS_TAP(X_GRAVE) SS_TAP(X_SPACE));
            }
            break;
        case CU_GRV_S:
            if (pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_EQUAL)) SS_TAP(X_SPACE));
            }
            break;
#endif

        default:
            // since none of our special codes was pressed we need to reinstate the oneshot modifiers
            set_oneshot_mods(osm_mods);
    }
    // hold modifiers need to be reinstated in any case
    set_mods(mods);

    return process_record_keymap(keycode, record);
}

#ifdef AUTO_SHIFT_ENABLE
#    ifdef GERMAN_ENABLE
typedef struct autoshift_key_codes_t {
    uint16_t custom_code;
    uint16_t normal_code;
    uint16_t shifted_code;
} autoshift_key_codes_t;

// clang-format off
autoshift_key_codes_t autoshift_codes[] = {
	{CU_2,     KC_2,             RALT(KC_Q)},
	{CU_3,     KC_3,             KC_NONUS_HASH},
	{CU_6,     KC_6,             CU_CIRC},
	{CU_7,     KC_7,             S(KC_6)},
	{CU_8,     KC_8,             S(KC_RIGHT_BRACKET)},
	{CU_9,     KC_9,             S(KC_8)},
	{CU_0,     KC_0,             S(KC_9)},
	{CU_COMM,  KC_COMMA,         KC_NONUS_BACKSLASH},
	{CU_DOT,   KC_DOT,           S(KC_NONUS_BACKSLASH)},
	{CU_SLSH,  KC_KP_SLASH,      S(KC_MINUS)},
	{CU_DSLSH, KC_KP_SLASH,      ALGR(KC_MINUS)},
	{CU_SCLN,  S(KC_COMMA),      S(KC_DOT)},
	{CU_QUOT,  S(KC_NONUS_HASH), S(KC_2)},
	{CU_DQUO,  S(KC_2),          S(KC_NONUS_HASH)},
	{CU_GRV,   CU_GRV_S,         S(KC_RIGHT_BRACKET)},
	{CU_EQL,   S(KC_0),          S(KC_KP_PLUS)},
	{CU_LBRC,  RALT(KC_8),       RALT(KC_7)},
	{CU_RBRC,  RALT(KC_9),       RALT(KC_0)},
	{CU_LCURL, RALT(KC_7),       RALT(KC_8)},
	{CU_RCURL, RALT(KC_0),       RALT(KC_9)},
	{CU_BSLS,  RALT(KC_MINUS),   RALT(KC_NONUS_BACKSLASH)},
	{CU_P4,    KC_KP_4,          KC_LEFT},
	{CU_P5,    KC_KP_5,          KC_DOWN},
	{CU_P6,    KC_KP_6,          KC_RIGHT},
	{CU_P8,    KC_KP_8,          KC_UP},
};
uint8_t NUM_AUTOSHIFT_CODES = sizeof(autoshift_codes) / sizeof(autoshift_key_codes_t);
// clang-format on
#    endif

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t* record) {
#    ifdef GERMAN_ENABLE
    for (uint16_t i = 0; i < NUM_AUTOSHIFT_CODES; ++i) {
        if (keycode == autoshift_codes[i].custom_code) {
            return true;
        }
    }
#    endif

    return false;
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t* record) {
#    ifdef GERMAN_ENABLE
    for (uint16_t i = 0; i < NUM_AUTOSHIFT_CODES; ++i) {
        if (keycode == autoshift_codes[i].custom_code) {
            register_code16(shifted ? autoshift_codes[i].shifted_code : autoshift_codes[i].normal_code);
            return;
        }
    }
#    endif

    if (shifted) {
        add_weak_mods(MOD_BIT(KC_LSFT));
    }
    // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
    register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t* record) {
#    ifdef GERMAN_ENABLE
    for (uint16_t i = 0; i < NUM_AUTOSHIFT_CODES; ++i) {
        if (keycode == autoshift_codes[i].custom_code) {
            unregister_code16(shifted ? autoshift_codes[i].shifted_code : autoshift_codes[i].normal_code);
            return;
        }
    }
#    endif

    // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
    // The IS_RETRO check isn't really necessary here, always using
    // keycode & 0xFF would be fine.
    unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
}
#endif
