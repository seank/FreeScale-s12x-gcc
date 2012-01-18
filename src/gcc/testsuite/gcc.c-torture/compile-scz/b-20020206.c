volatile char _io_ports[10];
char bar;

int get ()
{
  while (_io_ports[3] & 0x80)
    continue;

  if (bar & 0x80)
    return _io_ports[1];
  
  return _io_ports[2];
}
