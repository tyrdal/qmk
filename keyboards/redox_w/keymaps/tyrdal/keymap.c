#include "action.h"
#include "action_code.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "keycode.h"
#include "keycode_legacy.h"
#include "process_leader.h"
#include "process_tap_dance.h"
#include "quantum.h"
#include "quantum_keycodes.h"
// #include "xprintf.h"
#include QMK_KEYBOARD_H
#include "de_us_layout.h"
#include "keymap_german.h"

#ifdef __clang__
#    pragma clang diagnostic ignored "-Wunknown-attributes"  // clangd does not know PROGMEM
#endif

extern uint8_t def_layer;

enum Layers {
    COLEMAK_DH_DE,
    SYMBOLS,
    NAVIGATION,
    NUMPAD,
    GAMING,
};

enum custom_keycodes {
    CU_CODE = NEW_SAFE_RANGE,
};
#define CU_ACC KC_EQL  // use german dead keys for accents

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

#define OSL_SYM OSL(SYMBOLS)
#define OSL_NAV OSL(NAVIGATION)
#define OSL_NUM OSL(NUMPAD)

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
    TD_Q_PO,  // Q - (
    TD_Y_PC,  // Y - )
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
    // TD_PRNSO,
    // TD_PRNSC,
    TD_RBRC,
    TD_LBRC
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
	[TD_Q_PO] = ACTION_TAP_DANCE_DOUBLE(KC_Q, S(KC_8)),
	[TD_Y_PC] = ACTION_TAP_DANCE_DOUBLE(DE_Y, S(KC_9)),
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
	[TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(ALGR(KC_8), ALGR(KC_7)),
	[TD_RBRC] = ACTION_TAP_DANCE_DOUBLE(ALGR(KC_9), ALGR(KC_0)),
	// [TD_PRNSO] = ACTION_TAP_DANCE_FN(on_parens_open_tap),
	// [TD_PRNSC] = ACTION_TAP_DANCE_FN(on_parens_close_tap),
};

// create tap dance keycodes
#define TD_GA_1 TD(TD_1_6)
#define TD_GA_2 TD(TD_2_7)
#define TD_GA_3 TD(TD_3_8)
#define TD_GA_4 TD(TD_4_9)
#define TD_GA_5 TD(TD_5_0)
#define TD_GA_F1 TD(TD_F1_F6)
#define TD_GA_F2 TD(TD_F2_F7)
#define TD_GA_F3 TD(TD_F3_F8)
#define TD_GA_F4 TD(TD_F4_F9)
#define TD_GA_F5 TD(TD_F5_F0)
#define TD_Q TD(TD_Q_PO)  // Q - (
#define TD_Y TD(TD_Y_PC)  // Y - )
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
// #define TD_PO TD(TD_PRNSO)
// #define TD_PC TD(TD_PRNSC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [COLEMAK_DH_DE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            KC_MPLY , TD_F1   , TD_F2   , TD_F3   , TD_F4   , TD_F5   ,                                              TD_F6   , TD_F7   , TD_F8   , TD_F9   , TD_F10  , TD_F11  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , TD_Q    , KC_W    , KC_F    , KC_P    , KC_B    , OSL_NAV ,                          OSL_NAV , KC_J    , KC_L    , KC_U    , TD_Y    , CU_MINS , TD_F12  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , CU_LBRC ,                          CU_RBRC , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , OSM_C   ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            OSL_NUM , DE_Z    , KC_X    , KC_C    , KC_D    , KC_V    , OSL_SYM , KC_HOME ,      KC_END  , OSL_SYM , KC_K    , KC_H    , KC_DOT  , KC_COMM , KC_UP   , OSM_SHFT,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            OSM_GUI , KC_LEAD , OSM_MEH , OSM_HYP ,      OSM_LA  ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      OSM_RA  ,      CU_DQUO , KC_LEFT , KC_DOWN , KC_RIGHT
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [SYMBOLS] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX  , XXXXXXX, XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_DQUO , CU_AT   , CU_PERC , CU_COLN , CU_PO   , CU_TILD ,                          KC_GRV  , CU_UNDS , CU_BSLS , CU_SLSH , CU_AMPR , CU_ACC  , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_SCLN , CU_LT   , CU_GT   , CU_HASH , CU_EXLM , _______ ,                          _______ , CU_CIRC , CU_QUES , CU_EQL  , CU_DLR  , CU_PIPE , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_GRV_S, CU_AT   , CU_UNDS , CU_LT   , CU_GT   , _______ , KC_PGUP ,      KC_PGDN , _______ , CU_COM_S, DE_ADIA , DE_ODIA , DE_UDIA , CU_SZ   , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , _______ , _______ , _______ ,      _______ ,      KC_PPLS , KC_PMNS ,      KC_PSLS , KC_PAST ,      _______ ,      _______ , XXXXXXX , XXXXXXX , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [NAVIGATION] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , KC_ACL0 , KC_ACL1 , KC_ACL2 , XXXXXXX ,                                              XXXXXXX , KC_PSCR , KC_SLCK , KC_PAUS , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , KC_WH_L , KC_MS_U , KC_WH_R , KC_WH_U , OSL_NAV ,                          OSL_NAV , KC_PGUP , KC_HOME , KC_UP   , KC_END  , KC_MYCM , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , XXXXXXX ,                          XXXXXXX , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , OSM_GUI , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN1 , KC_BTN2 , _______ , _______,       _______ , _______ , XXXXXXX , OSM_CA  , OSM_C   , OSM_CG  , XXXXXXX , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_BTN8 , KC_BTN7 , KC_BTN6 ,      _______ ,      KC_BTN2 , KC_BTN1,       KC_BTN1 , KC_BTN2 ,      _______ ,      XXXXXXX , XXXXXXX , _______ , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [NUMPAD] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              KC_CALC , CU_PO   , CU_PC   , CU_LBRC , CU_RBRC , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_WFWD ,                          KC_NLCK , KC_PSLS , KC_P7   , CU_P8   , KC_P9   , KC_PMNS , KC_PMNS,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_WBAK ,                          KC_PSLS , KC_PAST , CU_P4   , CU_P5   , CU_P6   , KC_PPLS , KC_PPLS,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            OSL_NUM , OSM_SHFT, OSM_SHFT, OSM_SHFT, OSM_SHFT, XXXXXXX , XXXXXXX , XXXXXXX ,      KC_DEL  , KC_BSPC , CU_COM_S, KC_P1   , KC_P2   , KC_P3   , KC_PENT , KC_PENT ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX ,      _______ ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      _______ ,      KC_P0   , CU_DOT_S, KC_PENT , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [GAMING] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            OSM_SHFT, TD_GA_1 , TD_GA_2 , TD_GA_3 , TD_GA_4 , TD_GA_5 ,                                              KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_VOLU ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_ESC  ,                          KC_ESC  , DE_Y    , KC_I    , KC_O    , KC_P    , KC_MPLY , KC_VOLD ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , TD_GA_F5,                          XXXXXXX , KC_H    , KC_J    , KC_K    , KC_UP   , KC_L    , KC_RSFT ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LCTL , DE_Y    , KC_X    , KC_C    , KC_V    , KC_B    , KC_PGUP , KC_HOME ,      KC_END  , KC_PGDN , KC_N    , KC_M    , KC_LEFT , KC_DOWN , KC_RGHT , KC_RCTL ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            TD_GA_F1, TD_GA_F2, TD_GA_F3, TD_GA_F4,      KC_LALT ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      KC_RALT ,      XXXXXXX , XXXXXXX , KC_LEAD , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        )
};
// clang-format on

