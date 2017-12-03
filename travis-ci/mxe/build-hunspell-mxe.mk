include hunspell.mk

hunspell : $(hunspell_FILE)
	if [ "$(shell openssl dgst -sha256 '$^' 2>/dev/null)" != "SHA256($(hunspell_FILE))= $(hunspell_CHECKSUM)" ]; then echo "\nwrong checksum"; exit 1; fi
	tar -xf $^
	$(call hunspell_BUILD,$(hunspell_SUBDIR),hunspell-test)

$(hunspell_FILE) :
	wget --no-check-certificate -O "$(hunspell_FILE)" "$(hunspell_URL)"
