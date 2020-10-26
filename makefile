
# FILENAMES --------------------------------------------------------------------

HDR_ROOT = inc
SRC_ROOT = src
BLD_ROOT = tmp

HDR = $(shell find $(HDR_ROOT) -type f -name *.h)
SRC = $(shell find $(SRC_ROOT) -type f -name *.c)
OBJ = $(patsubst $(SRC_ROOT)/%, $(BLD_ROOT)/%, $(SRC:.c=.o))

EXE = ennbacklight

# FLAGS ------------------------------------------------------------------------

ifeq ($(cfg), debug)
    OPT_FLAGS = -O0 -g
else
    OPT_FLAGS = -O2 -DNDEBUG
endif

CMP_FLAGS = -std=c99 -Wall $(OPT_FLAGS) -I$(HDR_ROOT)
LNK_FLAGS =

# RULES ------------------------------------------------------------------------

.PHONY: build clean .build_root .debug_root

build: .build_root $(EXE)

clean:
	$(info )
	$(info Removing temporary files...)
	rm -df $(EXE) $(OBJ) $(BLD_ROOT)

.build_root:
	@mkdir -p $(BLD_ROOT)

.debug_root:
	@mkdir -p dbg/backlight
	@mkdir -p dbg/backlight/fld
	@mkdir -p dbg/backlight/.fld
	@ln -sf fld dbg/backlight/lnk
	@ln -sf .fld dbg/backlight/.lnk
	@echo "40" > dbg/backlight/fld/brightness
	@echo "200" > dbg/backlight/fld/max_brightness

$(EXE): $(OBJ)
	$(info )
	$(info Linking object files...)
	$(CC) $(CFLAGS) $(LNK_FLAGS) -o $(EXE) $(OBJ)

$(BLD_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(info )
	$(info Compiling $<...)
	$(CC) $(CFLAGS) $(CMP_FLAGS) -o $@ -c $<
