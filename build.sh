#!/usr/bin/env bash

function mkdirs {
    mkdir rythin
    mkdir rythin/boot 
    mkdir rythin/boot/grub 
    mkdir rythin/initramfs 
    mkdir rythin/initramfs/bin
    mkdir rythin/initramfs/lib
    mkdir rythin/initramfs/lib64
}

function cpfiles {
    cp kernel/vm-linuz rythin/boot
    cd initramfs/bin/echo && make
    cd ../../../
    cd initramfs/bin/rsh && make
    cd ../../../
    cd initramfs/init && make
    cd ../../
    cd initramfs/bin/rcat && make
    cd ../../../

    #libs 32bits
    sudo cp /usr/lib/libncursesw.so.6 rythin/initramfs/lib
    sudo cp /usr/lib/libc.so.6 rythin/initramfs/lib
    sudo cp /usr/lib/libncursesw.so.6 rythin/initramfs/lib
    #lib64 bits
    sudo cp /usr/lib64/ld-linux-x86-64.so.2 rythin/initramfs/lib64
    sudo cp /usr/lib64/libncursesw.so.6 rythin/initramfs/lib64

    cp grub/grub.cfg rythin/boot/grub
    cp memtest/memtest.efi64 rythin/boot/memtest.efi64
    cp memtest/memtest64.bios rythin/boot/memtest64.bios

    cp initramfs/bin/echo/echo rythin/initramfs/bin/echo
    cp initramfs/bin/rsh/rsh rythin/initramfs/bin/rsh
    cp initramfs/bin/bash/bash rythin/initramfs/bin/bash
    cp initramfs/init/init rythin/initramfs/init
    cp initramfs/bin/rcat/rcat rythin/initramfs/bin/rcat
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
    genCPIO
    genISO
}

start