# ARQ
x64 Operative system based on pure64 loader.

## Requirements

* QEMU
* bridge-utils
* uml-utilities

## Installation

```sh
git clone git@github.com:jjant/TP_Arqui.git arq && cd arq
sudo apt-get install qemu-system bridge-utils -uml-utilities
./install.sh
```

## Running

```sh
./run.sh 0
```

## Network

To test the network implementation just run `run.sh 0` and `run.sh 1` in different terminals.