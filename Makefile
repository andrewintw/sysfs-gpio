include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=sysfs-gpio
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/sysfs-gpio
  SECTION:=kernel
  CATEGORY:=Properties
  SUBMENU:=Drivers
  TITLE:=GPIO Sysfs Interface
  FILES:=$(PKG_BUILD_DIR)/sysfs-gpio.ko
  AUTOLOAD:=$(call AutoLoad,60,sysfs-gpio)
endef

define Build/Prepare
	$(call Build/Prepare/Default)
endef

EXTRA_CFLAGS += -I$(LINUX_DIR)/drivers/char -DHW_MODEL_WLR

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,sysfs-gpio))
