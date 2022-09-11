#!/bin/sh
printf "[i] Downloading gcc...\n"
git clone https://bitbucket.org/sol_prog/raspberry-pi-gcc-binary.git
cd raspberry-pi-gcc-binary
printf "[i] Expanding gcc-10.1 files... This may take a while.\n"
tar -xjf gcc-10.1.0-armhf-raspbian.tar.bz2
printf "[i] Instaling gcc-10.1...\n"
sudo mv gcc-10.1.0 /opt
sudo ln -s /usr/include/arm-linux-gnueabihf/sys /usr/include/sys
sudo ln -s /usr/include/arm-linux-gnueabihf/bits /usr/include/bits
sudo ln -s /usr/include/arm-linux-gnueabihf/gnu /usr/include/gnu
sudo ln -s /usr/include/arm-linux-gnueabihf/asm /usr/include/asm
sudo ln -s /usr/lib/arm-linux-gnueabihf/crti.o /usr/lib/crti.o
sudo ln -s /usr/lib/arm-linux-gnueabihf/crt1.o /usr/lib/crt1.o
sudo ln -s /usr/lib/arm-linux-gnueabihf/crtn.o /usr/lib/crtn.o
sudo update-alternatives --install /usr/bin/gcc gcc /opt/gcc-10.1.0/bin/gcc-10.1 20 --slave /usr/bin/g++ g++ /opt/gcc-10.1.0/bin/g++-10.1
printf "[i] Performing clean-up...\n"
cd ..
rm -rf raspberry-pi-gcc-binary
printf "[i] You should see "g++ (GCC) 10.1.0" if everything went to plan!\n"
gcc --version