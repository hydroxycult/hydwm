# hydwm

A pre-configured suckless desktop environment (dwm, st, dmenu, slstatus, slock).

## Prerequisites

Arch:
```bash
sudo pacman -S base-devel libx11 libxft libxinerama xorg-xsetroot fontconfig harfbuzz ttf-jetbrains-mono-nerd playerctl brightnessctl feh picom dunst
```

Debian/Ubuntu:
```bash
sudo apt install build-essential libx11-dev libxft-dev libxinerama-dev libharfbuzz-dev x11-xserver-utils fonts-jetbrains-mono playerctl brightnessctl feh picom dunst
```

Fedora:
```bash
sudo dnf install @development-tools libX11-devel libXft-devel libXinerama-devel harfbuzz-devel xsetroot jetbrains-mono-fonts playerctl brightnessctl feh picom dunst
```

## Installation

```bash
git clone https://github.com/hydroxycult/hydwm.git
cd hydwm
chmod +x install.sh
./install.sh # WARNING: CHECK THE CONTENTS BEFORE PROCEEDING.
```

Run `startx` to start.

## Customization

Edit `config.h` in each component, then rebuild:
```bash
cd dwm && sudo make install && cd ..
cd st && sudo make install && cd ..
cd dmenu && sudo make install && cd ..
cd slstatus && sudo make install && cd ..
cd slock && sudo make install && cd ..
```

Colors: `dwm/themes/mhtheme.h` <br>
Terminal opacity: `st/config.h` ---> `float alpha = 0.8` (Line 97) <br>
Wallpapers: `.xinitrc` ---> `feh --bg-scale ~/wallpapers/currentwall.jpg &` (Line 4)

