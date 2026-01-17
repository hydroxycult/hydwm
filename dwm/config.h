// clang-format off
/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 4;        // border pixel of windows
static const unsigned int snap      = 32;       // snap pixel
static const unsigned int gappih    = 12;        // horiz inner gap between windows
static const unsigned int gappiv    = 12;        // vert inner gap between windows
static const unsigned int gappoh    = 4;        // horiz outer gap between windows and screen edge
static const unsigned int gappov    = 4;        // vert outer gap between windows and screen edge
static       int smartgaps          = 0;        // 1 means no outer gap when there is only one window
static const int floatbar           = 0;        // 1 means floating bar (with gaps from edges), 0 means standard bar
static const int horizpadbar        = 5;        // horizontal padding for status bar text
static const int vertpadbar         = 10;       // vertical padding for bar height
static const int showbar            = 1;        // 0 means no bar
static const int topbar             = 1;        // 0 means bottom bar
static const char *fonts[]          = { "Jetbrains Mono NerdFont:size=12:style=Bold" };
static const char dmenufont[]       = "Jetbrains Mono NerdFont:size=12:style=Bold";
#include "themes/mhtheme.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, col_accnt  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagicon_selected = "󰮯"; /* Icon for the selected tag */
static const char *tagicon_occupied = ""; /* Icon for tags with windows */
static const char *tagicon_empty    = ""; /* Icon for empty tags */
static const unsigned int ulinepad      = 5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke   = 2; /* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0; /* how far above the bottom of the bar the line should appear */
static const int ulineall               = 0; /* 1 to show underline on all tags, 0 for just the active ones */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "com.lite_xl.LiteXL",  "lite-xl",  NULL,  0,  0,  -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;   /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;     /* number of clients in master area */
static const int resizehints = 0;     /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;  /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "unfloat.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask  /* Super key */
#define ALTKEY Mod1Mask  /* Alt key */
#define TAGKEYS(KEY,TAG) \
    { ALTKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accnt, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *thunar[] = { "thunar", NULL };
static const char *firefox[] = { "firefox", NULL };
static const char *litexl[] = { "lite-xl", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key                    function        argument */
	{ ALTKEY,                       XK_space,              spawn,          {.v = dmenucmd } },                                // app launcher
	{ ControlMask|ALTKEY,           XK_t,                  spawn,          {.v = termcmd  } },                               // terminal CTRL+ALT+T 
	{ ControlMask,                  XK_e,                  spawn,          {.v = thunar } },                                  // file manager CTRL+E 
	{ ControlMask|ShiftMask,        XK_z,                  spawn,          {.v = firefox } },                              // firefox CTRL+SHIFT+Z 
	{ ControlMask|ShiftMask,        XK_bracketright,       spawn,          SHCMD("$HOME/boomer/boomer") },                              // firefox CTRL+SHIFT+Z 
	{ MODKEY,                       XK_m,                  spawn,          {.v = litexl } },                                  // lite-xl SUPER+M 
	{ MODKEY,                       XK_l,                  spawn,          SHCMD("slock") },                                  // lock screen SUPER+L 
  { ControlMask,                  XK_space,              spawn,          SHCMD("xcolor | xclip -selection clipboard") }, // colorpicker	
	{ ControlMask,                  XK_q,                  killclient,     {0} },                                             // kill window 
	{ ControlMask|ShiftMask,        XK_q,                  spawn,          SHCMD("xkill") },                                  // force kill CTRL+SHIFT+Q
	{ MODKEY,                       XK_v,                  togglefloating, {0} },                                             // toggle float SUPER+V 
	{ MODKEY,                       XK_f,                  togglefullscr,  {0} },                                             // fullscreen SUPER+F 
	{ MODKEY|ShiftMask,             XK_z,                  unfloatvisible, {.v = &layouts[0]} },                              // unfloat windows
	{ MODKEY,                       XK_g,                  setlayout,      {.v = &layouts[13]} },                             // set workspace to float
	{ ALTKEY,                       XK_Tab,                focusstack,     {.i = +1 } },                                      // ALT+TAB cycle 
	{ MODKEY,                       XK_Left,               focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,              focusstack,     {.i = +1 } },                                      // focus right
	{ MODKEY,                       XK_Up,                 focusstack,     {.i = -1 } },                                      // focus up
	{ MODKEY,                       XK_Down,               focusstack,     {.i = +1 } },                                      // focus down
	{ MODKEY|ControlMask,           XK_Left,               setmfact,       {.f = -0.05} },                                    // resize left
	{ MODKEY|ControlMask,           XK_Right,              setmfact,       {.f = +0.05} },                                    // resize right
	{ MODKEY|ControlMask,           XK_Up,                 setcfact,       {.f = -0.25} },                                    // resize up
	{ MODKEY|ControlMask,           XK_Down,               setcfact,       {.f = +0.25} },                                    // resize down
	{ MODKEY|ShiftMask,             XK_Left,               movestack,      {.i = -1 } },                                      // swap left
	{ MODKEY|ShiftMask,             XK_Right,              movestack,      {.i = +1 } },                                      // swap right
	{ MODKEY|ShiftMask,             XK_Up,                 movestack,      {.i = -1 } },                                      // swap up
	{ MODKEY|ShiftMask,             XK_Down,               movestack,      {.i = +1 } },                                      // swap down
	{ MODKEY,                       XK_j,                  focusstack,     {.i = +1 } },                                      // focus down (vim)
	{ MODKEY,                       XK_k,                  focusstack,     {.i = -1 } },                                      // focus up (vim)
	{ MODKEY|ShiftMask,             XK_j,                  movestack,      {.i = +1 } },                                      // move down (vim)
	{ MODKEY|ShiftMask,             XK_k,                  movestack,      {.i = -1 } },                                      // move up (vim)
	{ MODKEY,                       XK_h,                  setmfact,       {.f = -0.05} },                                    // resize left (vim)
	{ MODKEY|ShiftMask,             XK_l,                  setmfact,       {.f = +0.05} },                                    // resize right (vim)
	{ ControlMask|ALTKEY,           XK_Left,               view,           {.ui = ~0 } },                                     // view all tags
	{ ControlMask|ALTKEY,           XK_Right,              view,           {.ui = ~0 } },                                     // next workspace (show all then cycle)
	{ MODKEY,                       XK_s,                  toggleview,     {.ui = 1 << 8} },                                  // special workspace (tag 9)
	{ MODKEY|ShiftMask,             XK_semicolon,          tag,            {.ui = 1 << 8} },                                  // move to special workspace silent
	{ MODKEY|ControlMask|ShiftMask, XK_s,                  tag,            {.ui = 1 << 8} },                                  // move to special workspace
	{ MODKEY,                       XK_0,                  view,           {.ui = ~0 } },                                     // view all tags
	{ MODKEY|ShiftMask,             XK_0,                  tag,            {.ui = ~0 } },                                     // tag on all workspaces
	{ MODKEY,                       XK_i,                  incnmaster,     {.i = +1 } },                                      // increase master
	{ MODKEY,                       XK_d,                  incnmaster,     {.i = -1 } },                                      // decrease master
	{ MODKEY,                       XK_Return,             zoom,           {0} },                                             // swap with master
	{ MODKEY,                       XK_b,                  togglebar,      {0} },                                             // toggle bar
	{ MODKEY|ALTKEY,                XK_1,                  setlayout,      {.v = &layouts[0]} },                              // tile layout
	{ MODKEY|ALTKEY,                XK_2,                  setlayout,      {.v = &layouts[13]} },                             // float layout
	{ MODKEY|ALTKEY,                XK_3,                  setlayout,      {.v = &layouts[5]} },                              // monocle layout
	{ MODKEY|ALTKEY,                XK_4,                  setlayout,      {.v = &layouts[11]} },                             // centered master
	{ MODKEY|ALTKEY,                XK_5,                  setlayout,      {.v = &layouts[3]} },                              // bstack
	{ MODKEY|ALTKEY,                XK_6,                  setlayout,      {.v = &layouts[7]} },                              // grid
	{ MODKEY|ALTKEY,                XK_7,                  setlayout,      {.v = &layouts[2]} },                              // spiral
	
	{ MODKEY|ShiftMask,             XK_minus,              incrgaps,       {.i = -2 } },                                      // decrease inner gaps
	{ MODKEY|ShiftMask,             XK_equal,              incrgaps,       {.i = +2 } },                                      // increase inner gaps
	{ MODKEY|ControlMask,           XK_minus,              incrgaps,       {.i = -2 } },                                      // decrease outer gaps
	{ MODKEY|ControlMask,           XK_equal,              incrgaps,       {.i = +2 } },                                      // increase outer gaps
	{ MODKEY|ShiftMask,             XK_bracketleft,        setborderpx,    {.i = -2 } },                                      // decrease border
	{ MODKEY|ShiftMask,             XK_bracketright,       setborderpx,    {.i = +2 } },                                      // increase border
	{ MODKEY,                       XK_minus,              spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -2%") },
	{ MODKEY,                       XK_equal,              spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +2%") },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,        SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,        SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
	{ 0,                            XF86XK_AudioMute,      spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
	{ 0,                            XF86XK_AudioMicMute,   spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0,                            XF86XK_MonBrightnessUp, spawn,         SHCMD("brightnessctl set +4%") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,       SHCMD("brightnessctl set 4%-") },
		
	{ MODKEY,                       XK_period,             spawn,          SHCMD("playerctl next") },                         // next track
	{ MODKEY,                       XK_comma,              spawn,          SHCMD("playerctl previous") },                     // prev track
	{ MODKEY,                       XK_slash,              spawn,          SHCMD("playerctl play-pause") },                   // play/pause
	{ 0,                            XF86XK_AudioNext,      spawn,          SHCMD("playerctl next") },
	{ 0,                            XF86XK_AudioPrev,      spawn,          SHCMD("playerctl previous") },
	{ 0,                            XF86XK_AudioPlay,      spawn,          SHCMD("playerctl play-pause") },
	{ 0,                            XF86XK_AudioPause,     spawn,          SHCMD("playerctl play-pause") },
  { MODKEY|ShiftMask, XK_s, spawn, SHCMD("file=\"$HOME/media/$(date +'%Y-%m-%d_%H-%M-%S').png\"; maim -s -u | tee \"$file\" | xclip -selection clipboard -t image/png -i && notify-send \"Screenshot saved\" \"$(basename \"$file\")\"") }, // area screenshot
	{ MODKEY|ShiftMask,             XK_comma,              tagmon,         {.i = -1 } },                                      // move to prev monitor
	{ MODKEY|ShiftMask,             XK_period,             tagmon,         {.i = +1 } },                                      // move to next monitor
	
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
	{ MODKEY|ControlMask,           XK_r,                  spawn,          SHCMD("pkill dwm && startx") },                              // reload dwm
	{ MODKEY|ShiftMask,             XK_BackSpace,          quit,           {0} },                                             // quit dwm
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button3,        spawn,          SHCMD("st bluetui") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
