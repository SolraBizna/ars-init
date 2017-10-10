ALL_IMAGES=nullinit.bin etinit.bin stdint.bin

all: $(addprefix bin/,$(ALL_IMAGES))

clean:
	rm -rf obj

bin/%.bin: src/%.link obj/%.o
	@mkdir -p bin
	wlalink -S -v $< $@

obj/%.o: src/%.65c
	@mkdir -p obj
	wla-65c02 -I src/ -o $@ $<

.PHONY: all clean
.SECONDARY: # keep secondary files
MAKEFLAGS += --no-builtin-rules # out! out, vile built-in rules!
