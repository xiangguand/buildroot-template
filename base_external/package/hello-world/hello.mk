
##############################################################
#
# AESD-FINAL
#
# Author: Xiang-Guan
#
##############################################################


HELLO_WORLD_VERSION = 1.0
HELLO_WORLD_SITE = $(BR2_EXTERNAL_BRTEMPLATE_PATH)/package/hello-world
HELLO_WORLD_SITE_METHOD = local

define HELLO_WORLD_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(HELLO_WORLD_SITE)/app all
endef

define HELLO_WORLD_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 $(@D)/example_load $(TARGET_DIR)/etc/init.d/S99aesddevicedriver
	$(INSTALL) -m 0755 $(@D)/example_unload $(TARGET_DIR)/usr/bin
	$(INSTALL) -m 0755 $(@D)/app/hello_linux $(TARGET_DIR)/usr/bin
endef

$(eval $(kernel-module))
$(eval $(generic-package))
