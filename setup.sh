#!/usr/bin/env bash

# Script to prepare the build environment for QCamber.
# It installs the required Qt6 development packages along with
# additional build tools such as qmake6, bison and flex.

set -euo pipefail

# Avoid interactive prompts during installation
export DEBIAN_FRONTEND=noninteractive

echo "Updating package lists..."
sudo apt-get update

packages=(
  qt6-base-dev
  qt6-tools-dev
  qt6-tools-dev-tools
  qt6-l10n-tools
  qt6-base-dev-tools
  qt6-declarative-dev
  qt6-multimedia-dev
  qt6-svg-dev
  qmake6
  bison
  flex
  build-essential
  cmake
  git
)

echo "Installing build dependencies..."
sudo apt-get install -y --no-install-recommends "${packages[@]}"

# Provide a qmake wrapper if qmake6 is installed but qmake is not.
if ! command -v qmake >/dev/null && command -v qmake6 >/dev/null; then
    echo "Creating symbolic link: /usr/local/bin/qmake -> qmake6"
    sudo ln -sf "$(command -v qmake6)" /usr/local/bin/qmake
fi

echo "Environment setup complete."
