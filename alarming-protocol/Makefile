#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=alarming-protocol
PKG_RELEASE:=1.2
REMOTE_PATH:=http://samtrac.informatik.hu-berlin.de/sosewin.git/
PKG_REV:=$(shell LC_ALL=C git ls-remote $(REMOTE_PATH) | grep HEAD | cut -f1)
PKG_VERSION:=$(PKG_RELEASE)+git$(PKG_REV)

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

DIR_AP=src
DIR_ASN1_GEN=AP_Messages_Cpp
DIR_ASN1_RUNTIME=cpp_runlib
DIR_SA=StreamingAnalysis
DIR_MSDP=model-sensor-data-provider

include $(INCLUDE_DIR)/package.mk

define Package/alarming-protocol
  SECTION:=seimo
  CATEGORY:=Seismo
  TITLE:=Alarming-Protocol
  DEPENDS:=+boost-serialization +boost-thread +boost-system +boost-regex +boost-date_time
  MAINTAINER:=Ingmar Eveslage <eveslage@informatik.hu-berlin.de>
endef

define Package/alarming-protocol/description
  The earthquake early warning alarming protocol for the sosewin nodes.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(CPFLAGS) ./files/Makefile $(PKG_BUILD_DIR)
	tar xfz ./src/alarming-protocol.tar.gz -C $(PKG_BUILD_DIR)/
	tar xfz ./src/asn1-generated.tar.gz -C $(PKG_BUILD_DIR)/
	tar xfz ./src/asn1-runtime.tar.gz -C $(PKG_BUILD_DIR)/
	tar xfz ./src/streaming-analysis.tar.gz -C $(PKG_BUILD_DIR)/	
	tar xfz ./src/model-sensor-data-provider.tar.gz -C $(PKG_BUILD_DIR)/
endef

# -I $(BUILD_DIR)/../toolchain-i386_gcc4.1.2/uClibc-0.9.29/libpthread/linuxthreads/sysdeps/pthread/

MAKE_FLAGS+=\
	CXXFLAGS+="-DBOOST -I $(PKG_BUILD_DIR)/$(DIR_ASN1_GEN) -I $(PKG_BUILD_DIR)/$(DIR_ASN1_RUNTIME) -I $(PKG_BUILD_DIR)/$(DIR_SA)"\
	LDFLAGS+="-L $(PKG_BUILD_DIR)/$(DIR_ASN1_GEN) -L $(PKG_BUILD_DIR)/$(DIR_ASN1_RUNTIME) -L $(PKG_BUILD_DIR)/$(DIR_SA)"\
	LDLIBS+="$(PKG_BUILD_DIR)/$(DIR_SA)/libSA.a $(PKG_BUILD_DIR)/$(DIR_ASN1_RUNTIME)/libASN1Run.a $(PKG_BUILD_DIR)/$(DIR_ASN1_GEN)/libASN1Gen.a -lSA -lASN1Run -lASN1Gen -lpthread -lboost_regex-mt -lboost_serialization-mt -lboost_thread-mt -lboost_system-mt"

define Package/alarming-protocol/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(DIR_AP)/alarming-protocol $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(DIR_MSDP)/msdp $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/alarming-protocol.init $(1)/etc/init.d/alarming-protocol
endef

$(eval $(call BuildPackage,alarming-protocol))
