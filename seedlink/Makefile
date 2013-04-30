# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=seiscomp
PKG_VERSION:=2.5.2006.104
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.gfz-potsdam.de/pub/home/st/GEOFON/software/SeisComP/2.5/
PKG_MD5SUM:=511318cc30e1ed9716d4f8ecc91c1c05

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/seedlink
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=Acquisition part of SeisComP (seedlink and slarchive)
  URL:=http://www.gfz-potsdam.de/geofon/seiscomp/
  DEPENDS:=+libxml2 +zlib +libpthread +libstdcpp +bash
  MAINTAINER:=Jens Nachtigall <nachtiga@informatik.hu-berlin.de>
endef

define Package/seedlink/description
	This package only includes some basic parts of SeisComP: 
	the seedlink server and the seedlink client slarchive.
endef

define Package/seedlink/conffiles
/etc/seedlink/filters.fir
/etc/seedlink/streams.xml
endef

define Build/Configure
endef

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)/acquisition/src/" \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)  -DLEAPSECONDS=\\\"/etc/seedlink/leapseconds\\\" " \
		qlib2 

	$(MAKE) -C "$(PKG_BUILD_DIR)/acquisition/src/" \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		libslink libslplugin slarchive 
	
        # necessary to for a #include in libsutils
	# I did not find a better way for this (jensN, 2008-07-03)
	cp /usr/include/FlexLexer.h $(TOOLCHAIN_DIR)/usr/include/

	# call STAGING_DIR/usr/bin/xml2-config --libs
	# to see what needs to be passed to XML_LIBS
	$(MAKE) -C "$(PKG_BUILD_DIR)/acquisition/src/" \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		XML_INCL="$(TARGET_CPPFLAGS) -I$(STAGING_DIR)/usr/include/libxml2" \
		XML_LIBS="$(TARGET_LDFLAGS) -lxml2 -lz -lpthread -lm" \
		libslutils 

	$(MAKE) -C "$(PKG_BUILD_DIR)/acquisition/src/" \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		XML_INCL="$(TARGET_CPPFLAGS) -I$(STAGING_DIR)/usr/include/libxml2" \
		XML_LIBS="$(TARGET_LDFLAGS) -lxml2 -lz -lpthread -lm" \
		CONFIG_FILE="/etc/seedlink/seedlink.ini" \
		slinktool seedlink 
endef

define Package/seedlink/install
	echo "##################################################"
	echo $(TARGET_DIR)
	echo $(PKG_BUILD_DIR)
	echo $(PKG_INSTALL_DIR)
	echo $(1)
	echo "##################################################"
	$(INSTALL_DIR) $(1)/etc/seedlink
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/lib/seedlink
	#$(INSTALL_DIR) $(1)/var/run
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/acquisition/src/bin/{seedlink,slarchive,slinktool}  $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/acquisition/lib/leapseconds   $(1)/etc/seedlink/
	$(CP) ./files/{filters.fir,streams.xml} $(1)/etc/seedlink/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/seedlink.init $(1)/etc/init.d/seedlink
	$(INSTALL_BIN) ./files/segment_backupper.py $(1)/usr/bin/segment_backupper.py
endef



$(eval $(call BuildPackage,seedlink))
