#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>

#define DRV_NAME	"keyint"

DECLARE_WAIT_QUEUE_HEAD(wq);
static int key_input_flag;

static irqreturn_t keyinterrupt_func(int irq, void *dev_id, struct pt_regs *regs) {

	printk("\nkeypad was pressed \n");
	key_input_flag = 1;
	wake_up_interruptible(&wq);
	return IRQ_HANDLED;
}

ssize_t sleepy_read(struct file *filp, char __user *buf, size_t count, loff_t *pos) {

	printk(KERN_DEBUG "process %i (%s) going to sleep\n",
					current->pid, current -> comm);

	if( key_input_flag == 0) {

		int ret = wait_event_interruptible(wq, flag != 0);

		if(ret) return -ERESTARTSYS;
	}


	key_input_flag = 0;
	
	printk(KERN_DEBUG "awoken %i (%s)\n", current -> pid, current -> comm);

	return 0;
}

static int __init keyint_init(void) {

	int ret;

	s3c_gpio_cfgpin(S3C2410_GPF(0), S3C_GPIO_SFN(2));

	if(request_irq(IRQ_EINT0, (void *)keyinterrupt_func, 
				IRQF_DISABLED|IRQF_TRIGGER_FALLING, DRV_NAME, NULL)) {
		
	//	printk("%d\n", request_irq(IRQ_EINT0, (void *)keyinterrupt_func, IRQF_DISABLED|IRQF_TRIGGER_FALLING, DRV_NAME, NULL));
		printk("failed to request external interrupt.\n");
		ret = -ENOENT;
		return ret;
	}

	printk(KERN_INFO "%s successfully loaded\n", DRV_NAME);

	return 0;
}

static void __exit keyint_exit(void) {

	free_irq(IRQ_EINT0, NULL);

	printk(KERN_INFO "%s successfully removed\n", DRV_NAME);
}

module_init(keyint_init);
module_exit(keyint_exit);

MODULE_LICENSE("GPL");

