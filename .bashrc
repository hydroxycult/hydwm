#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return
fastfetch
alias ls='ls -la --color=auto'
alias grep='grep --color=auto'
alias clear='clear && fastfetch'
n() {
    nohup lite-xl "$@" >/dev/null 2>&1 &
    disown
    kill -9 $$
}
export SCRIPTS="$HOME/.local/bin"

PS1='[\u@\h \W]\$ '
