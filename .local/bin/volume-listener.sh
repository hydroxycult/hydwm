#!/bin/bash

# QUERY MODE (for slstatus)
if [ "$1" = "--volume" ]; then
    if command -v pamixer &>/dev/null; then
        pamixer --get-volume
    else
        amixer get Master | grep -o "[0-9]*%" | head -1 | tr -d '%'
    fi
    exit
fi
# END QUERY MODE


get_volume_info() {
    if command -v pamixer &>/dev/null; then
        vol=$(pamixer --get-volume)
        muted=$(pamixer --get-mute)
    else
        vol=$(amixer get Master | grep -o "[0-9]*%" | head -1 | tr -d '%')
        amixer get Master | grep -q "\[off\]" && muted=true || muted=false
    fi
    echo "$vol:$muted"
}

notify_volume() {
    local vol=$1
    local muted=$2

    if [ "$muted" = "true" ]; then
        dunstify -u normal -h string:x-dunst-stack-tag:volume "Muted"
    else
        dunstify -u normal -h string:x-dunst-stack-tag:volume "Volume: ${vol}%"
    fi
}

if command -v pactl &>/dev/null; then
    PREV_INFO=$(get_volume_info)

    pactl subscribe | grep --line-buffered "sink" | while read -r _; do
        sleep 0.05
        CURRENT_INFO=$(get_volume_info)

        if [ "$CURRENT_INFO" != "$PREV_INFO" ]; then
            vol=${CURRENT_INFO%%:*}
            muted=${CURRENT_INFO##*:}
            notify_volume "$vol" "$muted"
            PREV_INFO="$CURRENT_INFO"
        fi
    done
else
    PREV_INFO=$(get_volume_info)

    while true; do
        sleep 0.25
        CURRENT_INFO=$(get_volume_info)

        if [ "$CURRENT_INFO" != "$PREV_INFO" ]; then
            vol=${CURRENT_INFO%%:*}
            muted=${CURRENT_INFO##*:}
            notify_volume "$vol" "$muted"
            PREV_INFO="$CURRENT_INFO"
        fi
    done
fi

