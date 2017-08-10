#include <linux/module.h>
#include <linux/init.h>
#include <linux/major.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/serial_core.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <plat/regs-serial.h>
#include <asm/serial.h>
#include <plat/map-base.h>
#include <asm/io.h>
#define SSER_MAJOR 126

MODULE_LICENSE("GPL");

static int sser_major = 0, sser_minor = 0;
static int result;
static dev_t my_dev;
static struct cdev my_cdev;
/* file_operations의 레코드를 할당한다. */
static struct file_operations sk_fops;

static int sser_register_cdev(void);

/* Define Prototype of functions */
static int sser_open(struct inode *inode, struct file *filp);
static int sser_release(struct inode *inode, struct file *filp);
ssize_t sser_write(struct file *filp, const char *buf, size_t count, loff_t *l);
ssize_t sser_read(struct file *filp, char *buf, size_t count, loff_t *l);

struct uart_port *port;

#define portaddr(port, reg) ((port) -> membase + (reg))
#define rd_regb(port, reg) (__raw_readb(portaddr(port, reg)))
#define rd_regl(port, reg) (__raw_readl(portaddr(port, reg)))

#define wr_regb(port, reg, val) \
	do {__raw_writeb(val, portaddr(port, reg)); }while(0)

#define wr_regl(port, reg, vla) \
	do{__raw_writel(val, portaddr(port, reg)); } while(0)


static int sser_open(struct inode *inode, struct file *filp) {

	port = kmalloc(sizeof(struct uart_port), GFP_ATOMIC);
	port -> membase = (void __iomem *)S3C24XX_VA_UART0;
	
	return 0;
}

static int sser_release(struct inode *inode, struct file *filp) {

	printk("Device has been closed...\n");

	return 0;
}

ssize_t sser_write(struct file *filp, const char *buf, size_t count, loff_t *l) {

	char *b2;
	int i;
	b2 = kmalloc(count, GFP_ATOMIC);
	copy_from_user(b2, buf, count);

	for(i = 0; i < count; i++) {

		while( !(rd_regl(port, S3C2410_UTRSTAT) & S3C2410_UTRSTAT_TXFE));
		wr_regb(port, S3C2410_UTXH, b2[i]);
	}

	kfree(b2);

	return count;
}

ssize_t sser_read(struct file *filp, char *buf, size_t count, loff_t *l) {
	
	char *b2;
	int i;
	b2 = kmalloc(count, GFP_ATOMIC);

	for(i = 0; i < count; i++) {

		while( !(rd_regl(port, S3C2410_UTRSTAT) & S3C2410_UTRSTAT_RXDR));
		b2[i] = rd_regb(port, S3C2410_URXH);
	}

	copy_to_user(buf, b2, count);
	kfree(b2);
	return count;
}

struct file_operations sser_fops = {

	.open = sser_open,
	.release = sser_release,
	.write = sser_write,
	.read = sser_read,
};

int simple_serial_init(void) {
	
	dev_t dev;
	sser_major = SSER_MAJOR;
	dev = MKDEV(sser_major, 0);
	char devicename[100];

	printk("starting simple_serial_init()...\n");
	strcpy(devicename, "Simple serial device driver");
	register_chrdev_region(dev, 128, devicename);
	cdev_init(&my_cdev, &sser_fops);
	cdev_add(&my_cdev, dev, 128);
	
	return 0;
}

static void simple_serial_exit(void) {

	printk("The module is down...\n");

	cdev_del(&my_cdev);
	unregister_chrdev_region(my_dev, 1);

}

static int sser_register_cdev(void) {

	int error;

	if(sser_major) {

		my_dev = MKDEV(sser_major, sser_minor);
		error = register_chrdev_region(my_dev, 1, "sser");
	
	} else {

		error = alloc_chrdev_region(&my_dev, sser_minor, 1, "sser");
		sser_major = MAJOR(my_dev);
	}

	if(error < 0) {

		printk(KERN_WARNING "sser : can't get major %d\n", sser_major);
		return result;
	}

	printk("major number = %d\n", sser_major);

	/* register chrdev */
	cdev_init(&my_cdev, &sser_fops);
	my_cdev.owner = THIS_MODULE;
	my_cdev.ops = &sser_fops;
	error = cdev_add(&my_cdev, my_dev, 1);

	if(error)
		printk(KERN_NOTICE "sk Register Error %d\n", error);

	return 0;
}


module_init(simple_serial_init);
module_exit(simple_serial_exit);


