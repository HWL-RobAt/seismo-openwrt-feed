# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=seismo-misc
PKG_VERSION:=r$(git rev-parse HEAD)
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/seismo-misc
  SECTION:=seismo
  CATEGORY:=Seismo
  TITLE:=Various config files and scripts
  MAINTAINER:=Jens Nachtigall <nachtiga@informatik.hu-berlin.de>
  DEPENDS:=+busybox
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

define Build/Compile
	echo "*** HEAD ***" >./files/revision.txt
	git rev-parse HEAD >>./files/revision.ttx
	#svnversion ../../ >>./files/revision.txt
	#svn info  ../../ >>./files/revision.txt
	echo "*** data-provider ***" >>./files/revision.txt
	svn info https://samtrac.informatik.hu-berlin.de/svn/data-provider/trunk >>./files/revision.txt
	echo "*** network-status-service ***" >>./files/revision.txt
	svn info https://samtrac.informatik.hu-berlin.de/svn/network-status-service/trunk >>./files/revision.txt
endef

define Package/seismo-misc/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/kismet/
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/etc/modules.d/
	$(INSTALL_DIR) $(1)/etc/jensN/
	$(CP) ./files/olsrd-node-2radios.conf $(1)/etc/
	$(CP) ./files/olsrd-node-1radio.conf $(1)/etc/
	$(CP) ./files/olsrd-new.conf $(1)/etc/
	$(CP) ./files/olsrd-gw.conf $(1)/etc/
	$(CP) ./files/kismet.conf $(1)/etc/kismet/
	$(CP) ./files/kismet_ui.conf $(1)/etc/kismet/
	$(CP) ./files/kismet_drone.conf $(1)/etc/kismet/
	$(CP) ./files/50-madwifi $(1)/etc/modules.d/
	$(INSTALL_BIN) ./files/olsr_or_brn.init $(1)/etc/init.d/olsr_or_brn
	$(INSTALL_BIN) ./files/startup_node_check.initd $(1)/etc/init.d/startup_node_check
	$(INSTALL_BIN) ./files/mount_data_partition.init $(1)/etc/init.d/mount_data_partition
	$(INSTALL_DIR) $(1)/etc/crontabs
	$(CP) ./files/root.cron $(1)/etc/crontabs/root
	$(INSTALL_DIR) $(1)/etc/dropbear/
	$(CP) ./files/dropbear.authorized_keys $(1)/etc/dropbear/authorized_keys
	$(CP) ./files/passwd $(1)/etc/passwd
	$(INSTALL_DIR) $(1)/etc/config
	$(CP) ./files/seismo $(1)/etc/config/seismo
	$(CP) ./files/hostapd-seismo.conf $(1)/etc/hostapd-seismo.conf
	# jensN for metric evaluation
	$(CP) ./files/jensN/olsrd*.conf $(1)/etc/jensN/
	$(CP) ./files/revision.txt $(1)/etc/revision.txt
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) ./files/mount_data_partition $(1)/sbin/mount_data_partition
	$(INSTALL_BIN) ./files/startup_node_check.sh $(1)/sbin/startup_node_check.sh
	$(INSTALL_DIR) $(1)/etc/config
	$(CP) ./files/network.config $(1)/etc/config/network
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/pingn.py $(1)/usr/bin/pingn.py
	$(INSTALL_BIN) ./files/temperature_logger.init $(1)/etc/init.d/temperature_logger
	$(INSTALL_BIN) ./files/temperature_logger.py $(1)/usr/bin/temperature_logger.py
	$(INSTALL_BIN) ./files/scp-resume.sh $(1)/usr/bin/scp-resume.sh
	$(INSTALL_BIN) ./files/udp_sender.py $(1)/usr/bin/udp_sender.py
	$(INSTALL_BIN) ./files/udp_receiver.py $(1)/usr/bin/udp_receiver.py
	$(INSTALL_BIN) ./files/shake.sh $(1)/usr/bin/shake.sh

	
endef


$(eval $(call BuildPackage,seismo-misc))
