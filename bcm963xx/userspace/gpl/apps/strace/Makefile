
all dynamic install: conditional_build

#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
# You do not need to modify this part.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))

include $(BUILD_DIR)/make.common

APP = strace-4.26

clean:
	@if [ -e $(APP)/Makefile ]; then \
	cd $(APP); $(MAKE) distclean ; \
	fi
	-rm -rf $(APP)

# The next line is a hint to our release scripts
# GLOBAL_RELEASE_SCRIPT_CALL_DISTCLEAN
distclean: clean
	rm -rf $(APP)

#.PHONY: check_untar_patch_configure conditional_build


check_untar_patch_configure: sanity_check
	@if [ ! -e $(APP)/Makefile.in ]; then \
    	echo "Untarring original $(APP) source"; \
	    (tar xkf $(APP).tar.xz 2> /dev/null || true; patch -p0 < 2c8b6de.patch); \
        fi; \
	    (cd $(APP); ./configure --host=$(TOOLCHAIN_PREFIX) \
        --target=$(TOOLCHAIN_PREFIX) \
        --prefix=$(INSTALL_DIR) \
        --disable-mpers \
        --sbindir=$(INSTALL_DIR)/bin); 

ifneq ($(strip $(BUILD_STRACE)),)

conditional_build: check_untar_patch_configure
	cd $(APP); $(MAKE) 
	install -m 755 $(APP)/strace  $(INSTALL_DIR)/bin/strace
else
conditional_build: sanity_check
	@echo "skipping $(APP) (not configured)"
endif
