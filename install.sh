#!/bin/bash

set -e

# Build and install suckless tools
for dir in dwm st dmenu slstatus slock; do
    sudo make -C "$dir" clean install
done

# Create directories
mkdir -p ~/wallpapers
mkdir -p ~/.config

# Copy wallpapers (keeps originals in repo)
cp -r wallpapers/* ~/wallpapers/

# Backup existing configs if they exist
[ -f ~/.xinitrc ] && mv ~/.xinitrc ~/.xinitrc.bak
[ -d ~/.config/dunst ] && mv ~/.config/dunst ~/.config/dunst.bak
[ -d ~/.config/picom ] && mv ~/.config/picom ~/.config/picom.bak

# Install configs
cp .xinitrc ~/
cp -r dunst ~/.config/
cp -r picom ~/.config/

echo "Installation complete. Run 'startx' to start."