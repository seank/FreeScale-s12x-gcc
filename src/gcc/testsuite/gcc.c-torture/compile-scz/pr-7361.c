# 5 "essai.c"
# 1 "nanoK.h" 1
# 26 "nanoK.h"
# 1 "type_def.h" 1
# 26 "type_def.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
# 27 "nanoK.h" 2
# 45 "nanoK.h"
u8 nanoK_init(void);
# 56 "nanoK.h"
u8 nanoK_task_init(u8 t, void (*fct)(void), u8* stk, u16 stk_len);
# 65 "nanoK.h"
u8 nanoK_aggregate_task(u8 t1, u8 t2);
# 74 "nanoK.h"
inline void nanoK_task_terminate(void);
# 84 "nanoK.h"
inline u8 nanoK_task_reset(u8 t);
# 98 "nanoK.h"
void nanoK_hook_init(void (*fct)(void), u8* stk, u16 stk_len);





void nanoK_start(void);





void nanoK_kernel(void);




typedef struct {
        struct {
                u8 CCR;
                u16 D;
                u16 X;
                u16 Y;
                u16 PC;
                u16 SP;
        } hard_regs;
        struct {
                u16 r[8];
                u16 tmp;
                u16 z;
                u16 xy;
                u16 frame;
        } soft_regs;
} t_context;
# 6 "essai.c" 2
# 1 "vectors.h" 1
# 26 "vectors.h"
# 1 "type_def.h" 1
# 27 "vectors.h" 2

typedef enum {
        Sci,
        Spi,
        Pulse_acc_input,
        Pulse_acc_overf,
        Timer_overf,
        Output_compare_5,
        Output_compare_4,
        Output_compare_3,
        Output_compare_2,
        Output_compare_1,
        Input_capture_3,
        Input_capture_2,
        Input_capture_1,
        Real_time,
        Irq,
        Xirq,
        Swi,
        Illegal,
        Cop_fail,
        Cop_clock_fail

} t_vector_num;

extern u8 VECTORS_init(void);
extern void VECTORS_set(t_vector_num n, void (*f)(void));
# 7 "essai.c" 2
# 23 "essai.c"
extern u8 run_task_num;
# 37 "essai.c"
static u16 compteur;

static u8 stk0[50];
static void task0(void)
{

        while(1) {
                (*((u8*)0x1003)) &= ~0x03;
                (*((u8*)0x1003)) |= 0x00;
                nanoK_task_terminate();
        }
}

static u8 stk1[50];
static void task1(void)
{

        while(1) {
                (*((u8*)0x1003)) &= ~0x02;
                (*((u8*)0x1003)) |= 0x01;
                nanoK_task_terminate();
        }
}

static u8 stk2[50];
static void task2(void)
{

        while(1) {
                (*((u8*)0x1003)) &= ~0x01;
                (*((u8*)0x1003)) |= 0x02;
                nanoK_task_terminate();
        }
}

static u8 stk3[50];
static void task3(void)
{

        while(1) {
                (*((u8*)0x1003)) &= ~0x00;
                (*((u8*)0x1003)) |= 0x03;
                nanoK_task_terminate();
        }
}

static u8 hook_stk[50];

static void hook(void)
{

        compteur++;







        (*((u8*)0x1025)) |= 0x40;

}

typedef void(*JMP)(void);
typedef struct t_vectors_table {
  u8 opcode;
  JMP f;
} t_vectors_table;

int main(void)
{

        (*((u8*)0x1007)) = 0xf3;

        nanoK_init();
        VECTORS_init();
        compteur = 0;


        nanoK_task_init(0, task0, stk0, sizeof(stk0));


        nanoK_task_init(1, task1, stk1, sizeof(stk1));


        nanoK_task_init(2, task2, stk2, sizeof(stk2));


        nanoK_task_init(3, task3, stk3, sizeof(stk3));


        nanoK_hook_init(hook, hook_stk, sizeof(hook_stk));







        VECTORS_set(Real_time, nanoK_kernel);
        (*((u8*)0x1026)) |= 0x03;
        (*((u8*)0x1024)) |= 0x43;



        nanoK_start();


        return 0;
}




void __premain() {
  return;
}

