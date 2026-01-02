#!/bin/bash

STATUS_FILE="/tmp/bluetooth_status"

while true; do
    # Quick check - doesn't hang
    if ! bluetoothctl show 2>/dev/null | grep -q 'Powered: yes'; then
        echo " ^c#7aa2f7^󰂲^d^" > "$STATUS_FILE"
    elif bluetoothctl devices Connected 2>/dev/null | grep -q 'Device'; then
        mac=$(bluetoothctl devices Connected 2>/dev/null | head -n1 | awk '{print $2}')
        bat=$(bluetoothctl info "$mac" 2>/dev/null | grep 'Battery Percentage' | grep -o '[0-9]*' | head -1)
        if [ -n "$bat" ]; then
            echo " ^c#9ece6a^󰂯 $bat%^d^" > "$STATUS_FILE"
        else
            echo " ^c#9ece6a^󰂯^d^" > "$STATUS_FILE"
        fi
    else
        echo " ^c#f7768e^󰂲^d^" > "$STATUS_FILE"
    fi
    
    sleep 5
done
