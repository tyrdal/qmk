#include "action_layer.h"
#include "action_util.h"
// #include "eeconfig.h"
// #include "keycode.h"
// #include "keycode_config.h"
#include "process_auto_shift.h"
#include "quantum_keycodes.h"
// #include "report.h"
#include "send_string_keycodes.h"
#ifdef CONSOLE_ENABLE
#    include "xprintf.h"
#endif
#include QMK_KEYBOARD_H
#include "de_us_layout.h"
#include "keymap_german.h"
#if __has_include("passwords.h")
// #    include "passwords.h"
#endif

#ifdef __clang__
#    undef PROGMEM
#    define PROGMEM // clangd does not know PROGMEM
#endif

extern uint8_t def_layer;

enum Layers {
    BASE,
    SYMBOLS,
    NUMPAD,
    FKEYS,
    MOUSE,
};

enum custom_keycodes { CU_BUF = NEW_SAFE_RANGE, CU_OLBUF, CU_GREP, CU_LGREP, CU_LDIAG, CU_FDIAG, CU_HELP, CU_GOTO, CU_CTRX, CU_CIW, CU_BLCK, CU_SYS, CU_ZERO };

#define CU_ACC KC_EQL // use german dead keys for accents

// Shortcut to make keymap more readable
#define LCTL_ESC LCTL_T(KC_ESC)

#define OSM_GUI OSM(MOD_LGUI)
#define OSM_HYP OSM(MOD_HYPR)
#define OSM_MEH OSM(MOD_MEH)
#define OSM_SHFT OSM(MOD_LSFT)
#define OSM_RC OSM(MOD_RCTL)

#define LT_SYM_B LT(SYMBOLS, KC_BSPC)
#define LT_SYM_S LT(SYMBOLS, KC_SPC)
#define LT_NUM_D LT(NUMPAD, KC_DEL)
#define LT_NUM_E LT(NUMPAD, KC_ENT)
#define LT_FKEY_C OSL(FKEYS)
#define OSL_MOUS OSL(MOUSE)
#define OSM_LA OSM(MOD_LALT)
#define KC_SERCH LGUI(KC_S)
#define KC_EXPLR LGUI(KC_E)
#define KC_DESK LGUI(KC_D)
#define KC_ALTAB LCTL(LALT(KC_TAB))
#define KC_BTOGG LCTL(KC_6)
#define KC_BUF LSFT(KC_SLASH)
#define KC_VFWD LGUI(LCTL(KC_LEFT))
#define KC_VBWD LGUI(LCTL(KC_RIGHT))
#define CU_EQL_S S(KC_0)

enum TAP_DOUBLE_KEYCODES {
    TD_F1_13,
    TD_F2_14,
    TD_F3_15,
    TD_F4_16,
    TD_F5_17,
    TD_F6_18,
    TD_F7_19,
    TD_F8_20,
    TD_F9_21,
    TD_F10_22,
    TD_F11_23,
    TD_F12_24,
};

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
  [TD_F1_13] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F13),
  [TD_F2_14] = ACTION_TAP_DANCE_DOUBLE(KC_F2,KC_F14),
  [TD_F3_15] = ACTION_TAP_DANCE_DOUBLE(KC_F3,KC_F15),
  [TD_F4_16] = ACTION_TAP_DANCE_DOUBLE(KC_F4,KC_F16),
  [TD_F5_17] = ACTION_TAP_DANCE_DOUBLE(KC_F5,KC_F17),
  [TD_F6_18] = ACTION_TAP_DANCE_DOUBLE(KC_F6,KC_F18),
  [TD_F7_19] = ACTION_TAP_DANCE_DOUBLE(KC_F7,KC_F19),
  [TD_F8_20] = ACTION_TAP_DANCE_DOUBLE(KC_F8,KC_F20),
  [TD_F9_21] = ACTION_TAP_DANCE_DOUBLE(KC_F9,KC_F21),
  [TD_F10_22] = ACTION_TAP_DANCE_DOUBLE(KC_F10,KC_F22),
  [TD_F11_23] = ACTION_TAP_DANCE_DOUBLE(KC_F11,KC_F23),
  [TD_F12_24] = ACTION_TAP_DANCE_DOUBLE(KC_F12,KC_F24),
};

