struct Regs
{
volatile unsigned char reg;
};

struct Device
{
struct Regs *regs;
};

struct Device dev0 =
{
(struct Regs *) 0x0100,
};

void init(struct Device *device)
{
device->regs->reg |= 0x01;
device->regs->reg &= ~0x01;
}
