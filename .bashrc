#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return
fastfetch
alias ls='ls -l --color=auto'
alias grep='grep --color=auto'
alias clear='clear && fastfetch'
alias remake='cd ~/hydwm/dwm/; sudo make install;cd ~'
n() {
    nohup lite-xl "$@" >/dev/null 2>&1 &
    disown
    kill -9 $$
}
eval "$(fzf --bash)"
export SCRIPTS="$HOME/.local/bin"

PS1='[\u@\h \W]\$ '
