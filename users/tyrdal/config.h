#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 300

#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 3000 // Time (in ms) before the one shot key is released
#define ONESHOT_TAP_TOGGLE 2 // Tapping this number of times holds the key until tapped once again.

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 1000
#define LEADER_PER_KEY_TIMING

#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 3000
