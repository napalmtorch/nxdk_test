rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

XBE_TITLE = Minecraft
GEN_XISO = $(XBE_TITLE).iso
SRCS = $(call rwildcard,src/,*.c)
NXDK_DIR ?= $(CURDIR)/../nxdk
NXDK_CXX = n
NXDK_SDL = y
CFLAGS = -Iinclude
DEBUG = y
LTO = n
CFLAGS += -Oz -DNDEBUG
CXXFLAGS += -Oz -DNDEBUG
NXDK_CFLAGS += -Oz -DNDEBUG
NXDK_CXXFLAGS += -Oz -DNDEBUG

include $(NXDK_DIR)/Makefile 