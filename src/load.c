#define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

#define SEC_HALF 0x401FF200


//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
void load_inode(int inode);

char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char sector_buff[512];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group;

unsigned int i_block[15];

void cload(void){
	
	
	
	put_chA('H');
	//put_chA('e');
	put_chA('\n');
	
	//load second half
	//read_sector_c(1,(char*)SEC_HALF);
	
	
	
	read_sector_c(2,&superblock[0]);
	read_sector_c(3,&superblock[512]);
	
	s_inodes_count = read_endian_int(&superblock[0]);
	s_blocks_count = read_endian_int(&superblock[4]);
	s_blocks_per_group = read_endian_int(&superblock[32]);
	s_inodes_per_group = read_endian_int(&superblock[40]);
	
	print_int(s_inodes_count);
	print_int(s_blocks_count);
	print_int(s_blocks_per_group);
	print_int(s_inodes_per_group);
	
	
	load_inode(EXT2_ROOT_INO);

	read_sector_c(i_block[0],sector_buff);
	
	
	put_chA('q');
	//put_chA('u');
	put_chA('\n');
	
	while(1){}
}

void load_inode(int inode){
	
	unsigned int bg=(inode-1)/s_inodes_per_group;
	unsigned int ino_indx=(inode-1)%s_inodes_per_group;
	unsigned int bg_desc_sect=bg/16;
	unsigned int bg_desc_indx=bg%16;
	
	read_sector_c(4+bg_desc_sect,&block_group_descriptor_table[0]);
	
	unsigned int bg_inode_table=read_endian_int(&block_group_descriptor_table[32*bg_desc_indx + 8]);
	
	unsigned int ino_indx_sect=ino_indx/4;
	unsigned int ino_indx_sect_indx=ino_indx%4;
	
	read_sector_c(bg_inode_table*2+ino_indx_sect,&inode_table[0]);
	
	for(int i=0;i<15;i++){
		i_block[i]=read_endian_int(&inode_table[128*ino_indx_sect_indx+40+4*i]);
	}
	
	
	put_chA('b');print_int(bg);
	put_chA('i');print_int(ino_indx);
	put_chA('s');print_int(bg_desc_sect);
	put_chA('i');print_int(bg_desc_indx);
	
	put_chA('t');print_int(bg_inode_table);
	put_chA('n');print_int(ino_indx_sect);
	put_chA('x');print_int(ino_indx_sect_indx);
	//*/

}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		i|=c[3-j];
	}
	
	return i;
	
}

void print_int(unsigned int i){
	unsigned b10=1000000000;
	int p=0;
	while(b10!=0){
		unsigned int f=i/b10;
		if(f)p=1;
		i-=f*b10;
		b10/=10;
		
		if(p||(b10==0))put_chA('0'+f);
	}
	put_chA('\n');
}


//////////////////////////////////////////
#define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

#define SEC_HALF 0x401FF200


//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
void load_inode(int inode);

char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char sector_buff[512];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group;

unsigned int i_block[15];

void cload(void){
	
	
	
	put_chA('H');
	//put_chA('e');
	put_chA('\n');
	
	//load second half
	//read_sector_c(1,(char*)SEC_HALF);
	
	
	
	read_sector_c(2,&superblock[0]);
	read_sector_c(3,&superblock[512]);
	
	s_inodes_count = read_endian_int(&superblock[0]);
	s_blocks_count = read_endian_int(&superblock[4]);
	s_blocks_per_group = read_endian_int(&superblock[32]);
	s_inodes_per_group = read_endian_int(&superblock[40]);
	
	print_int(s_inodes_count);
	print_int(s_blocks_count);
	print_int(s_blocks_per_group);
	print_int(s_inodes_per_group);
	
	
	load_inode(EXT2_ROOT_INO);

	read_sector_c(i_block[0]*2,sector_buff);
	
	
	put_chA('q');
	//put_chA('u');
	put_chA('\n');
	
	while(1){}
}

