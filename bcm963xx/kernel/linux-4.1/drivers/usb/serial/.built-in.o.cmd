cmd_drivers/usb/serial/built-in.o :=  /opt/toolchains//crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-ld -EL   -r -o drivers/usb/serial/built-in.o drivers/usb/serial/usbserial.o drivers/usb/serial/cp210x.o drivers/usb/serial/ftdi_sio.o drivers/usb/serial/option.o drivers/usb/serial/pl2303.o drivers/usb/serial/usb_wwan.o 