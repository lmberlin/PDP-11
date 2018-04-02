#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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

unsigned int w,start, y,i;


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

void do_add(){
	printf("ADD");
	
}
void do_mov(){
	printf("MOV");
	
}
void do_halt(){
	printf("HALT");
	
}
void do_unknow(){
	printf("unknow");
	
}


struct Command{
	word opcode;
	word mask;
	char * name;
	void (*func)();


} commands[] =
	{
		{0,0177777,"halt",do_halt},
		{0010000,0170000,"mov",do_mov},
		{0060000,0177777,"add",do_add},
		{0000000,0000000,"unknow",do_unknow},
};




 void run(adr pc0) 
{
	 adr pc = pc0;
	 int i;
	 while(1)
	 {
		word w=w_read(pc);
		printf("06o:%06o ",pc,w);
		pc+=2;
		for(i=0; ; i++)
		{
			struct Command cmd = commands[i];
			if((w & cmd.mask) == cmd.opcode)
			{
				printf("%s", cmd.name);
				cmd.func();
				break;
			}
		}
	}
}    

















int main() {
    test_mem();
    load_file();
    run(0100);
    return 0;

}
