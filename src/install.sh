# Compiling the OS
cd Toolchain && make
cd .. && make

# Setting up TAP0 and TAP1
sudo tunctl -u $(whoami)
sudo tunctl -u $(whoami)

# Setting up BRIDGE connection
sudo ip link set dev br2 down
sudo brctl delbr br2
sudo brctl addbr br2
sudo brctl addif br2 tap0
sudo brctl addif br2 tap1
sudo brctl addif br2 tap2
sudo ip link set dev br2 up
sudo ip link set dev tap0 up
sudo ip link set dev tap1 up
sudo ip link set dev tap2 up
sudo echo 1 > /proc/sys/net/ipv6/conf/br2/autoconf

