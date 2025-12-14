// clang-format off
/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "?";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */
static const struct arg args[] = {
    // uses https://dwm.suckless.org/patches/status2d patch ^c#[HEX]^ to set color and ^d^ to reset color

{ run_command, " %s", "{ command -v pamixer &>/dev/null && pamixer --get-mute | grep -q \"true\" && echo \"^c#ffffff^ 0%^d^\" || command -v pamixer &>/dev/null && echo \"^c#ffffff^$(pamixer --get-volume | awk '{ if ($1 == 0) { print \" 0%\" } else if ($1 < 33) { print \" \"$1\"%\" } else { print \" \"$1\"%\" } }')^d^\" || amixer get Master | awk -F'[][]' 'END{ vol=$2; if (vol ~ /off/) { print \"^c#ffffff^ 0%^d^\" } else { gsub(/%/, \"\", vol); if (vol == 0) { print \"^c#ffffff^ 0%^d^\" } else { gsub(/%/, \"\", vol); if (vol < 33) { print \"^c#ffffff^ \"vol\"%^d^\" } else { print \"^c#ffffff^ \"vol\"%^d^\" } } } }'; }" },
{ run_command, " %s", "{ if ! bluetoothctl show 2>/dev/null | grep -q 'Powered: yes'; then echo '^c#7aa2f7^󰂲^d^'; elif bluetoothctl devices Connected 2>/dev/null | grep -q 'Device'; then mac=$(bluetoothctl devices Connected 2>/dev/null | head -n1 | awk '{print $2}'); bat=$(bluetoothctl info \"$mac\" 2>/dev/null | grep 'Battery Percentage' | grep -o '[0-9]*'); if [ -n \"$bat\" ]; then echo \"^c#9ece6a^󰂯 $bat%^d^\"; else echo \"^c#9ece6a^󰂯^d^\"; fi; else echo '^c#f7768e^󰂲^d^'; fi; }" },
          { cpu_perc,		    " ^c#ffffff^ %s%%^d^ ",        NULL },
{ run_command, "%s", "{ bat_perc=$(cat /sys/class/power_supply/BAT0/capacity); if [ \"$bat_perc\" -le 50 ]; then echo \"^c#ffffff^ $bat_perc% ^d^\"; else echo \"^c#ffffff^ $bat_perc% ^d^\"; fi; }" },
    // { battery_state,  "^c#f43f5e^%s^d^ ",           "BAT0" },
    // { battery_perc,   "^c#f43f5e^ %s%%^d^",         "BAT1" },
    // { battery_state,  "^c#f43f5e^%s^d^ ",           "BAT1" },
    { datetime,       "^c#ffffff^󰸗 %s^d^",            "%I:%M %p" },

};
