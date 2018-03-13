

#define EXT2_ROOT_INO 2

#define INODE_PER_SECT  4

//assembly functions
void put_chA(char c);
void read_sector_c(unsigned int sector, char* buff);
void LADDR(void);

//c functions
void print_int(unsigned int i);
unsigned int read_endian_int(char* c);
unsigned short read_endian_short(char* c);
void load_inode(int inode);
void read_block_c(int block,char* buff);
int search_dir(char* sname,unsigned int* inode, char *type);


//buffers
char superblock[1024];
char block_group_descriptor_table[512];
char inode_table[512];

char block_buff0[1024];


unsigned int s_inodes_count;
unsigned int s_blocks_count;
unsigned int s_blocks_per_group;
unsigned int s_inodes_per_group=8192;

unsigned int i_block[15];
unsigned int i_size;

void cload(void){
	
	
	//put_chA('H');
		
	read_sector_c(2,&superblock[0]);
	
	//read_sector_c(3,&superblock[512]);
	

	
	//s_inodes_count = read_endian_int(&superblock[0]);
	//s_blocks_count = read_endian_int(&superblock[4]);
	//s_blocks_per_group = read_endian_int(&superblock[32]);

	s_inodes_per_group = read_endian_int(&superblock[40]);
	//print_int(s_inodes_per_group);
	
	
	
	
	
	
	unsigned int inode_n=EXT2_ROOT_INO;
	char type;
	
	load_inode(inode_n);
	search_dir("boot",&inode_n,&type);
	load_inode(inode_n);
	search_dir("kern",&inode_n,&type);
	load_inode(inode_n);

	int blocks = (i_size-1)/1024+1;
	
	//put_chA('0'+blocks);
	
	for(int i=0;(i<12) && (i<blocks);i++){
		read_block_c(i_block[i],(char*)(0x40000000+1024*i));
	}
	
	
	
	if(blocks>12){ // TODO Kernel size limited to 256+12 kB, follow linked list to extend
		read_block_c(i_block[12],block_buff0);
		for(int i=0;(i<256)&&(i<(blocks-12));i++){
			int block=read_endian_int(&(block_buff0[4*i]));
			read_block_c(block,(char*)(0x40000000+1024*(12+i)));
		}
	}
	
	
	//print_int(i_size);
	//put_chA('k');
	//char c= *((char*)0x40000440);
	//print_int(c);
	//put_chA('\n');
	LADDR();
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
	
	i_size=read_endian_int(&inode_table[128*ino_indx_sect_indx+4]);
	
	
	//print_int(ino_indx_sect_indx);
	//print_int(bg_inode_table*2+ino_indx_sect);
	//print_int(inode_table[i_size]);
	
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

int search_dir(char* sname, unsigned int* inode, char *type){
	read_block_c(i_block[0],block_buff0); // only looks in fist block out of possible thousands ( probably should do at least 12)
	int i=0;
	unsigned int t_inode;
	char t_type,name_len;
	unsigned short rec_len;
	while(i<1024){
		t_inode=read_endian_int(&block_buff0[i+0]);
		rec_len=read_endian_short(&block_buff0[i+4]);
		name_len=block_buff0[i+6];
		t_type=block_buff0[i+7];
		char dif=0;
		for(int j=0;j<name_len && sname[j];j++)
			dif|= (block_buff0[i+8+j] ^ sname[j]);
		
		if(!dif){
			*inode=t_inode;
			*type=t_type;
			return 1;
		}
		
		i+=rec_len;
		if(t_inode==0)break;
	}
	return 0;
}

unsigned short read_endian_short(char* c){
	unsigned short i=0;
	for(int j=0;j<2;j++){
		i=i<<8;
		unsigned char cu=c[1-j];
		i|=cu;
	}
	
	return i;
	
}

unsigned int read_endian_int(char* c){
	unsigned int i=0;
	for(int j=0;j<4;j++){
		i=i<<8;
		unsigned char cu=c[3-j];
		//put_chA(cu);
		i|=cu;
	}
	return i;
}

/*
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
}*/

