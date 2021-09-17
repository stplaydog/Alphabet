sudo apt-get -y update
sudo apt-get -y install openssh-server  ## this is not needed but I installed to have easy ssh to my test machine from my Macbook.
sudo apt-get -y install libssl-dev
sudo apt-get -y install libncurses5 libncurses5-dev   ## Needed for make menuconfig

sudo mkdir -p /usr/src/kernel
sudo chown -R myuser_id:myuser_id /usr/src/kernel
cd /usr/src/kernel
wget https://git.kernel.org/torvalds/t/linux-4.12-rc4.tar.gz
tar xvfz https://git.kernel.org/torvalds/t/linux-4.12-rc4.tar.gz
cd linux-4.12-rc4
cp /boot/config-4.2.0-27-generic .config    ## Check if your boot has the same config as mine or replace with the appropriate version.
make menuconfig
From inside the menuconfig, select load, choose .config, save, exit. In any doubt then watch the video how make menuconfig works.
make -j4 bzImage && make -j4 modules && sudo make -j4 modules_install

## Installation of kernel modules and initramfs using mkinitramfs:-
-----------------------------------------------------
sudo cp arch/x86/boot/bzImage /boot/vmlinuz-4.12.0-rc4   ## substitute with the appropriate version

sudo mkinitramfs /lib/modules/4.12.0-rc4 -o /boot/initrd.img-4.12.0-rc4 ## Chekc the kernel version you downloaded and compiled
sudo grub-mkconfig -o /boot/grub/grub.cfg     ## When you run this command please ensure as party of output that both your intramfs and vmlinuz with appropriate versions are detected and entered in grub.cfg

sudo update-grub2 

## reboot and select the kernel which you have compiled.
-----------------------------------------------------