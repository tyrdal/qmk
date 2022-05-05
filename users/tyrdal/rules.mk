ifeq ($(strip $(GERMAN_ENABLE)), yes)
  OPT_DEFS += -DGERMAN_ENABLE
  SRC      += de_us_layout.c
endif

LTO_ENABLE        = yes
EXTRA_KEY_ENABLE  = yes
MOUSEKEY_ENABLE   = yes
LEADER_ENABLE     = yes
CONSOLE_ENABLE    = no
NKRO_ENABLE       = yes
BOOTMAGIC_ENABLE  = no
COMMAND_ENBALE    = no
SWAP_HANDS_ENABLE = no
