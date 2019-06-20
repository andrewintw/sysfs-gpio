#ifndef __SYSFS_GPIO_H__
#define __SYSFS_GPIO_H__

static int  __init sysfs_gpio_init(void);
static void __exit sysfs_gpio_exit(void);
static ssize_t sysfs_gpio_show (struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_gpio_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);

#define SYSFS_GPIO_DIRNAME	"wlrdev"

#endif	// __SYSFS_GPIO_H__
