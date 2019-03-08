# This file is part of MXE. See LICENSE.md for licensing information.

PKG             := hunspell
$(PKG)_WEBSITE  := http://hunspell.github.io/
$(PKG)_DESCR    := Hunspell
$(PKG)_IGNORE   :=
$(PKG)_VERSION  := 1.7.0
$(PKG)_CHECKSUM := bb27b86eb910a8285407cf3ca33b62643a02798cf2eef468c0a74f6c3ee6bc8a
$(PKG)_GH_CONF  := hunspell/hunspell/tags, v
$(PKG)_DEPS     := cc gettext libiconv pthreads readline

define $(PKG)_UPDATE
    $(WGET) -q -O- 'https://github.com/hunspell/hunspell/releases' | \
    $(SED) -n 's,.*/archive/v\([0-9][^>]*\)\.tar.*,\1,p' | \
    head -1
endef

define $(PKG)_BUILD
    # Note: the configure file doesn't pick up pdcurses, so "ui" is disabled
    cd '$(1)' && autoreconf -vfi && ./configure \
        $(MXE_CONFIGURE_OPTS) \
        --with-warnings \
        --without-ui \
        --with-readline
    $(MAKE) -C '$(1)' -j '$(JOBS)' install bin_PROGRAMS= sbin_PROGRAMS= noinst_PROGRAMS=

    # Test
    '$(TARGET)-g++' \
        -W -Wall -Werror -std=c++0x -pedantic \
        '$(TEST_FILE)' -o '$(PREFIX)/$(TARGET)/bin/test-hunspell.exe' \
        `'$(TARGET)-pkg-config' hunspell --cflags --libs`
endef
