#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_mit(
            KC_TAB,  KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_QUOT,
            KC_BSPC, KC_A,       KC_R,       KC_S,       KC_T,       KC_D,       KC_H,       KC_N,       KC_E,       KC_I,       KC_O,       KC_ENT,
            KC_LSFT, KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_K,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
            KC_LCTL, MO(3),      KC_LGUI,    KC_LALT,    MO(1),      KC_SPC,     MO(2),      KC_RALT,    KC_RGUI,    KC_CAPS,    KC_RCTL),

	[1] = LAYOUT_planck_mit(
            KC_TILD, KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_DQUO,
            KC_DEL,  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_PIPE,    KC_MINS,    KC_EQL,     KC_LCBR,    KC_RCBR,    KC_INS,
            KC_TRNS, KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSLS,    KC_UNDS,    KC_PLUS,    KC_LBRC,    KC_RBRC,    KC_TRNS,
            KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_ESC,     MO(4),      KC_TRNS,    KC_TRNS,    KC_APP,     KC_TRNS),

	[2] = LAYOUT_planck_mit(
            KC_GRV,  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_DQUO,
            KC_DEL,  KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_BSLS,    KC_UNDS,    KC_PLUS,    KC_LBRC,    KC_RBRC,    KC_INS,
            KC_TRNS, KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,     KC_TRNS,
            KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    MO(4),      KC_ESC,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_APP,     KC_TRNS),

	[3] = LAYOUT_planck_mit(
            KC_TAB,  KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_PSCR,    KC_SLCT,    KC_PAUS,    KC_NO,      KC_QUOT,
            KC_DEL,  KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      KC_INS,
            KC_TRNS, KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_NO,      KC_TRNS,
            KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS),

	[4] = LAYOUT_planck_mit(
            KC_NO,   LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), QK_BOOTLOADER,
            KC_NO,   KC_NO,      KC_MPLY,    KC_MSTP,    KC_VOLU,    KC_NO,      RGB_TOG,    RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_SPI,    KC_NO,
            KC_TRNS, KC_NO,      KC_MPRV,    KC_MNXT,    KC_VOLD,    RGB_RMOD,   RGB_MOD,    RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_SPD,    KC_TRNS,
            KC_TRNS, KC_NO,      KC_NO,      KC_NO,      KC_TRNS,    KC_NO,      KC_TRNS,    KC_NO,      KC_NO,      KC_TRNS,    KC_TRNS)
};

// ------------------------------

#define JCKMGNS_QK_BOOTLOADER_TIMEOUT 2000

static uint16_t bootloader_timer = 0; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { // Enter bootloader if released after JCKMGNS_QK_BOOTLOADER_TIMEOUT ms.
        case QK_BOOTLOADER:
            if (record->event.pressed) {
                bootloader_timer = timer_read();
            }
            else {
                uint16_t elapsed = timer_elapsed(bootloader_timer);

                bootloader_timer = 0;

                if (elapsed >= JCKMGNS_QK_BOOTLOADER_TIMEOUT) {
                    bootloader_jump();
                }
            }
            return false;
        default:
            return true;
    }
}
