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
	int hooked_syscalls;
	struct file *fd;
	char message[128], tmp[64];
	void **sys_call_table = (void *) sysmap_sys_call_table;
	
	hooked_syscalls = 0;
	
	/* create the file with write and append mode */
	fd = filp_open("/sys_call_table.log", O_CREAT|O_WRONLY|O_APPEND|O_TRUNC, S_IRWXU);
	
	/* log our current op */
	strncpy(message, "[system call table pointer check]\n", 64);
	write_to_file(fd, message, strlen(message));
	
	if((void *)sys_call_table[__NR_read] == (void *) sysmap_sys_read) {
		strncpy(message, "read - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "read - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_getdents] == (void *) sysmap_sys_getdents) {
		strncpy(message, "getdents - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "getdents - NOT OK!\n", 64);
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
		strncpy(message, "recvmsg - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "recvmsg - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_open] == (void *) sysmap_sys_open) {
		strncpy(message, "open - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "open - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_close] == (void *) sysmap_sys_close) {
		strncpy(message, "close - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "close - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_readlink] == (void *) sysmap_sys_readlink) {
		strncpy(message, "readlink - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "readlink - NOT OK!\n", 64);
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
		strncpy(message, "kill - OK\n", 64);
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		strncpy(message, "kill - NOT OK!\n", 64);
		write_to_file(fd, message, strlen(message));
	}
	
	/* log our current op */
	strncpy(message, "[system call function stack frame creation check]\n", 64);
	write_to_file(fd, message, strlen(message));

	/* check the first parts of memory */
	memcpy(tmp, (void *) sysmap_sys_read, 64);
	memset(message, 0, 128);
	sprintf(message, "read            - %8X %8X %8X %8X\n", (unsigned int) *tmp, (unsigned int) *(tmp+4), (unsigned int) *(tmp+8),
		(unsigned int) *(tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_getdents, 64);
	memset(message, 0, 128);
	sprintf(message, "getdents        - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_getdents64, 64);
	memset(message, 0, 128);
	sprintf(message, "getdents64      - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_recvmsg, 64);
	memset(message, 0, 128);
	sprintf(message, "recvmsg         - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_open, 64);
	memset(message, 0, 128);
	sprintf(message, "open            - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_close, 64);
	memset(message, 0, 128);
	sprintf(message, "close           - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_readlink, 64);
	memset(message, 0, 128);
	sprintf(message, "readlink        - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_readlinkat, 64);
	memset(message, 0, 128);
	sprintf(message, "readlinkat      - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_sys_kill, 64);
	memset(message, 0, 128);
	sprintf(message, "kill            - %8X %8X %8X %8X\n", *((unsigned int *) tmp), *((unsigned int *) tmp+4), *((unsigned int *) tmp+8),
		*((unsigned int *) tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_packet_rcv, 64);
	memset(message, 0, 128);
	sprintf(message, "packet_rcv      - %08X %08X %08X %08X\n", (unsigned int) *tmp, (unsigned int) *(tmp+4), (unsigned int) *(tmp+8),
		(unsigned int) *(tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_packet_rcv_spkt, 64);
	memset(message, 0, 128);
	sprintf(message, "packet_rcv_spkt - %08X %08X %08X %08X\n", (unsigned int) *tmp, (unsigned int) *(tmp+4), (unsigned int) *(tmp+8),
		(unsigned int) *(tmp+12));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	memcpy(tmp, (void *) sysmap_tpacket_rcv, 64);
	memset(message, 0, 128);
	sprintf(message, "tpacket_rcv     - %08X %08X %08X %08X\n", (unsigned int) *tmp, (unsigned int) *(tmp+1), (unsigned int) *(tmp+2),
		(unsigned int) *(tmp+3));
	memset(message+127, '\0', 1);
	write_to_file(fd, message, strlen(message));
	
	filp_close(fd, NULL);
	
	return 0;
}
