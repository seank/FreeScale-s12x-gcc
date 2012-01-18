extern char clock_flags;
extern char time_secs;
extern char min_flag;

#define REG_BASE 0
#define REGISTER char
#define PORTA           (*(volatile REGISTER *)(REG_BASE + 0x00))
#define SHUTDOWN  0x40
#define TIMING  0x01
void __attribute__((interrupt))
clock_interrupt_handler()
{
        PORTA &= ~SHUTDOWN;     /* power everything up*/
        clock_flags |= TIMING;
        if(time_secs != 0)
                return;
        min_flag = 1;           /* 1 minute flag for main.c*/
}

