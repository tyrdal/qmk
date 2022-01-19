#include "action.h"
#include "action_code.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keycode.h"
#include "keycode_legacy.h"
#include "process_leader.h"
#include "process_tap_dance.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "song_list.h"
#include QMK_KEYBOARD_H
#include "de_us_layout.h"
#include "keymap_german.h"

#ifdef __clang__
#    pragma clang diagnostic ignored "-Wunknown-attributes"  // clangd does not know PROGMEM
#endif

enum Layers {
    _COLEMAK_DH_DE,
    _NUMPAD,
    _NAVIGATION,
    _GAMING,
    _COLEMAK_DH_US,
};

enum custom_keycodes {
    CU_CODE = NEW_SAFE_RANGE,
};

// Shortcut to make keymap more readable
#define LCTL_ESC LCTL_T(KC_ESC)
#define RCTL_ESC RCTL_T(KC_ESC)

#define OSM_GUI OSM(MOD_LGUI)
#define OSM_HYP OSM(MOD_HYPR)
#define OSM_MEH OSM(MOD_MEH)
#define OSM_SHFT OSM(MOD_LSFT)
#define OSM_CA OSM(MOD_LCTL | MOD_LALT)
#define OSM_CG OSM(MOD_LCTL | MOD_LGUI)
#define OSM_C OSM(MOD_LCTL)
#define OSM_LA OSM(MOD_LALT)
#define OSM_RA OSM(MOD_RALT)

#define C_BREAK LCTL(KC_PAUS)  // ctrl + break => cancel build process in msvs
#define CA_DEL LCA(KC_DEL)     // ctrl + alt + del

#define LT_PGUP LT(_NUMPAD, KC_PGUP)
#define LT_PGDN LT(_NUMPAD, KC_PGDN)
#define LT_HOME LT(_NAVIGATION, KC_HOME)
#define LT_END LT(_NAVIGATION, KC_END)
#define DF_DE DF(_COLEMAK_DH_DE)
#define DF_US DF(_COLEMAK_DH_US)

// IMPORTANT:
// With the current implementation you cannot use CU_LSPO/CU_RSPC at the same time as the normal KC_LSFT/KC_RSFT
// modifiers. Choose one set or the other.

void on_parens_open_tap(qk_tap_dance_state_t* state, void* data);
void on_parens_close_tap(qk_tap_dance_state_t* state, void* data);

enum TAP_DOUBLE_KEYCODES {
    TD_1_6,
    TD_2_7,
    TD_3_8,
    TD_4_9,
    TD_5_0,
    TD_F1_F6,
    TD_F2_F7,
    TD_F3_F8,
    TD_F4_F9,
    TD_F5_F0,
    TD_Q_EX,  // Q - MyPC aka Explorer
    TD_Y_TM,  // Y - Task Manager
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
    TD_PRNSO,
    TD_PRNSC
};

// clang-format off
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_1_6]   = ACTION_TAP_DANCE_DOUBLE(KC_1,KC_6),
	[TD_2_7]   = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_7),
	[TD_3_8]   = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_8),
	[TD_4_9]   = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_9),
	[TD_5_0]   = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_0),
	[TD_F1_F6] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_6),
	[TD_F2_F7] = ACTION_TAP_DANCE_DOUBLE(KC_F2, KC_F7),
	[TD_F3_F8] = ACTION_TAP_DANCE_DOUBLE(KC_F3, KC_F8),
	[TD_F4_F9] = ACTION_TAP_DANCE_DOUBLE(KC_F4, KC_F9),
	[TD_F5_F0] = ACTION_TAP_DANCE_DOUBLE(KC_F5, KC_F10),
	[TD_Q_EX] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_MPLY),
	[TD_Y_TM] = ACTION_TAP_DANCE_DOUBLE(KC_Y, RCS(KC_ESC)),
	[TD_F1_13] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F13),
	[TD_F2_14] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F14),
	[TD_F3_15] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F15),
	[TD_F4_16] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F16),
	[TD_F5_17] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F17),
	[TD_F6_18] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F18),
	[TD_F7_19] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F19),
	[TD_F8_20] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F20),
	[TD_F9_21] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F21),
	[TD_F10_22] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F22),
	[TD_F11_23] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F23),
	[TD_F12_24] = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F24),
	[TD_PRNSO] = ACTION_TAP_DANCE_FN(on_parens_open_tap),
	[TD_PRNSC] = ACTION_TAP_DANCE_FN(on_parens_close_tap),
};

