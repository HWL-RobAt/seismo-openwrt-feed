# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

#PKG_BRANCH:=trunk
PKG_SOURCE_URL:=http://samtrac.informatik.hu-berlin.de/node-info-service.git/
PKG_REV:=$(shell LC_ALL=C git ls-remote $(PKG_SOURCE_URL) | grep HEAD | cut -f1)

PKG_NAME:=node-info-service
PKG_VERSION:=$(PKG_REV)
PKG_RELEASE:=1

PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.gz
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=HEAD

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_INSTALL_DIR:=$(PKG_BUILD_DIR)/ipkg-install

include $(INCLUDE_DIR)/package.mk

define Package/node-info-service
  SECTION:=seismo
  CATEGORY:=Seismo
  DEPENDS:=+boost-serialization +boost-thread +libthrift
  TITLE:= node-info-service
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
endef

define Build/Configure
	$(CP) $(PKG_BUILD_DIR)/Makefile.openwrt $(PKG_BUILD_DIR)/Makefile
endef

MAKE_VARS+= \
 LDFLAGS+="-L $(STAGING_DIR)/usr/lib -lcrypto -lssl"\
 CXXFLAGS+="-I $(STAGING_DIR)/usr/include/thrift/ -I $(STAGING_DIR)/usr/include"

define Package/node-info-service/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/NodeInfoService/node-info-service $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/node-info-service.init $(1)/etc/init.d/node-info-service
endef

$(eval $(call BuildPackage,node-info-service))
