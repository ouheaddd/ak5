#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Kramar Mykyta");
MODULE_DESCRIPTION("hello1 module for lab4");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(lst_head);

void print_hello(unsigned int hello_counter)
{

	int i;

	for (i = 0; i < hello_counter; i++) {
		struct lst_obj *lst_elem = kmalloc(sizeof(*lst_elem), GFP_KERNEL);

		if (i == 3)
			lst_elem = 0;		
		
		lst_elem->timestamp_start = ktime_get();
		pr_info("Hello, world!\n");
		lst_elem->timestamp_end = ktime_get();
		list_add(&lst_elem->list, &lst_head);
	}
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct lst_obj *lst_elem, *temp;

	list_for_each_entry_safe(lst_elem, temp, &lst_head, list) {
		pr_info("Time start: %lld\n", lst_elem->timestamp_start);
		pr_info("Time spent: %lld\n", ktime_to_ns(ktime_sub(lst_elem->timestamp_end, lst_elem->timestamp_start)));
		list_del(&lst_elem->list);
		kfree(lst_elem);
	}
}


module_exit(hello1_exit);

