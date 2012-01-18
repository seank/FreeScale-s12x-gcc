/*
command that triggered the bug:
$ m68hc12-elf-gcc -O3 -c -I./src -I./sys-inc -fno-builtin  src/hc12_eeprom.c -o obj/hc12_eeprom.o
src/hc12_eeprom.c: In function `write_eeprom':
src/hc12_eeprom.c:44: Insn does not satisfy its constraints:
(insn 32 30 128 (set (mem:QI (const_int 243 [0xf3]) 0)
        (ior:QI (mem:QI (const_int 243 [0xf3]) 0)
            (const_int 22 [0x16]))) 83 {*iorqi3_const} (insn_list 25 (nil))
    (nil))
src/hc12_eeprom.c:44: Internal compiler error in reload_cse_simplify_operands, at reload1.c:8387
Please submit a full bug report,
with preprocessed source if appropriate.
See <URL:http://www.gnu.org/software/gcc/bugs.html> for instructions.
make: *** [obj/hc12_eeprom.o] Error 1
*/
# 7 "src/hc12_eeprom.c"
# 1 "src/hc912bc32.h" 1
# 8 "src/hc12_eeprom.c" 2
# 1 "src/hc12_util.h" 1
# 12 "src/hc12_util.h"
enum true_false { false=0, true};
# 22 "src/hc12_util.h"
typedef char bool;
typedef char boolean;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef const unsigned char* pcbyte;
typedef const unsigned short* pcword;
# 40 "src/hc12_util.h"
void wait_1msec(void);
void wait_10msec(void);
void sleep(unsigned long);
char bitNr(char);

void initMain(void);
void restartMain(void);

void InitLock(char*);
bool SetLock(char*);
void ResetLock(char*);
void WaitLock(char*);

void BootLoaderDownload(void);
void BootLoad(void);
void Reboot(void);
void Coldstart(void);
char IsInterrupt(void);

boolean isMenu(void);
# 9 "src/hc12_eeprom.c" 2



# 1 "src/hc12_eeprom.h" 1
# 41 "src/hc12_eeprom.h"
void write_eeprom(unsigned char*,unsigned char);
# 13 "src/hc12_eeprom.c" 2



void write_eeprom
   (unsigned char* pPointer,
    unsigned char bByte)
{
    if (*pPointer!=bByte)
    {

        (* (unsigned char *) (0x0000 + 0xF1))=0x00;
        (* (unsigned char *) (0x0000 + 0xF3))|=0x02|0x04|0x10;
        *pPointer=bByte;
        (* (unsigned char *) (0x0000 + 0xF3))|=0x01;
        wait_10msec();
        (* (unsigned char *) (0x0000 + 0xF3))&=~(0x01);



        (* (unsigned char *) (0x0000 + 0xF3))&=~(0x04|0x10);
        *pPointer=bByte;
        (* (unsigned char *) (0x0000 + 0xF3))|=0x01;
        wait_10msec();
        (* (unsigned char *) (0x0000 + 0xF3))&=~(0x01);
        (* (unsigned char *) (0x0000 + 0xF3))&=~(0x02);
        (* (unsigned char *) (0x0000 + 0xF1))=0xFF;
    }
}