#define TD_F1 TD(TD_F1_13)
#define TD_F2 TD(TD_F2_14)
#define TD_F3 TD(TD_F3_15)
#define TD_F4 TD(TD_F4_16)
#define TD_F5 TD(TD_F5_17)
#define TD_F6 TD(TD_F6_18)
#define TD_F7 TD(TD_F7_19)
#define TD_F8 TD(TD_F8_20)
#define TD_F9 TD(TD_F9_21)
#define TD_F10 TD(TD_F10_22)
#define TD_F11 TD(TD_F11_23)
#define TD_F12 TD(TD_F12_24)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            KC_ALTAB, XXXXXXX , CU_BLCK , CU_ZERO , CU_SYS  , OSM_HYP ,                                              OSM_MEH , KC_VFWD , KC_VBWD , XXXXXXX , XXXXXXX , KC_MPLY ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_F    , KC_P    , KC_B    , DM_REC1 ,                          DM_REC2 , KC_J    , KC_L    , KC_U    , DE_Y    , KC_SLSH , OSM_GUI ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , DM_PLY1 ,                          DM_PLY2 , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , OSM_RC  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            OSM_SHFT, DE_Z    , KC_X    , KC_C    , KC_D    , KC_V    , XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX , KC_K    , KC_H    , KC_DOT  , CU_COMM , CU_DSLSH, OSM_SHFT,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            OSL_MOUS, XXXXXXX , XXXXXXX , QK_LEAD ,     LT_FKEY_C,      LT_SYM_B, LT_NUM_D,      LT_NUM_E, LT_SYM_S,      OSM_LA  ,      QK_REP  , QK_AREP , XXXXXXX , OSL_MOUS
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [SYMBOLS] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            KC_SYRQ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , KC_WREF , KC_WBAK , KC_WFWD , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_GRV_S, CU_EURO , CU_QUES , CU_LBC_S, CU_EXLM , XXXXXXX ,                          XXXXXXX , CU_TILD , CU_RBC_S, CU_PERC , CU_PARAG, CU_AT   , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_HASH , CU_PIPE , CU_AMPR , CU_LP_S , CU_UNDS , XXXXXXX ,                          XXXXXXX , CU_CIRC , CU_RP_S ,CU_DQUO_S, CU_QUOT , CU_DLR  , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌────────-┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , DE_ADIA , CU_LT   , CU_SZ   , CU_LCL_S, KC_PPLS , XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX , CU_EQL_S, CU_RCL_S, DE_UDIA , CU_GT   , DE_ODIA , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX ,      _______ ,      _______ , _______ ,      _______ , _______ ,      _______ ,      XXXXXXX , XXXXXXX , CU_DEG   , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [NUMPAD] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              KC_NUM  , KC_PSCR , KC_SCRL , KC_PAUS , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , KC_UP   , KC_PGUP , MS_WHLU , XXXXXXX ,                          XXXXXXX , KC_PSLS , KC_P7   , KC_P8   , KC_P9   , KC_PMNS , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_HOME , KC_LEFT , KC_DOWN , KC_RIGHT, KC_END  , XXXXXXX ,                          XXXXXXX , KC_PAST , KC_P4   , KC_P5   , KC_P6   , CU_PLUS , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX , KC_PGDN , MS_WHLD , XXXXXXX , XXXXXXX,       XXXXXXX , XXXXXXX , CU_PDOT , KC_P1   , KC_P2   , KC_P3   , KC_P0   , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX ,      _______ ,      _______ , _______,       _______ , _______ ,      _______ ,      KC_P0   , XXXXXXX , XXXXXXX , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [FKEYS] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , CU_HELP , KC_BTOGG, CU_CTRX , KC_MNXT , XXXXXXX ,                          XXXXXXX , KC_VOLU , TD_F9   , TD_F10  , TD_F11  , TD_F12  , CU_FIRST,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_GREP , CU_LGREP, CU_CIW  , KC_BUF  , KC_MUTE , XXXXXXX ,                          XXXXXXX , KC_MPLY , TD_F5   , TD_F6   , TD_F7   , TD_F8   , CU_LAST ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , CU_FDIAG, CU_GOTO , CU_LDIAG, KC_MPRV , XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX , KC_VOLD , TD_F1   , TD_F2   , TD_F3   , TD_F4   , CU_MAIL ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX ,      _______ ,      XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX ,      _______ ,      XXXXXXX , XXXXXXX , XXXXXXX , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),
    [MOUSE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , KC_SLEP , XXXXXXX , XXXXXXX , XXXXXXX , KC_PWR  ,                                              XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , MS_WHLU , MS_UP   , MS_BTN5 , MS_BTN7 , CU_ACL1 ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , MS_WHLL , MS_LEFT , MS_DOWN , MS_RGHT , MS_WHLR , CU_ACL0 ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , MS_WHLD , MS_BTN4 , MS_BTN6 , MS_BTN8 , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , MS_ACL2 , MS_ACL1 , MS_ACL0 ,      _______ ,      XXXXXXX , XXXXXXX ,      MS_BTN1 , MS_BTN2 ,      MS_BTN3 ,      XXXXXXX , XXXXXXX , XXXXXXX , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

};
// clang-format on

