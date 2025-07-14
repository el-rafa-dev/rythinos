#!/usr/bin/env bash

function mkdirs {
    mkdir rythin
    mkdir rythin/boot 
    mkdir rythin/boot/grub 
    mkdir rythin/initramfs
    mkdir rythin/initramfs/usr
    mkdir rythin/initramfs/usr/bin
    mkdir rythin/initramfs/usr/lib
}

function cpfiles {
    cp kernel/vm-linuz rythin/boot

    cd initramfs/bin/passwd && make
    cd ../../../
    cd initramfs/bin/echo && make
    cd ../../../
    cd initramfs/bin/rsh && make
    cd ../../../
    cd initramfs/init && make
    cd ../../
    cd initramfs/bin/rcat && make
    cd ../../../

    cp grub/grub.cfg rythin/boot/grub
    cp memtest/memtest.efi64 rythin/boot/memtest.efi64
    cp memtest/memtest64.bios rythin/boot/memtest64.bios

    cp initramfs/defprogs/* rythin/initramfs/usr/bin

    #cp initramfs/bin/echo/echo rythin/initramfs/bin/echo
    cp  initramfs/bin/rsh/rsh rythin/initramfs/usr/bin/rsh
    cp  initramfs/bin/bash/bash rythin/initramfs/usr/bin/bash
    cp  initramfs/init/init rythin/initramfs/init
    cp  initramfs/bin/rcat/rcat rythin/initramfs/usr/bin/rcat
    cp  initramfs/bin/passwd/passwd rythin/initramfs/usr/bin/passwd
    cp  /usr/bin/bash rythin/initramfs/usr/bin/bash
    
}

function genCPIO {
    cd rythin/initramfs
    find . | cpio -o -H newc | zstd > ../boot/initramfs.cpio.zstd
    cd ../../
}

function genISO {
    grub-mkrescue -o rythin-iso.iso rythin/
}

function start {
    mkdirs
    cpfiles
    #genCPIO
    cp squashfs/initramfs-linux.img rythin/boot
    genISO
}

start