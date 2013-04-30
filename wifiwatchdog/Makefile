#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk

PKG_NAME:=wifiwatchdog
PKG_VERSION:=0.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/wifiwatchdog
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=WifiWatchDog
  MAINTAINER:=Robert
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/wifiwatchdog/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) ./files/wifiwatchdog.sh $(1)/usr/sbin/wifiwatchdog.sh
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_CONF) ./files/wifiwatchdog.conf $(1)/etc/wifiwatchdog.conf
	$(INSTALL_BIN) ./files/wifiwatchdog.initd $(1)/etc/init.d/wifiwatchdog
endef

$(eval $(call BuildPackage,wifiwatchdog))
