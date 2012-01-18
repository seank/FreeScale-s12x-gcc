# 1 "eeprom.c"
#define ASM 0 







# 1 "eeprom.h" 1
 














# 1 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stdbool.h" 1 3
 



 

typedef enum
  {
    false = 0,
    true = 1
  } bool;

 



 



# 16 "eeprom.h" 2

# 1 "../../include/sys/hwreg.h" 1
 








# 1 "../../include/asm-m68hc12/hwreg.h" 1
 











# 1 "../../include/asm-m68hc12/param.h" 1
 









 





 





 







 













# 13 "../../include/asm-m68hc12/hwreg.h" 2

# 1 "../../include/asm-m68hc12/hwregaddr.h" 1
 







 












 








 











 









 






 





 









 







 



 






















 




























 


  
  


 










 























 














 







 





 



  




                                    


 






 
































 









 







 








 




 



 






































 






 










 










 










 













 





 


 










 







 










 











              


 







              

              


 





 









 











              

 


 








 





 





 






 












 










 








 








 

















 






 




 





 




 


 

 









 


 





 











 

 













# 14 "../../include/asm-m68hc12/hwreg.h" 2


typedef unsigned char byte;
typedef unsigned short word;

 
extern volatile byte _io_ports[];
extern volatile byte *io_ports;






 



 





 


 


static inline void
relocate_reg(word base)
{
  _io_ports[0x11 ] = (base/0x100) & 0xF8;
  io_ports = (byte*) base;
}

 


static inline void
set_bus_expanded(void)
{
  *((volatile word*) &_io_ports[( 0x0A  )])  = (word)((byte)(1<<7) | (1<<2) )*0x100 + ((1<<5) | (1<<4) ) ;
  _io_ports[( 0x13  )]  = 0x7F;        
}


 


static inline void
set_bus_expanded_wide(void)
{
  *((volatile word*) &_io_ports[( 0x0A  )])  = (word)((byte)(1<<7) | (1<<2) )*0x100 + ((1<<6) | (1<<5) | (1<<4) ) ;
  _io_ports[( 0x13  )]  = 0x7F;
}

 
static inline void
set_bus_single_chip(void)
{
  _io_ports[( 0x0B  )]  = (byte)(1<<7) | (1<<4) ;
}

 


static inline void
rti_init(byte scale)
{
  _io_ports[( 0x14  )]  = (1<<5)  | (scale & (0x7) );
}

 
static inline byte
rti_getFlg(void)
{
  return _io_ports[( 0x15  )] ;
}

 
static inline void
rti_clearFlg(void)
{
  _io_ports[( 0x15  )]  = 0x80 ;
}

 
static inline void
cop_disable(void)
{
#if ASM
  asm("bclr %0,%1" : : "R"( _io_ports[( 0x16  )]  ), "i"(  (0x7)  )) ;        
#endif
}

 
static inline void
cop_force_reset(void)
{
  _io_ports[( 0x17  )]  = 0x55;
  _io_ports[( 0x17  )]  = 0xAA;
}

 

static inline void
cop_reset(void)
{

  cop_force_reset();

}

 
static inline void
cop_init(void)
{
  cop_force_reset();
  _io_ports[( 0x16  )]  = (1<<3)  | 2 ;
}






# 10 "../../include/sys/hwreg.h" 2







# 17 "eeprom.h" 2


# 1 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stddef.h" 1 3






 


# 19 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stddef.h" 3



 


 





 


# 61 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stddef.h" 3


 





 


















 





 

 

# 131 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stddef.h" 3


 

 


































typedef short unsigned int size_t;






















 




 

# 271 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stddef.h" 3


# 283 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stddef.h" 3


 

 

# 317 "/usr/lib/gcc-lib/m6811-elf/2.95.3/include/stddef.h" 3




 





















# 19 "eeprom.h" 2




 
bool eeprom_isWriting (void);

 

int eeprom_prepareRead (word offset);

 


int eeprom_readByte (word offset);

 


word eeprom_readWord (word offset);

 
void eeprom_chkWrite (void);

 

int eeprom_writeByte (word offset, byte data);

 


int eeprom_writeWord (word offset, word data);






# 9 "eeprom.c" 2

# 1 "../../include/timer.h" 1
 












# 1 "../../include/sys/timer.h" 1
 









