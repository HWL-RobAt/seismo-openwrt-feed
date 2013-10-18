# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=gateway-enabler
PKG_VERSION:=r$(git rev-parse HEAD)
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/gateway-enabler
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=Enables olsr gateway rule for node with internet access und upnp deamon 
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
  DEPENDS:=+miniupnpd +olsrd
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

define Package/webcam-enabler/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/gateway-enabler.init $(1)/etc/init.d/gateway-enabler
endef

$(eval $(call BuildPackage,webcam-enabler))
