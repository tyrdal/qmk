#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "keycode.h"
#include "keycode_config.h"
#include "process_auto_shift.h"
#include "quantum_keycodes.h"
#include "report.h"
#include "send_string_keycodes.h"
#ifdef CONSOLE_ENABLE
#    include "xprintf.h"
#endif
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

enum custom_keycodes { CU_HOP = NEW_SAFE_RANGE, CU_FUZZY };
#define CU_ACC KC_EQL  // use german dead keys for accents

// Shortcut to make keymap more readable
#define LCTL_ESC LCTL_T(KC_ESC)
#define RCTL_ESC RCTL_T(KC_ESC)

#define OSM_GUI OSM(MOD_LGUI)
#define OSM_HYP OSM(MOD_HYPR)
#define OSM_MEH OSM(MOD_MEH)
#define OSM_SHFT OSM(MOD_LSFT)
#define OSM_LC OSM(MOD_LCTL)
#define OSM_RC OSM(MOD_RCTL)
#define OSM_CA OSM(MOD_LCTL | MOD_LALT)
#define OSM_CG OSM(MOD_LCTL | MOD_LGUI)
#define OSM_CS OSM(MOD_LCTL | MOD_LSFT)
#define OSM_LA OSM(MOD_LALT)
#define OSM_RA OSM(MOD_RALT)

#define OSL_SYM OSL(SYMBOLS)
#define OSL_NAV OSL(NAVIGATION)
#define OSL_NUM OSL(NUMPAD)

#define TG_GAME TG(GAMING)

#define LT_SYM_B LT(SYMBOLS, KC_BSPC)
#define LT_SYM_P LT(SYMBOLS, KC_PPLS)
#define LT_SYM_S LT(SYMBOLS, KC_SPC)
#define LT_SYM_A LT(SYMBOLS, KC_PAST)
#define LT_NAV_D LT(NAVIGATION, KC_DEL)
#define LT_NAV_M LT(NAVIGATION, CU_MINS)
#define LT_NAV_E LT(NAVIGATION, KC_ENT)
#define LT_NAV_S LT(NAVIGATION, CU_DSLSH)

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [COLEMAK_DH_DE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            KC_MPLY , TD_F1   , TD_F2   , TD_F3   , TD_F4   , TD_F5   ,                                              TD_F6   , TD_F7   , TD_F8   , TD_F9   , TD_F10  , TD_F11  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_F    , KC_P    , KC_B    , CU_FUZZY,                          CU_HOP  , KC_J    , KC_L    , KC_U    , DE_Y    , CU_DQUO , TD_F12  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , CU_EQL  ,                          CU_MINS , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , OSM_LC  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            OSM_SHFT, DE_Z    , KC_X    , KC_C    , KC_D    , KC_V    , OSL_SYM , OSL_NAV ,      OSL_NAV , OSL_SYM , KC_K    , KC_H    , KC_DOT  , KC_COMM , KC_UP   , OSM_SHFT,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            OSM_GUI , KC_LEAD , OSM_MEH , OSM_HYP ,      OSL_NUM ,      LT_SYM_B, LT_NAV_D,      LT_NAV_E, LT_SYM_S,      OSM_LA  ,      CU_DSLSH, KC_LEFT , KC_DOWN , KC_RIGHT
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [SYMBOLS] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , CU_1    , CU_2    , CU_3    , CU_4    , CU_5    ,                                              CU_6    , CU_7    , CU_8    , CU_9    , CU_0    , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_GRV  , CU_AT   , CU_PERC , CU_HASH , CU_LCURL, KC_HOME ,                          KC_END  , CU_RCURL, CU_EXLM , CU_AMPR , CU_UNDS , CU_ACC  , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_GRV_S, CU_TILD ,  CU_LT  , CU_GT   , CU_LP   , KC_PGUP ,                          KC_PGDN , CU_RP   , CU_CIRC , CU_EQL  , CU_DLR  , CU_PIPE , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌────────-┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_DEG  , CU_MAIL , CU_LAST , CU_FIRST, CU_QUES , _______ , _______ ,      _______ , _______ , CU_DQUO , DE_ADIA , DE_ODIA , DE_UDIA , CU_SZ   , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , _______ , _______ , _______ ,      _______ ,      LT_SYM_P, LT_NAV_M,      LT_NAV_S, LT_SYM_A,      _______ ,      _______ , XXXXXXX , XXXXXXX , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [NAVIGATION] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , KC_PSCR , KC_SLCK , KC_PAUS , XXXXXXX , XXXXXXX  ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , KC_WH_L , KC_MS_U , KC_WH_R , KC_WH_U , KC_WFWD ,                          KC_MSEL , KC_PGUP , KC_HOME , KC_UP   , KC_END  , KC_MYCM , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , KC_WBAK ,                          KC_MAIL , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , OSM_GUI , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN1 , KC_BTN2 , _______ , _______,       _______ , _______ , OSM_CS  , OSM_CA  , OSM_LC  , OSM_CG  , XXXXXXX , _______ ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , KC_BTN8 , KC_BTN7 , KC_BTN6 ,      _______ ,      KC_BTN2 , KC_BTN1,       XXXXXXX , XXXXXXX ,      _______ ,      KC_ACL0 , KC_ACL1 , KC_ACL2 , TG_GAME
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [NUMPAD] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , KC_SLEP , KC_PWR  , XXXXXXX , NK_ON   , NK_OFF  ,                                              KC_CALC , CU_LP   , CU_RP   , CU_LBRC , CU_RBRC , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            XXXXXXX , OSM_SHFT, OSM_SHFT, OSM_SHFT, OSM_SHFT, OSM_SHFT, KC_WFWD ,                          KC_NLCK , KC_PSLS , KC_P7   , CU_P8   , KC_P9   , KC_PMNS , KC_PMNS,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            LCTL_ESC, KC_MPRV , KC_MSTP , KC_MPLY , KC_MNXT , KC_VOLU , KC_WBAK ,                          KC_PSLS , KC_PAST , CU_P4   , CU_P5   , CU_P6   , KC_PPLS , KC_PPLS,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , OSM_SHFT, OSM_SHFT, OSM_SHFT, OSM_SHFT, KC_VOLD , XXXXXXX , XXXXXXX ,      KC_DEL  , KC_BSPC , CU_COM_S, KC_P1   , KC_P2   , KC_P3   , KC_PENT , KC_PENT ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX ,      _______ ,      KC_BSPC , KC_DEL  ,      KC_ENT  , KC_SPC  ,      _______ ,      KC_P0   , CU_DOT_S, KC_PENT , XXXXXXX
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),

    [GAMING] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            OSM_SHFT, TD_GA_1 , TD_GA_2 , TD_GA_3 , TD_GA_4 , TD_GA_5 ,                                              KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_VOLU ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_ESC  ,                          KC_BSPC , DE_Y    , KC_I    , KC_O    , KC_P    , KC_MPLY , KC_VOLD ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , TD_GA_F5,                          OSM_GUI , KC_H    , KC_J    , KC_K    , KC_UP   , KC_L    , KC_RSFT ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            OSM_LC  , DE_Y    , KC_X    , KC_C    , KC_V    , KC_B    , KC_PGUP , KC_HOME ,      KC_END  , KC_PGDN , KC_N    , KC_M    , KC_LEFT , KC_DOWN , KC_RGHT , OSM_RC  ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            TD_GA_F1, TD_GA_F2, TD_GA_F3, TD_GA_F4,      OSM_LA  ,      KC_SPC  , KC_ENT  ,      KC_DEL  , KC_BSPC ,      OSM_RA  ,      XXXXXXX , XXXXXXX , KC_LEAD , TG_GAME
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        )
};
// clang-format on

