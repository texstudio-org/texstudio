# This file is part of MXE. See LICENSE.md for licensing information.

PKG             := poppler
$(PKG)_WEBSITE  := https://poppler.freedesktop.org
$(PKG)_IGNORE   :=
$(PKG)_VERSION  := 0.74.0
$(PKG)_CHECKSUM := 92e09fd3302567fd36146b36bb707db43ce436e8841219025a82ea9fb0076b2f
$(PKG)_SUBDIR   := poppler-$($(PKG)_VERSION)
$(PKG)_FILE     := poppler-$($(PKG)_VERSION).tar.xz
$(PKG)_URL      := https://poppler.freedesktop.org/poppler-$($(PKG)_VERSION).tar.xz
$(PKG)_DEPS     := cc cairo curl freetype glib jpeg lcms libpng libwebp openjpeg qtbase tiff zlib

define $(PKG)_UPDATE
    $(call GET_LATEST_VERSION, https://poppler.freedesktop.org/releases.html, poppler-)
endef

define $(PKG)_BUILD
    # build and install the library
    cd '$(BUILD_DIR)' && $(TARGET)-cmake \
        -DENABLE_UNSTABLE_API_ABI_HEADERS=ON -DENABLE_TESTS=OFF -DENABLE_UTILS=OFF \
        '$(SOURCE_DIR)'
    $(MAKE) -C '$(BUILD_DIR)' -j '$(JOBS)'
    $(MAKE) -C '$(BUILD_DIR)' -j 1 install

    # compile test
    '$(TARGET)-g++' \
        -W -Wall -Werror -ansi -pedantic \
        '$(TEST_FILE)' -o '$(PREFIX)/$(TARGET)/bin/test-$(PKG).exe' \
        `'$(TARGET)-pkg-config' poppler-cpp --cflags --libs`
endef
