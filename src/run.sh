#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -vga std -netdev user,id=mynet0 -device rtl8139,netdev=mynet0
