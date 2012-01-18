extern volatile unsigned char _io_ports[];

int main(void)
{
    unsigned short x;
    int i = 0;

    x = (_io_ports[0x00] << 8) | _io_ports[0x00];

    if (x >> i)
    {
        _io_ports[0x00] = 0;
    }

    return 0;
}
