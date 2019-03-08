include poppler.mk

poppler : $(poppler_FILE)
	if [ "$(shell openssl dgst -sha256 '$^' 2>/dev/null)" != "SHA256($(poppler_FILE))= $(poppler_CHECKSUM)" ]; then echo "\nwrong checksum"; exit 1; fi
	tar -xf $^
	for F in poppler-*.patch; do echo "Applying $$F"; patch -d $(poppler_SUBDIR) -p1 < "$$F"; done
	$(eval SOURCE_DIR := $(shell pwd)/$(poppler_SUBDIR))
	$(eval BUILD_DIR := $(poppler_SUBDIR)/build)
	$(eval TEST_FILE := $(shell pwd)/poppler-test.cxx)
	mkdir $(BUILD_DIR)
	$(call poppler_BUILD)

$(poppler_FILE) :
	wget --no-check-certificate -O "$(poppler_FILE)" "$(poppler_URL)"