// key customization happens here
bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    uint8_t mods     = get_mods();
    uint8_t osm_mods = get_oneshot_mods();
    bool    pressed  = record->event.pressed;

#ifdef CONSOLE_ENABLE
    bool is_ctrl_pressed  = (mods | osm_mods) & MOD_MASK_CTRL;
    bool is_alt_pressed   = (mods | osm_mods) & MOD_MASK_ALT;
    bool is_shift_pressed = (mods | osm_mods) & MOD_MASK_SHIFT;
    xprintf("     c %d | a %d | s %d \n", is_ctrl_pressed, is_alt_pressed, is_shift_pressed);
    xprintf("hold c %d | a %d | s %d \n", mods & MOD_MASK_CTRL, mods & MOD_MASK_ALT, mods & MOD_MASK_SHIFT);
    xprintf("osm  c %d | a %d | s %d \n", osm_mods & MOD_MASK_CTRL, osm_mods & MOD_MASK_ALT, osm_mods & MOD_MASK_SHIFT);
#endif

    // Here we can clear all oneshot modifiers because only codes using SEND_STRING follow
    // therefore this section needs to be the last
    // should this change then modifier handling needs to be adjusted
    // hold modifiers need to be reinstated though
    clear_mods();
    clear_oneshot_mods();
    switch (keycode) {
        case CU_CTRX:
            if (pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_BRK))) SS_DELAY(300) SS_TAP(X_DOWN) SS_TAP(X_ENTER));
            }
            break;

        case CU_OLBUF:
            if (pressed) {
                SEND_STRING(" " SS_LSFT(SS_TAP(X_SLASH)));
            }
            break;

        case CU_GREP:
            if (pressed) {
                SEND_STRING(" fg");
            }
            break;

        case CU_LGREP:
            if (pressed) {
                SEND_STRING(" fl");
            }
            break;

        case CU_LDIAG:
            if (pressed) {
                SEND_STRING("/dl");
            }
            break;

        case CU_FDIAG:
            if (pressed) {
                SEND_STRING("/dd");
            }
            break;

        case CU_GOTO:
            if (pressed) {
                SEND_STRING("/gf");
            }
            break;

        case CU_HELP:
            if (pressed) {
                SEND_STRING("/h");
            }
            break;

        case CU_CIW:
            if (pressed) {
                SEND_STRING("ciw");
            }
            break;

        case CU_BLCK:
            if (pressed) {
                SEND_STRING("@?");
            }
            break;

        case CU_SYS:
            if (pressed) {
                SEND_STRING("@}");
            }
            break;

        case CU_ZERO:
            if (pressed) {
                SEND_STRING("@0p");
            }
            break;

        default:
            // since none of our special codes was pressed we need to reinstate the oneshot modifiers
            set_oneshot_mods(osm_mods);
    }
    set_mods(mods);

    return true;
}