# 1 "../../include/asm-m68hc12/timer.h" 1
 















   

  static inline void
  timer_init(void)
  {
    _io_ports[( 0x8D  )]  = (byte)(1<<5)  | 3 ;
     
    _io_ports[( 0x86  )]   = (byte)(1<<7)  | (byte)(1<<5)  | (byte)(1<<4) ;
  }

   

  static inline short
  get_hwtime(void)
  {
    return *((volatile word*) &_io_ports[( 0x84  )]) ;
  }

   

  static inline byte
  get_tof_flg(void)
  {
    return (_io_ports[( 0x8F  )]  & (byte)(1<<7) );
  }

   
  static inline void
  tc_set_outputcompare(byte n)
  {
    _io_ports[( 0x80  )]  |= 1<<n;
  }

   
  static inline void
  tc_set_inputcapture(byte n)
  {
    _io_ports[( 0x80  )]  &= (byte)~(1<<n);
  }

   
  static inline void
  tc_interrupt_enable(byte n)
  {
    _io_ports[( 0x8C  )]  |= (byte)(1<<n);
  }

   
  static inline void
  tc_interrupt_disable(byte n)
  {
    _io_ports[( 0x8C  )]  &= (byte)~(1<<n);
  }

   

  static inline byte
  tc_get_flg(byte n)
  {
    return (_io_ports[( 0x8E  )]  & (byte)(1<<n));
  }

   

  static inline word
  tc_get_value(byte n)
  {
    return ((volatile word*) &_io_ports[( 0x90  )]) [n];
  }

   

  static inline void
  tc_set_value(byte n, word val)
  {
    ((volatile word*) &_io_ports[( 0x90  )]) [n] = val;
  }

   


  static inline void
  tc_add_microseconds(byte n, unsigned long t)
  {
    tc_set_value(n, tc_get_value(n) + (word)((8000000   / (1<< 3 ))   * t/1000000));
  }

   


  static inline void
  tc_set_tocmode(byte n, byte mode)
  {
    word d = *((volatile word*) &_io_ports[( 0x88  )]) ;
    n *= 2;                        
    d &= ~(0x3 << n);              
    d |= mode << n;                

    *((volatile word*) &_io_ports[( 0x88  )])  = d;
  }

   


  static inline void
  tc_toggle_tocmode(byte n)
  {
    *((volatile word*) &_io_ports[( 0x88  )])  ^= (word)(1<<(n*2));
  }

   


  static inline void
  tc_set_ticmode(byte n, byte mode)
  {
    word d = *((volatile word*) &_io_ports[( 0x8A  )]) ;
    n *= 2;                         
    d &= ~(0x3 << n);
    d |= mode << n;

    *((volatile word*) &_io_ports[( 0x8A  )])  = d;
  }






# 11 "../../include/sys/timer.h" 2






# 14 "../../include/timer.h" 2

# 1 "../../include/sys/locks.h" 1
 









# 1 "../../include/asm-m68hc12/locks.h" 1
 














 

 

static inline short
lock(void)
{
  short ccsav;
  asm volatile ("tpa\nsei": "=d"(ccsav):: "cc");
  return ccsav;
}

 

static inline void
unlock(void)
{
  asm volatile ("cli"::: "cc");
}

 

static inline void
restorelock(short ccsav)
{
  asm volatile ("tap":: "d"(ccsav): "cc");
}






# 11 "../../include/sys/locks.h" 2






# 15 "../../include/timer.h" 2


   






   






  extern volatile unsigned TofCnt;          
  extern volatile unsigned MillisecCnt;
  extern volatile byte TimerFlgs;

   

  extern void timer_init_tof (void);

   

  extern signed char reserveTimerNum (byte n);

   

  extern signed char reserveTimerNumOnly (byte n);
  extern void freeTimerNum (byte n);
  extern void timer_init_msec (byte tnum);
  extern void doTimeMsec (void);
  extern unsigned long get_time (void);

  extern void intTof (void) __attribute__((__interrupt__));
  extern void intTimeMsec (void) __attribute__((__interrupt__));

   

  static inline void
  doTof (void)
  {
    get_hwtime();   
    TofCnt++;
#if ASM
    asm("bset %0,%1"::"a"( TimerFlgs ), "i"(  (byte)(1<<7)  )) ;
#endif
  }

   
  static inline byte
  isTickMsecFlg (void)
  {
    return TimerFlgs & (1<<6) ;
  }

   
  static inline void
  clearTickMsecFlg (void)
  {
#if ASM
    asm("bclr %0,%1"::"R"( TimerFlgs ), "i"(  (1<<6)  )) ;
#endif
  }






# 10 "eeprom.c" 2




extern volatile byte _eeprom_base[0x300 ];
static word   dataOffset;           
static byte   dataBuf[2];           
static byte   dataSize;             
static byte   writeTries = 2 ;     
static signed char eepTimerNum = -1;





 

bool
eeprom_isWriteMode (void)
{
  return _io_ports[( 0xF3  )]  & (1<<1) ;
}

 

