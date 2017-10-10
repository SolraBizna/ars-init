This is a collection of initialization and interrupt related code for the Eiling Technologies [Artificial Reality System](https://github.com/SolraBizna/ars-emu/), a fictional 8-bit game console.

A `manifest.bml` is provided so that you can load this folder up in ARS-emu and see the Eiling Technologies logo, in isolation.

# License

Everything in this repository is in the public domain. You are free to use, modify, redistribute, repurpose, and steal it without restriction.

`bin/etinit.bin` is a special case, in that I courteously request that you follow certain kayfabe guidelines when using it. Nevertheless, it's still public domain, and you're free to do whatever you want with it. I promise I won't do anything but stand on the sidelines and shed a single, dramatic tear.

# Files

## `etinit.bin`

This is the standard Eiling Technologies startup code, including "Licensed By" screen. It initializes all hardware to a sane, zeroed state, and then displays the logo. It provides Standard Interrupts and AwaitNMI. 

If you use `etinit.bin`, please read the Kayfabe section. To use it in a game, add a source file like the following:

```65c02
.INCLUDE "obj/common"

.BANK 0 SLOT TopSlot ; TopSlot is the uppermost slot
.ORGA $F800
.SECTION "!InitImage" SIZE 2048 FORCE
.INCBIN "path/to/etinit.bin"
.ENDS
```

A future version of ARS-emu will add an optional feature to detect the presence of `etinit.bin` in the right location in a ROM, and "skip" directly to the part where it hands control to your game. If you were planning to modify `etinit.bin` to make the logo skippable (or for any other reason), bear in mind that doing so will break this feature with your game.

## `nullinit.bin`

A drop-in replacement for `etinit.bin` that does initialization and goes directly to your program, without stopping to make a pretty logo in between. It contains a lot of empty space, so that it takes up the same amount of space as `etinit.bin`. It provides Standard Interrupts and AwaitNMI.

`nullinit.bin` is useful for development work, where you want to test your game without sitting through the ET logo every time, but you also want to *eventually* include the ET logo without having to worry about compatibility issues cropping up. When ARS-emu becomes able to skip the standard ET intro, this file will be obsolete.

To use it in a game, add a source file like the following:

```65c02
.INCLUDE "obj/common"

.BANK 0 SLOT TopSlot ; TopSlot is the uppermost slot
.ORGA $F800
.SECTION "!InitImage" SIZE 2048 FORCE
.INCBIN "path/to/nullinit.bin"
.ENDS
```

## `stdint.bin`

This file is a minimal set of Standard Interupts, suitable for insertion into any bank that will sometimes be mapped into the top slot.

To use it in a game, add a source file like the following for every bank that needs it:

```65c02
.INCLUDE "obj/common"

.BANK 0 SLOT TopSlot ; TopSlot is the uppermost slot
.ORGA $F800
.SECTION "!InitImage" SIZE 2048 FORCE
.INCBIN "path/to/nullinit.bin"
.ENDS
```

Note: `etinit.bin` and `nullinit.bin` initialize the NMI and IRQ handlers with a pointer to an `RTI` instruction. There is NOT an `RTI` at the same address in `stdint.bin`! If you use `stdint.bin` and do not use NMI or IRQ (or both), you must manually set the handler to an `RTI` instruction!

Note 2: `stdint.bin` does not provide Standard Interrupts or AwaitNMI!

# Standard Interrupts

- Hardware is initialized for you on reset. Control enters "your program" at `$8000`.
- You may provide an NMI handler by writing its entry point address to `$0250`. Whether or not you provide one, `$00` will be incremented every NMI.
- You may provide an IRQ handler by writing its entry point address to `$0252`. It will only be called on an actual IRQ.
- You may provide a BRK handler by writing its entry point address to `$0254`. If you don't, a default handler that writes a message to the Debug Port and does `STP` will be used. (The address of this default handler is `$FFCB`.)

Memory addresses you can't safely use for other purposes with Standard Interrupts:

- `$00`
- `$0250`-`$0255`

# AwaitNMI

`etinit.bin` has a perfectly serviceable wait-for-NMI routine located at `$ffc1`. `nullinit.bin` has it, too.

# Kayfabe

The ARS is fictional. Eiling Technologies never existed. Neither did the mysterious programmer who supposedly wrote the `etinit` code. Nevertheless, part of the fun of the ARS is *pretending* it existed.

Like in professional wrestling, I have adopted a deliberate strategy of acting, in most contexts, as though the entire Eiling Technologies fiction is real and serious. If you wish to do the same:

- Use `etinit.bin` in your game.
- Have a fictional copyright notice on the main menu.
    - Don't use real people or companies in a misleading way or they'll probably sue you and win.
    - *Do* take reasonable measures to ensure that you can still genuinely claim copyright on the game.
- Include dated cultural and technological references: floppy disks, communists, landlines, "cyberspace", CRTs, newspapers, etc.

