typedef char byte;
extern int strlen(char*);
extern void LcdWriteChar(byte,byte,byte,byte);
extern void os_disable();
enum align {
  LCD_ALIGN_LEFT,
  LCD_ALIGN_CENTER,
  LCD_ALIGN_RIGHT
};

void LcdWriteString(
    byte page_no, byte x, byte y, char *str, byte align
) {

char *ptr;

 os_disable ();
    switch( align ) {
    case LCD_ALIGN_LEFT:
        break;
    case LCD_ALIGN_CENTER:
        x -= strlen( str ) >> 1; break;
    case LCD_ALIGN_RIGHT:
        x -= strlen( str ); break;
    }
    for( ptr = str; *ptr != 0; ptr++ ) {
        LcdWriteChar( page_no, x, y, *ptr );
        x++;
    }
}

void
os_disable()
{
  ;
}
int main()
{
  LcdWriteString(1,2,3,"Hello",LCD_ALIGN_CENTER);
  return 0;
}
void
LcdWriteChar(byte p, byte x, byte y, byte c)
{
  ;
}
