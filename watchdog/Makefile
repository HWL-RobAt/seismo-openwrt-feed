#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id: Makefile 10812 2008-04-13 12:06:07Z olli $
#
#http://downloads.sourceforge.net/watchdog/watchdog-5.4.tar.gz
#
# Note that  busyboy watchdog must be disabled
#

include $(TOPDIR)/rules.mk

PKG_NAME:=watchdog
PKG_VERSION:=5.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/$(PKG_NAME)
PKG_MD5SUM:=66480128b9dabcced2e4c8db3e60fa50

include $(INCLUDE_DIR)/package.mk

define Package/watchdog
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Standard linux watchdog daemon (version 5.4)
  URL:=http://sourceforge.net/projects/watchdog/
endef

define Package/watchdog/description
	Standard linux watchdog daemon (version 5.4) from sourceforge
endef

define Build/Configure
    $(call Build/Configure/Default, --with-linux-headers="$(LINUX_DIR)")
endef

define Package/watchdog/install	
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/$(PKG_NAME) $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_CONF) ./files/watchdog.conf $(1)/etc/watchdog.conf
	$(INSTALL_BIN) ./files/watchdog.initd $(1)/etc/init.d/watchdog
endef

$(eval $(call BuildPackage,watchdog))
