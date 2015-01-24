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
#include <linux/sched.h>
 
#include "include.h"

int
check_processes (void)
{
	char message[128];
	struct task_struct *task;
	unsigned int procs = 0;
	
	/* log our current op */
	strncpy(message, "\n[Checking currently running processes...]\n", 127);
	write_to_file(message, strlen(message));

	/* iterate each process and write its information */
	for_each_process(task) {
		memset(message, 0, 128);
		sprintf(message, "[%05d] %s\n", task->pid, task->comm);
		write_to_file(message, strlen(message));
		procs++;
	}
	
	memset(message, 0, 128);
	sprintf(message, "Number of processes: %u (%u if you account for the 'insmod').\n", procs, procs-1);
	write_to_file(message, strlen(message));
	strncpy(message, "Verify by running the command 'ps ax --no-headers | wc -l'.\n", 127);
	write_to_file(message, strlen(message));
	
	return 0;
}
