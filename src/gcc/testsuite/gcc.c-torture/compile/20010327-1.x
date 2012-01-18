# This test does not compile on m68hc11 because it
# assumes pointers are 32-bits

if { [istarget "m6811-*-*"] || [istarget "m6812-*-*"] } {
      return 1
}

return 0
