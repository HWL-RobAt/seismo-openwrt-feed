# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_BRANCH:=trunk
PKG_SOURCE_URL:=https://samtrac.informatik.hu-berlin.de/svn/data-provider/$(PKG_BRANCH)
PKG_REV:=$(shell LC_ALL=C svn info ${PKG_SOURCE_URL} | sed -ne's/^Last Changed Rev: //p')

PKG_NAME:=data-provider-v1
PKG_VERSION:=0.1+svn$(PKG_REV)
PKG_RELEASE:=1

PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.gz
PKG_SOURCE_PROTO:=svn
PKG_SOURCE_VERSION:=$(PKG_REV)

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_INSTALL_DIR:=$(PKG_BUILD_DIR)/ipkg-install

include $(INCLUDE_DIR)/package.mk

define Package/data-provider-v1
  SECTION:=seismo
  CATEGORY:=Seismo
  DEPENDS:=+kmod-usb-serial-ftdi 
  TITLE:=sensorboard data reading software (first version) and SEEDLink plugin
  URL:=http://www.edim-whatever.org
  MAINTAINER:=Jens Nachtigall <nachtiga@informatik.hu-berlin.de>
endef

define Package/data-provider-v1/description
	Read data and GPS time from sensorboard and feed the SeedLink server 
	and other enabled plugins.
endef

define Package/data-provider-v1/install
	$(INSTALL_DIR) $(1)/usr/sbin
	#$(INSTALL_DIR) $(1)/usr/lib/data-provider
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/etc/data-provider/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/data-provider $(1)/usr/sbin/
	$(CP) $(PKG_BUILD_DIR)/ChiChi_215_usec.txt $(1)/etc/data-provider/
	$(CP) $(PKG_BUILD_DIR)/plugins/demo_plugin/demo_plugin.so $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/plugins/seedlink/seedlink.so $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/plugins/set_time/set_time.so $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/plugins/ew_plugin/ew_plugin.so $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/plugins/clocksync/clocksync.so $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/plugins/netcoords/netcoords.so $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/plugins/rsdp_plugin/rsdp_plugin.so $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/plugins/click_plugin/click_plugin.so $(1)/usr/lib/
endef

$(eval $(call BuildPackage,data-provider-v1))

