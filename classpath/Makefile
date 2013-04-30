include $(TOPDIR)/rules.mk

PKG_NAME:=classpath
PKG_VERSION:=0.96.1
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.gnu.org/gnu/classpath/

include $(INCLUDE_DIR)/package.mk

define Package/classpath
  SUBMENU:=Java
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=GNU Classpath for JamVM
  MAINTAINER:=Siamak Haschemi (haschemi@informatik.hu-berlin.de)
  URL:=http://www.gnu.org/software/classpath/
  DEPENDS:=+jamvm
endef

define Package/classpath/Description 
    GNU Classpath, Essential Libraries for Java, is a GNU project 
    to create free core class libraries for use with virtual 
    machines and compilers for the java programming language.
endef 

CONFIGURE_ARGS+= \
    --with-ecj=$(TOPDIR)/package/classpath/files/ecj \
    --enable-jni \
    --disable-gtk-peer \
    --disable-gconf-peer \
    --disable-plugin \

define Build/Compile    
	cp ./files/glibj.zip ${PKG_BUILD_DIR}/lib
	cp ./files/tools.zip ${PKG_BUILD_DIR}/tools
	$(MAKE) -C $(PKG_BUILD_DIR) DESTDIR="$(PKG_INSTALL_DIR)" \
	CPPFLAGS="$(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include -I$(STAGING_DIR)/include" \
	all install
endef

define Package/classpath/install
	$(INSTALL_DIR) $(1)/usr/local/classpath/lib/classpath
	$(INSTALL_DIR) $(1)/usr/local/classpath/share/classpath
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/java $(1)/usr/bin/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/classpath/* $(1)/usr/local/classpath/lib/classpath
	$(CP) $(PKG_INSTALL_DIR)/usr/share/classpath/glibj.zip $(1)/usr/local/classpath/share/classpath
endef

$(eval $(call BuildPackage,classpath))

