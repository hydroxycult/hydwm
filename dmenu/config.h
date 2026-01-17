static int topbar = 1;
static int centered = 0;
static int min_width = 500;
static const char *fonts[] = {"Jetbrains Mono NerdFont:size=12:style=Bold"};
static const char *prompt = NULL;
static const char *colors[SchemeLast][2] = {
    /*     fg         bg       */
    [SchemeNorm] = {"#d1d5db", "#0a0a0a"},
    [SchemeSel] = {"#000000", "#3a3a3a"},
    [SchemeOut] = {"#ffffff", "#3a3a3a"},
};
static unsigned int lines = 8;
static unsigned int columns = 1;
static const char worddelimiters[] = " ";
static unsigned int border_width = 2;
