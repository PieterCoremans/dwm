  /* See LICENSE file for copyright and license details. */

  /* appearance */
  static const unsigned int borderpx  = 3;        /* border pixel of windows */
  static const unsigned int gappx     = 10;       /*gaps size between windows -> manuele toevoeging, werkt niet*/
  static const unsigned int snap      = 32;       /* snap pixel */
  static const int showbar            = 1;        /* 0 means no bar */
  static const int topbar             = 1;        /* 0 means bottom bar */
  static const char *fonts[]          = { "JetBrainsMono Nerd Font:style=Medium:size=12" };
  static const char dmenufont[]       = "JetBrainsMono:style=Regular:size=12";
  //background color
  static const char col_gray1[]       = /*"#00374d"*/ "#222222";
  //inactive window border color
  static const char col_gray2[]       = "#444444"; /* Green: "#2D7C4A"; */
  //font color
  static const char col_gray3[]       = "#bbbbbb";
  //current tag and current window font color
static const char col_gray4[]       = "#eeeeee";
//Top bar second color 
static const char col_cyan[]         = "#005577";
//Active window border color
static const char col_windowborder[]      = "#b38302"; /*"#C8112A"*/
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_windowborder  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
/*	 xprop(1):
*	 	WM_CLASS(STRING) = instance, class
*	 	WM_NAME(STRING) = title
*/	 
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Brave-browser",  NULL,       NULL,       1 << 0,       0,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "evolution",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Yad",      NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* originally 0.55 factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },  /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MUDKEY Mod4Mask /*super key*/
#define MODKEY Mod1Mask /*alt key*/
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };

#include "shiftview.c"
/*START_KEYS*/
static Key keys[] = {
	/* modifier                     key        function        argument */
	// launch programs and scripts: replaced by sxhkd
	/*{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },*//*launch firefox*/
	/*{ MODKEY,                       XK_e,      spawn,          SHCMD("thunar") },*//*launch a file manager*/
	/*{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },*//*launch a terminal*/
	/*{ MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("$HOME/.local/bin/changekeys") },*//*run changekeys script*/
	/*{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("$HOME/.local/bin/shutspend") },*//*run shutdown script*/
	/*{ MODKEY|ShiftMask,             XK_comma,  spawn,          SHCMD("$HOME/.local/bin/dwm_keys") },*//*run dwm keys script*/
	/*{ MODKEY,                       XK_Up,     spawn,          SHCMD("$HOME/.local/bin/lmc up") },*//*volume up*/
	/*{ MODKEY,                       XK_Down,   spawn,          SHCMD("$HOME/.local/bin/lmc down") },*//*volume down*/
	/*{ MODKEY,                       XK_Right,  spawn,          SHCMD("$HOME/.local/bin/pbc up") },*//*screen brightness up*/
	/*{ MODKEY,                       XK_Left,   spawn,          SHCMD("$HOME/.local/bin/pbc down") },*//*screen brightness down*/
	/*{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("$HOME/.local/bin/wifi_on_off") },*//*toggle wifi*/
	{ MUDKEY,                       XK_p,      spawn,          {.v = dmenucmd } },/*launch dmenu*/
	{ MUDKEY,                       XK_q,      killclient,     {0} },/*close window*/
	//change layout of screens
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },/*toggle top bar*/
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },/*go up a window*/
	{ MODKEY,                       XK_a,      focusstack,     {.i = +1 } },/*go up a window*/
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },/*go down a window*/
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },/*increment master*/
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },/*decrement master*/
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },/*expand window left*/
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },/*expand window right*/
	{ MODKEY,                       XK_Return, zoom,           {0} },/*put in master*/
	{ MODKEY,                       XK_Tab,    view,           {0} },/*toggle between two last windows*/
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },/*tiled view*/
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },/*floating view*/
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },/*each window full size*/
	{ MODKEY,                       XK_space,  setlayout,      {0} },/*fix current layout (toggle)*/
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        //bekijk alle tags tezamen (maak ongedaan door MODKEY + Control + te verwijderen tag:
	{ MODKEY,                       XK_agrave,      view,           {.ui = ~0 } },
        //zet window op alle tags (maak ongedaan door MODKEY|ShiftMask + Control + te verwijderen tag
	{ MODKEY|ShiftMask,             XK_agrave,      tag,            {.ui = ~0 } },
	//meerdere schermen
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },/*focus op vorig scherm */
	{ MODKEY,                       XK_semicolon, focusmon,    {.i = +1 } },/*focus op volgend scherm */
	{ MODKEY,                       XK_c,     focusmon,        {.i = +1 } },/*focus op volgend scherm */
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, /*verplaats window naar vorig scherm*/
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,      {.i = +1 } },/*verplaats window naar volgend scherm*/
	//verander gaps tijdens sessie
	{ MODKEY,                       XK_minus, setgaps,         {.i = -1 } },/*maak gaps kleiner*/
	{ MODKEY,                       XK_equal, setgaps,         {.i = +1 } },/*maak gaps groter*/
	{ MODKEY|ShiftMask,             XK_equal, setgaps,         {.i = 0  } },/*verwijder gaps*/
	//Shiftview keys
	{ MODKEY,                       XK_n, shiftview ,          {.i = +1 } },/*ga naar volgende tag*/
	{ MODKEY,                       XK_b, shiftview,           {.i = -1 } },/*ga naar vorige tag*/ 
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
  //Change to other tag
  //TAGKEYS(                        XK_ampersand,              0)
  //TAGKEYS(                        XK_eacute,                 1)
  //TAGKEYS(                        XK_quotedbl,               2)
  //TAGKEYS(                        XK_apostrophe,             3)
  //TAGKEYS(                        XK_parenleft,              4)
  //TAGKEYS(                        XK_section,                5)
  //TAGKEYS(                        XK_egrave,                 6)
  //TAGKEYS(                        XK_exclam,                 7)
  //TAGKEYS(                        XK_ccedilla,               8)
	{ MUDKEY|ShiftMask,	        XK_q,      quit,           {0} },/*quit window*/
};
/*END_KEYS*/

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

