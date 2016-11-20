#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -device rtl8139,netdev=net0,mac=BA:DA:55:EE:55:0$1 -netdev tap,id=net0,ifname=tap$1,script=no,downscript=no
