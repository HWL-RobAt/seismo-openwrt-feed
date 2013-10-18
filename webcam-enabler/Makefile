# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=webcam-enabler
PKG_VERSION:=r$(git rev-parse HEAD)
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/webcam-enabler
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=Enables webcam support on sosewin nodes
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
  DEPENDS:=+mjpg_streamer +hotplug2 -kmod-usb2
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

define Package/webcam-enabler/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/webcam-enabler.init $(1)/etc/init.d/webcam-enabler
endef

$(eval $(call BuildPackage,webcam-enabler))
