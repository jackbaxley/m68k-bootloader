.equ MR1A, 0x80000000
.equ MR2A, 0x80000000
.equ SRA,  0x80000001
.equ CSRA, 0x80000001
.equ CRA,  0x80000002
.equ RXA,  0x80000003
.equ TXA,  0x80000003
.equ ACR,  0x80000004

.equ MR1B, 0x80000008
.equ MR2B, 0x80000008
.equ SRB,  0x80000009
.equ CSRB, 0x80000009
.equ CRB,  0x8000000A
.equ RXB,  0x8000000B
.equ TXB,  0x8000000B
.global LADDR
.equ LADDR, 0x40000000/* load addr*/

.equ SEC_HALF,0x401FF200/* load addr*/

.equ VFS_SEEK, 1
.equ VFS_READ, 2
.equ VFS_WRITE, 3
.equ EXT2_ROOT_INODE, 2 | is this correct?

.equ INODE_PER_SECT, 4

.comm superblock, 512
.comm bgdt, 1024
.comm inode_table_sector, 512
.comm block_load, 1024
.comm s_inodes_per_group,4


.data


.section .text.init

.align 2
.global _start
_start:

	move.l #1, %d0
	move.l #SEC_HALF, %a0
	jsr read_sector


	jsr cload

	|jsr LADDR
	/*

	| get superblock
	moveq #2, %d0
	move.l #superblock, %a0
	jsr read_sector
	move.l #(superblock+40+4), %a0 | addr of s_inodes_per_group in superblock
	move.l #s_inodes_per_group,%a1
	move.b -(%a0),(%a1)+
	move.b -(%a0),(%a1)+
	move.b -(%a0),(%a1)+
	move.b -(%a0),(%a1)+

	|load bgdt
	moveq #4, %d0
	move.l #bgdt, %a0
	jsr read_sector
	moveq #5, %d0
	jsr read_sector


	move.l #EXT2_ROOT_INODE,%d0
	jsr get_inode

	move.b #0x70, %d0
	move.l s_inodes_per_group, %d1
	jsr send_debug

	
	
	


iloop:
	bra iloop
*/

.text

.globl put_chA
put_chA: | byte to send on stack, uses %d1
	
	move.b SRA, %d1
	and.b #4, %d1
	beq put_chA
	move.l 4(%sp), %d0
	move.b %d0, TXA |move from stack to transmit
	rts

.section .text.init

.globl read_sector_c	
read_sector_c: | makes function c compatible
	move.l 8(%sp),%a0
	move.l 4(%sp),%d0

	
read_sector: | sector # in %d0, load_addr in %a0 

	movem.l %d2-%d3, -(%sp)
	move.l %d0, %d2
	move.b #VFS_SEEK, %d0
	jsr put_chB
	move.l %d2, %d0
	moveq #4, %d2 | set counter to 4
read_sector_l0:	
	jsr put_chB | send lower byte
	lsr.l #8,%d0 | shift to next byte
	subi.b #1,%d2 | decrement counter
	bne read_sector_l0 
	
	move.b #2, %d0 | send 2 for read cmd
	jsr put_chB
	
	move.w #512, %d2
read_sector_l1:
	move.b SRB, %d1
	and.b #1, %d1 | check if rx is rdy 
	beq read_sector_l1
	
	move.b RXB, (%a0)+
	subi.w #1, %d2
	bne read_sector_l1
	movem.l (%sp)+, %d2-%d3
	rts
	
	

put_chB: | byte to send in %d0, uses %d1
	
	move.b SRB, %d1
	and.b #4, %d1
	beq put_chB
	move.b %d0, TXB | send byte 
	rts


	
.section .rodata

path:
	|.asciz "/boot/kern"

	
	


	
/*
debug_code
	|debug
	movem.l %d0-%d1, -(%sp)
	move.l %d0, %d1
	move.b #0xC1, %d0
	jsr send_debug
	movem.l (%sp)+, %d0-%d1
	|debug
*/



	
	
	
	
	
	
	
	
	
	
	
	