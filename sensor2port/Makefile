# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=sensor2port
PKG_VERSION:=0.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/sensor2port
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=init script to forward a serial dev to a tcp port
  DEPENDS:=+socat +kmod-usb-serial +kmod-usb-serial-ftdi 
  MAINTAINER:=Kai Warncke <warncke@informatik.hu-berlin.de>
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

define Package/sensor2port/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/init.d	
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) ./files/sensor2port.init $(1)/etc/init.d/sensor2port
	$(INSTALL_BIN) ./files/sensor2port $(1)/sbin/sensor2port
endef

$(eval $(call BuildPackage,sensor2port))

