static int topbar = 1;      
static int centered = 0;    
static int min_width = 500; 
static const char *fonts[] = {"Jetbrains Mono NerdFont:size=12:style=Bold"};
static const char *prompt =
    NULL; 
static const char *colors[SchemeLast][2] = {
    /*     fg         bg       */
    [SchemeNorm] = {"#bbbbbb", "#222222"},
    [SchemeSel] = {"#eeeeee", "#005577"},
    [SchemeOut] = {"#000000", "#00ffff"},
};
static unsigned int lines = 8;
static unsigned int columns = 1;
static const char worddelimiters[] = " ";
static unsigned int border_width = 2;