static inline void
eeprom_mapOn (void)
{
#if ASM
  asm("bset %0,%1"::"R"( _io_ports[( 0x12  )]  ), "i"(  (1<<0)  )) ;
#endif
}

 
static inline void
eeprom_mapOff (void)
{
#if ASM
  asm("bclr %0,%1"::"R"( _io_ports[( 0x12  )]  ), "i"(  (1<<0)  )) ;
#endif
}

 

int
eeprom_prepareRead (word offset)
{
  if(offset >= 0x300 )    return -2;    
  if(eeprom_isWriteMode())   return -1;    
  eeprom_mapOn();                        
  return 0;
}

 


int
eeprom_readByte (word offset)
{
  int rtn;

  rtn = eeprom_prepareRead(offset);
  if(rtn < 0) return rtn;

  return _eeprom_base[( offset )] ;         
}

 


word
eeprom_readWord (word offset)
{
  if(eeprom_prepareRead(offset) < 0) return 0xFFFF;
  return *((volatile word*) &_eeprom_base[( offset )]) ;         
}

 
void
eeprom_chkWrite (void)
{
  if(eepTimerNum < 0) return;        

   
  if((_io_ports[( 0xF3  )]  & (1<<0) ) )
  {
     
    if(tc_get_flg(eepTimerNum))
    {
       
#if ASM
      asm("bclr %0,%1" : : "R"(_io_ports[( 0xF3  )]  ), "i"(  (1<<0)  )) ;
      asm("bclr %0,%1" : : "R"( _io_ports[( 0xF3  )]  ), "i"(  (1<<1)  )) ;    
#endif
    }
  }

   
  if(! (_io_ports[( 0xF3  )]  & (1<<0) ) )
  {
     
    if(dataSize)
    {
      byte dataOddBoundary = dataSize & 1;      
      byte dataIdx;
      word currOffset, r, w;

       
      dataIdx = dataSize - 1;
#if ASM
      asm("bclr %0,%1"::"R"( dataIdx ), "i"(  1 )) ;                    
#endif
      currOffset = dataOffset + dataIdx;

      if(dataOddBoundary) {
         
        r = eeprom_readByte(currOffset);
        w = dataBuf[dataIdx];
      }
      else {
         
        r = eeprom_readWord(currOffset);
        w = *((word*)&dataBuf[dataIdx]);
      }

       
      if((w ^ r) & w)
      {
         
#if ASM
        asm("bset %0,%1"::"R"( _io_ports[( 0xF3  )]  ), "i"(  (1<<4) | (1<<2) | (1<<1)  )) ;
#endif
        if(dataOddBoundary)
        {
          _eeprom_base[( currOffset )]  = w;      
        }
        else
        {
          *((volatile word*) &_eeprom_base[( currOffset )])  = w;      
        }

         
        tc_set_value(eepTimerNum, get_hwtime()+(word)((8000000   / (1<< 3 ))  *.010));
#if ASM
        asm("bset %0,%1"::"R"( _io_ports[( 0xF3  )]  ), "i"(  (1<<0)  )) ;       
#endif
      }
      else if(r != w && writeTries)    
      {
         
        _io_ports[( 0xF3  )]  = (_io_ports[( 0xF3  )]  & ~(1<<2) ) | (1<<1) ;

        if(dataOddBoundary) {
          _eeprom_base[( currOffset )]  = w;      
        }
        else {
          *((volatile word*) &_eeprom_base[( currOffset )])  = w;      
        }

        writeTries--;                        

         
        tc_set_value(eepTimerNum, get_hwtime()+(word)((8000000   / (1<< 3 ))  *.010));
#if ASM
        asm("bset %0,%1"::"R"( _io_ports[( 0xF3  )]  ), "i"(  (1<<0)  )) ;       
#endif
      }
      else    
      {
        dataSize = dataIdx;                 
        writeTries = 2 ;        

        if(!dataSize)
        {
           
          freeTimerNum(eepTimerNum);
          eepTimerNum = -1;
        }
      }
    }
  }
}

 




static int
eeprom_writeData (word offset, void *data, size_t sz)
{
  if(dataSize) return -1;                       
  if(offset + sz > 0x300 ) return -2;       
  eepTimerNum = reserveTimerNum(0);              
  if(eepTimerNum < 0) return -3;                    
  if(sz > sizeof(dataBuf)) return -4;                  

   
  tc_set_outputcompare(eepTimerNum);

   
  dataOffset = offset;
  memcpy(dataBuf, data, sz);
  dataSize   = sz;

  return 0;
}

 

int
eeprom_writeByte (word offset, byte data)
{
  return eeprom_writeData(offset, &data, 1);
}

 


int
eeprom_writeWord (word offset, word data)
{
  return eeprom_writeData(offset, &data, 2);
}

