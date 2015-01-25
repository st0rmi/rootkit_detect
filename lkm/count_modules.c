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

#include <linux/module.h>
#include <linux/rbtree.h>
#include <linux/kernfs.h>
#include <linux/delay.h>

#include "include.h"

struct list_head *modules = (struct list_head *) sysmap_modules;

typedef struct module * func(char *name);
func* find_module1 = (func*) sysmap_find_module;

//typedef bool func1(unsigned long addr);
//func1* is_module_addr1 = (func1*) sysmap_is_module_address;

//func1* is_module_percpu_address1 = (func1 *)sysmap_is_module_percpu_address;

//func1* is_module_text_address1 = (func1 *) sysmap_is_module_text_address;
struct mutex *mod_mutex = (struct mutex *) (sysmap_module_mutex);
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
getcount_list (void)
{
	struct module* mod;
	int count = 0;
	char message[128];
	
	/*bool tf;
	int flag = 0;
	struct module * tmp;
	unsigned long addr = 0;
	unsigned long i = 0;	
	*/

	/* log our current op */
	strncpy(message, "\n[Checking loaded kernel modules in lsmod...]\n", 127);
	write_to_file(message, strlen(message));

	list_for_each_entry(mod, modules, list) {
		memset(message, 0, 128);
		sprintf(message, "%s\n", mod->name);
		write_to_file(message, strlen(message));

		count++;
	}
		/*tf =  is_module_addr1((unsigned long) 0xffffffffa03be060);
		if(tf)
		{
			ROOTKIT_DEBUG("wow!!module = %s  Address = %lx, is modules = %u\n",mod->name, (unsigned long)mod, tf);
		}*/
		
		/*addr = 18446744072101531000;	
		       
		for(i = addr; i<18446744072104580000; i+=4)
		{
			tmp = (struct module *) i;
			tf =  is_module_addr1((unsigned long) i);
			//tf = is_module_percpu_address1(i);
			//tf = is_module_text_address1(i);
			if(tf)
			{
				ROOTKIT_DEBUG("name = %s   Address = %lx, is modules = %u\n",tmp->name, (unsigned long)tmp, tf);
				//break;
			}
		}*/
	
	

	memset(message, 0, 128);
	sprintf(message, "Number of loaded kernel modules: %d\n", count);
	write_to_file(message, strlen(message));

	return count;
}


int 
getcount_kobj(void)
{
	struct list_head *head = &THIS_MODULE->mkobj.kobj.entry;
	struct kobject *ko;
	
	int count = 0;
	char message[128];

	strncpy(message, "\n[Checking loaded kernel modules in kobjects...]\n", 127);
	write_to_file(message, strlen(message));

	list_for_each_entry(ko, head, entry) {
			count++;
			if(ko->name != NULL){
				memset(message, 0, 128);
				sprintf(message, "%s\n", ko->name);
				write_to_file(message, strlen(message));
			}
	}

	memset(message, 0, 128);
	sprintf(message, "Number of loaded kernel modules: %d\n", count);
	write_to_file(message, strlen(message));
		
	 return count;
}


/* Function to get the count from the kernel file system */
int 
getcount_kernfs(void)
{
	struct kernfs_node *kn = THIS_MODULE->mkobj.kobj.sd;
	//struct rb_node *node = kn->parent->dir.children.rb_node;
	int count = 0;
	char message[128];
	struct kernfs_node *entry,*n;
	/* log our current op */
	strncpy(message, "\n[Checking loaded kernel modules in /sys/modules...]\n", 127);
	write_to_file(message, strlen(message));
	
	rbtree_postorder_for_each_entry_safe(entry, n, &kn->parent->dir.children, rb)
	{ 
		char buf[250];
		memset(message, 0, 128);
		sprintf(message, "%s\n", kernfs_path(entry,buf,250));
		write_to_file(message, strlen(message));
		
		
	/*	memset(message, 0, 128);
		sprintf(message, "%s\n", entry->parent->name);
		write_to_file(message, strlen(message)); */
		count++;	
	}
	
	memset(message, 0, 128);
	sprintf(message, "Number of loaded kernel modules in /sys/modules: %d\n", count);
	write_to_file(message, strlen(message));
	
	return count;
}


/* To count the number of modules */
int
count_modules (void)
{
	int count = 0;
	
	struct module *mod;
	char name[64] = "narooto";

        mutex_lock(mod_mutex);
        mod = find_module1(name);
        mutex_unlock(mod_mutex);
	
	if(mod){
		ROOTKIT_DEBUG("yaay! found something %s \n",mod->name);
	}
	
	count = getcount_kernfs();
	ROOTKIT_DEBUG("count in kernfs  = %d \n",count);
	count = getcount_list();
	ROOTKIT_DEBUG("count in lsmod = %d\n",count);
	count = getcount_kobj();
	ROOTKIT_DEBUG("count of kobj = %d\n",count);
	return count;
}
