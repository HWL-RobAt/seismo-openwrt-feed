# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_BRANCH:=trunk
PKG_SOURCE_URL:=https://samtrac.informatik.hu-berlin.de/svn/m-noti/$(PKG_BRANCH)
PKG_REV:=$(shell LC_ALL=C svn info ${PKG_SOURCE_URL} | sed -ne's/^Last Changed Rev: //p')

PKG_NAME:=m-noti
PKG_VERSION:=0.1+svn$(PKG_REV)
PKG_RELEASE:=1

PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.gz
PKG_SOURCE_PROTO:=svn
PKG_SOURCE_VERSION:=$(PKG_REV)

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_INSTALL_DIR:=$(PKG_BUILD_DIR)/ipkg-install


include $(INCLUDE_DIR)/package.mk

define Package/m-noti
  SECTION:=seismo
  CATEGORY:=Seismo
  DEPENDS:=
  TITLE:=Notification middleware service
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
endef

MAKE_FLAGS+=\
	CPPFLAGS+="-std=c++0x -I./"

define Package/m-noti/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/m-noti $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/m-noti.init $(1)/etc/init.d/m-noti
endef

$(eval $(call BuildPackage,m-noti))
