#!/bin/bash

set -e
cat <<'EOF'
 _               _
| |__  _   _  __| |_      ___ __ ___
| '_ \| | | |/ _` \ \ /\ / / '_ ` _ \
| | | | |_| | (_| |\ V  V /| | | | | |
|_| |_|\__, |\__,_| \_/\_/ |_| |_| |_|
       |___/
EOF

echo "[1/5] Installing required packages..."
sudo pacman -S --needed --noconfirm \
    base-devel \
    obs-studio \
    libx11 \
    libxft \
    libxinerama \
    xorg-xsetroot \
    xorg-xkill \
    fontconfig \
    harfbuzz \
    ttf-jetbrains-mono-nerd \
    ttf-iosevka-nerd \
    playerctl \
    brightnessctl \
    feh \
    picom \
    dunst \
    pamixer \
    bluetui \
    firefox \
    lite-xl \
    fastfetch \
    figlet \
    fzf \
    thunar \
    maim \
    xclip \
    xcolor \
    zathura \
    zathura-pdf-mupdf \
    xdg-user-dirs \
    ripgrep \
    xorg-xinit

echo "Packages installed successfully."
echo ""
echo "[2/5] Building suckless tools..."
for dir in dwm st dmenu slstatus slock; do
    echo "-> Installing $dir"
    (
        cd "$dir" || exit 1
        sudo make install
    )
done
echo "Suckless tools built and installed."
echo ""
echo "[3/5] Creating directories..."
mkdir -p ~/wallpapers
mkdir -p ~/.config
mkdir -p ~/downloads ~/media ~/desktop ~/music
echo "Directories created."
echo ""

echo "[4/5] Installing config files..."
echo "  -> Copying wallpapers..."
cp -r wallpapers/* ~/wallpapers/
echo "  -> Installing dunst config..."
rm -rf ~/.config/dunst
cp -r dunst ~/.config/
echo "  -> Installing picom config..."
rm -rf ~/.config/picom
cp -r picom ~/.config/
echo "  -> Installing fastfetch config..."
rm -rf ~/.config/fastfetch
cp -r fastfetch ~/.config/

echo "-> Installing .xinitrc and .bashrc"

cp -f .bashrc  ~/.bashrc
cp -f .xinitrc ~/.xinitrc
chmod +x ~/.xinitrc


echo "  -> Installing lite-xl colors..."
rm -rf ~/.config/lite-xl/colors
cp -r colors ~/.config/lite-xl/

echo "core.reload_module('colors.blacky')" >> ~/.config/lite-xl/init.lua
echo "  -> Setting up XDG user directories..."
cp user-dirs.dirs ~/.config/
xdg-user-dirs-update
echo "  -> Installing custom scripts..."
mkdir -p ~/.local/bin
cp -r .local/bin/* ~/.local/bin/
chmod +x ~/.local/bin/*.sh
echo "  -> Installing systemd user services..."
mkdir -p ~/.config/systemd/user
cp -r systemd/user/* ~/.config/systemd/user/
systemctl --user daemon-reload
systemctl --user enable --now battery-monitor.service
systemctl --user enable --now volume-listener.service
echo "Configuration files installed."
echo ""
echo "[5/5] Post-installation notes..."
echo ""
echo ""
echo "Firefox userChrome setup:"
echo "  1. Open Firefox and go to about:config"
echo "  2. Set 'toolkit.legacyUserProfileCustomizations.stylesheets' to true"
echo "  3. Find your Firefox profile folder:"
echo "     ls ~/.mozilla/firefox/*.default-release"
echo "  4. Copy the chrome folder to your profile:"
echo "     cp -r chrome ~/.mozilla/firefox/<your-profile>/"
echo ""
echo "=========================================="
echo "       Installation Complete!             "
echo "=========================================="
echo ""
echo "Run 'startx' to start the desktop environment."
