#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word adr;

word mem[64*1024];

#define LO(x) ((x) & 0xFF)
#define HI(x) (((x) >> 8) & 0xFF)
word w_read (adr a) {
    return mem[a];
}
void w_write(adr a, word val) {
    mem[a] = val;
}
byte b_read (adr a) {
    byte res;
    if(a%2 == 0) {
        res = LO(mem[a]);
    }
    else {
        res = HI(mem[a-1]);
        a=a-1;
        printf("mem[%d]=%04x res=%02x HI=%02x\n", a, mem[a], res, HI(mem[a]));
        
    }
    return res;
}

void b_write(adr a, byte val)
{
	if(a%2 == 0) {
		mem[a] = val;
	}
	else
	{
		mem[a-1] = (((word)val) << 8) | mem[a-1];
	}
}


void test_mem() {
    byte b1;
    word w;
    w=0x0d0c;
    w_write(4, w);
    
    b1=b_read(5);
    printf("%04x = %02x" , w, b1);

}

int main() {
    test_mem();
    
    return 0;

}
