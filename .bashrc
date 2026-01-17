#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return
source ~/ble.sh/out/ble.sh
alias ls='ls -l --color=auto'
alias grep='grep --color=auto'
alias remake='cd ~/hydwm/dwm/; sudo make install;cd ~'
n() {
    nohup st nvim "$@" >/dev/null 2>&1 &
    disown
    kill -9 $$
}
eval "$(fzf --bash)"
export SCRIPTS="$HOME/.local/bin"

PS1='[\u@\h \W]\$ '
