/* Copyright 2023 ecosse3
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

// SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Define two separate USB endpoints for left and right side of the keyboard
#define LEFT_EP_ADDR 0x01
#define RIGHT_EP_ADDR 0x02

// Light combinations
#define SET_INDICATORS(hsv) \
  {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
  {1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
  {35+15, 5, hsv},\
    {35+22, 3, hsv},\
    {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
  {10, 2, hsv}, \
  {20, 2, hsv}, \
  {30, 2, hsv}, \
  {35+ 10, 2, hsv}, \
  {35+ 20, 2, hsv}, \
  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
  {33, 4, hsv}, \
    {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
  {7, 4, hsv}, \
    {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
  {25, 2, hsv}, \
    {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
  {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
  {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
  {1, 6, hsv}, \
  {35+1, 6, hsv}, \
  {7, 4, hsv}, \
  {35+ 7, 4, hsv}, \
  {25, 2, hsv}, \
  {35+ 25, 2, hsv}


enum sofle_layers {
  _DEFAULTS = 0,
  _QWERTY = 0,
  _XBOX,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _SWITCH
};

enum custom_keycodes {
  KC_QWERTY = SAFE_RANGE,
  KC_XBOX,
  KC_LOWER,
  KC_RAISE,
  KC_ADJUST,
  KC_PRVWD,
  KC_NXTWD,
  KC_DLINE,
  KC_D_MUTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    //,------------------------------------------------.                    ,----------------------------------------------------|
       KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,             LT(_SWITCH,KC_6), KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    LT(_NUMPAD,KC_TAB),KC_Q,KC_W,KC_E,  KC_R,    KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,        KC_P,   KC_GRV,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,     KC_SCLN,  KC_QUOT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,     KC_D_MUTE,KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_MINUS,

    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    KC_LGUI, KC_HYPR, KC_LALT, KC_LOWER, KC_SPC  ,   KC_ENT,  KC_RAISE, KC_RCTL, KC_HYPR, KC_RGUI
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
  ),
  /*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BSPC  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | - |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ` |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |DISCORD|------+------+------+------+------+------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |LShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | ALT | CTRL  |CMD | LOWER | /Space  /       \Enter \  | RAISE | HYPER | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

  [_LOWER] = LAYOUT(
    //|---------------------------------------------------|                   |-----------------------------------------------------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,  KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_BSPC,
    //|------+--------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     _______,_______, _______, _______,  KC_F11,   KC_F12,
    //|------+--------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                     KC_LEFT,KC_DOWN,   KC_UP, KC_RGHT, _______,  KC_PIPE,
    //|------+--------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
      _______,  KC_EQL, KC_MINS, KC_PLUS, _______, _______,_______,    _______, _______,_______, KC_SCLN, KC_COLN, KC_BSLS,  KC_PLUS,
    //|------+--------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                        _______, _______, _______, _______,_______,    _______, _______,_______, _______, _______
    //               \---------+--------+--------+--------+-------|   |-------+--------+-------+--------+--------+--------/
  ),

  [_RAISE] = LAYOUT(
    //|---------------------------------------------------|                   |-----------------------------------------------------|
      _______, _______, _______, _______, _______, _______,                     _______,_______, _______,KC_PRVWD,KC_NXTWD,  KC_BSPC,
    //|------+--------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
      _______, KC_INS,  KC_PSCR,  KC_APP, XXXXXXX, XXXXXXX,                      KC_EQL,KC_LCBR, KC_RCBR, _______, _______,  KC_BSPC,
    //|------+--------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
      _______, KC_LALT,  KC_LCTL,KC_LSFT, XXXXXXX, KC_CAPS,                     KC_PLUS,KC_LBRC, KC_RBRC, _______, _______,  KC_PIPE,
    //|------+--------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
      _______, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,_______,    _______, KC_UNDS,_______, _______, _______, KC_BSLS,  _______,
    //|------+--------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                        _______, _______, _______, _______,_______,    _______, _______,_______, _______, _______
    //               \---------+--------+--------+--------+-------|   |-------+--------+-------+--------+--------+--------/
  ),

  /* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RGB_TOG|hue^ |sat ^ | bri ^|      |COLEMAK|-------.   ,-------|desk <|      |      |desk >|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | mode | hue dn|sat d|bri dn|      |QWERTY|-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

  [_ADJUST] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   C(G(KC_LEFT)), C(G(KC_RGHT)), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    XXXXXXX,   XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    RGB_TOG, RGB_HUI,RGB_SAI, RGB_VAI, XXXXXXX,KC_XBOX,             KC_BRIGHTNESS_UP,KC_NO,KC_NO,XXXXXXX, XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    RGB_MOD, RGB_HUD,RGB_SAD, RGB_VAD, XXXXXXX,KC_QWERTY,XXXXXXX,   XXXXXXX, KC_BRIGHTNESS_DOWN, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
  ),

  [_XBOX] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,             LT(_SWITCH,KC_6), KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_GRV,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,  KC_D_MUTE,KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_MINUS,

    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_LOWER, KC_MINUS, KC_QUOT, KC_RALT, KC_SPC  ,   KC_ENT,  KC_RAISE, KC_RCTL, KC_HYPR, KC_LGUI
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
  ),

  /* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|      |      |      |      |      |                    |      |NumLck|      |      |      |Bspc  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |      |      |      |      |                    |   ^  |   7  |   8  |   9  |   *  |Bspc  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------.    ,-------|   -  |   4  |   5  |   6  |      |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------|    |-------|   +  |   1  |   2  |   3  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_NUMPAD] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, KC_NUM, XXXXXXX, XXXXXXX,XXXXXXX, _______,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC, KC_P7,  KC_P8,   KC_P9,   KC_ASTR, _______,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS, KC_P4,  KC_P5,   KC_P6,   KC_EQL,  KC_PIPE,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______,   _______,KC_PLUS, KC_P1,  KC_P2,   KC_P3,   KC_SLSH, _______,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, OSM(MOD_MEH), _______, _______, _______,   _______, _______,  KC_P0,   KC_PDOT, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
  ),

  /* SWITCH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | qwer | cole |col_dh| low  | raise| adj  |                    |numpad|      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | SLEEP|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  // layer switcher
  [_SWITCH] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    TO(0),   TO(1),   TO(2),   TO(3),   TO(4),   TO(5),                      TO(6),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   XXXXXXX,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_NO,   KC_NO, KC_BRIU,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   XXXXXXX,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    KC_SYSTEM_SLEEP,KC_NO,KC_NO,KC_NO,  KC_NO,   KC_NO, KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                     KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/

  ),
};

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_PURPLE)

  );

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_TEAL)

  );
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_BLUE)

  );
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_PURPLE)
  );

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_INDICATORS(HSV_ORANGE),
    SET_UNDERGLOW(HSV_ORANGE),
    SET_NUMPAD(HSV_BLUE),
    {7, 4, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {35+6, 4, HSV_ORANGE},
    {35+25, 2, HSV_ORANGE}
  );
// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_GREEN),
    SET_NUMROW(HSV_GREEN)
  );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_qwerty_lights,
    layer_num_lights, // overrides layer 1
    layer_symbol_lights,
    layer_command_lights,
    layer_numpad_lights,
    layer_switcher_lights
  );

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
  
  rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
  rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
  rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
  rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
  rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
  return state;
}
void keyboard_post_init_user(void) {
  // Enable the LED layers
  rgblight_layers = my_rgb_layers;

  rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif

#ifdef OLED_ENABLE

// static void render_logo(void) {
//   static const char PROGMEM qmk_logo[] = {
//     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//     0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//     0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//   };
//
//   oled_write_P(qmk_logo, false);
// }

static void render_logo(void) {
  static const char PROGMEM enativ_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0x00, 0xC1, 0xC2, 0xC3, 0x00, 0xC5, 0xC6, 0x00, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0x00, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4
  };

  oled_write_P(enativ_logo, false);
}

static void print_status_narrow(void) {
  // Print current mode
  oled_write_P(PSTR("\n\n"), false);
  //oled_write_ln_P(PSTR("Dane\nEvans"), false);

  oled_write_ln_P(PSTR(""), false);

  //snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)


  switch (get_highest_layer(default_layer_state)) {
    case _QWERTY:
      oled_write_ln_P(PSTR("Qwrty"), false);
      break;
    case _XBOX:
      oled_write_ln_P(PSTR("XBOX"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undef"), false);
  }
  oled_write_P(PSTR("\n\n"), false);
  // Print current layer
  oled_write_ln_P(PSTR("LAYER"), false);
  switch (get_highest_layer(layer_state)) {
    case _XBOX:
    case _QWERTY:
      oled_write_P(PSTR("\n\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("Raise"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("Lower"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("Adj\n"), false);
      break;
    case _NUMPAD:
      oled_write_P(PSTR("Nump\n"), false);
      break;
    case _SWITCH:
      oled_write_P(PSTR("Swit\n"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undef"), false);
  }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  }
  return rotation;
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    print_status_narrow();
  } else {
    render_logo();
  }
  return false;
}

#endif

// Define a variable to keep track of the currently active USB endpoint
uint8_t current_endpoint = LEFT_EP_ADDR;

// Define a function to switch between the left and right USB endpoints
void switch_endpoint(void) {
  if (current_endpoint == LEFT_EP_ADDR) {
    current_endpoint = RIGHT_EP_ADDR;
  } else {
    current_endpoint = LEFT_EP_ADDR;
  }
  // Switch the USB endpoint
  usb_set_ep_addr(USB_ENDPOINT_IN(1), current_endpoint);
  usb_set_ep_addr(USB_ENDPOINT_OUT(1), current_endpoint);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        // switch_endpoint();
      }
      return false;
    case KC_XBOX:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_XBOX);
        // switch_endpoint();
      }
      return false;
    case KC_LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case KC_RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case KC_ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
    case KC_PRVWD:
      if (record->event.pressed) {
        if (keymap_config.swap_lctl_lgui) {
          register_mods(mod_config(MOD_LALT));
          register_code(KC_LEFT);
        } else {
          register_mods(mod_config(MOD_LCTL));
          register_code(KC_LEFT);
        }
      } else {
        if (keymap_config.swap_lctl_lgui) {
          unregister_mods(mod_config(MOD_LALT));
          unregister_code(KC_LEFT);
        } else {
          unregister_mods(mod_config(MOD_LCTL));
          unregister_code(KC_LEFT);
        }
      }
      break;
    case KC_NXTWD:
      if (record->event.pressed) {
        if (keymap_config.swap_lctl_lgui) {
          register_mods(mod_config(MOD_LALT));
          register_code(KC_RIGHT);
        } else {
          register_mods(mod_config(MOD_LCTL));
          register_code(KC_RIGHT);
        }
      } else {
        if (keymap_config.swap_lctl_lgui) {
          unregister_mods(mod_config(MOD_LALT));
          unregister_code(KC_RIGHT);
        } else {
          unregister_mods(mod_config(MOD_LCTL));
          unregister_code(KC_RIGHT);
        }
      }
      break;
    case KC_DLINE:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_LCTL));
        register_code(KC_BSPC);
      } else {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(KC_BSPC);
      }
      break;
    case KC_D_MUTE:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_MEH));
        register_code(KC_UP);
      } else {
        unregister_mods(mod_config(MOD_MEH));
        unregister_code(KC_UP);
      }
  }
  return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_VOLD);
    } else {
      tap_code(KC_VOLU);
    }
} else if (index == 1) {
    switch (get_highest_layer(layer_state)) {
      case _XBOX:
      case _QWERTY:
        if (clockwise) {
          tap_code(KC_PGDN);
      } else {
          tap_code(KC_PGUP);
        }
        break;
      case _RAISE:
      case _LOWER:
        if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);
        }
        break;
      default:
        if (clockwise) {
          tap_code(KC_WH_D);
      } else {
          tap_code(KC_WH_U);
        }
        break;
    }
  }
  return true;
}

#endif
