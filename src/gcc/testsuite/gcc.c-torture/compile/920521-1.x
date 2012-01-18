# Test defines an asm which sometimes requires too many
# registers for HC11/HC12.
if { [istarget "m6811-*-*"] || [istarget "m6812-*-*"] } {
      return 1
}
set options "-S"
return 0
