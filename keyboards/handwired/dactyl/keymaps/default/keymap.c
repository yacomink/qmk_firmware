#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // ensure these codes start after the highest keycode defined in Quantum
  VRSN,
  VSCODE_KEEP,
  CLIP
};

enum combos {
  EQ1_ESC,
  PG_KEEP,
  HOME_CLIP
};

const uint16_t PROGMEM eq1_combo[] = {KC_EQL, KC_1, COMBO_END};
const uint16_t PROGMEM pg_keep_combo[] = {KC_PGUP, KC_PGDN, COMBO_END};
const uint16_t PROGMEM home_clip_combo[] = {KC_HOME, KC_END, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [EQ1_ESC] = COMBO(eq1_combo, KC_ESC),
  [PG_KEEP] = COMBO_ACTION(pg_keep_combo),
  [HOME_CLIP] = COMBO_ACTION(home_clip_combo)
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case PG_KEEP:
      if (pressed) {
        SEND_STRING(SS_LGUI("k"));
        SEND_STRING(SS_TAP(X_ENTER));
      }
      break;
    case HOME_CLIP:
      if (pressed) {
        SEND_STRING(SS_LGUI(SS_LALT("c")));
      }
      break;
  }
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   =  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tag  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BkSp |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |; / L2|'/Cmd |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|Z/Ctrl|   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |//Ctrl|RShift|
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |SYMB|  '"  |AltShf| Left | Right|                                  |  Up  | Down |   [  |   ]  | ~L1  |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      | App  | LGui |  | Alt  | ^/Esc|
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      | Home |  | PgUp |      |      |
 *                               | Space|Backsp|------|  |------|  Tab |Enter |
 *                               |      |ace   | End  |  | PgDn |      |      |
 *                               `--------------------'  `--------------------'
 */
[BASE] = LAYOUT_dactyl(  // layer 0 : default
        // left hand
          KC_EQL,             KC_1,    KC_2,     KC_3,     KC_4,  KC_5,
          KC_TAB,             KC_Q,    KC_W,     KC_E,     KC_R,  KC_T,
          KC_LCTL,            KC_A,    KC_S,     KC_D,     KC_F,  KC_G,
          KC_LSFT,            KC_Z,    KC_X,     KC_C,     KC_V,  KC_B,
      VSCODE_KEEP,            KC_GRV,  KC_BSLS,  KC_LEFT,  KC_RGHT,
                                                                      KC_LGUI,  KC_LALT,
                                                                                KC_HOME,
                                                           KC_BSPC,   KC_DELT,   KC_END,
        // right hand
                             KC_6,    KC_7,     KC_8,     KC_9,       KC_0,         KC_MINS,
                             KC_Y,    KC_U,     KC_I,     KC_O,       KC_P,         KC_BSLS,
                             KC_H,    KC_J,     KC_K,     KC_L,       KC_SCLN,      KC_QUOT,
                             KC_N,    KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,      KC_RSFT,
                                      KC_UP,    KC_DOWN,  KC_LBRC,    KC_RBRC,      MO(SYMB),
          KC_RALT,  KC_ESC,
          KC_PGUP,
          KC_PGDN, KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |Versn |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |                    |  Up  |   7  |   8  |   9  |   *  |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   #  |   $  |   (  |   )  |   `  |                    | Down |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   ~  |                    |   &  |   1  |   2  |   3  |   \  |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |RESET |      |      |      |      |                                  |      |   .  |   0  |   =  |      |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_dactyl(
       // left hand
          VRSN,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
       KC_TRNS,  KC_EXLM,    KC_AT,  KC_LCBR,  KC_RCBR,  KC_PIPE,
       KC_TRNS,  KC_HASH,   KC_DLR,  KC_LPRN,  KC_RPRN,   KC_GRV,
       KC_TRNS,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,
         RESET,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,
       // right hand
                KC_F6,      KC_F7,   KC_F8, KC_F9,  KC_F10,   KC_F11,
                KC_UP,       KC_7,    KC_8,  KC_9, KC_ASTR,   KC_F12,
                KC_DOWN,     KC_4,    KC_5,  KC_6, KC_PLUS,  KC_TRNS,
                KC_AMPR,     KC_1,    KC_2,  KC_3, KC_BSLS,  KC_TRNS,
                          KC_TRNS,  KC_DOT,  KC_0,  KC_EQL,  TG(BASE),
      KC_TRNS,  KC_TRNS,
      KC_TRNS,
      KC_TRNS,  KC_TRNS,  KC_TRNS
),
/* Keymap 2: Media and mouse keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | MsUp |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MsLeft|MsDown|MsRght|      |                    |      |      |      |      |      | Play |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      | Prev | Next |      |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |      |      |      | Lclk | Rclk |                                  | VolUp| VolDn| Mute |      |      |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |Brwser|
 *                               |      |      |------|  |------|      |Back  |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 *
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_dactyl(
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_BTN2,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,
    // right hand
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MPLY,
                KC_TRNS,  KC_TRNS,  KC_MPRV,  KC_MNXT,  KC_TRNS,  KC_TRNS,
                          KC_VOLU,  KC_VOLD,  KC_MUTE,  KC_TRNS,  KC_TRNS,
      KC_TRNS,  KC_TRNS,
      KC_TRNS,
      KC_TRNS,  KC_TRNS,  KC_WBAK
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case VSCODE_KEEP:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("k"));
        SEND_STRING(SS_TAP(X_ENTER));
      }
      break;
    case CLIP:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LALT("c")));
      }
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
//  debug_enable=true;
//  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
