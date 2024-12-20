#pragma once

#define FORCE_NKRO

// auto shift settings
#define AUTO_SHIFT_MODIFIERS // enable modifiers like ctrl, alt etc to work with autoshift
#define AUTO_SHIFT_TIMEOUT 150
#define AUTO_SHIFT_NO_AUTO_REPEAT // disables automatic key repetition after the timeout is exceeded

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 400
#define LEADER_PER_KEY_TIMING

#define MK_COMBINED
#define MOUSEKEY_DELAY 10             // Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL 16          // Time between cursor movements in milliseconds
#define MOUSEKEY_MOVE_DELTA 6         // Step size
#define MOUSEKEY_MAX_SPEED 8          // Maximum cursor speed at which acceleration stops
#define MOUSEKEY_TIME_TO_MAX 70       // Time until maximum cursor speed is reached
#define MOUSEKEY_WHEEL_DELAY 10       // Delay between pressing a wheel key and wheel movement
#define MOUSEKEY_WHEEL_INTERVAL 80    // Time between wheel movements
#define MOUSEKEY_WHEEL_MAX_SPEED 8    // Maximum number of scroll steps per scroll action
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40 // Time until maximum scroll speed is reached

#define DYNAMIC_MACRO_NO_NESTING
#define DYNAMIC_MACRO_SIZE 104 // the default of 128 is too large for the config
#define DYNAMIC_MACRO_DELAY 20 // delay after echa key in ms
#define EXTRA_SHORT_COMBOS

#define CAPS_WORD_INVERT_ON_SHIFT   // invert the behavior of the caps word feature when shift is pressed
#define CAPS_WORD_IDLE_TIMEOUT 3000 // 3 seconds.

#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT // limit to max 8 Layers
