/* Copyright 2020 Paul James
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _LOWER,
    _HIGHER,
};

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    CMD_TAB
};

// Aliases for readability
#define LOWER MO(_LOWER)
#define HIGHER MO(_HIGHER)

// Home Row Mod layer Base
#define HRM_MEH_BSPC MT(MOD_MEH, KC_BSPC)
#define HRM_HYPR_A MT(MOD_HYPR, KC_A)
#define HRM_CTL_R MT(MOD_LCTL, KC_R)
#define HRM_ALT_S MT(MOD_LALT, KC_S)
#define HRM_CMD_T MT(MOD_LGUI, KC_T)

#define HRM_CMD_N MT(MOD_RGUI, KC_N)
#define HRM_ALT_E MT(MOD_RALT, KC_E)
#define HRM_CTL_I MT(MOD_RCTL, KC_I)
#define HRM_HYPR_O MT(MOD_HYPR, KC_O)
#define HRM_MEH_ESC MT(MOD_MEH, KC_ESC)


// Home Row Mod layer Lower
#define HRM_MEH_TILD MT(MOD_MEH, KC_TILD)
#define HRM_HYPR_QUOT MT(MOD_HYPR, KC_QUOT)
#define HRM_CTL_LPRN MT(MOD_LCTL, KC_LPRN)
#define HRM_ALT_EQL MT(MOD_LALT, KC_EQL)
#define HRM_CMD_0 MT(MOD_LGUI, KC_0)

#define HRM_CMD_1 MT(MOD_RGUI, KC_1)
#define HRM_ALT_ASTR MT(MOD_RALT, KC_PAST)
#define HRM_CTL_RPRN MT(MOD_RCTL, KC_RPRN)
#define HRM_HYPR_MINS MT(MOD_HYPR, KC_MINS)
#define HRM_MEH_PIPE MT(MOD_MEH, KC_PIPE)


// Home Row Mod layer higher
#define HRM_HYPR_F12 MT(MOD_HYPR, KC_F12)
#define HRM_CTL_LFT MT(MOD_LCTL, KC_LEFT)
#define HRM_ALT_DWN MT(MOD_LALT, KC_DOWN)
#define HRM_CMD_UP MT(MOD_LGUI, KC_UP)

#define HRM_CMD_DWN MT(MOD_RGUI, KC_DOWN)
#define HRM_ALT_UP MT(MOD_RALT, KC_UP)
#define HRM_CTL_RGHT MT(MOD_RCTL, KC_RGHT)
#define HRM_HYPR_F11 MT(MOD_HYPR, KC_F11)


bool is_alt_tab_active = false;
bool is_cmd_tab_active = false;
uint16_t alt_tab_timer = 0;
uint16_t cmd_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer
 */
[_BASE] = LAYOUT_ortho_5x12(
    XXXXXXX,        XXXXXXX,       XXXXXXX,           XXXXXXX,                 XXXXXXX,                XXXXXXX,                XXXXXXX,                XXXXXXX,             XXXXXXX,               XXXXXXX,    XXXXXXX,     XXXXXXX,
    CMD_TAB,        KC_Q,          KC_W,              KC_F,                    KC_P,                   KC_G,                   KC_J,                   KC_L,                KC_U,                  KC_Y,       KC_SCLN,     ALT_TAB,
    HRM_MEH_BSPC,   HRM_HYPR_A,    HRM_CTL_R,         HRM_ALT_S,               HRM_CMD_T,              KC_D,                   KC_H,                   HRM_CMD_N,           HRM_ALT_E,             HRM_CTL_I,  HRM_HYPR_O,  HRM_MEH_ESC,
    KC_TAB,         KC_Z,          KC_X,              KC_C,                    KC_V,                   KC_B,                   KC_K,                   KC_M,                KC_COMM,               KC_DOT,     KC_SLSH,     KC_ENT,
    XXXXXXX,        XXXXXXX,       XXXXXXX,           LT(HIGHER, KC_LEFT),     LT(LOWER, KC_DOWN),     MT(MOD_LSFT, KC_SPC),   MT(MOD_RSFT, KC_SPC),   LT(LOWER, KC_UP),    LT(HIGHER, KC_RGHT),   XXXXXXX,    XXXXXXX,     XXXXXXX
),

/*
 * Lower Layer
 */
[_LOWER] = LAYOUT_ortho_5x12(
    XXXXXXX,         XXXXXXX,           XXXXXXX,               XXXXXXX,         XXXXXXX,                XXXXXXX,          XXXXXXX,          XXXXXXX,             XXXXXXX,               XXXXXXX,        XXXXXXX,        XXXXXXX,
    KC_GRV,          KC_PERC,           KC_AMPR,               KC_DQUO,         KC_PLUS,                KC_AT,            KC_DLR,           KC_UNDS,             KC_LBRC,               KC_RBRC,        KC_EXLM,        KC_BSLS,
    HRM_MEH_TILD,    HRM_HYPR_QUOT,     HRM_CTL_LPRN,          HRM_ALT_EQL,     HRM_CMD_0,              KC_LCBR,          KC_RCBR,          HRM_CMD_1,           HRM_ALT_ASTR,          HRM_CTL_RPRN,   HRM_HYPR_MINS,  HRM_MEH_PIPE,
    _______,         KC_6,              KC_7,                  KC_8,            KC_9,                   KC_CIRC,          KC_HASH,          KC_2,                KC_3,                  KC_4,           KC_5,           _______,
    XXXXXXX,         XXXXXXX,           XXXXXXX,               _______,         _______,                _______,          _______,          _______,             _______,               XXXXXXX,        XXXXXXX,        XXXXXXX
),

/*
 * Higher Layer
 */
[_HIGHER] = LAYOUT_ortho_5x12(
    XXXXXXX,         XXXXXXX,       XXXXXXX,           XXXXXXX,         XXXXXXX,                XXXXXXX,          XXXXXXX,          XXXXXXX,             XXXXXXX,               XXXXXXX,        XXXXXXX,        XXXXXXX,
    XXXXXXX,         XXXXXXX,       XXXXXXX,           XXXXXXX,         XXXXXXX,                XXXXXXX,          KC_MPRV,          KC_MPLY,             KC_MNXT,               KC_VOLD,        KC_MUTE,        KC_VOLU,
    HRM_MEH_BSPC,    HRM_HYPR_F12,  HRM_CTL_LFT,       HRM_ALT_DWN,     HRM_CMD_UP,             KC_RGHT,          KC_LEFT,          HRM_CMD_DWN,         HRM_ALT_UP,            HRM_CTL_RGHT,   HRM_HYPR_F11,   HRM_MEH_ESC,
    _______,         KC_F6,         KC_F7,             KC_F8,           KC_F9,                  KC_F10,           KC_F1,            KC_F2,               KC_F3,                 KC_F4,          KC_F5,          _______,
    XXXXXXX,        XXXXXXX,        XXXXXXX,           _______,         _______,                _______,          _______,          _______,             _______,               XXXXXXX,        XXXXXXX,        XXXXXXX
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode){
        case ALT_TAB:
            if(record->event.pressed){
                if(!is_alt_tab_active){
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case CMD_TAB:
            if(record->event.pressed){
                if(!is_cmd_tab_active){
                    is_cmd_tab_active = true;
                    register_code(KC_LCMD);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if(is_alt_tab_active) {
        if(timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    if(is_cmd_tab_active){
        if(timer_elapsed(cmd_tab_timer) > 1000) {
            unregister_code(KC_LCMD);
            is_cmd_tab_active = false;
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(LED1, state);

    return state;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(LED2, led_state.caps_lock);
    }
    return res;
}