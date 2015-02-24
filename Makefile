include $(TOPDIR)/rules.mk

PKG_NAME:=lm75
PKG_VERSION:=1.0
PKG_RELEASE:=1

#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)    
SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=$(PKG_NAME)
	DEPENDS:= +libi2c
	MAINTAINER:=sittisak <sittisaks@hotmail.com>
endef

define Package/$(PKG_NAME)/description
	Monitor Temperature through i2c	with lm75a
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

CONFIGURE_VARS+= \
	CC="$(TOOLCHAIN_DIR)/bin/$(TARGET_CC)"

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME),+libi2c))
