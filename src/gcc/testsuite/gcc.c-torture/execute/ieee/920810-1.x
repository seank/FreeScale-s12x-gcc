# sprintf %g is not supported on HC11/HC12 (too big for a final link)
if { [istarget "m6811-*-*"] || [istarget "m6812-*-*"]} {
	return 1
}

return 0

