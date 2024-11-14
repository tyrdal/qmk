#if __has_include("passwords.h")
#    define HAS_PASSWORDS
#endif

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
#ifdef HAS_PASSWORDS
#    include "passwords.h"
#endif

#ifdef __clang__
#    undef PROGMEM
#    define PROGMEM // clangd does not know PROGMEM
#endif

// TODO split into different parts that can be included/linked

enum custom_keycodes {
    CU_BUF = NEW_SAFE_RANGE,
    CU_OLBUF,
    CU_GREP,
    CU_LGREP,
    CU_LDIAG,
    CU_FDIAG,
    CU_HELP,
    CU_GOTO,
    CU_CTRX,
    CU_CIW,
    CU_BLCK,
    CU_SYS,
    CU_ZERO,
    CU_SEL_LINE,
    CU_CLEAR_LINE,
    CU_ARROW,
    CU_SCOPE,
    CU_PARENS,
    CU_BRACKETS,
    CU_BRACES,
    CU_LTGT,
    CU_DQUOTES,
    CU_SQUOTES,
    CU_JUMP,
    CU_IN_W,
    CU_IN_WW,
    CU_AS,
    CU_RESET,
    CU_ROOT,
    CU_USER,
    CU_GIT,
    CU_EW,
    CU_BK,
};

#ifdef COMBO_ENABLE
enum COMBO_KEYCODES {
    CB_SELWRD_R,
    CB_SEL_LINE,
    CB_SELWRD_L,
    CB_CLR_LINE,
    CB_CAPS_WORD,
    CB_ARROW,
    CB_SCOPE,
    CB_PARENS,
    CB_BRACKETS,
    CB_BRACES,
    CB_LTGT,
    CB_DQUOTES,
    CB_SQUOTES,
    CB_JUMP,
    CB_IN_WORD,
    CB_IN_WWORD,
};

