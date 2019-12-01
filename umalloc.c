#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

typedef long Align;

union header {
	struct {
		union header *ptr;
		uint          size;
	} s;
	Align x;
};

typedef union header Header;

static Header  base;
static Header *freep;

void
free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) break;
	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

static Header *
morecore(uint nu)
{
	char *  p;
	Header *hp;

	if (nu < 4096) nu = 4096;
	p = sbrk(nu * sizeof(Header));
	if (p == (char *)-1) return 0;
	hp         = (Header *)p;
	hp->s.size = nu;
	free((void *)(hp + 1));
	return freep;
}

void *
malloc(uint nbytes)
{
	Header *p, *prevp;
	uint    nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if ((prevp = freep) == 0) {
		base.s.ptr = freep = prevp = &base;
		base.s.size                = 0;
	}
	for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == 0) return 0;
	}
}

struct p2header{
	int pow2;
};

struct p2freelist{
	int pow2;
	struct p2freelist *next, *prev;
};

//smallest: 16, largest: 4096
//12-16, 17-32, 33-64, 65-128, 129-256, 257-512, 513-1024, 1025-2048, 2049-4096
// (int)given size / 16 = index of memtable
struct p2freelist* memtable[9];

int totmem = 0;
int totalloc = 0;

void *
p2malloc(int size)
{
	//implement sbrk when mem is full
	int realsize = size + sizeof(struct p2header);
	int i = index(realsize);

	int pow = 16;
	for(int x=0; x<i; x++)
	{
		pow = pow*2;
	}

	if(memtable[i] == 0)
	{
		char *  p;
		struct p2header *hp;

		uint nu = 4096;
		p = sbrk(nu);
		if (p == (char *)-1) return 0;
		hp         = (struct p2header *)p;
		hp->pow2 = pow;
		
		for(int x = 0; x < hp->pow2/pow; x++)
		{
			
		}

		//free((void *)(hp + 1));

	}

	//add new mem to list
	/*
	struct p2freelist* add;
	add->next = memtable[i];
	add->prev = 0;
	add->pow2 = pow;

	memtable[i]->prev = add;
	memtable[i] = add;
	*/
	//actually allocate mem + header

	return (void*)0;
}

void
p2free(void *ptr)
{
	//obtain header val
	struct p2header* head = (struct p2header *)((char *)ptr - sizeof(struct p2header));
	int list = head->pow2;

	printf(1, "%d\n", list);
}

int
p2allocated(void)
{

	return totalloc;
}

int
p2totmem(void)
{

	return totmem;
}

int
index(int size)
{
	if(size <= 16)
		return 0;
	else if(size <= 32)
		return 1;
	else if(size <= 64)
		return 2;
	else if(size <= 128)
		return 3;
	else if(size <= 256)
		return 4;
	else if(size <= 512)
		return 5;
	else if(size <= 1024)
		return 6;
	else if(size <= 2048)
		return 7;

	return 8;
}