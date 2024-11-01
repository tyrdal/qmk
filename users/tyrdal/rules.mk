ifeq ($(strip $(GERMAN_ENABLE)), yes)
  OPT_DEFS += -DGERMAN_ENABLE
  SRC      += de_us_layout.c
endif

LTO_ENABLE        = yes
EXTRA_KEY_ENABLE  = yes
NKRO_ENABLE       = yes
BOOTMAGIC_ENABLE  = no
COMMAND_ENABLE    = no
SWAP_HANDS_ENABLE = no
MUSIC_ENABLE      = no
MAGIC_ENABLE      = yes
RGB_ENABLE        = no
