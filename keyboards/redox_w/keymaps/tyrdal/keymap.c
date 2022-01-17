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
    _MULTIMEDIA,
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

#define C_BREAK LCTL(KC_PAUS)  // ctrl + break => cancel build process in msvs
#define CA_DEL LCA(KC_DEL)     // ctrl + alt + del
#define CS_ESC RCS(KC_ESC)     // ctrl + shift + esc => open task manager in windows

#define LT_PGUP LT(_NUMPAD, KC_PGUP)
#define LT_PGDN LT(_NUMPAD, KC_PGDN)
#define LT_HOME LT(_NAVIGATION, KC_HOME)
#define LT_END LT(_NAVIGATION, KC_END)
#define OL_MEDIA OSL(_MULTIMEDIA)
#define DF_DE DF(_COLEMAK_DH_DE)
#define DF_US DF(_COLEMAK_DH_US)

#define VD_LEFT LCTL(LGUI(KC_LEFT))  // switch windows virtual desktop to the left
#define VD_RGHT LCTL(LGUI(KC_RGHT))  // switch windows virtual desktop to the right
#define BF_LEFT LCA(KC_LEFT)         // switch n/vim buffer to the left
#define BF_RGHT LCA(KC_RGHT)         // switch n/vim buffer to the right
#define TAB_LEFT LCA(KC_UP)          // switch n/vim tab to the left
#define TAB_RGHT LCA(KC_DOWN)        // switch n/vim tab to the right

// IMPORTANT:
// With the current implementation you cannot use CU_LSPO/CU_RSPC at the same time as the normal KC_LSFT/KC_RSFT
// modifiers. Choose one set or the other.

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
    TD_Q_PLY,  // Q - Media Play/Pause
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
	[TD_Q_PLY] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_MPLY),
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
};

