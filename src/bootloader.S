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


.text

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


.globl put_chA
put_chA: | byte to send on stack, uses %d1
	
	move.b SRA, %d1
	and.b #4, %d1
	beq put_chA
	move.l 4(%sp), %d0
	move.b %d0, TXA |move from stack to transmit
	rts
/*


|sends debug data to fileserver
|%d0 contains debug_code
|%d1 contains debug_data

send_debug:
	move.l %d2, -(%sp)
	move.l %d3, -(%sp)
	
	move.l %d0, %d2
	move.l %d1, %d3
	move.b #16, %d0
	jsr put_chB
	move.l %d2, %d0
	jsr put_chB
	move.l %d3, %d0 | data to send in d0
	
	moveq #4, %d2 | set counter to 4
send_debug_l0:	
	jsr put_chB | send lower byte
	lsr.l #8,%d0 | shift to next byte
	subi.b #1,%d2 | decrement counter
	bne send_debug_l0
	
	move.l (%sp)+, %d3
	move.l (%sp)+, %d2
	rts


|Searches for inode in by name in directory
|inode of directry to search in is given in
|%d0


get_inode: 
	movem.l %d2-%d7, -(%sp)
	
	subi.l #1, %d0 | sub 1 from d0
	divul.l s_inodes_per_group, %d1:%d0 | divide %d0 by s_inodes_per_group, quotiont in d0, rem in d1
	| d0 is block group, d1 is inode withing bgdt
	
	
	lsl.l #5,%d0 | entries in bgdt are 32 bytes
	addi.l #(bgdt+8+4),%d0 | addr of byte after last byte of bg_inode_table_value
	move.l %d0, %a0
	
	move.b -(%a0), %d0
	lsl.l #8, %d0
	move.b -(%a0), %d0
	lsl.l #8, %d0
	move.b -(%a0), %d0
	lsl.l #8, %d0
	move.b -(%a0), %d0
	|lsl.l #8, %d0
	
	|d0 has bg_inode_table from bgdt
	|figure out which sector contains inode struct
	
	
	
	divul.l #INODE_PER_SECT, %d2:%d1
	|%d1 contains sector# within inode table
	|%d2 contains inode# within sector
	add.l %d0, %d0
	add.l %d1, %d0
	|d0 contains sector# of useful inode_table
	move.l #inode_table_sector, %a0
	jsr read_sector | read the sector
	
	
	lsl.l #7, %d2 |128 bytes per inode entry, get byte offset of inode table
	move.l %d2, %a2 | %a2 contains base of inode stucture
	add.l #inode_table_sector, %a2
	
	clr.l %d2 | %d2 contains block # to load
get_inode_load_new_block:
	move.l %d2, %d0
	move.l %a2, %a0
	move.l #block_load, %a1
	jsr load_block_from_inode

	move.l #block_load, %a3 |%a3 contains current address within block
	
	move.l (%a3)+, %d0
	|jsr flip_endian_d0_l
	move.l %d0, %d3 | %d3 is inode of current directory entry
	
	|move.l (%a3 
	
	
	
	movem.l (%sp)+, %d2-%d7
	rts

|loads a 1kB block from an inode into memory
|%d0 contains block # to load
|%a0 is address of inode structure
|%a1 is load address of block
load_block_from_inode:
	move.l %d0, %d1
	subi.l #12, %d0
	blt load_block_from_inode_dir_block
	subi.l #256, %d0
	blt load_block_from_inode_single_link_block
	subi.l #65536, %d0
	blt load_block_from_inode_link_block
	blt load_block_from_inode_triple_link_block
	
	
	load_block_from_inode_dir_block:
	load_block_from_inode_single_link_block:
	load_block_from_inode_link_block:
	load_block_from_inode_triple_link_block:
	
	rts

*/
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



	
	
	
	
	
	
	
	
	
	
	
	