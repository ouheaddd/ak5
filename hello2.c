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
MODULE_DESCRIPTION("hello module for lab4");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int hello_counter = 1;
module_param(hello_counter, uint, 0644);
MODULE_PARM_DESC(hello_counter, "counter of 'Hello world' printing");

static int __init hello2_init(void)
{
	BUG_ON(hello_counter > 10);
	
	if (hello_counter == 0 || (hello_counter >= 5 && hello_counter <= 10))
		pr_warn("Warning! hello_counter == 0 or 5 <= hello_counter <= 10\n");

	print_hello(hello_counter);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Uninstalled\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

