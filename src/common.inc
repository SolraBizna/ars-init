; Instructions WLA-DX doesn't know about
.MACRO WAI
.DB $CB
.ENDM
.MACRO STP
.DB $DB
.ENDM

; PPU registers
.ENUM $0200
r_BGScrollX DB
r_BGScrollY DB
r_Multi DB
r_BGTileBases DW
r_SPPalettes DB
r_BGPalettes DS 4
r_BGFG DS 4
r_OLPalette DB
r_ColorMod DB
r_VRAMPage DB
r_VRAMPort DB
r_CRAMIndex DB
r_CRAMPort DB
r_SSMIndex DB
r_SSMPort DB
r_SAMIndex DB
r_SAMPort DB
r_VRAMIndex DB
r_IRQScanline DB
r_VRAMDMA DB
r_VRAMSplatDMA DB
r_CRAMDMA DB
r_SSMDMA DB
r_SAMDMA DB
r_SSMUnpackedDMA DB
.ENDE

; APU registers
.ENUM $0220
r_VoiceRateLo DS 7
r_APUUnused DB
r_VoiceRateHi DS 7
r_NoisePeriod DB
r_VoiceWaveform DS 7
r_NoiseWaveform DB
r_VoiceVolume DS 7
r_NoiseVolume DB
.ENDE

; IO registers
.DEFINE r_Controller1 $0240
.DEFINE r_Controller2 $0241
.DEFINE r_HAM $0245
.DEFINE r_EmuConfig $0246
.DEFINE r_DebugPort $0247

; Memory map registers (there are 8 of them, starting at this address)
.DEFINE r_BankSelect $0248

; Overlay tilemap and attribute map
; (not really registers, but they are at fixed memory addresses)
.DEFINE r_OLTiles $7C00
.DEFINE r_OLAttributes $7C00+(32*28)
