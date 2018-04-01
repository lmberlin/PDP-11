#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word adr;

byte mem[64*1024];




#define LO(x) ((x) & 0xFF)
#define HI(x) (((x) >> 8) & 0xFF)



word w_read (adr a) {
    word t;
    t=0;
    t=t^mem[a+1];
    t=t<<8;
    t=t^mem[a];



    return t;
}
void w_write(adr a, word val) {
    byte q;
    q=0;
    q=q^val;

    mem[a] = q;
    val=val>>8;
    q=0;
    q=q^val;
    mem[a+1]=q;

}
byte b_read (adr a) {
    return mem[a];
}

void b_write(adr a, byte val)
{
    mem[a]=val;
}


void test_mem() {
    word b1;
    word w;
    w=0x0d0c;
    w_write(4, w);

    b1=w_read(4);
    printf("%04x = %04x" , w, b1);

}

void load_file( )
{

unsigned int w,v,start, y,i;


    while(scanf("%x%x", &start, &y) == 2)
    {
        //printf("%x = %x" , start, y);

        for(i=0; i<y; i=i+1)
        {
            scanf("%x", &w);
            b_write(start,w);

            //v=b_read(start);
            //printf("%02x  %02x" , w, v);
            start=start+1;


        }

    }
}

void mem_dump(adr start, word n)
{
word i;
    for(i = 0; i < n; i = i + 2)
    {
        printf("%06o : %06o\n", (start+i), w_read(start+i));
    }

}















int main() {
    //test_mem();
    load_file();

    return 0;

}
