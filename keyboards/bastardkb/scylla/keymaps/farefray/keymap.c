#include QMK_KEYBOARD_H
#include "tap_dances.h"

enum custom_keycodes {
    TOGGLE_LAYOUT = SAFE_RANGE,
    BSPC_DEL,
    ESC_CAPS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Base Layer (Colemak-DH)
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |QK_GESC |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |  +=    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  |      |   -_   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | TD(<[{)|   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | TD(>}])|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LCTRL  |   Z  |   X  |   C  |   D  |   V  |                              |   K  |   H  |  '"  |  \|  |  /?  |   ;:   |
 * `----------------------+------+------+------'                              `------+------+------+----------------------'
 *                        |  .>  | LALT |MO(1) |                              |MO(1) | RGUI | ,<   |
 *                        |      |      |      |                              |      |      |      |
 *                        `--------------------'                              `--------------------'
 *                                     |SPC/L |BCSPS/|                    |SHIFT/|   .  |
 *                                     |SHIFT)|DEL   |                    |ENTER |      |
 *                                     `-------------'                    `-------------'
 */
    [0] = LAYOUT_split_4x6_5(
        QK_GESC,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                       KC_J,    KC_L,    KC_U,    KC_Y,    _______, KC_MINS,
        TD(TD_LBRC), KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                       KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    TD(TD_RBRC),
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                       KC_K,    KC_H,    KC_QUOTE, KC_SLSH, KC_BSLS, KC_SEMICOLON,
        KC_DOT, KC_LALT, MO(1), MO(1), KC_RGUI, KC_COMMA, KC_BSPC, LSFT_T(KC_SPACE), RSFT_T(KC_ENT), _______
    ),

/* Layer 1: Function, Navigation, and IDE shortcuts Layer
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  F12   |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | UNDO | CUT  | COPY |PASTE |      |                              | PGUP | HOME |  UP  | END  |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | LCTR | LALT | LGUI |LSHFT |      |                              | PGDN | LEFT | DOWN |RIGHT |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | MUTE | VOL- | VOL+ |BRIG- |BRIG+ |QK_BOOT |
 * `----------------------+------+------+------'                              `------+------+------+----------------------'
 *                        |      |      | TRNS |                              | TRNS |      |      |
 *                        |      |      |      |                              |      |      |      |
 *                        `--------------------'                              `----------------------'
 *                                              ,-------------.  ,-------------.
 *                                              | TRNS |      |  |      | TRNS |
 *                                              |      |      |  |      |      |
 *                                              `-------------'  `-------------'
 */
    [1] = LAYOUT_split_4x6_5(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,_______,                    KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______,
        _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                    KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, QK_BOOT,
                          _______, _______, _______, KC_TRNS, _______,           _______, KC_TRNS, _______, _______, _______
    ),

/* Layer 2: QWERTY Layout for Ukrainian
 */
    [2] = LAYOUT_split_4x6_5(
        _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,    KC_COMM, KC_DOT,  _______, _______,
                          _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case KC_BSPC: {
      static uint16_t registered_key = KC_NO;
      if (record->event.pressed) {  // On key press.
        const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
        uint8_t shift_mods = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;
#else
        uint8_t shift_mods = mods & MOD_MASK_SHIFT;
#endif  // NO_ACTION_ONESHOT
        if (shift_mods) {  // At least one shift key is held.
          registered_key = KC_DEL;
          // If one shift is held, clear it from the mods. But if both
          // shifts are held, leave as is to send Shift + Del.
          if (shift_mods != MOD_MASK_SHIFT) {
#ifndef NO_ACTION_ONESHOT
            del_oneshot_mods(MOD_MASK_SHIFT);
#endif  // NO_ACTION_ONESHOT
            unregister_mods(MOD_MASK_SHIFT);
          }
        } else {
          registered_key = KC_BSPC;
        }

        register_code(registered_key);
        set_mods(mods);
      } else {  // On key release.
        unregister_code(registered_key);
      }
    } return false;

    // Other macros...
  }

  return true;
}
