#pragma once

#include QMK_KEYBOARD_H

// Tap Dance declarations
enum {
    TD_LBRC,
    TD_RBRC,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);
void lbrc_finished(tap_dance_state_t *state, void *user_data);
void lbrc_reset(tap_dance_state_t *state, void *user_data);
void rbrc_finished(tap_dance_state_t *state, void *user_data);
void rbrc_reset(tap_dance_state_t *state, void *user_data);

