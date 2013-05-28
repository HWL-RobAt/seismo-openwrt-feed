#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=seismic-analysis
PKG_RELEASE:=1.0
PKG_VERSION:=1.0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/seismic-analysis
  SECTION:=seimo
  CATEGORY:=Seismo
  TITLE:=seismic-analysis
  DEPENDS:=+data-provider +libstdcpp
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
endef

define Package/seismic-analysis/description
  standalone seismic analysis of sensordata
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -R -u ./src/* $(PKG_BUILD_DIR)/
endef


define Package/seismic-analysis/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/seismic-analysis $(1)/usr/bin/
endef

$(eval $(call BuildPackage,seismic-analysis))
