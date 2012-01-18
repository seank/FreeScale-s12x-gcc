void foo(char* addr, char* data)
{
    *((volatile char*)0x0) |= 0x1;
    *addr++ = *data++;
    *((volatile char*)0x0) |= 0x1;
}
