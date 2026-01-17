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
> **Only run `install.sh` if you know what you're doing.** This script will:
>
> * Install packages via pacman (Arch Linux only).
> * Build and install suckless tools system-wide.
> * Overwrite existing configs in `~/.config/`.
> * Replace your `~/.bashrc` and `~/.xinitrc`.

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

---

## Troubleshooting

<details>
<summary><strong>pamixer: Connection error / No PulseAudio server</strong></summary>
<br>

If `pamixer` reports a connection error, it usually means `pipewire-pulse` is not running.

Check status:

```bash
systemctl --user status pipewire pipewire-pulse
```

If `pipewire-pulse.service` is inactive, enable and start its socket:

```bash
systemctl --user enable --now pipewire-pulse.socket
systemctl --user start pipewire-pulse.service
```

Ensure PulseAudio is not running:

```bash
systemctl --user stop pulseaudio.service pulseaudio.socket
systemctl --user disable pulseaudio.service pulseaudio.socket
```

Make sure required packages are installed:

```bash
sudo pacman -S pipewire pipewire-pulse wireplumber
```

Restart user services:

```bash
systemctl --user daemon-reexec
systemctl --user restart pipewire pipewire-pulse wireplumber
```

After this, `pamixer` should work correctly.

</details>

