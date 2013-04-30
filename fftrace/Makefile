# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk
PKG_NAME:=fftrace
PKG_VERSION:=svn2008-04-09
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www2.informatik.hu-berlin.de/~nachtiga/seismo/sources/
PKG_MD5SUM:=25b48de293a26309bf198d455b172d34

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/fftrace
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+libncurses 
  TITLE:=olsr-route-link-quality monitor similar to traceroute
  URL:=https://dev.open-mesh.net/fftrace/browser/trunk/
endef


define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
	$(TARGET_CONFIGURE_OPTS) \
	fftrace
endef

define Package/fftrace/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_BUILD_DIR)/fftrace $(1)/usr/sbin/
endef



$(eval $(call BuildPackage,fftrace))
