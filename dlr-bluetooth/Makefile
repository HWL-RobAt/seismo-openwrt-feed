#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk

PKG_NAME:=dlr-bluetooth
PKG_VERSION:=0.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/dlr-bluetooth
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=DLR Bluetooth
  MAINTAINER:=eveslage@informatik.hu-berlin.de
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/dlr-bluetooth/install
	$(INSTALL_DIR) $(1)/usr/bin/dlr-bluetooth
	$(CP) ./files/jblub.jar $(1)/usr/bin/dlr-bluetooth/jblub.jar
	$(CP) ./files/upload.jar $(1)/usr/bin/dlr-bluetooth/upload.jar
	$(CP) ./files/config.xml $(1)/usr/bin/dlr-bluetooth/config.xml
	$(INSTALL_BIN) ./files/BT_OneDongle_HUB.sh $(1)/usr/bin/dlr-bluetooth/BT_OneDongle_HUB.sh
	
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/dlr-bluetooth.init $(1)/etc/init.d/dlr-bluetooth
endef

$(eval $(call BuildPackage,dlr-bluetooth))