void load_inode(int inode){
	
	unsigned int bg=(inode-1)/s_inodes_per_group;
	unsigned int ino_indx=(inode-1)%s_inodes_per_group;
	unsigned int bg_desc_sect=bg/16;
	unsigned int bg_desc_indx=bg%16;
	
	read_sector_c(4+bg_desc_sect,&block_group_descriptor_table[0]);
	
	unsigned int bg_inode_table=read_endian_int(&block_group_descriptor_table[32*bg_desc_indx + 8]);
	
	unsigned int ino_indx_sect=ino_indx/4;
	unsigned int ino_indx_sect_indx=ino_indx%4;
	
	read_sector_c(bg_inode_table*2+ino_indx_sect,&inode_table[0]);
	
	for(int i=0;i<15;i++){
		i_block[i]=read_endian_int(&inode_table[128*ino_indx_sect_indx+40+4*i]);
	}
	
	
	put_chA('b');print_int(bg);
	put_chA('i');print_int(ino_indx);
	put_chA('s');print_int(bg_desc_sect);
	put_chA('i');print_int(bg_desc_indx);
	
	put_chA('t');print_int(bg_inode_table);
	put_chA('n');print_int(ino_indx_sect);
	put_chA('x');print_int(ino_indx_sect_indx);
	//*/

}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		i|=c[3-j];
	}
	
	return i;
	
}

void print_int(unsigned int i){
	unsigned b10=1000000000;
	int p=0;
	while(b10!=0){
		unsigned int f=i/b10;
		if(f)p=1;
		i-=f*b10;
		b10/=10;
		
		if(p||(b10==0))put_chA('0'+f);
	}
	put_chA('\n');
}


////////////////////////////////////////// #define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

#define SEC_HALF 0x401FF200


//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
void load_inode(int inode);
void read_block_c(int block);

char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char sector_buff[1024];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group;

unsigned int i_block[15];

void cload(void){
	
	
	
	put_chA('H');
	//put_chA('e');
	put_chA('\n');
	
	//load second half
	//read_sector_c(1,(char*)SEC_HALF);
	
	
	
	read_sector_c(2,&superblock[0]);
	read_sector_c(3,&superblock[512]);
	
	s_inodes_count = read_endian_int(&superblock[0]);
	s_blocks_count = read_endian_int(&superblock[4]);
	s_blocks_per_group = read_endian_int(&superblock[32]);
	s_inodes_per_group = read_endian_int(&superblock[40]);
	
	print_int(s_inodes_count);
	print_int(s_blocks_count);
	print_int(s_blocks_per_group);
	print_int(s_inodes_per_group);
	
	
	load_inode(EXT2_ROOT_INO);

	read_sector_c(i_block[0]*2,sector_buff);
	read_sector_c(i_block[0]*2+1,sector_buff);
	
	
	put_chA('q');
	//put_chA('u');
	put_chA('\n');
	
	while(1){}
}

void load_inode(int inode){
	
	unsigned int bg=(inode-1)/s_inodes_per_group;
	unsigned int ino_indx=(inode-1)%s_inodes_per_group;
	unsigned int bg_desc_sect=bg/16;
	unsigned int bg_desc_indx=bg%16;
	
	read_sector_c(4+bg_desc_sect,&block_group_descriptor_table[0]);
	
	unsigned int bg_inode_table=read_endian_int(&block_group_descriptor_table[32*bg_desc_indx + 8]);
	
	unsigned int ino_indx_sect=ino_indx/4;
	unsigned int ino_indx_sect_indx=ino_indx%4;
	
	read_sector_c(bg_inode_table*2+ino_indx_sect,&inode_table[0]);
	
	for(int i=0;i<15;i++){
		i_block[i]=read_endian_int(&inode_table[128*ino_indx_sect_indx+40+4*i]);
	}
	
	/*
	put_chA('b');print_int(bg);
	put_chA('i');print_int(ino_indx);
	put_chA('s');print_int(bg_desc_sect);
	put_chA('i');print_int(bg_desc_indx);
	
	put_chA('t');print_int(bg_inode_table);
	put_chA('n');print_int(ino_indx_sect);
	put_chA('x');print_int(ino_indx_sect_indx);
	//*/

}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		i|=c[3-j];
	}
	
	return i;
	
}

