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
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
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
static const char *termcmd[]  = { "st", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },/*launch dmenu*/
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },/*launch a terminal*/
	{ MODKEY,                       XK_e,      spawn,          SHCMD("thunar") },/*launch a file manager*/
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },/*launch firefox*/
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },/*toggle top bar*/
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },/*go up a window*/
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },/*go down a window*/
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },/*increment master*/
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },/*decrement master*/
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },/*expand winodw left*/
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },/*expand window right*/
	{ MODKEY,                       XK_Return, zoom,           {0} },/*put in master*/
	{ MODKEY,                       XK_Tab,    view,           {0} },/*toggle between two last windows*/
	{ MODKEY,                       XK_q,      killclient,     {0} },/*close window*/
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("shutdown_prompt") },/*run shutdown script*/
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },/*tiled view*/
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },/*floating view*/
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },/*each window full size*/
	{ MODKEY,                       XK_space,  setlayout,      {0} },/*fix current layout (toggle)*/
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_agrave,      view,           {.ui = ~0 } },/* bekijk alle tags tezamen (maak ongedaan door MODKEY + Control + te verwijderen tag*/
	{ MODKEY|ShiftMask,             XK_agrave,      tag,            {.ui = ~0 } },/* zet window op alle tags (maak ongedaan door MODKEY|ShiftMask + Control + te verwijderen tag*/
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/*verander gaps tijdens sessie*/
	{ MODKEY,                       XK_minus, setgaps,         {.i = -1 } }, /*maak gaps kleiner*/
	{ MODKEY,                       XK_equal, setgaps,         {.i = +1 } }, /*maak gaps groter*/
	{ MODKEY|ShiftMask,             XK_equal, setgaps,         {.i = 0  } }, /*verwijder gaps*/
	/*Shiftview keys*/
	{ MODKEY,                       XK_n, shiftview ,          {.i = +1 } }, /*ga naar volgende tag*/
	{ MODKEY,                       XK_b, shiftview,           {.i = -1 } }, /*ga naar vorige tag*/ 
	{ MODKEY,                       XK_Up,    spawn,          SHCMD("lmc up") },/*volume up*/
	{ MODKEY,                       XK_Down,  spawn,          SHCMD("lmc down") },/*volume down*/
	/*TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)*/
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_section,                5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_exclam,                 7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ShiftMask,	        XK_q,      quit,           {0} },/*quit window*/
};

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

