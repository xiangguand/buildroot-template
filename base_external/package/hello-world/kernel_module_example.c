#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <asm/io.h>
#include <asm/page.h>

#include "kernel_module_example.h"

int kernel_module_example_major = 0;
int kernel_module_example_minor = 0;

static struct kernel_module_example_dev debug_device = { .is_open_ = false };

MODULE_AUTHOR("Xiang Guan Deng");
MODULE_LICENSE("Dual BSD/GPL");

static int kernel_module_example_open(struct inode *inode, struct file *file)
{
	printk("===== Open =====\n");
	if (debug_device.is_open_) {
		// device is already open
		return -EBUSY;
	}
	debug_device.is_open_ = true;

	return 0;
}

static ssize_t kernel_module_example_read(struct file *filp, char __user *buf,
				 size_t count, loff_t *f_pos)
{
	printk("===== Read =====\n");
	if (!debug_device.is_open_) {
		return -1;
	}
	printk("read %zu bytes with offset %lld", count, *f_pos);

	return 0;
}

static ssize_t kernel_module_example_write(struct file *filp, const char __user *buf,
				  size_t count, loff_t *f_pos)
{
	printk("===== Write =====\n");
	if (!debug_device.is_open_) {
		return -1;
	}
	printk("write %zu bytes with offset %lld", count, *f_pos);

	return count;
}

static int kernel_module_example_release(struct inode *inode, struct file *file)
{
	printk("release kernel_module\n");
	debug_device.is_open_ = false;
	return 0;
}

struct file_operations kernel_module_example_fops = {
	.owner = THIS_MODULE,
	.open = kernel_module_example_open,
	.read = kernel_module_example_read,
	.write = kernel_module_example_write,
	.release = kernel_module_example_release,
};

static int setup_kernel_module_example_cdev(struct kernel_module_example_dev *dev)
{
	int err, devno = MKDEV(kernel_module_example_major, kernel_module_example_minor);

	cdev_init(&dev->cdev, &kernel_module_example_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &kernel_module_example_fops;

	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		printk(KERN_ERR "Error %d adding kernel_module_example cdev", err);
		return -ENOMEM;
	}

	return 0;
}

/* Device driver init function, create cdev */
static int kernel_module_example_init(void)
{
	dev_t dev = 0;
	int result;
	printk("kernel_module_example_init\n");
	result = alloc_chrdev_region(&dev, kernel_module_example_minor, 1,
				     "kernel_module_example");
	kernel_module_example_major = MAJOR(dev);
	printk("kernel_module_example_major = %d\n", kernel_module_example_major);
	if (result < 0) {
		printk(KERN_WARNING "Can't get major %d\n", kernel_module_example_major);
	}
	memset(&debug_device, 0, sizeof(struct kernel_module_example_dev));

	result = setup_kernel_module_example_cdev(&debug_device);

	if (result) {
		printk(KERN_WARNING "Can't setup kernel_module_example cdev\n");
		unregister_chrdev_region(dev, 1);
	}
	printk("Register dubug_access module successfully");

	return result;
}

static void kernel_module_example_exit(void)
{
	printk("kernel_module_example_exit\n");
}

module_init(kernel_module_example_init);
module_exit(kernel_module_example_exit);
