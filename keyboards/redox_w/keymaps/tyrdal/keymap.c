#include QMK_KEYBOARD_H
#include "de_us_layout.h"

#ifdef __clang__
#    pragma clang diagnostic ignored "-Wunknown-attributes"  // clangd does not know PROGMEM
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK_DH_DE 0
#define _NUMPAD 1
#define _NAVIGATION 2
#define _MULTIMEDIA 3
#define _GAMING 4
#define _COLEMAK_DH_US 5

enum custom_keycodes {
    CU_CODE = SAFE_RANGE,
};

// Shortcut to make keymap more readable
#define OSM_HYP OSM(MOD_HYPR)
#define OSM_MEH OSM(MOD_MEH)

#define C_BREAK LCTL(KC_PAUS)  // ctrl + break => cancel build process in msvs
#define CA_DEL LCA(KC_DEL)     // ctrl + alt + del
#define CS_ESC RCS(KC_ESC)     // ctrl + shift + esc => open task manager in windows

#define LT_PGUP LT(_NUMPAD, KC_PGUP)
#define LT_PGDN LT(_NUMPAD, KC_PGDN)
#define LT_HOME LT(_NAVIGATION, KC_HOME)
#define LT_END LT(_NAVIGATION, KC_END)
#define GT_MENU RGUI_T(KC_APP)
#define MO_MEDIA MO(_MULTIMEDIA)
#define TT_BASE TT(_COLEMAK_DH_DE)
#define TO_BASE TO(_COLEMAK_DH_DE)
#define TO_GAME TO(_GAMING)
#define DF_DE DF(_COLEMAK_DH_DE)
#define DF_US DF(_COLEMAK_DH_US)

