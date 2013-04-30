#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=thrift
PKG_VERSION:=0.7.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#Automatic downloading of the current Thrift HEAD does not work with the URL below
PKG_SOURCE_URL:=http://www.apache.org/dist/$(PKG_NAME)/$(PKG_VERSION)/
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/libthrift
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Thrift Library
  DEPENDS:=+boost
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
endef

CONFIGURE_ARGS+= \
  LIBS="-lssl -lcrypto" \
  CXXFLAGS="-O0 -g" --with-csharp=no --with-java=no --with-erlang=no --with-python=no --with-perl=no \
  --with-php=no --with-php_extension=no --with-ruby=no --with-haskell=no  --enable-gen-cpp=yes \
  --enable-gen-java=no --enable-gen-as3=no --enable-gen-csharp=no --enable-gen-py=no --enable-gen-rb=no \
  --enable-gen-perl=no --enable-gen-php=no --enable-gen-erl=no --enable-gen-cocoa=no --enable-gen-st=no \
  --enable-gen-ocaml=no  --enable-gen-hs=no --enable-gen-xsd=no --enable-gen-html=no  --enable-gen-js=no \
  --enable-gen-javame=no --with-boost=$(STAGING_DIR)/i386/usr/include --prefix=$(2)

MAKE_VARS+= \
 LDFLAGS+=""\
 CXXFLAGS+=""

define Build/Configure
	$(RM) -rf $(PKG_BUILD_DIR)/lib/cpp/test	
	mkdir $(PKG_BUILD_DIR)/lib/cpp/test	
	chmod +x $(PKG_BUILD_DIR)/configure
	$(call Build/Configure/Default)	
	$(CP) ./files/Makefile $(PKG_BUILD_DIR)/lib/cpp/test
	$(CP) ./files/Makefile $(PKG_BUILD_DIR)/test
endef

define Package/libthrift/install	
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib/cpp/.libs/libthrift.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/lib/cpp/.libs/libthrift.a $(1)/usr/lib/
endef

define Build/InstallDev
	mkdir -p $(1)/usr/include
	mkdir -p $(1)/usr/include/thrift
	mkdir -p $(1)/usr/include/thrift/concurrency
	mkdir -p $(1)/usr/include/thrift/processor
	mkdir -p $(1)/usr/include/thrift/protocol
	mkdir -p $(1)/usr/include/thrift/server
	mkdir -p $(1)/usr/include/thrift/transport
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/lib/cpp/src/concurrency/*.h $(1)/usr/include/thrift/concurrency
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/lib/cpp/src/processor/*.h $(1)/usr/include/thrift/processor
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/lib/cpp/src/protocol/*.h $(1)/usr/include/thrift/protocol
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/lib/cpp/src/server/*.h $(1)/usr/include/thrift/server
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/lib/cpp/src/transport/*.h $(1)/usr/include/thrift/transport
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/lib/cpp/src/*.h $(1)/usr/include/thrift
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/lib/cpp/src/protocol/*.tcc $(1)/usr/include/thrift/protocol
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/config.h $(1)/usr/include/thrift/config.h

	mkdir -p $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib/cpp/.libs/libthrift.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/lib/cpp/.libs/libthrift.a $(1)/usr/lib/
	$(call Build/InstallDev/Default)
endef

$(eval $(call BuildPackage,libthrift))