// key code customization happens here
bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    uint8_t mods             = get_mods();
    uint8_t osm_mods         = get_oneshot_mods();
    bool    is_ctrl_pressed  = (mods | osm_mods) & MOD_MASK_CTRL;
    bool    is_alt_pressed   = (mods | osm_mods) & MOD_MASK_ALT;
    bool    is_shift_pressed = (mods | osm_mods) & MOD_MASK_SHIFT;
    bool    pressed          = record->event.pressed;

#ifdef CONSOLE_ENABLE
    // xprintf("     c %d | a %d | s %d \n", is_ctrl_pressed, is_alt_pressed, is_shift_pressed);
    // xprintf("hold c %d | a %d | s %d \n", mods & MOD_MASK_CTRL, mods & MOD_MASK_ALT, mods & MOD_MASK_SHIFT);
    // xprintf("osm  c %d | a %d | s %d \n", osm_mods & MOD_MASK_CTRL, osm_mods & MOD_MASK_ALT, osm_mods & MOD_MASK_SHIFT);
#endif

    // Here we can clear all oneshot modifiers because only codes using SEND_STRING follow
    // therefore this section needs to be the last
    // should this change then modifier handling needs to be adjusted
    // hold modifiers need to be reinstated though
    clear_mods();
    clear_oneshot_mods();
    switch (keycode) {
        case CU_HOP:
            if (pressed) {
                if (is_ctrl_pressed) {
                    SEND_STRING(SS_TAP(X_ESCAPE) " he");
                } else if (is_alt_pressed) {
                    SEND_STRING(SS_TAP(X_ESCAPE) " hj");
                } else if (is_shift_pressed) {
                    SEND_STRING(SS_TAP(X_ESCAPE) " hG");
                } else {
                    SEND_STRING(SS_TAP(X_ESCAPE) " hg");
                }
            }
            break;
        case CU_FUZZY:
            if (pressed) {
                if (is_ctrl_pressed) {
                    SEND_STRING(SS_TAP(X_ESCAPE) " fr");
                } else if (is_alt_pressed) {
                    SEND_STRING(SS_TAP(X_ESCAPE) " fb");
                } else if (is_shift_pressed) {
                    SEND_STRING(SS_TAP(X_ESCAPE) " fy");
                } else {
                    SEND_STRING(SS_TAP(X_ESCAPE) " ff");
                }
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
    def_layer = eeconfig_read_default_layer();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case COLEMAK_DH_DE:
            set_led_off;
            autoshift_enable();
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
            set_led_all;
            autoshift_disable();
            break;
        default:
            break;
    }
    return state;
}

#ifdef LEADER_ENABLE
LEADER_EXTERNS();

uint8_t leader_matched = 0;
void    matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading        = false;
        leader_matched = 0;

        // debug
        SEQ_THREE_KEYS(KC_D, KC_B, KC_G) {
            leader_matched = 1;
            tap_code16(DEBUG);
        }

        // reset
        SEQ_THREE_KEYS(KC_R, KC_S, KC_T) {
            leader_matched = 2;
            reset_keyboard();
        }

        leader_end();
    }
}

void leader_end(void) {
#   ifdef CONSOLE_ENABLE
    xprintf("%d %d %d %d %d\n", leader_sequence[0], leader_sequence[1], leader_sequence[2], leader_sequence[3], leader_sequence[4]);
    xprintf("m %d\n", leader_matched);
#   endif
}

#endif

// TODO
// - Timeouts for leader key