// key code customization happens here
// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

// For some uknown reason the colors are garbled and I have a yellow instead of a green led
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

void matrix_init_user(void) {
    set_led_off;
    def_layer = eeconfig_read_default_layer();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case COLEMAK_DH_DE:
            set_led_off;
            break;
        case SYMBOLS:
            set_led_blue;
            break;
        case NAVIGATION:
            set_led_yellow;
            break;
        case NUMPAD:
            set_led_red;
            break;
        case GAMING:
            red_led_on;
            yellow_led_on;
            blu_led_on;
            break;
        default:
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

        // Wake
        SEQ_ONE_KEY(KC_W) { tap_code(KC_WAKE); }

        // debug
        SEQ_THREE_KEYS(KC_D, KC_B, KC_G) { tap_code16(DEBUG); }

        // nkro toggle
        SEQ_TWO_KEYS(KC_N, KC_K) { tap_code16(NK_TOGG); }

        // goto/turn on default layer
        SEQ_TWO_KEYS(KC_D, KC_F) { layer_on(def_layer); }  // df -> default

        // game mode
        SEQ_TWO_KEYS(KC_G, KC_A) { layer_on(GAMING); }

        // reset
        SEQ_THREE_KEYS(KC_R, KC_S, KC_T) { reset_keyboard(); }
    }

    leader_end();
}
#endif

// void on_parens_open_tap(qk_tap_dance_state_t* state, void* user_data) {
//     bool is_shift_pressed = get_mods() & MOD_MASK_SHIFT;
//     switch (state->count) {
//         case 1:
//             if (is_shift_pressed) {
//                 del_weak_mods(MOD_MASK_SHIFT);
//                 tap_code16(ALGR(KC_7));  // {
//             } else {
//                 tap_code16(S(KC_8));  // (
//             }
//             break;
//         case 2:
//             if (is_shift_pressed) {
//                 del_weak_mods(MOD_MASK_SHIFT);
//             }
//             register_code16(ALGR(KC_8));  // [
//             break;
//     }
// }
//
// void on_parens_close_tap(qk_tap_dance_state_t* state, void* user_data) {
//     bool is_shift_pressed = get_mods() & MOD_MASK_SHIFT;
//     switch (state->count) {
//         case 1:
//             if (is_shift_pressed) {
//                 unregister_code16(KC_LSFT | KC_RSFT);
//                 tap_code16(ALGR(KC_0));  // }
//                 register_code16(KC_LSFT);
//             } else {
//                 tap_code16(S(KC_9));  // )
//             }
//             break;
//         case 2:
//             if (is_shift_pressed) {
//                 unregister_code16(KC_LSFT | KC_RSFT);
//             }
//             register_code16(ALGR(KC_9));  // ]
//             if (is_shift_pressed) {
//                 register_code16(KC_LSFT);
//             }
//             break;
//     }
// }
