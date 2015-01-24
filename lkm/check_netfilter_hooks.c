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
 
#include <linux/list.h>
#include <linux/netfilter.h>
#include <linux/string.h>
 
#include "include.h"

int
check_netfilter_hooks (void)
{
	char message[128];
	int netfilter_hooks = 0;
	struct list_head *cursor;
	struct nf_hook_ops *cur;
	struct module *mod;
	
	/* log our current op */
	strncpy(message, "\n[Checking netfilter hooks...]\n", 127);
	write_to_file(message, strlen(message));

	/* iterate all netfilter hooks */
	list_for_each(cursor, &nf_hooks[PF_INET][NF_INET_LOCAL_IN]) {
		cur = list_entry(cursor, struct nf_hook_ops, list);
		mod = cur->owner;
		
		memset(message, 0, 128);
		sprintf(message, "[%s] 0x%08lX\n", mod->name, (unsigned long) cur->hook);
		write_to_file(message, strlen(message));
		
		netfilter_hooks++;
	}
	
	memset(message, 0, 128);
	sprintf(message, "Number of current netfilter hooks: %u.\n", netfilter_hooks);
	write_to_file(message, strlen(message));
	
	return 0;
}
