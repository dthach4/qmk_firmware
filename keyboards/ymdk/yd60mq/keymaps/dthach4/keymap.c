#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       KC_RSFT,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                              KC_RALT,  KC_APP,  KC_RCTL,       MO(1)
    ),
    [1] = LAYOUT_60_ansi(
        KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT,
        _______,     KC_MS_BTN2, KC_MS_U, KC_MS_BTN1, _______, _______, KC_PSCR,  KC_SCRL, KC_PAUS, UG_HUED, UG_HUEU, UG_PREV, UG_NEXT, UG_TOGG,
        _______,       KC_MS_L, KC_MS_D, KC_MS_R, KC_MUTE, KC_VOLD, KC_VOLU,  KC_INS, KC_HOME, KC_PGUP, UG_SPDD, UG_SPDU, _______,
        _______,            KC_WH_U, KC_WH_D, KC_MS_BTN3, _______, _______, _______, KC_DEL, KC_END, KC_PGDN, KC_UP,       _______,
        _______,   _______,   _______,                      _______,                              KC_LEFT, KC_DOWN, KC_RGHT,   _______
    ),

};

static bool last_capslock = false;

static uint8_t saved_mode;
static uint8_t saved_hue;
static uint8_t saved_sat;
static uint8_t saved_val;

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock == last_capslock) {
        return true;
    }
    last_capslock = led_state.caps_lock;
    if (led_state.caps_lock) {
        saved_mode = rgblight_get_mode();
        HSV hsv = rgblight_get_hsv();
        saved_hue = hsv.h;
        saved_sat = hsv.s;
        saved_val = hsv.v;

        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb(255, 0, 0);
    } else {
        rgblight_mode(saved_mode);
        rgblight_sethsv(saved_hue, saved_sat, saved_val);
    }
    return false;
}
