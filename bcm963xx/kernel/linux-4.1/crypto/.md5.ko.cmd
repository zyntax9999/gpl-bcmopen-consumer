cmd_crypto/md5.ko := /opt/toolchains//crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-ld -EL -r  -T ./scripts/module-common.lds --build-id  -o crypto/md5.ko crypto/md5.o crypto/md5.mod.o