// For some unknown reason the colors are garbled and I have a yellow instead of a green led
#undef set_led_off
#undef set_led_red
#undef set_led_blue
#undef set_led_yellow
#undef red_led_off
#undef red_led_on
#define red_led_off PORTD |= (1 << 1)
#define red_led_on PORTD &= ~(1 << 1)
#define blue_led_off PORTF |= (1 << 5)
#define blue_led_on PORTF &= ~(1 << 5)
#define yellow_led_off PORTF |= (1 << 4)
#define yellow_led_on PORTF &= ~(1 << 4)

#define set_led_off \
    red_led_off;    \
    yellow_led_off; \
    blue_led_off
#define set_led_red \
    red_led_on;     \
    yellow_led_off; \
    blue_led_off
#define set_led_blue \
    red_led_off;     \
    yellow_led_off;  \
    blue_led_on
#define set_led_yellow \
    red_led_off;       \
    yellow_led_on;     \
    blue_led_off
#define set_led_violet \
    red_led_on;        \
    yellow_led_off;    \
    blue_led_on
#define set_led_all \
    red_led_on;     \
    yellow_led_on;  \
    blue_led_on

void matrix_init_user(void) {
    set_led_off;
    // def_layer = eeconfig_read_default_layer();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case BASE:
            set_led_off;
            break;
        case SYMBOLS:
            set_led_blue;
            break;
        case NUMPAD:
            set_led_yellow;
            break;
        case FKEYS:
            set_led_red;
            break;
        case MOUSE:
            set_led_violet;
        default:
            break;
    }
    return state;
}

#ifdef LEADER_ENABLE

void leader_end_user(void) {
#    ifdef CONSOLE_ENABLE
    int leader_matched = 0;
#    endif

    // debug
    if (leader_sequence_three_keys(KC_D, KC_B, KC_G)) {
#    ifdef CONSOLE_ENABLE
        leader_matched = 1;
#    endif
        tap_code16(DB_TOGG);
    }
    // reset
    else if (leader_sequence_three_keys(KC_R, KC_S, KC_T)) {
#    ifdef CONSOLE_ENABLE
        leader_matched = 2;
#    endif
        reset_keyboard();
    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
#    ifdef CONSOLE_ENABLE
        leader_matched = 3;
#    endif
        autoshift_toggle();
    } else if (leader_sequence_three_keys(KC_N, KC_K, KC_R)) {
#    ifdef CONSOLE_ENABLE
        leader_matched = 4;
#    endif
        tap_code16(NK_TOGG);
    }
#    if __has_include("passwords.h")
#        include "passwords.h"
    else if (leader_sequence_one_key(KC_U)) {
#        ifdef CONSOLE_ENABLE
        leader_matched = 5;
#        endif
        SEND_STRING(ROOT);
    } else if (leader_sequence_one_key(KC_E)) {
#        ifdef CONSOLE_ENABLE
        leader_matched = 6;
#        endif
        SEND_STRING(USER);
    } else if (leader_sequence_one_key(KC_N)) {
#        ifdef CONSOLE_ENABLE
        leader_matched = 7;
#        endif
        SEND_STRING(GITHUB);
    } else if (leader_sequence_one_key(KC_DOT)) {
#        ifdef CONSOLE_ENABLE
        leader_matched = 8;
#        endif
        SEND_STRING(BDR_EW);
    } else if (leader_sequence_one_key(KC_H)) {
#        ifdef CONSOLE_ENABLE
        leader_matched = 9;
#        endif
        SEND_STRING(BDR_BK);
    }
#    endif

#    ifdef CONSOLE_ENABLE
    extern uint16_t leader_sequence[5];
    xprintf("%d %d %d %d %d\n", leader_sequence[0], leader_sequence[1], leader_sequence[2], leader_sequence[3], leader_sequence[4]);
    xprintf("m %d\n", leader_matched);
#    endif
}

#endif

#ifndef MAGIC_ENABLE
// reduce firmware size by replacing magic functions with empty functions
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif

// TODO
// - Timeouts for leader key

// vim :set expandtab :set ts=2
