
/*
write a C program to simulate paging 
take as input
1. size of physical memory
2. size of logical memory
3. partition size
4. logical address
5. base address
 for a given logical and base address, calculate physical address using 
	physical address = base address + (frame number * frame size) + offset
*/

#include <stdio.h>
#include <conio.h>
struct pstruct
{
	int fno;
	int pbit;
}ptable[10];

int pmsize,lmsize,psize,frame,page,ftable[20],frameno;
void info()
{
	printf("\nMEMORY MANAGEMENT USING PAGING\n\n");
	printf("Enter the Size of Physical memory: ");
	scanf("%d",&pmsize);
	printf("\nEnter the size of Logical memory: ");
	scanf("%d",&lmsize);
	printf("\nEnter the partition size: ");
	scanf("%d",&psize);
	frame = (int) pmsize/psize;
	page = (int) lmsize/psize;
	printf("\nThe physical memory is divided into %d no.of frames\n",frame);
	printf("\nThe Logical memory is divided into %d no.of pages\n",page);
}
void assign()
{
	int i;
	for (i=0;i<page;i++)
	{
		ptable[i].fno = -1;
		ptable[i].pbit= -1;
	}
	for(i=0; i<frame;i++)
		ftable[i] = 32555;
	for (i=0;i<page;i++)
	{
		printf("\nEnter the Frame number where page %d must be placed: ",i);
		scanf("%d",&frameno);
		ftable[frameno] = i;
		if(ptable[i].pbit == -1)
		{
			ptable[i].fno = frameno;
			ptable[i].pbit = 1;
		}
	}
	getch();
	printf("\n\nPAGE TABLE\n\n");
	printf("PageAddress FrameNo. PresenceBit\n");
	for (i=0;i<page;i++)
		printf("%d\t\t%d\t\t%d\n",i,ptable[i].fno,ptable[i].pbit);
}

void cphyaddr()
{
	int laddr,paddr,disp,phyaddr,baddr;
	getch();
	printf("\nProcess to create the Physical Address\n");
	printf("\nEnter the Base Address: ");
	scanf("%d",&baddr);
	printf("\nEnter the Logical Address: ");
	scanf("%d",&laddr);
	paddr = laddr / psize;
	disp = laddr % psize;
	if(ptable[paddr].pbit == 1 )
		phyaddr = baddr + (ptable[paddr].fno*psize) + disp;
	printf("\nThe Physical Address where the instruction present: %d",phyaddr);
}
void main()
{
	info();
	assign();
	cphyaddr();
	getch();
}