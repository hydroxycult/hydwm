#!/bin/bash
CHECK_INTERVAL=60
LOW_THRESHOLD=45
HIGH_THRESHOLD=75
LOW_NOTIFIED=false
HIGH_NOTIFIED=false

# Function to get battery percentage
get_battery_level() {

    if [ -f /sys/class/power_supply/BAT0/capacity ]; then
        cat /sys/class/power_supply/BAT0/capacity
    elif [ -f /sys/class/power_supply/BAT1/capacity ]; then
        cat /sys/class/power_supply/BAT1/capacity
    elif command -v acpi &> /dev/null; then
        acpi -b | grep -P -o '[0-9]+(?=%)'
    else
        echo "Error: Unable to determine battery level" >&2
        return 1
    fi
}
get_charging_status() {
    if [ -f /sys/class/power_supply/BAT0/status ]; then
        cat /sys/class/power_supply/BAT0/status
    elif [ -f /sys/class/power_supply/BAT1/status ]; then
        cat /sys/class/power_supply/BAT1/status
    elif command -v acpi &> /dev/null; then
        acpi -b | grep -o "Charging\|Discharging\|Full"
    else
        echo "Unknown"
    fi
}


send_notification() {
    local title="$1"
    local message="$2"
    local urgency="$3"
    
    if command -v notify-send &> /dev/null; then
        notify-send -u "$urgency" "$title" "$message"
    else
        echo "$title: $message"
    fi
}

echo "Battery monitor started. Monitoring every $CHECK_INTERVAL seconds..."
echo "Low threshold: ${LOW_THRESHOLD}%"
echo "High threshold: ${HIGH_THRESHOLD}%"

while true; do
    battery_level=$(get_battery_level)
    charging_status=$(get_charging_status)
    
    if [ -z "$battery_level" ]; then
        echo "Failed to read battery level"
        sleep $CHECK_INTERVAL
        continue
    fi
    
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] Battery: ${battery_level}% | Status: $charging_status"
    if [ "$battery_level" -le "$LOW_THRESHOLD" ] && [ "$LOW_NOTIFIED" = false ]; then
        send_notification "Low Battery" \
            "Battery level is at ${battery_level}%. Please charge your device." \
            "critical"
        LOW_NOTIFIED=true
        HIGH_NOTIFIED=false
    fi
    if [ "$battery_level" -ge "$HIGH_THRESHOLD" ] && [ "$HIGH_NOTIFIED" = false ]; then
        send_notification "Battery Charged" \
            "Battery level is at ${battery_level}%. Consider unplugging to preserve battery health." \
            "normal"
        HIGH_NOTIFIED=true
        LOW_NOTIFIED=false
    fi
    if [ "$battery_level" -gt "$LOW_THRESHOLD" ] && [ "$battery_level" -lt "$HIGH_THRESHOLD" ]; then
        LOW_NOTIFIED=false
        HIGH_NOTIFIED=false
    fi
    
    sleep $CHECK_INTERVAL
done
