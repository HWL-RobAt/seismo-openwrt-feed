# 
# Copyright (C) 2007 BerlinRoofNet Lab
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# For additional licensing options, consult http://www.BerlinRoofNet.de
# or contact brn@informatik.hu-berlin.de.
#
# $Id: Makefile 366 2007-08-30 13:09:41Z jeschke $

include $(TOPDIR)/rules.mk

PKG_NAME:=berlinroofnet
PKG_SOURCE_URL:=https://sarforge.informatik.hu-berlin.de/svn/berlinroofnet/BerlinRoofNet/trunk/click/@375
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

#BRN_PKG_VERSION:=r$(shell svn info $(PKG_SOURCE_URL) 2>&- | awk 'NR==5{ print $$2 }')
BRN_PKG_VERSION:=r375

PKG_VERSION:=$(BRN_PKG_VERSION)
PKG_DL_REV:=$(DL_DIR)/$(PKG_NAME).$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk


define Package/berlinroofnet
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Multihop wireless mesh network technology
  URL:=http://berlinroofnet.de/
  DEPENDS:=+kmod-tun +kmod-madwifi +libstdcpp
endef

define Package/berlinrootnet/description
	Framework for building multihop wireless mesh networks
endef

$(PKG_DL_REV):
	touch $@

$(STAMP_PREPARED): $(PKG_DL_REV)

define Build/Prepare
	svn co --non-interactive $(PKG_SOURCE_URL) $(PKG_BUILD_DIR)/
	@if [ -d $(PATCH_DIR) -a "$$$$(ls $(PATCH_DIR) | wc -l)" -gt 0 ]; then \
		$(PATCH) $(PKG_BUILD_DIR) $(PATCH_DIR); \
	fi
endef


define Build/Configure
	(cd $(PKG_BUILD_DIR)/click-core; \
		test -x configure || autoconf; \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		CXXFLAGS="$(TARGET_CFLAGS)" \
		./configure \
			--target=$(GNU_TARGET_NAME) \
			--host=$(GNU_TARGET_NAME) \
			--build=$(GNU_HOST_NAME) \
			--enable-tools=host \
			--disable-linuxmodule \
			--enable-gateway \
			--enable-analysis \
			--enable-etherswitch \
			--enable-brn \
	);
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/click-core/userlevel \
		$(TARGET_CONFIGURE_OPTS) \
		LD="$(TARGET_CC)"
	$(MAKE) -C $(PKG_BUILD_DIR)/click-core/tools/click-align \
		$(TARGET_CONFIGURE_OPTS) \
		LD="$(TARGET_CC)"
endef
	
define Package/berlinroofnet/install
	$(INSTALL_DIR)  $(1)/usr/bin
	$(INSTALL_BIN)  $(PKG_BUILD_DIR)/click-core/userlevel/click $(1)/usr/bin/click
	$(INSTALL_BIN)  $(PKG_BUILD_DIR)/click-core/tools/click-align/click-align $(1)/usr/bin/click-align
	$(INSTALL_DIR)  $(1)/lib/berlinroofnet
	$(INSTALL_BIN)  $(PKG_BUILD_DIR)/init-meshnode/BrnNodeFunctions.sh $(1)/lib/berlinroofnet/
	$(INSTALL_DIR)  $(1)/lib/berlinroofnet/BrnNodeFunctions
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/init-meshnode/BrnNodeFunctions/* $(1)/lib/berlinroofnet/BrnNodeFunctions/
	$(INSTALL_DIR)  $(1)/etc/init.d
	$(INSTALL_BIN)  ./files/berlinroofnet.init $(1)/etc/init.d/berlinroofnet
	$(INSTALL_DIR)  $(1)/etc/config
	$(INSTALL_CONF) ./files/berlinroofnet.config $(1)/etc/config/berlinroofnet
	$(INSTALL_DIR)  $(1)/etc/berlinroofnet
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/configurations/main/* $(1)/etc/berlinroofnet/
	$(INSTALL_BIN)  $(PKG_BUILD_DIR)/configurations/main/click-include $(1)/etc/berlinroofnet/
endef


$(eval $(call BuildPackage,berlinroofnet))
