#!/bin/bash
apt update -y
apt install -y git
apt install -y build-essential
apt install -y cmake
apt install -y libssl-dev
apt install -y libboost-dev
apt install -y libboost-program-options-dev
cd /maidea
git clone https://github.com/yourWaifu/sleepy-discord.git
mkdir bld
cd bld
cmake ../
make
cp /maidea/maidea.cfg /maidea/bld/maidea.cfg
/maidea/bld/maidea

