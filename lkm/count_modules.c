#include<linux/module.h>
#include <linux/rbtree.h>

#include "include.h"

int count_recursive(struct rb_node *node)
{
        if(node == NULL) return 0;

        if(node->rb_left == NULL && node->rb_right == NULL)
        {
                return 0;
        }
        else
        {
                return count_recursive(node->rb_left) + count_recursive(node->rb_right) +1;
        }

}


/* To count the number of modules */
int count_modules(void)
{
	 // struct module *mod = THIS_MODULE;
	//  struct sysfs_dirent *entry, *parent;
	 int count = 0;

	 struct kernfs_node *kn = THIS_MODULE->mkobj.kobj.sd;

	 struct rb_node *node = kn->parent->dir.children.rb_node;

	 count = count_recursive(node);

	 printk ( KERN_INFO "_detector_mod;modules %d;\n",count);

	 return count;
}
