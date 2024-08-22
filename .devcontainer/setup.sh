#!/usr/bin/env bash

set -eEuo pipefail

wget https://bootstrap.pypa.io/get-pip.py
python3 get-pip.py
python3 -m pip install qmk
rm get-pip.py

python3 -m pip install --upgrade milc

userspacePath="$1"

git config --global --add safe.directory "$userspacePath"
git submodule update --init --recursive

git config --global --add safe.directory /workspaces/bastardkb-qmk/

qmk config user.qmk_home=/workspaces/bastardkb-qmk/
qmk config user.overlay_dir="$userspacePath"

qmk git-submodule
