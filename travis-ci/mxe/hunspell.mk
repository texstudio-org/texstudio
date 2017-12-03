# This file is part of MXE. See LICENSE.md for licensing information.

PKG             := hunspell
$(PKG)_WEBSITE  := http://hunspell.github.io/
$(PKG)_DESCR    := Hunspell
$(PKG)_IGNORE   :=
$(PKG)_VERSION  := 1.6.1
$(PKG)_CHECKSUM := 30f593733c50b794016bb03d31fd2a2071e4610c6fa4708e33edad2335102c49
$(PKG)_SUBDIR   := hunspell-$($(PKG)_VERSION)
$(PKG)_FILE     := hunspell-$($(PKG)_VERSION).tar.gz
$(PKG)_URL      := https://github.com/hunspell/hunspell/archive/v$($(PKG)_VERSION).tar.gz
$(PKG)_DEPS     := gcc gettext libiconv pthreads readline

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
