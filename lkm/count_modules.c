/******************************************************************************
 *
 * Name: count_modules.c 
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

#include<linux/module.h>
#include <linux/rbtree.h>

#include "include.h"

struct list_head *modules = (struct list_head *) sysmap_modules;

/*
 * Get the modules from the kernfs tree 
 * Not working right now
 */
int
count_recursive (struct rb_node *node)
{
	if(node == NULL)
		return 0;

	if(node->rb_left == NULL && node->rb_right == NULL) {
		return 0;
	} else {
		return count_recursive(node->rb_left) + count_recursive(node->rb_right) + 1;
	}

}

/* Get the module header from sysmap and iterate the list */
int
get_count (void)
{
	struct module* mod;
	int count = 0;
	char message[128];
	
	/* log our current op */
	strncpy(message, "\n[Checking loaded kernel modules...]\n", 127);
	write_to_file(message, strlen(message));

	list_for_each_entry(mod, modules, list) {
		memset(message, 0, 128);
		sprintf(message, "%s\n", mod->name);
		write_to_file(message, strlen(message));
		count++;
	}

	memset(message, 0, 128);
	sprintf(message, "Number of loaded kernel modules: %d\n", count);
	write_to_file(message, strlen(message));

	return count;
}

/* To count the number of modules */
int
count_modules (void)
{
	int count = 0;

	struct kernfs_node *kn = THIS_MODULE->mkobj.kobj.sd;
	struct rb_node *node = kn->parent->dir.children.rb_node;

	count = get_count();

	return count;
}
