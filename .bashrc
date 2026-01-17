# ~/.bashrc
# If not running interactively, don't do anything
[[ $- != *i* ]] && return
alias ls='ls -l --color=auto'
alias grep='grep --color=auto'
alias remake='cd ~/hydwm; for dir in dwm st dmenu slstatus slock; do     echo "-> Installing $dir";     (         cd "$dir" || exit 1;         sudo make install;     ); done; cd ~'
alias copy='xclip -selection clipboard'
alias n='nvim'
export FZF_DEFAULT_OPTS=" \
  --height=100% \
  --layout=reverse \
  --color='fg:#d0d0d0,bg:-1,hl:#5f87af,fg+:#ffffff,bg+:#262626,hl+:#5fd7ff' \
  --color='info:#afaf87,prompt:#67A38D,pointer:#50769B,marker:#67A38D,spinner:#50769B,header:#87afaf' \
  --border=sharp \
  --preview-window='hidden,right,50%,border-sharp' \
  --bind='ctrl-r:toggle-preview' \
  --bind='tab:down' \
  --bind='shift-tab:up' \
  --bind='space:toggle' \
  --preview 'bat --color=always --style=numbers --line-range :500 {}' \
"
bind 'TAB:menu-complete'
eval "$(fzf --bash)"
export SCRIPTS="$HOME/.local/bin"
PS1='[\u@\h \W]\$ '

