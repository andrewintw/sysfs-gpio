#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/slab.h>			//kmalloc()
#include <linux/uaccess.h>		//copy_to/from_user()
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/stat.h>
#include "sysfs-gpio.h"

volatile int value_from_user = 0;

struct kobject *kobj_ref;

EXPORT_SYMBOL_GPL(kobj_ref);

#if defined (HW_MODEL_WLR)
struct kobj_attribute gpo_mcu_boot1    = __ATTR(GPO_MCU_BOOT1,    (S_IWUSR|S_IWGRP|S_IRUSR|S_IRGRP), sysfs_gpio_show, sysfs_gpio_store);
struct kobj_attribute gpo_mcu_boot0    = __ATTR(GPO_MCU_BOOT0,    (S_IWUSR|S_IWGRP|S_IRUSR|S_IRGRP), sysfs_gpio_show, sysfs_gpio_store);
struct kobj_attribute gpo_pwr_led_en   = __ATTR(GPO_PWR_LED_EN,   (S_IWUSR|S_IWGRP|S_IRUSR|S_IRGRP), sysfs_gpio_show, sysfs_gpio_store);
struct kobj_attribute gpo_mcu_nrst     = __ATTR(GPO_MCU_NRST,     (S_IWUSR|S_IWGRP|S_IRUSR|S_IRGRP), sysfs_gpio_show, sysfs_gpio_store);
                                                                  
struct kobj_attribute gpi_rst_pcb      = __ATTR(GPI_RST_PCB,      (S_IRUSR|S_IRGRP), sysfs_gpio_show, NULL);
struct kobj_attribute gpi_gpio1        = __ATTR(GPI_GPIO1,        (S_IRUSR|S_IRGRP), sysfs_gpio_show, NULL);
struct kobj_attribute gpi_gpio2        = __ATTR(GPI_GPIO2,        (S_IRUSR|S_IRGRP), sysfs_gpio_show, NULL);
#else
#error Please specify the hardware model!
#endif

static struct attribute *kernel_attrs[] = {
#if defined (HW_MODEL_WLR)
	&gpo_mcu_boot1.attr,
	&gpo_mcu_boot0.attr,
	&gpo_pwr_led_en.attr,
	&gpo_mcu_nrst.attr,
	&gpi_rst_pcb.attr,
	&gpi_gpio1.attr,
	&gpi_gpio2.attr,
#else
#error Please specify the hardware model!
#endif
	NULL						/* need to NULL terminate the list of attributes */
};

static struct attribute_group kernel_attr_group = {
	.attrs = kernel_attrs,
};

static ssize_t sysfs_gpio_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	printk(KERN_INFO "%s: %s\n", __func__, attr->attr.name);
	return sprintf(buf, "%d", value_from_user);
}

static ssize_t sysfs_gpio_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	printk(KERN_INFO "%s: %s\n", __func__, attr->attr.name);
	sscanf(buf, "%d", &value_from_user);
	printk(KERN_INFO "value=[%d]\n", value_from_user);
	return count;
}

static int __init sysfs_gpio_init(void)
{
	int error;

	kobj_ref = kobject_create_and_add(SYSFS_GPIO_DIRNAME, NULL);	/* directory in /sys/SYSFS_GPIO_DIRNAME */
	if (!kobj_ref) {
		error = -ENOMEM;
		goto exit;
	}

	error = sysfs_create_group(kobj_ref, &kernel_attr_group);
	if (error) {
		goto kset_exit;
	}

	printk(KERN_INFO "sysfs-gpio driver inserted\n");
	return 0;

  kset_exit:
	kobject_put(kobj_ref);

  exit:
	return error;
}

void __exit sysfs_gpio_exit(void)
{
	kobject_put(kobj_ref);
	printk(KERN_INFO "sysfs-gpio driver removed\n");
}

module_init(sysfs_gpio_init);
module_exit(sysfs_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/andrewintw");
MODULE_DESCRIPTION("GPIO Sysfs Interface");
MODULE_VERSION("1.0");
