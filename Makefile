TARGET_LIB  = libnotengine.a

OBJS     = src/system/Callbacks.o \
           src/math/MathUtils.o \
           src/audio/Music.o \
           src/audio/MusicYM.o \
           src/audio/AudioManager.o \
           src/graphic/BaseRender.o \
           src/graphic/SpriteList.o \
           src/graphic/TextureManager.o \
           src/graphic/Render2D.o \
           src/game/GameState.o \

INCDIR	 =
CFLAGS   = -std=c++03 -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS	 = $(CFLAGS)
LDFLAGS  =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
