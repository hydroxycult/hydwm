#!/bin/sh
xmodmap $HOME/.Xmodmap
feh --bg-scale ~/wallpapers/currentwall.jpg & # change this line for wallpaper change on start>
picom &
dunst &
slstatus &
exec dwm
