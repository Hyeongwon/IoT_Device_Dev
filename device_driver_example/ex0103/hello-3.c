#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "Josh <p@dirac.org>"
#define DRIVER_DESC "A sample driver"

static int __init init_hello_3(void) {

	printk(KERN_INFO "Hello, world 3\n");
	return 0;
}

static void __exit cleanup_hello_3(void) {

	printk(KERN_INFO "Goodbye, world 3\n");
}

module_init(init_hello_3);
module_exit(cleanup_hello_3);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");

