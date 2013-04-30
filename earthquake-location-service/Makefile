#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=earthquake-location-service
PKG_RELEASE:=1.0
#REMOTE_PATH:=https://samtrac.informatik.hu-berlin.de/svn/sosewin/AlarmingProtocol/SingleNode
#PKG_REV:=$(shell LC_ALL=C svn info ${REMOTE_PATH} | sed -ne's/^Last Changed Rev: //p')
PKG_VERSION:=$(PKG_RELEASE)

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

DIR_AP=src

include $(INCLUDE_DIR)/package.mk

define Package/earthquake-location-service
  SECTION:=seimo
  CATEGORY:=Seismo
  TITLE:=Earthquake-Location-Service
  DEPENDS:=+boost-serialization +boost-thread +boost-system +boost-regex
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
endef

define Package/earthquake-location-service/description
  The earthquake location service for the sosewin nodes.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -R -u ./src/* $(PKG_BUILD_DIR)/
#	tar xfz ./src/alarming-protocol.tar.gz -C $(PKG_BUILD_DIR)/
endef

# -I $(BUILD_DIR)/../toolchain-i386_gcc4.1.2/uClibc-0.9.29/libpthread/linuxthreads/sysdeps/pthread/

define Package/earthquake-location-service/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/boost_pack/els $(1)/usr/bin/
endef

$(eval $(call BuildPackage,earthquake-location-service))
