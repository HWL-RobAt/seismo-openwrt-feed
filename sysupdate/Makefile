# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=sysupdate
PKG_VERSION:=0.2
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/sysupdate
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=script to install sysupdate-package on Seismo-OpenWRT Nodes 
  MAINTAINER:=Kai Warncke <warncke@informatik.hu-berlin.de>
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

define Package/sysupdate/install
	$(INSTALL_BIN) ./files/sysupdate $(TOPDIR)/sysupdate
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) ./files/sysupdate $(1)/sbin/sysupdate
endef

$(eval $(call BuildPackage,sysupdate))

