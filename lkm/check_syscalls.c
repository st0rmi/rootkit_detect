/******************************************************************************
 *
 * Name: check_syscalls.c 
 * 
 *
 *****************************************************************************/
/*
 * This file is part of naROOTo.

 * naROOTo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * naROOTo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with naROOTo.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include <linux/string.h>
#include <linux/unistd.h>
 
#include "include.h"

#define AMOUNT_SYS_CALLS 150

int
check_syscalls (void)
{
	int hooked_syscalls = 0;
	struct file *fd;
	char message[128];
	
	void **sys_call_table = (void *) sysmap_sys_call_table;
	
	unsigned int tmp[4]						 = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
	unsigned int original_read[4]            = { 0xD5894855, 0xEC834853, 0x74894848, 0x61E80824 };
	unsigned int original_getdents[4]        = { 0x89495541, 0xB9C031F8, 0x0000000A, 0x48555441 };
	unsigned int original_getdents64[4]      = { 0x89495541, 0xB9C031F8, 0x0000000A, 0x48555441 };
	unsigned int original_recvmsg[4]         = { 0x0578D285, 0xFFFFA0E9, 0xC0C748FF, 0xFFFFFFEA };
	unsigned int original_open[4]            = { 0x00CE8148, 0x0F000080, 0xF289CAB7, 0xBFFE8948 };
	unsigned int original_close[4]           = { 0x048B4865, 0x00B98025, 0x8B485100, 0x0005D080 };
	unsigned int original_readlink[4]        = { 0x8948D189, 0xFE8948F2, 0xFFFF9CBF, 0xF952E9FF };
	unsigned int original_readlinkat[4]      = { 0xFFF964E9, 0x48D189FF, 0x8948F289, 0xFF9CBFFE };
	unsigned int original_kill[4]            = { 0xFFECE5E9, 0x7EF685FF, 0x7EFF850E, 0xFBE8510A };
	unsigned int original_packet_rcv[4]      = { 0x56415741, 0x54415541, 0x89485355, 0xEC8348FB };
	unsigned int original_packet_rcv_spkt[4] = { 0x54415541, 0x89485355, 0x8A5241FB, 0x8B4C7D47 };
	unsigned int original_tpacket_rcv[4]     = { 0x56415741, 0x54415541, 0x89485355, 0xEC8348FB };
	
	/* create the file with write and append mode */
	fd = filp_open("/sys_call_table.log", O_CREAT|O_WRONLY|O_APPEND|O_TRUNC, S_IRWXU);
	
	/* log our current op */
	strncpy(message, "\n[Checking the pointers in the system call table...]\n", 64);
	write_to_file(fd, message, strlen(message));
	
	if((void *)sys_call_table[__NR_read] == (void *) sysmap_sys_read) {
		strncpy(message, "read       - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "read       - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_getdents] == (void *) sysmap_sys_getdents) {
		strncpy(message, "getdents   - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "getdents   - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_getdents64] == (void *) sysmap_sys_getdents64) {
		strncpy(message, "getdents64 - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "getdents64 - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_recvmsg] == (void *) sysmap_sys_recvmsg) {
		strncpy(message, "recvmsg    - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "recvmsg    - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_open] == (void *) sysmap_sys_open) {
		strncpy(message, "open       - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "open       - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_close] == (void *) sysmap_sys_close) {
		strncpy(message, "close      - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "close      - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_readlink] == (void *) sysmap_sys_readlink) {
		strncpy(message, "readlink   - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "readlink   - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_readlinkat] == (void *) sysmap_sys_readlinkat) {
		strncpy(message, "readlinkat - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "readlinkat - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_kill] == (void *) sysmap_sys_kill) {
		strncpy(message, "kill       - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "kill       - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	memset(message, 0, 128);
	sprintf(message, "There are %u manipulated pointers in the system call table.\n", hooked_syscalls);
	write_to_file(fd, message, strlen(message));
	
	/* log our current op */
	strncpy(message, "\n[Checking the first bytes of some system calls and other important functions...]\n", 128);
	write_to_file(fd, message, strlen(message));
	
	hooked_syscalls = 0;

	/* check the first parts of memory */
	if(memcmp(original_read, (void *) sysmap_sys_read, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_sys_read, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "read            - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "read            - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_getdents, (void *) sysmap_sys_getdents, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_sys_getdents, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "getdents        - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "getdents        - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_getdents64, (void *) sysmap_sys_getdents64, sizeof(unsigned int)*4) != 0) {

		memcpy(tmp, (void *) sysmap_sys_getdents64, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "getdents64      - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "getdents64      - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_recvmsg, (void *) sysmap_sys_recvmsg, sizeof(unsigned int)*4) != 0) {

		memcpy(tmp, (void *) sysmap_sys_recvmsg, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "recvmsg         - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "recvmsg         - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_open, (void *) sysmap_sys_open, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_sys_open, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "open            - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "open            - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_close, (void *) sysmap_sys_close, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_sys_close, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "close           - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "close           - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_readlink, (void *) sysmap_sys_readlink, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_sys_readlink, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "readlink        - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "readlink        - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}	
	
	if(memcmp(original_readlinkat, (void *) sysmap_sys_readlinkat, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_sys_readlinkat, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "readlinkat      - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "readlinkat      - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_kill, (void *) sysmap_sys_kill, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_sys_kill, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "kill            - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "kill            - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
		
	if(memcmp(original_packet_rcv, (void *) sysmap_packet_rcv, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_packet_rcv, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "packet_rcv      - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "packet_rcv      - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_packet_rcv_spkt, (void *) sysmap_packet_rcv_spkt, sizeof(unsigned int)*4) != 0) {

		memcpy(tmp, (void *) sysmap_packet_rcv_spkt, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "packet_rcv_spkt - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "packet_rcv_spkt - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	if(memcmp(original_tpacket_rcv, (void *) sysmap_tpacket_rcv, sizeof(unsigned int)*4) != 0) {
		
		memcpy(tmp, (void *) sysmap_tpacket_rcv, sizeof(unsigned int)*4);
		memset(message, 0, 128);
		sprintf(message, "tpacket_rcv     - %08X %08X %08X %08X\n", tmp[0], tmp[1], tmp[2], tmp[3]);
		memset(message+127, '\0', 1);
		write_to_file(fd, message, strlen(message));
		hooked_syscalls++;
		
	} else {
		
		strncpy(message, "tpacket_rcv     - OK\n", 64);
		write_to_file(fd, message, strlen(message));
		
	}
	
	memset(message, 0, 128);
	sprintf(message, "There are %u manipulated functions.\n", hooked_syscalls);
	write_to_file(fd, message, strlen(message));
	
	filp_close(fd, NULL);
	
	return 0;
}
