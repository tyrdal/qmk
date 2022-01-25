#pragma once

#define IGNORE_MOD_TAP_INTERRUPT

#undef TAPPING_TERM
#define TAPPING_TERM 300

#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 3000  // Time (in ms) before the one shot key is released
#define ONESHOT_TAP_TOGGLE 3  // Tapping this number of times holds the key until tapped once again.

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 400
#define LEADER_PER_KEY_TIMING