const uint16_t PROGMEM combo_select_word_right[] = {KC_U, KC_Z, COMBO_END};
const uint16_t PROGMEM combo_select_word_left[]  = {KC_U, KC_L, COMBO_END};
const uint16_t PROGMEM combo_select_line[]       = {KC_L, KC_U, KC_Z, COMBO_END};
const uint16_t PROGMEM combo_clear_line[]        = {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM combo_caps_word[]         = {KC_C, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_arrow[]             = {KC_H, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_scope[]             = {KC_DOT, CU_COMM, COMBO_END};
const uint16_t PROGMEM combo_parens[]            = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM combo_brackets[]          = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM combo_braces[]            = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM combo_ltgt[]              = {KC_X, CU_COMM, COMBO_END};
const uint16_t PROGMEM combo_double_quote[]      = {KC_E, KC_N, COMBO_END};
const uint16_t PROGMEM combo_single_quote[]      = {KC_E, KC_I, KC_N, COMBO_END};
const uint16_t PROGMEM combo_jump[]              = {KC_E, KC_N, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_in_word[]           = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_in_WORD[]           = {KC_R, KC_S, KC_T, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [CB_SELWRD_R]  = COMBO(combo_select_word_right, LCTL(LSFT(KC_RIGHT))),
    [CB_SELWRD_L]  = COMBO(combo_select_word_left,  LCTL(LSFT(KC_LEFT))),
    [CB_CLR_LINE]  = COMBO(combo_clear_line,        CU_CLEAR_LINE),
    [CB_SEL_LINE]  = COMBO(combo_select_line,       CU_SEL_LINE),
    [CB_CAPS_WORD] = COMBO(combo_caps_word,         QK_CAPS_WORD_TOGGLE),
    [CB_ARROW]     = COMBO(combo_arrow,             CU_ARROW),
    [CB_SCOPE]     = COMBO(combo_scope,             CU_SCOPE),
    [CB_PARENS]    = COMBO(combo_parens,            CU_PARENS),
    [CB_BRACKETS]  = COMBO(combo_brackets,          CU_BRACKETS),
    [CB_BRACES]    = COMBO(combo_braces,            CU_BRACES),
    [CB_LTGT]      = COMBO(combo_ltgt,              CU_LTGT),
    [CB_DQUOTES]   = COMBO(combo_double_quote,      CU_DQUOTES),
    [CB_SQUOTES]   = COMBO(combo_single_quote,      CU_SQUOTES),
    [CB_JUMP]      = COMBO(combo_jump,              CU_JUMP),
    [CB_IN_WORD]   = COMBO(combo_in_word,           CU_IN_W),
    [CB_IN_WWORD]  = COMBO(combo_in_WORD,           CU_IN_WW),
};
// clang-format on
#endif

extern uint8_t def_layer;

enum Layers {
    BASE,
    SYMBOLS,
    NUMPAD,
    FKEYS,
#ifdef MOUSE_ENABLE
    MOUSE,
#endif
    UTIL,
};

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
#define OSL_UTIL OSL(UTIL)
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
    TD_CW_CIW,
};

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
  [TD_F1_13]  = ACTION_TAP_DANCE_DOUBLE(KC_F1,KC_F13),
  [TD_F2_14]  = ACTION_TAP_DANCE_DOUBLE(KC_F2,KC_F14),
  [TD_F3_15]  = ACTION_TAP_DANCE_DOUBLE(KC_F3,KC_F15),
  [TD_F4_16]  = ACTION_TAP_DANCE_DOUBLE(KC_F4,KC_F16),
  [TD_F5_17]  = ACTION_TAP_DANCE_DOUBLE(KC_F5,KC_F17),
  [TD_F6_18]  = ACTION_TAP_DANCE_DOUBLE(KC_F6,KC_F18),
  [TD_F7_19]  = ACTION_TAP_DANCE_DOUBLE(KC_F7,KC_F19),
  [TD_F8_20]  = ACTION_TAP_DANCE_DOUBLE(KC_F8,KC_F20),
  [TD_F9_21]  = ACTION_TAP_DANCE_DOUBLE(KC_F9,KC_F21),
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
            OSL_MOUS, XXXXXXX , XXXXXXX , OSL_UTIL,     LT_FKEY_C,      LT_SYM_B, LT_NUM_D,      LT_NUM_E, LT_SYM_S,      OSM_LA  ,      QK_REP  , QK_AREP , XXXXXXX , OSL_MOUS
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
#ifdef MOUSEKEY_ENABLE
    [MOUSE] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
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
#endif
    [UTIL] = LAYOUT(
        //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                                            ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                              XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐                        ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX , KC_PWR  , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , CU_ROOT , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , CU_AS   , CU_RESET, KC_SLEP , NK_TOGG , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , CU_GIT  , CU_USER , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX , DB_TOGG , XXXXXXX , XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , CU_EW   , CU_BK   , XXXXXXX , XXXXXXX , XXXXXXX ,
        //├─────────┼─────────┼─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┤    ├─────────┼─────────┼────┬────┴────┬────┼─────────┼─────────┼─────────┼─────────┤
            _______ , XXXXXXX , XXXXXXX , XXXXXXX ,      _______ ,      XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX ,      XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , _______
        //└─────────┴─────────┴─────────┴─────────┘    └─────────┘    └─────────┴─────────┘    └─────────┴─────────┘    └─────────┘    └─────────┴─────────┴─────────┴─────────┘
        ),
};
// clang-format on

// For some unknown reason the colors are garbled and I have a yellow instead of a green led
#undef set_led_off
#undef set_led_red
#undef set_led_blue
#undef set_led_yellow
#undef set_led_green
#undef red_led_off
#undef red_led_on

#define red_led_off PORTD |= (1 << 1)
#define red_led_on PORTD &= ~(1 << 1)
#define blue_led_off PORTF |= (1 << 5)
#define blue_led_on PORTF &= ~(1 << 5)
#define yellow_led_off PORTF |= (1 << 4)
#define yellow_led_on PORTF &= ~(1 << 4)
#define green_led_off PORTD |= (1 << 0)
#define green_led_on PORTD &= ~(1 << 0)

#define set_led_off \
    red_led_off;    \
    yellow_led_off; \
    blue_led_off;   \
    green_led_off;

#define set_led_red \
    red_led_on;     \
    yellow_led_off; \
    blue_led_off;   \
    green_led_off;

#define set_led_blue \
    red_led_off;     \
    yellow_led_off;  \
    blue_led_on
#define set_led_yellow \
    red_led_off;       \
    yellow_led_on;     \
    blue_led_off;      \
    green_led_off;

#define set_led_green \
    red_led_off;      \
    yellow_led_off;   \
    blue_led_off;     \
    green_led_on;

#define set_led_violet \
    red_led_on;        \
    yellow_led_off;    \
    blue_led_on;       \
    green_led_off;

#define set_led_all \
    red_led_on;     \
    yellow_led_on;  \
    blue_led_on;    \
    green_led_on;

void enable_red_led(bool enable) {
    if (enable) {
        red_led_on;
    } else {
        red_led_off;
    }
}

void enable_green(bool enable) {
    if (enable) {
        green_led_on;
    } else {
        green_led_off;
    }
}
void enable_blue_led(bool enable) {
    if (enable) {
        blue_led_on;
    } else {
        blue_led_off;
    }
}
void enable_yellow_led(bool enable) {
    if (enable) {
        yellow_led_on;
    } else {
        yellow_led_off;
    }
}
void matrix_init_user(void) {
    set_led_off;
    // def_layer = eeconfig_read_default_layer();
}

void matrix_scan_user(void) {
    uint8_t mods          = get_mods();
    uint8_t osm_mods      = get_oneshot_mods();
    uint8_t combined_mods = osm_mods | mods;

    bool is_ctrl_pressed  = combined_mods & MOD_MASK_CTRL;
    bool is_alt_pressed   = combined_mods & MOD_MASK_ALT;
    bool is_shift_pressed = combined_mods & MOD_MASK_SHIFT;
    bool is_gui_pressed   = combined_mods & MOD_MASK_GUI;

    enable_red_led(is_gui_pressed);
    enable_green(is_shift_pressed);
    enable_blue_led(is_ctrl_pressed);
    enable_yellow_led(is_alt_pressed);
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//         case BASE:
//             set_led_off;
//             break;
//         case SYMBOLS:
//             set_led_blue;
//             break;
//         case NUMPAD:
//             set_led_green;
//             break;
//         case FKEYS:
//             set_led_red;
//             break;
//         case MOUSE:
//             set_led_yellow;
//         default:
//             break;
//     }
//     return state;
// }

// key customization happens here
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods          = get_mods();
    uint8_t osm_mods      = get_oneshot_mods();
    uint8_t combined_mods = osm_mods | mods;

    bool pressed          = record->event.pressed;
    bool is_shift_pressed = combined_mods & MOD_MASK_SHIFT;

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
                // use black hole register
                SEND_STRING("@?");
            }
            break;

        case CU_SYS:
            if (pressed) {
                // use the + system register
                SEND_STRING("@]");
            }
            break;

        case CU_ZERO:
            if (pressed) {
                // "0 use last inserted text for pasting
                SEND_STRING("@0");
            }
            break;

        case CU_RESET:
            if (pressed) {
                reset_keyboard();
            }
            break;

        case CU_AS:
#ifdef CONSOLE_ENABLE
            // TODO print autoshift_is_enabled();
#endif
            autoshift_toggle();
            break;

#ifdef HAS_PASSWORDS
        case CU_ROOT:
            if (pressed) {
                SEND_STRING(ROOT);
            }
            break;

        case CU_USER:
            if (pressed) {
                SEND_STRING(USER);
            }
            break;

        case CU_GIT:
            if (pressed) {
                SEND_STRING(GITHUB);
            }
            break;

        case CU_EW:
            if (pressed) {
                SEND_STRING(BDR_EW);
            }
            break;

        case CU_BK:
            if (pressed) {
                SEND_STRING(BDR_BK);
            }
            break;
#endif

#ifdef COMBO_ENABLE
        case CU_SEL_LINE:
            if (pressed) {
                tap_code16(KC_END);
                tap_code16(LSFT(KC_HOME));
                break;
            }

        case CU_CLEAR_LINE:
            if (pressed) {
                tap_code16(KC_END);
                tap_code16(LSFT(KC_HOME));
                tap_code16(KC_BSPC);
            }
            break;

        case CU_ARROW: // Arrow macro, types -> or =>.
            if (record->event.pressed) {
                if (is_shift_pressed) {
                    // Temporarily delete shift.
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    unregister_mods(MOD_MASK_SHIFT);
                    SEND_STRING(SS_LSFT(SS_TAP(X_0)) SS_LSFT(SS_TAP(X_NUBS)));
                    register_mods(mods); // Restore mods.
                } else {
                    SEND_STRING(SS_TAP(X_SLASH) SS_LSFT(SS_TAP(X_NUBS)));
                }
            }
            break;

        case CU_SCOPE:
            if (pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_DOT)) SS_LSFT(SS_TAP(X_DOT)));
            }
            break;

        case CU_PARENS:
            if (pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_8)) SS_LSFT(SS_TAP(X_9)) SS_TAP(X_LEFT));
            }
            break;

        case CU_BRACKETS:
            if (pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_8))) SS_LCTL(SS_LALT(SS_TAP(X_9))) SS_TAP(X_LEFT));
            }
            break;

        case CU_BRACES:
            if (pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_7))) SS_LCTL(SS_LALT(SS_TAP(X_0))) SS_TAP(X_LEFT));
            }
            break;

        case CU_LTGT:
            if (pressed) {
                SEND_STRING(SS_TAP(X_NONUS_BACKSLASH) SS_LSFT(SS_TAP(X_NONUS_BACKSLASH)) SS_TAP(X_LEFT));
            }
            break;

        case CU_DQUOTES:
            if (pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_2)) SS_LSFT(SS_TAP(X_2)) SS_TAP(X_LEFT));
            }
            break;

        case CU_SQUOTES:
            if (pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_NONUS_HASH)) SS_LSFT(SS_TAP(X_NONUS_HASH)) SS_TAP(X_LEFT));
            }
            break;

        case CU_JUMP:
            if (pressed) {
                tap_code16(LCTL(LALT(KC_J)));
            }
            break;

        case CU_IN_W:
            if (pressed) {
                SEND_STRING("iw");
            }
            break;

        case CU_IN_WW:
            if (pressed) {
                SEND_STRING("iW");
            }
            break;
#endif

        default:
            // since none of our special codes was pressed we need to reinstate the oneshot modifiers
            set_oneshot_mods(osm_mods);
    }
    set_mods(mods);

    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_SLASH:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case LSFT(KC_SLASH):
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

#ifndef MAGIC_ENABLE
// reduce firmware size by replacing magic functions with empty functions
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif

// vim :set expandtab :set ts=2
