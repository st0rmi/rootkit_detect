/******************************************************************************
 *
 * Name: main.c 
 * Rootkit for the course Rootkit Programming at TUM in WS2014/15.
 * Implemented by Guru Chandrasekhara and Martin Herrmann.
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

#include <linux/kernel.h>

#include "check_syscalls.h"
#include "check_processes.h"
#include "include.h"
#include "main.h"

/*
 * Function called when loading the kernel module.
 * Prints a welcome-message and then does its magic.
 */
int init_module (void)
{
	int ret;

	ROOTKIT_DEBUG("****************************************\n");	
	ROOTKIT_DEBUG("Beginning rootkit detection procedure...\n");
	ROOTKIT_DEBUG("****************************************\n");
	
	
	
	/* check the sys call table */
	ret = check_syscalls();	
	if(ret < 0) {
		ROOTKIT_DEBUG("Error while checking the system call table!\n");
		return ret;
	}

	/* log the completion */
	ROOTKIT_DEBUG("****************************************\n");	
	ROOTKIT_DEBUG("Check complete. You may now unload.\n");
	ROOTKIT_DEBUG("****************************************\n");
	return 0;
}

/*
 * Function called when unloading the kernel module.
 * Prints a goodbye-message and restores the kernel to its
 * original form.
 */
void cleanup_module (void)
{	
	/* Finally, log the unloading */
	ROOTKIT_DEBUG("****************************************\n");	
	ROOTKIT_DEBUG("Unloading was successful. Bye!\n");
	ROOTKIT_DEBUG("****************************************\n");	
}
