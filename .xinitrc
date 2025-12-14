#!/bin/sh

# Wallpaper
feh --bg-scale ~/wallpapers/currentwall.jpg & # change this line for wallpaper change on startup.

# Compositor
picom &

# Notif daemon
dunst &

# Status bar
slstatus &

# Wait a moment for everything to initialize
sleep 1

# Window manager (must be last, blocks until exit)
exec dwm
