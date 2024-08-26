#include "tap_dances.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t lbrc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t rbrc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void lbrc_finished(tap_dance_state_t *state, void *user_data) {
    lbrc_tap_state.state = cur_dance(state);
    // < { [
    switch (lbrc_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_LCBR); break;
        case TD_SINGLE_HOLD: register_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: register_code16(KC_LABK); break;
        default: break;
    }
}

void lbrc_reset(tap_dance_state_t *state, void *user_data) {
    switch (lbrc_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LCBR); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_LABK); break;
        default: break;
    }

    lbrc_tap_state.state = TD_NONE;
}

void rbrc_finished(tap_dance_state_t *state, void *user_data) {
    rbrc_tap_state.state = cur_dance(state);
    // > } ]
    switch (rbrc_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_RCBR); break;
        case TD_SINGLE_HOLD: register_code(KC_RBRC); break;
        case TD_DOUBLE_TAP: register_code16(KC_RABK); break;
        default: break;
    }
}

void rbrc_reset(tap_dance_state_t *state, void *user_data) {
    switch (rbrc_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_RCBR); break;
        case TD_SINGLE_HOLD: unregister_code(KC_RBRC); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_RABK); break;
        default: break;
    }
    rbrc_tap_state.state = TD_NONE;
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] PROGMEM = {
    [TD_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbrc_finished, lbrc_reset),
    [TD_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbrc_finished, rbrc_reset),
};
