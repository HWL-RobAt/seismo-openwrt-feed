# $Id$
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sysstat
PKG_VERSION:=8.0.1
PKG_RELEASE:=1


PKG_BUILD_DIR:=$(BUILD_DIR)/sysstat-$(PKG_VERSION)
PKG_SOURCE:=sysstat-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://perso.orange.fr/sebastien.godard
PKG_MD5SUM:=10369aeb42290f0141e685d33cdac658
PKG_CAT:=zcat

include $(INCLUDE_DIR)/package.mk

define Package/sysstat
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Sysstat performance monitoring tools
  VERSION:=$(PKG_VERSION)
  URL:=http://perso.orange.fr/sebastien.godard/index.html
endef

define Package/sysstat/description
	The sysstat utilities are a collection of performance monitoring 
	tools for Linux. These include sar, sadf, mpstat, iostat, pidstat 
	and sa tools.
endef

define Package/sysstat/conffiles
/etc/sysstat/sysstat.ioconf
/etc/sysstat/config
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR); rm -rf config.{cache,status}; \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		sa_lib_dir="/usr/lib/sysstat" \
		sa_dir="/var/log/sysstat" \
		conf_dir="/etc/sysstat" \
		./configure \
		  --target=$(GNU_TARGET_NAME) \
		  --host=$(GNU_TARGET_NAME) \
		  --build=$(GNU_HOST_NAME) \
		  --program-prefix="" \
		  --program-suffix="" \
		  --prefix=/usr \
		  --exec-prefix=/usr \
		  --bindir=/usr/bin \
		  --sbindir=/usr/sbin \
		  --libexecdir=/usr/lib \
		  --sysconfdir=/etc \
		  --datadir=/usr/share \
		  --localstatedir=/var \
		  --mandir=/usr/man \
		  --infodir=/usr/info \
		  $(DISABLE_NLS) \
		  $(DISABLE_LARGEFILE) \
	);
endef

define Package/sysstat/install
	$(INSTALL_DIR) $(1)/usr/lib/sysstat
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/{sadc,sa1,sa2} $(1)/usr/lib/sysstat
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/{sar,sadf,iostat,mpstat} $(1)/usr/bin
	$(INSTALL_DIR) $(1)/var/log/sysstat
	$(INSTALL_DIR) $(1)/etc/sysstat
	$(CP) $(PKG_BUILD_DIR)/sysstat.ioconf $(1)/etc/sysstat
	$(CP) ./files/config $(1)/etc/sysstat/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/sysstat.init $(1)/etc/init.d/sysstat
endef

$(eval $(call BuildPackage,sysstat))