void print_int(unsigned int i){
	unsigned b10=1000000000;
	int p=0;
	while(b10!=0){
		unsigned int f=i/b10;
		if(f)p=1;
		i-=f*b10;
		b10/=10;
		
		if(p||(b10==0))put_chA('0'+f);
	}
	put_chA('\n');
}

#define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

#define SEC_HALF 0x401FF200


//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
void load_inode(int inode);
void read_block_c(int block);

char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char block_buff[1024];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group;

unsigned int i_block[15];

void cload(void){
	
	
	
	put_chA('H');
	//put_chA('e');
	put_chA('\n');
	
	//load second half
	//read_sector_c(1,(char*)SEC_HALF);
	
	
	
	read_sector_c(2,&superblock[0]);
	read_sector_c(3,&superblock[512]);
	
	s_inodes_count = read_endian_int(&superblock[0]);
	s_blocks_count = read_endian_int(&superblock[4]);
	s_blocks_per_group = read_endian_int(&superblock[32]);
	s_inodes_per_group = read_endian_int(&superblock[40]);
	
	print_int(s_inodes_count);
	print_int(s_blocks_count);
	print_int(s_blocks_per_group);
	print_int(s_inodes_per_group);
	
	
	load_inode(EXT2_ROOT_INO);

	
	
	
	put_chA('q');
	//put_chA('u');
	put_chA('\n');
	
	while(1){}
}

void read_block_c(int block){
	read_sector_c(block*2,block);
	read_sector_c(block*2+1,block);
}


void load_inode(int inode){
	
	unsigned int bg=(inode-1)/s_inodes_per_group;
	unsigned int ino_indx=(inode-1)%s_inodes_per_group;
	unsigned int bg_desc_sect=bg/16;
	unsigned int bg_desc_indx=bg%16;
	
	read_sector_c(4+bg_desc_sect,&block_group_descriptor_table[0]);
	
	unsigned int bg_inode_table=read_endian_int(&block_group_descriptor_table[32*bg_desc_indx + 8]);
	
	unsigned int ino_indx_sect=ino_indx/4;
	unsigned int ino_indx_sect_indx=ino_indx%4;
	
	read_sector_c(bg_inode_table*2+ino_indx_sect,&inode_table[0]);
	
	for(int i=0;i<15;i++){
		i_block[i]=read_endian_int(&inode_table[128*ino_indx_sect_indx+40+4*i]);
	}
	
	/*
	put_chA('b');print_int(bg);
	put_chA('i');print_int(ino_indx);
	put_chA('s');print_int(bg_desc_sect);
	put_chA('i');print_int(bg_desc_indx);
	
	put_chA('t');print_int(bg_inode_table);
	put_chA('n');print_int(ino_indx_sect);
	put_chA('x');print_int(ino_indx_sect_indx);
	//*/

}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		i|=c[3-j];
	}
	
	return i;
	
}

void print_int(unsigned int i){
	unsigned b10=1000000000;
	int p=0;
	while(b10!=0){
		unsigned int f=i/b10;
		if(f)p=1;
		i-=f*b10;
		b10/=10;
		
		if(p||(b10==0))put_chA('0'+f);
	}
	put_chA('\n');
}

#define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

#define SEC_HALF 0x401FF200


//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
void load_inode(int inode);
void read_block_c(int block);

char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char block_buff[1024];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group;

unsigned int i_block[15];

void cload(void){
	
	
	
	put_chA('H');
	//put_chA('e');
	put_chA('\n');
	
	//load second half
	//read_sector_c(1,(char*)SEC_HALF);
	
	
	
	read_sector_c(2,&superblock[0]);
	read_sector_c(3,&superblock[512]);
	
	s_inodes_count = read_endian_int(&superblock[0]);
	s_blocks_count = read_endian_int(&superblock[4]);
	s_blocks_per_group = read_endian_int(&superblock[32]);
	s_inodes_per_group = read_endian_int(&superblock[40]);
	
	print_int(s_inodes_count);
	print_int(s_blocks_count);
	print_int(s_blocks_per_group);
	print_int(s_inodes_per_group);
	
	
	load_inode(EXT2_ROOT_INO);

	
	read_block_c(i_block[0]);
	
	put_chA('q');
	//put_chA('u');
	put_chA('\n');
	
	while(1){}
}

