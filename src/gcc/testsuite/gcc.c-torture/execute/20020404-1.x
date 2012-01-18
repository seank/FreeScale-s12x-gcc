# This test fails on HC11/HC12 when it is compiled with 16-bit integers
# because it passes value 0x1eadbeef in an int.
if { [istarget "m6811-*-*"] || [istarget "m6812-*-*"] } {
    return 1
}
return 0
