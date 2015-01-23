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
	int i, hooked_syscalls;
	struct file *fd;
	char * message[64];
	void **sys_call_table = (void *) sysmap_sys_call_table;
	
	hooked_syscalls = 0;
	
	/* create the file with write and append mode */
	fd = filp_open("/sys_call_table.log", O_CREAT|O_WRONLY|O_APPEND|O_TRUNC, S_IRWXU);
	
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
		strncpy(message, "getdents - NOT OK!\n";, 64);
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_getdents64] == (void *) sysmap_sys_getdents64) {
		message = "getdents64 - OK\n";
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		message = "getdents64 - NOT OK!\n";
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_recvmsg] == (void *) sysmap_sys_recvmsg) {
		message = "recvmsg - OK\n";
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		message = "recvmsg - NOT OK!\n";
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_open] == (void *) sysmap_sys_open) {
		message = "open - OK\n";
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		message = "open - NOT OK!\n";
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_close] == (void *) sysmap_sys_close) {
		message = "close - OK\n";
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		message = "close - NOT OK!\n";
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_readlink] == (void *) sysmap_sys_readlink) {
		message = "readlink - OK\n";
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		message = "readlink - NOT OK!\n";
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_readlinkat] == (void *) sysmap_sys_readlinkat) {
		message = "readlinkat - OK\n";
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		message = "readlinkat - NOT OK!\n";
		write_to_file(fd, message, strlen(message));
	}
	
	if((void *)sys_call_table[__NR_kill] == (void *) sysmap_sys_kill) {
		message = "kill - OK\n";
		write_to_file(fd, message, strlen(message));
	} else {
		hooked_syscalls++;
		message = "kill - NOT OK!\n";
		write_to_file(fd, message, strlen(message));
	}

	filp_close(fd, NULL);
	
	return 0;
}