// check which one feels more ergonomic
// Idea: remove numbers on default layer and replace with all 24 F-Keys, make sure all symbols are covered on def + numpad
// Idea: alternative-> flip number on default so the symbols are normal and the nmber shifted => all F-Keys can
//       replace symbols on the numpad layer, numlock goes to num side

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK_DH_DE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            CU_VOL  , TD_F1_13, TD_F2_14, TD_F3_15, TD_F4_16, TD_F5_17,                                              TD_F8_20, TD_F9_21,TD_F10_22,TD_F11_23,TD_F12_24, CU_TRCK ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , TD_Q_EX , KC_W    , KC_F    , KC_P    , KC_B    , TD_F6_18,                          TD_F7_19, KC_J    , KC_L    , KC_U    , TD_Y_TM , CU_MINS , KC_MPLY ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , TD_PRNSO,                          TD_PRNSC, KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , OSM_C   ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            OSM_SHFT, DE_Z    , KC_X    , KC_C    , KC_D    , KC_V    , LT_PGUP , LT_HOME ,      LT_END  , LT_PGDN , KC_K    , KC_H    , CU_SCLN , CU_COMM , CU_DOT  , OSM_SHFT,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            OSM_GUI , OSM_MEH , OSM_HYP , CU_FUZZ ,      OSM_LA  ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      OSM_RA  ,      CU_HOP  , CU_EQL  , KC_LEAD , KC_APP
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_NUMPAD] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , CU_DEG  , CU_EACUT, CU_LAST , CU_FIRST, CU_MAIL ,                                              KC_CALC , CU_PO   , CU_PC   , CU_LBRC , CU_RBRC , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_EXLM , CU_QUOT , CU_HASH , CU_TILD , CU_PERC , CU_EQL  ,                          KC_NLCK , KC_PSLS , KC_P7   , CU_P8   , KC_P9   , KC_PMNS , _______  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_CIRC , CU_PIPE , CU_AMPR , CU_DLR  , CU_DQUO , CU_COLN ,                          CU_BSLS , KC_PAST , CU_P4   , CU_P5   , CU_P6   , KC_PPLS , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_GRV_S, CU_AT   , CU_UNDS , CU_LT   , CU_GT   , _______ , CU_UE   ,      _______ , _______ , CU_COM_S, KC_P1   , KC_P2   , KC_P3   , KC_PENT , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_SZ   , CU_EURO , CU_QUES ,      _______ ,      CU_OE   , CU_AE   ,      _______ , _______ ,      _______ ,      KC_P0   , CU_DOT_S, KC_PENT , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_NAVIGATION] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , KC_PSCR , KC_SLCK , KC_PAUS , XXXXXXX , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , KC_MS_U , XXXXXXX , KC_WH_U , KC_WFWD ,                          XXXXXXX , KC_PGUP , KC_HOME , KC_UP   , KC_END  , XXXXXXX , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , KC_WBAK ,                          XXXXXXX , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_MYCM , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , KC_BTN1 , _______ , _______,       _______ , _______ , OSM_GUI , OSM_CA  , OSM_C   , OSM_CG  , XXXXXXX , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , _______ , _______ , _______ ,      _______ ,      KC_BTN2 , KC_BTN1,       _______ , _______ ,      _______ ,      XXXXXXX , XXXXXXX , _______ , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_GAMING] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            OSM_SHFT, TD_1_6  , TD_2_7  , TD_3_8  , TD_4_9  , TD_5_0  ,                                              KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , CU_TRCK ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_ESC  ,                          KC_ESC  , KC_Y    , KC_I    , KC_O    , KC_P    , KC_MPLY , CU_VOL  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , TD_F5_F0,                          XXXXXXX , KC_H    , KC_J    , KC_K    , KC_UP   , KC_L   , KC_RSFT ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LCTL , KC_Y    , KC_X    , KC_C    , KC_V    , KC_B    , KC_PGUP , KC_HOME ,      KC_END  , KC_PGDN , KC_N    , KC_M    , KC_LEFT , KC_DOWN , KC_RGHT , KC_RCTL ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            TD_F1_F6, TD_F2_F7, TD_F3_F8, TD_F4_F9,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      XXXXXXX , XXXXXXX , KC_LEAD , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_COLEMAK_DH_US] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            CU_VOL  , TD_F1_13, TD_F2_14, TD_F3_15, TD_F4_16, TD_F5_17,                                              TD_F8_20, TD_F9_21,TD_F10_22,TD_F11_23,TD_F12_24, CU_TRCK ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , TD_Q_EX , KC_W    , KC_F    , KC_P    , KC_B    , TD_F6_18,                          TD_F7_19, KC_J    , KC_L    , KC_U    , TD_Y_TM , KC_MINS , KC_MPLY ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , TD_PRNSO,                          TD_PRNSC, KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , OSM_C   ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            OSM_SHFT, KC_Z    , KC_X    , KC_C    , KC_D    , KC_V    , LT_PGUP , LT_HOME ,      LT_END  , LT_PGDN , KC_K    , KC_H    , KC_SCLN , KC_COMM , KC_DOT  , OSM_SHFT,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            OSM_GUI , OSM_MEH , OSM_HYP , CU_FUZZ ,      OSM_LA  ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      OSM_RA  ,      CU_HOP  , KC_EQL  , KC_LEAD , KC_APP
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        )

};
// clang-format on

