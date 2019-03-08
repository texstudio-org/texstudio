# This file is part of MXE. See LICENSE.md for licensing information.

PKG             := poppler
$(PKG)_WEBSITE  := https://poppler.freedesktop.org/
$(PKG)_IGNORE   :=
$(PKG)_VERSION  := 0.74.0
$(PKG)_CHECKSUM := 92e09fd3302567fd36146b36bb707db43ce436e8841219025a82ea9fb0076b2f
$(PKG)_SUBDIR   := poppler-$($(PKG)_VERSION)
$(PKG)_FILE     := poppler-$($(PKG)_VERSION).tar.xz
$(PKG)_URL      := https://poppler.freedesktop.org/$($(PKG)_FILE)
#$(PKG)_DEPS     := gcc cairo curl freetype glib jpeg lcms libpng qt tiff zlib
$(PKG)_DEPS     := gcc cairo curl freetype glib jpeg lcms libpng  libwebp openjpeg qtbase tiff zlib

define $(PKG)_UPDATE
    $(WGET) -q -O- 'https://poppler.freedesktop.org/' | \
    $(SED) -n 's,.*"poppler-\([0-9.]\+\)\.tar\.xz".*,\1,p' | \
    head -1
endef

define $(PKG)_BUILD
    mkdir -p '$(1)/build'
    cd '$(1)/build' && '$(TARGET)-cmake' .. -DENABLE_UNSTABLE_API_ABI_HEADERS=ON -DENABLE_TESTS=OFF -DENABLE_UTILS=OFF
    $(MAKE) -C '$(1)/build' -j 1 $(MXE_DISABLE_CRUFT) HTML_DIR=
    $(MAKE) -C '$(1)/build' -j 1 install $(MXE_DISABLE_CRUFT) HTML_DIR=

    # Test program
    '$(TARGET)-g++' \
        -W -Wall -Werror -ansi -pedantic \
        '$(TEST_FILE)' -o '$(PREFIX)/$(TARGET)/bin/test-poppler.exe' \
        `'$(TARGET)-pkg-config' poppler poppler-cpp --cflags --libs`
endef
