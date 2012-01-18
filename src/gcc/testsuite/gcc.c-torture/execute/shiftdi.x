# 16-bit "int"
if { [istarget "xstormy16-*"] } {
	return 1
}
if { [istarget "m6811-*-*"] || [istarget "m6812-*-*"]} {
	return 1
}

return 0