void read_block_c(int block){
	read_sector_c(block*2,block);
	read_sector_c(block*2+1,block);
}


void load_inode(int inode){
	
	unsigned int bg=(inode-1)/s_inodes_per_group;
	unsigned int ino_indx=(inode-1)%s_inodes_per_group;
	unsigned int bg_desc_sect=bg/16;
	unsigned int bg_desc_indx=bg%16;
	
	read_sector_c(4+bg_desc_sect,&block_group_descriptor_table[0]);
	
	unsigned int bg_inode_table=read_endian_int(&block_group_descriptor_table[32*bg_desc_indx + 8]);
	
	unsigned int ino_indx_sect=ino_indx/4;
	unsigned int ino_indx_sect_indx=ino_indx%4;
	
	read_sector_c(bg_inode_table*2+ino_indx_sect,&inode_table[0]);
	
	for(int i=0;i<15;i++){
		i_block[i]=read_endian_int(&inode_table[128*ino_indx_sect_indx+40+4*i]);
	}
	
	/*
	put_chA('b');print_int(bg);
	put_chA('i');print_int(ino_indx);
	put_chA('s');print_int(bg_desc_sect);
	put_chA('i');print_int(bg_desc_indx);
	
	put_chA('t');print_int(bg_inode_table);
	put_chA('n');print_int(ino_indx_sect);
	put_chA('x');print_int(ino_indx_sect_indx);
	//*/

}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		i|=c[3-j];
	}
	
	return i;
	
}

void print_int(unsigned int i){
	unsigned b10=1000000000;
	int p=0;
	while(b10!=0){
		unsigned int f=i/b10;
		if(f)p=1;
		i-=f*b10;
		b10/=10;
		
		if(p||(b10==0))put_chA('0'+f);
	}
	put_chA('\n');
}

#define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

#define SEC_HALF 0x401FF200


//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
void load_inode(int inode);
void read_block_c(int block,char* buff);

//buffers
char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char block_buff[1024];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group;

unsigned int i_block[15];

void cload(void){
	
	
	
	put_chA('H');
	//put_chA('e');
	put_chA('\n');
	
	//load second half
	//read_sector_c(1,(char*)SEC_HALF);
	
	
	
	read_sector_c(2,&superblock[0]);
	read_sector_c(3,&superblock[512]);
	
	s_inodes_count = read_endian_int(&superblock[0]);
	s_blocks_count = read_endian_int(&superblock[4]);
	s_blocks_per_group = read_endian_int(&superblock[32]);
	s_inodes_per_group = read_endian_int(&superblock[40]);
	
	print_int(s_inodes_count);
	print_int(s_blocks_count);
	print_int(s_blocks_per_group);
	print_int(s_inodes_per_group);
	
	
	load_inode(EXT2_ROOT_INO);

	
	read_block_c(i_block[0],block_buff);
	
	put_chA('q');
	//put_chA('u');
	put_chA('\n');
	
	while(1){}
}

void read_block_c(int block,char* b){
	read_sector_c(block*2,&b[0]);
	read_sector_c(block*2+1,&b[512]);
}


void load_inode(int inode){
	
	unsigned int bg=(inode-1)/s_inodes_per_group;
	unsigned int ino_indx=(inode-1)%s_inodes_per_group;
	unsigned int bg_desc_sect=bg/16;
	unsigned int bg_desc_indx=bg%16;
	
	read_sector_c(4+bg_desc_sect,&block_group_descriptor_table[0]);
	
	unsigned int bg_inode_table=read_endian_int(&block_group_descriptor_table[32*bg_desc_indx + 8]);
	
	unsigned int ino_indx_sect=ino_indx/4;
	unsigned int ino_indx_sect_indx=ino_indx%4;
	
	read_sector_c(bg_inode_table*2+ino_indx_sect,&inode_table[0]);
	
	for(int i=0;i<15;i++){
		i_block[i]=read_endian_int(&inode_table[128*ino_indx_sect_indx+40+4*i]);
	}
	
	/*
	put_chA('b');print_int(bg);
	put_chA('i');print_int(ino_indx);
	put_chA('s');print_int(bg_desc_sect);
	put_chA('i');print_int(bg_desc_indx);
	
	put_chA('t');print_int(bg_inode_table);
	put_chA('n');print_int(ino_indx_sect);
	put_chA('x');print_int(ino_indx_sect_indx);
	//*/

}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		i|=c[3-j];
	}
	
	return i;
	
}

