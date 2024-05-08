#!/bin/sh
# Shared definitions for buildroot scripts

# The defconfig from the buildroot directory we use for qemu builds
# QEMU_DEFCONFIG=configs/raspberrypi3_64_defconfig
# The place we store customizations to the qemu configuration

DEFCONFIG_FILE=base_external/configs/qemu_defconfig

if [ $# -eq 1 ]; then
  echo "defconfig:$1"
  DEFCONFIG_FILE=$1
fi

MODIFIED_DEFCONFIG=${DEFCONFIG_FILE}
# The defconfig from the buildroot directory we use for the project
AESD_DEFAULT_DEFCONFIG=${MODIFIED_DEFCONFIG}
AESD_MODIFIED_DEFCONFIG=${MODIFIED_DEFCONFIG}
AESD_MODIFIED_DEFCONFIG_REL_BUILDROOT=../${AESD_MODIFIED_DEFCONFIG}
