# sysfs-gpio
openWRT package: a small GPIO sysfs interface framework


	root:~# modprobe  sysfs-gpio
	sysfs-gpio driver inserted

	root:~# ls -l /sys/wlrdev/
	-r--r-----    1 root     root          4096 Jun 20 15:40 GPI_GPIO1
	-r--r-----    1 root     root          4096 Jun 20 15:40 GPI_GPIO2
	-r--r-----    1 root     root          4096 Jun 20 15:40 GPI_RST_PCB
	-rw-rw----    1 root     root          4096 Jun 20 15:40 GPO_MCU_BOOT0
	-rw-rw----    1 root     root          4096 Jun 20 15:40 GPO_MCU_BOOT1
	-rw-rw----    1 root     root          4096 Jun 20 15:40 GPO_MCU_NRST
	-rw-rw----    1 root     root          4096 Jun 20 15:40 GPO_PWR_LED_EN

	root:~# cat /sys/wlrdev/GPO_PWR_LED_EN 
	sysfs_gpio_show: GPO_PWR_LED_EN

	root:~# echo 1 > /sys/wlrdev/GPO_PWR_LED_EN 
	sysfs_gpio_store: GPO_PWR_LED_EN
	value=[1]

	root:~# cat /sys/wlrdev/GPO_PWR_LED_EN 
	sysfs_gpio_show: GPO_PWR_LED_EN

	root:~# echo 23 > /sys/wlrdev/GPO_MCU_BOOT0 
	sysfs_gpio_store: GPO_MCU_BOOT0
	value=[23]

	root:~# cat /sys/wlrdev/GPO_MCU_BOOT0 
	sysfs_gpio_show: GPO_MCU_BOOT0

	root:~# cat /sys/wlrdev/GPI_GPIO2 
	sysfs_gpio_show: GPI_GPIO2

	root:~# echo 1 > /sys/wlrdev/GPI_GPIO2 
	-ash: can't create /sys/wlrdev/GPI_GPIO2: Permission denied

	root:~# rmmod sysfs-gpio
	sysfs-gpio driver removed

	root:~# ls -l /sys/wlrdev
	ls: /sys/wlrdev: No such file or directory
	root:~#
