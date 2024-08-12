/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#define CTL_R MT(MOD_LCTL, KC_R)
#define ALT_S MT(MOD_LALT, KC_S)
#define CMD_TE MT(MOD_LGUI, KC_T)

#define ALT_EQL MT(MOD_LALT, KC_EQL)
#define CMD_0   MT(MOD_LGUI, KC_0)

#define CMD_F10 MT(MOD_LGUI, KC_F10)

#define CTL_I MT(MOD_RCTL, KC_I)
#define ALT_E MT(MOD_RALT, KC_E)
#define CMD_N MT(MOD_RGUI, KC_N)

#define ALT_ASTR MT(MOD_RALT, KC_ASTR)
#define CMD_1   MT(MOD_RGUI, KC_1)

#define CMD_F1 MT(MOD_RGUI, KC_F1)

bool is_alt_tab_active = false;
bool is_cmd_tab_active = false;
uint16_t alt_tab_timer = 0;
uint16_t cmd_tab_timer = 0;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer 
 */
    [_BASE] = LAYOUT(
     CMD_TAB , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_G ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, ALT_TAB,
     KC_BSPC , KC_A ,  CTL_R  ,  ALT_S ,  CMD_TE,   KC_D ,                                        KC_H,   CMD_N,  ALT_E,   CTL_I,  KC_O , KC_ESC,
     KC_TAB  , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LEFT,KC_DOWN,     KC_UP  , KC_RGHT, KC_K,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_ENT,
                      LSFT(KC_TAB), MO(HIGHER), MO(LOWER), KC_SPC, KC_LSFT,     KC_RSFT, KC_SPC , MO(LOWER), MO(HIGHER), RSFT(KC_ENT)
    ),

/*
 * Lower Layer
 */
    [_LOWER] = LAYOUT(
     KC_GRV  ,   KC_PERC ,   KC_AMPR ,   KC_DQUO ,   KC_PLUS ,   KC_AT ,                                       KC_DLR ,   KC_UNDS ,   KC_LBRC ,   KC_RBRC ,   KC_EXLM , KC_BSLS ,
     KC_TILD ,   KC_QUOT ,   SC_LCPO ,   ALT_EQL ,   CMD_0   ,  KC_LCBR,                                      KC_RCBR ,   CMD_1   ,   ALT_ASTR,   SC_RCPC ,   KC_MINS , KC_PIPE ,
     _______ ,   KC_6    ,   KC_7    ,   KC_8    ,   KC_9    ,  KC_CIRC, _______, _______, _______, _______,  KC_HASH ,   KC_2    ,   KC_3    ,   KC_4    ,   KC_5    , _______ ,
                                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Higher Layer
 */
    [_HIGHER] = LAYOUT(
      KC_NO,  KC_NO ,   KC_NO,  KC_NO,  KC_NO, KC_VOLU,                                     KC_MNXT, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,
      KC_NO, KC_F12 , KC_LCTL,KC_LALT,CMD_F10, KC_MUTE,                                     KC_MPLY,CMD_F1,KC_RALT,KC_RCTL,KC_F11, KC_NO,
      KC_NO,  KC_F6 ,   KC_F7,  KC_F8,  KC_F9, KC_VOLD, _______, _______, _______, _______, KC_MPRV, KC_F2,  KC_F3,  KC_F4, KC_F5, KC_NO,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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