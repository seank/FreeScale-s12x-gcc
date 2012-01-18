extern void Hex2Ascii(unsigned char,unsigned char*);
extern void cputch(char);
class CFrame {
 protected:
  unsigned char *m_rxBuf;
  unsigned int m_frameLen;
  unsigned char OnRxChar(unsigned char __c);
 private:
  unsigned int m_rxCnt;
  unsigned char m_state;
};

unsigned char
CFrame::OnRxChar(unsigned char c)
{
  switch (m_state)
    {
    case 0:
      m_rxCnt = 0;
      m_state = 1;
      
    case 1:
      if (c == 0x5a)
        {
          ++m_rxCnt;
          if (m_rxCnt == 2)
            m_state = 2;
        }
      else
        {
          char buf[2];
          Hex2Ascii(c, (unsigned char*)buf);
          cputch(buf[0]);
          cputch(buf[1]);
          m_rxCnt = 0;
        }
      break;
      
    case 2:
      m_rxBuf[m_rxCnt++] = c;
      if (m_rxCnt == (unsigned int) 7)
        m_frameLen = *(unsigned short*)(&m_rxBuf[4]);
      break;
    }
  
  return 0;
}