// key code customization happens here
// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _COLEMAK_DH_DE:
            set_led_green;
            break;
        case _NUMPAD:
            set_led_blue;
            break;
        case _NAVIGATION:
            set_led_cyan;
            break;
        // case _GERMAN:
        //     set_led_red;
        //     break;
        // case _MULTIMEDIA:
        //     set_led_white;
        //     break;
        case _GAMING:
            set_led_yellow;
            break;
        case _COLEMAK_DH_US:
            set_led_magenta;
            break;
        default:
            set_led_off;
            break;
    }
    return state;
}

#ifdef LEADER_ENABLE
LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;

        // Sleep
        SEQ_ONE_KEY(KC_S) { tap_code(KC_SLEP); }  // st -> standard

        // Power
        SEQ_THREE_KEYS(KC_P, KC_W, KC_R) { tap_code(KC_PWR); }

        // Power
        SEQ_ONE_KEY(KC_W) { tap_code(KC_WAKE); }

        // debug
        SEQ_THREE_KEYS(KC_D, KC_B, KC_G) { tap_code16(DEBUG); }

        // nkro toggle
        SEQ_TWO_KEYS(KC_N, KC_K) { tap_code16(NK_TOGG); }

        // goto/turn on default layer
        SEQ_TWO_KEYS(KC_D, KC_F) { layer_on(def_layer); }  // df -> default

        // game mode
        SEQ_TWO_KEYS(KC_G, KC_A) { layer_on(_GAMING); }

        // set us as default layer
        SEQ_TWO_KEYS(KC_U, KC_S) {
            set_single_persistent_default_layer(_COLEMAK_DH_US);
            def_layer = _COLEMAK_DH_US;
        }

        // set ge(rman) as default layer
        SEQ_TWO_KEYS(KC_G, KC_E) {
            set_single_persistent_default_layer(_COLEMAK_DH_DE);
            def_layer = _COLEMAK_DH_DE;
        }

        // reset
        SEQ_THREE_KEYS(KC_R, KC_S, KC_T) { reset_keyboard(); }
    }

    leader_end();
}

#endif

void on_parens_open_tap(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (get_mods() & MOD_MASK_SHIFT) {
                SEND_STRING("{");
            } else {
                SEND_STRING("(");
            }
            break;
        case 2:
            SEND_STRING("[");
            break;
    }
}

void on_parens_close_tap(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (get_mods() & MOD_MASK_SHIFT) {
                SEND_STRING("}");
            } else {
                SEND_STRING(")");
            }
            break;
        case 2:
            SEND_STRING("]");
            break;
    }
}