void print_int(unsigned int i){
	unsigned b10=1000000000;
	int p=0;
	while(b10!=0){
		unsigned int f=i/b10;
		if(f)p=1;
		i-=f*b10;
		b10/=10;
		
		if(p||(b10==0))put_chA('0'+f);
	}
	put_chA('\n');
}

#define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

#define SEC_HALF 0x401FF200


//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
void load_inode(int inode);
void read_block_c(int block,char* buff);
int search_dir(unsigned int* inode, char *type);

//buffers
char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char block_buff[1024];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group;

unsigned int i_block[15];

void cload(void){
	
	
	
	put_chA('H');
	//put_chA('e');
	put_chA('\n');
	
	//load second half
	//read_sector_c(1,(char*)SEC_HALF);
	
	
	
	read_sector_c(2,&superblock[0]);
	read_sector_c(3,&superblock[512]);
	
	s_inodes_count = read_endian_int(&superblock[0]);
	s_blocks_count = read_endian_int(&superblock[4]);
	s_blocks_per_group = read_endian_int(&superblock[32]);
	s_inodes_per_group = read_endian_int(&superblock[40]);
	
	print_int(s_inodes_count);
	print_int(s_blocks_count);
	print_int(s_blocks_per_group);
	print_int(s_inodes_per_group);
	
	
	load_inode(EXT2_ROOT_INO);

	
	
	
	put_chA('q');
	//put_chA('u');
	put_chA('\n');
	
	while(1){}
}

void read_block_c(int block,char* b){
	read_sector_c(block*2,&b[0]);
	read_sector_c(block*2+1,&b[512]);
}


void load_inode(int inode){
	
	unsigned int bg=(inode-1)/s_inodes_per_group;
	unsigned int ino_indx=(inode-1)%s_inodes_per_group;
	unsigned int bg_desc_sect=bg/16;
	unsigned int bg_desc_indx=bg%16;
	
	read_sector_c(4+bg_desc_sect,&block_group_descriptor_table[0]);
	
	unsigned int bg_inode_table=read_endian_int(&block_group_descriptor_table[32*bg_desc_indx + 8]);
	
	unsigned int ino_indx_sect=ino_indx/4;
	unsigned int ino_indx_sect_indx=ino_indx%4;
	
	read_sector_c(bg_inode_table*2+ino_indx_sect,&inode_table[0]);
	
	for(int i=0;i<15;i++){
		i_block[i]=read_endian_int(&inode_table[128*ino_indx_sect_indx+40+4*i]);
	}
	
	/*
	put_chA('b');print_int(bg);
	put_chA('i');print_int(ino_indx);
	put_chA('s');print_int(bg_desc_sect);
	put_chA('i');print_int(bg_desc_indx);
	
	put_chA('t');print_int(bg_inode_table);
	put_chA('n');print_int(ino_indx_sect);
	put_chA('x');print_int(ino_indx_sect_indx);
	//*/

}

int search_dir(unsigned int* inode, char *type){
	read_block_c(i_block[0],block_buff);
	int i=0;
	unsigned int t_inode=
	
}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		i|=c[3-j];
	}
	
	return i;
	
}

void print_int(unsigned int i){
	unsigned b10=1000000000;
	int p=0;
	while(b10!=0){
		unsigned int f=i/b10;
		if(f)p=1;
		i-=f*b10;
		b10/=10;
		
		if(p||(b10==0))put_chA('0'+f);
	}
	put_chA('\n');
}

