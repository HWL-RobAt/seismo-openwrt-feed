#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=boost
PKG_VERSION:=1_36_0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@SF/$(PKG_NAME)
PKG_MD5SUM:=328bfec66c312150e4c2a78dcecb504b

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)_$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/boost
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Boost library for C++
  URL:=http://www.boost.org
  DEPENDS:=+uclibcxx
endef

define Package/botan/description
       The Boost C++ Library.
       The Boost threading library is included.
endef

CONFIGURE_ARGS= --with-libraries=thread,system,regex,date_time,serialization --without-icu

define Build/Compile
	cd	$(PKG_BUILD_DIR)/tools/jam/src && ./build.sh
	$(CP)	$(PKG_BUILD_DIR)/tools/jam/src/bin.linuxx86_64/* $(STAGING_DIR)/bin/

# Create a wrt compiler configuration
	echo	"using gcc : wrt : $(TOOLCHAIN_DIR)/usr/bin/i486-openwrt-linux-c++ ;" > ~/user-config.jam

# Create the thread library
	cd	$(PKG_BUILD_DIR) && $(STAGING_DIR)/bin/bjam --v2 gcc-wrt threading=multi link=shared,static --layout=system --with-system --with-thread --with-date_time --with-regex --with-serialization release debug stage
endef

define Build/InstallDev
	mkdir -p $(STAGING_DIR)/usr/include
	mkdir -p $(STAGING_DIR)/usr/include/boost
	$(CP) $(PKG_BUILD_DIR)/boost/* $(STAGING_DIR)/usr/include/boost
	#copy the static libraries for static linking
	$(CP) $(PKG_BUILD_DIR)/stage/lib/* $(STAGING_DIR)/usr/lib
endef

define Build/UninstallDev
	$(RM) -f $(STAGING_DIR)/usr/include/boost
	$(RM) -f $(STAGING_DIR)/usr/lib/libboost-*
endef

define Package/boost/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/stage/lib/*.so $(1)/usr/lib
endef

$(eval $(call BuildPackage,boost))
