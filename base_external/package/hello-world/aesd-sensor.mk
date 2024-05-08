
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

endef

define HELLO_WORLD_INSTALL_TARGET_CMDS

endef

$(eval $(kernel-module))
$(eval $(generic-package))
