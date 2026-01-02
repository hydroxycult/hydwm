# hydwm

A pre-configured and highly opinionated suckless desktop environment (dwm, st, dmenu, slstatus, slock).

## Installation

```bash
sudo pacman -S git
git clone https://github.com/hydroxycult/hydwm.git
cd hydwm
chmod +x install.sh
./install.sh
```

> [!WARNING]
> **Only run `install.sh` if you know what you're doing.** In short, this script will:
> - Install packages via pacman (Arch Linux only).
> - Build and install suckless tools system-wide.
> - Overwrite existing configs in `~/.config/`.
> - Replace your `~/.bashrc` and `~/.xinitrc`.

Run `startx` to start.

## Post-Installation

### Firefox userChrome (Optional - suitable only for vertical tabs)

1. Open Firefox → `about:config`
2. Set `toolkit.legacyUserProfileCustomizations.stylesheets` to `true`
3. Copy the chrome folder to your profile:
   ```bash
   cp -r chrome ~/.mozilla/firefox/*.default-release/
   ```

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