#define VD_LEFT LCTL(LGUI(KC_LEFT))  // switch windows virtual desktop to the left
#define VD_RGHT LCTL(LGUI(KC_RGHT))  // switch windows virtual desktop to the right
#define BF_LEFT LCA(KC_LEFT)         // switch n/vim buffer to the left
#define BF_RGHT LCA(KC_RGHT)         // switch n/vim buffer to the right

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK_DH_DE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            KC_EXEC , DE_1    , CU_2    , CU_3    , DE_4    , DE_5    ,                                              CU_6    , CU_7    , CU_8    , CU_9    , CU_0    , MO_MEDIA,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , DE_Q    , DE_W    , DE_F    , DE_P    , DE_B    , KC_ESC  ,                          KC_ESC  , DE_J    , DE_L    , DE_U    , DE_Y    , CU_BSLS , CU_EQL  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            CU_SLSH , DE_A    , DE_R    , DE_S    , DE_T    , DE_G    , KC_LBRC ,                          KC_RBRC , DE_M    , DE_N    , DE_E    , DE_I    , KC_O    , CU_SCLN ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSPO , DE_Z    , DE_X    , DE_C    , DE_D    , DE_V    , LT_PGUP , LT_HOME ,      LT_END  , LT_PGDN , DE_K    , DE_H    , KC_MINS , CU_COMM , CU_DOT  , KC_RSPC ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            KC_LGUI , KC_LCTL , OSM_HYP , OSM_MEH ,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      KC_LEAD , CU_QUOT , KC_RALT , GT_MENU
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_NUMPAD] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            KC_LNUM , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                              KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_EXLM , CU_QUOT , KC_HASH , KC_TILD , KC_PERC , KC_F6   ,                          KC_F7   , KC_PSLS , KC_P7   , KC_P8   , KC_P9   , KC_PMNS, _______  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_QUES , KC_CIRC , KC_AMPR , KC_PIPE , KC_DLR  , KC_DQUO , _______ ,                          _______ , KC_PAST , KC_P4   , KC_P5   , KC_P6   , KC_PPLS , KC_COLN ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_AT   , CU_GRV  , KC_UNDS , KC_LT   , KC_GT   , _______ , _______,       _______ , _______ , KC_COMM , KC_P1   , KC_P2   , KC_P3   , KC_PENT , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , _______ , _______ , _______ ,      _______ ,      _______ , _______ ,      _______ , _______ ,      KC_P0   ,      KC_P0   , KC_PDOT , KC_PENT , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_NAVIGATION] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            C_BREAK , KC_F13  , KC_F14  , KC_F15  , KC_F16  , KC_F17  ,                                              KC_F20  , KC_F21  , KC_F22  , KC_F23  , KC_F24  , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , XXXXXXX , KC_MS_U , XXXXXXX , KC_WH_U , KC_F18  ,                          KC_F19  , KC_PGUP , VD_LEFT , KC_UP   , VD_RGHT , KC_HOME , KC_PSCR ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , CA_DEL  ,                          CS_ESC  , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_END  , KC_SLCK ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , KC_BTN1 , _______ , _______,       _______ , _______ , XXXXXXX , BF_LEFT , XXXXXXX , BF_RGHT , XXXXXXX , KC_PAUS ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , _______ , XXXXXXX , XXXXXXX ,      _______ ,      KC_BTN2 , KC_BTN1,       _______ , _______ ,      _______ ,      XXXXXXX , XXXXXXX , _______ , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_MULTIMEDIA] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            TO_BASE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , TO_GAME , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , KC_MUTE , KC_VOLD , KC_VOLU , XXXXXXX , XXXXXXX ,                          KC_WAKE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_MPRV , KC_MRWD , KC_MSTP , KC_MPLY , KC_MFFD , KC_MNXT , KC_EJCT ,                          KC_SLEP , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      DF_DE   , DF_US   , KC_PWR  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      XXXXXXX ,      XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX ,      XXXXXXX ,      RESET   , XXXXXXX , NK_ON   , NK_OFF
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_GAMING] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            TT_BASE , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                                              KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_ESC  ,                          KC_ESC  , KC_Y    , KC_I    , KC_O    , KC_P    , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , XXXXXXX ,                          XXXXXXX , KC_H    , KC_J    , KC_K    , KC_L    , XXXXXXX , KC_RSFT ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LCTL , KC_Y    , KC_X    , KC_C    , KC_V    , KC_B    , KC_PGUP , KC_HOME ,      KC_END  , KC_PGDN , KC_N    , KC_M    , XXXXXXX , KC_UP   , XXXXXXX , KC_RCTL ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [_COLEMAK_DH_US] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            KC_EXEC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                                              KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , MO_MEDIA,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_F    , KC_P    , KC_B    , KC_ESC  ,                          KC_ESC  , KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN , KC_QUOT ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_BSLS , KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , KC_LBRC ,                          KC_RBRC , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , KC_EQL  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSPO , KC_Z    , KC_X    , KC_C    , KC_D    , KC_V    , LT_PGUP , LT_HOME ,      LT_END  , LT_PGDN , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSPC ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            KC_LGUI , KC_LCTL , OSM_HYP , OSM_MEH ,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        )

};
// clang-format on

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

// first draft for umlaute and dead keys
void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;

        SEQ_ONE_KEY(KC_A) { SEND_STRING("ä"); }
        SEQ_TWO_KEYS(KC_A, KC_A) { SEND_STRING("Ä"); }
        SEQ_ONE_KEY(KC_O) { SEND_STRING("ö"); }
        SEQ_TWO_KEYS(KC_O, KC_O) { SEND_STRING("Ö"); }
        SEQ_ONE_KEY(KC_U) { SEND_STRING("ü"); }
        SEQ_TWO_KEYS(KC_U, KC_U) { SEND_STRING("Ü"); }
        SEQ_TWO_KEYS(KC_S, KC_S) { SEND_STRING("ß"); }
        SEQ_TWO_KEYS(KC_N, KC_R) { SEND_STRING("René"); }
        SEQ_TWO_KEYS(KC_N, KC_M) { SEND_STRING("Möhring"); }
        SEQ_TWO_KEYS(KC_E, KC_M) { SEND_STRING("rene_moehring@gmx.de"); }
    }

    leader_end();
}

#endif