// check which one feels more ergonomic
// Idea: remove numbers on default layer and replace with all 24 F-Keys, make sure all symbols are covered on def + numpad
// Idea: alternative-> flip number on default so the symbols are normal and the nmber shifted => all F-Keys can
//       replace symbols on the numpad layer, numlock goes to num side

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK_DH_DE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            CU_VOL  , TD_F1_13, TD_F2_14, TD_F3_15, TD_F4_16, TD_F5_17,                                              TD_F8_20, TD_F9_21,TD_F10_22,TD_F11_23,TD_F12_24, OL_MEDIA,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , TD_Q_PLY, DE_W    , DE_F    , DE_P    , DE_B    , TD_F6_18,                          TD_F7_19, DE_J    , DE_L    , DE_U    , DE_Y    , CU_MINS , CU_EQL  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, DE_A    , DE_R    , DE_S    , DE_T    , DE_G    , KC_LBRC ,                          KC_RBRC , DE_M    , DE_N    , DE_E    , DE_I    , DE_O    , RCTL_ESC,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            CU_LSPO , DE_Z    , DE_X    , DE_C    , DE_D    , DE_V    , LT_PGUP , LT_HOME ,      LT_END  , LT_PGDN , DE_K    , DE_H    , CU_SCLN , CU_COMM , CU_DOT  , CU_RSPC ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            OSM_GUI , KC_MYCM , OSM_MEH , OSM_HYP ,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      KC_LEAD , CU_QUOT , KC_APP  , KC_RGUI
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_NUMPAD] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , CU_DEG  , CU_EACUT, CU_LAST , CU_FIRST, CU_MAIL ,                                              KC_CALC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_EXLM , CU_QUOT , CU_HASH , CU_TILD , CU_PERC , KC_PASTE,                          KC_NUM  , KC_PSLS , KC_P7   , CU_P8   , KC_P9   , KC_PMNS , _______  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_CIRC , CU_AMPR , CU_PIPE , CU_DLR  , CU_DQUO , CU_COLN ,                          CU_BSLS , KC_PAST , CU_P4   , CU_P5   , CU_P6   , KC_PPLS , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_AT   , CU_GRV_S, CU_UNDS , CU_LT   , CU_GT   , _______ , CU_UE   ,      _______ , _______ , CU_COM_S, KC_P1   , KC_P2   , KC_P3   , KC_PENT , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_SZ   , CU_EURO , CU_QUES ,      _______ ,      CU_OE   , CU_AE   ,      _______ , _______ ,      _______ ,      KC_P0   , CU_DOT_S, KC_PENT , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_NAVIGATION] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              C_BREAK , KC_PSCR , KC_SLCK , KC_PAUS , CS_ESC  , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , KC_MS_U , XXXXXXX , KC_WH_U , XXXXXXX ,                          XXXXXXX , KC_PGUP , VD_LEFT , KC_UP   , VD_RGHT , KC_HOME , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , XXXXXXX ,                          CA_DEL  , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_END  , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , KC_BTN1 , _______ , _______,       _______ , _______ , TAB_LEFT, BF_LEFT , XXXXXXX , BF_RGHT , TAB_RGHT, _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , _______ , _______ , _______ ,      _______ ,      KC_BTN2 , KC_BTN1,       _______ , _______ ,      _______ ,      XXXXXXX , XXXXXXX , _______ , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_MULTIMEDIA] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , OL_MEDIA,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , KC_MUTE , KC_VOLD , KC_VOLU , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_MPRV , KC_MRWD , KC_MSTP , KC_MPLY , KC_MFFD , KC_MNXT , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_WAKE , KC_PWR  ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      XXXXXXX ,      KC_SLEP , XXXXXXX ,      XXXXXXX , XXXXXXX ,      XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_GAMING] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            OSM_SHFT, TD_1_6  , TD_2_7  , TD_3_8  , TD_4_9  , TD_5_0  ,                                              KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , OL_MEDIA,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_ESC  ,                          KC_ESC  , KC_Y    , KC_I    , KC_O    , KC_P    , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , TD_F5_F0,                          XXXXXXX , KC_H    , KC_J    , KC_K    , KC_UP   , KC_L   , KC_RSFT ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LCTL , KC_Y    , KC_X    , KC_C    , KC_V    , KC_B    , KC_PGUP , KC_HOME ,      KC_END  , KC_PGDN , KC_N    , KC_M    , KC_LEFT , KC_DOWN , KC_RGHT , KC_RCTL ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            TD_F1_F6, TD_F2_F7, TD_F3_F8, TD_F4_F9,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      KC_LEAD , XXXXXXX , XXXXXXX , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_COLEMAK_DH_US] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            CU_VOL  , TD_F1_13, TD_F2_14, TD_F3_15, TD_F4_16, TD_F5_17,                                              TD_F8_20, TD_F9_21,TD_F10_22,TD_F11_23,TD_F12_24, OL_MEDIA,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , TD_Q_PLY, KC_W    , KC_F    , KC_P    , KC_B    , KC_BSLS ,                          KC_SLSH , KC_J    , KC_L    , KC_U    , KC_Y    , KC_MINS , KC_EQL  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , KC_LBRC ,                          KC_RBRC , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , RCTL_ESC,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSPO , KC_Z    , KC_X    , KC_C    , KC_D    , KC_V    , LT_PGUP , LT_HOME ,      LT_END  , LT_PGDN , KC_K    , KC_H    , KC_SCLN , KC_COMM , KC_DOT  , KC_RSPC ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            OSM_GUI , KC_MYCM , OSM_MEH , OSM_HYP ,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      KC_LEAD , CU_QUOT , KC_APP  , KC_RGUI
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
            set_led_yellow;
            break;
        /*case _GERMAN:
            set_led_red;
            break;*/
        case _MULTIMEDIA:
            set_led_magenta;
            break;
        case _GAMING:
            set_led_white;
            break;
        case _COLEMAK_DH_US:
            set_led_cyan;
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

        // debug
        SEQ_THREE_KEYS(KC_D, KC_B, KC_G) { tap_code16(DEBUG); }

        // nkro toggle
        SEQ_TWO_KEYS(KC_N, KC_K) { tap_code16(NK_TOGG); }

        // goto/turn on default layer
        SEQ_TWO_KEYS(KC_D, KC_F) { layer_on(def_layer); }  // df -> default
        SEQ_TWO_KEYS(KC_S, KC_T) { layer_on(def_layer); }  // st -> standard

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
