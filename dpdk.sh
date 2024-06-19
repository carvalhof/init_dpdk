#!/bin/bash

# Fail on error.
set -e

# Install pre-requisites.
sudo apt install -y meson python3 python3-pip
pip3 install pyelftools

# Download sources.
wget https://fast.dpdk.org/rel/dpdk-22.11.1.tar.xz
tar -xvf dpdk-22.11.1.tar.xz
cd dpdk-stable-22.11.1
mkdir -p build

# Build and install.
meson --prefix=$HOME build
ninja -C build
ninja -C build install

# Set hugepages.
echo 1024 | sudo tee /sys/devices/system/node/node*/hugepages/hugepages-2048kB/nr_hugepages
mkdir -p /mnt/huge || true
mount -t hugetlbfs -opagesize=2M nodev /mnt/huge
