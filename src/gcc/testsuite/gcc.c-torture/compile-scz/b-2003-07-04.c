typedef unsigned long __u32;
typedef unsigned short __u16;
__u16 tcp_chksum;
void a(void)
{
   
     __u32 checksum;
     checksum += checksum >> 16;
     tcp_chksum = ~checksum;
}


