#!/bin/sh
xmodmap $HOME/.Xmodmap
feh --bg-scale ~/wallpapers/banner.jpg
picom &
dunst &
slstatus &
exec dwm
