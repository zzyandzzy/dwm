/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx = 1;        /* border pixel of windows */
static const unsigned int snap = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;     /* 0 means no systray */
static const int showbar = 1;        /* 0 means no bar */
static const int topbar = 0;        /* 0 means bottom bar */
static const Bool viewontag = True;     /* Switch view on tag switch */
static const char *fonts[] = {"monospace:size=10"};
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3] = {
        /*               fg         bg         border   */
        [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
        [SchemeSel]  = {col_gray4, col_cyan, col_cyan},
        [SchemeHid]  = {col_cyan, col_gray1, col_cyan},
};
static const unsigned int alphas[][3] = {
        /*               fg      bg        border     */
        [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
        [SchemeSel]  = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = {"1", "2", "3"};

static const Rule rules[] = {
        /* xprop(1):
         *	WM_CLASS(STRING) = instance, class
         *	WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        {"Gimp",    NULL, NULL, 0,      1, -1},
        {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
        /* symbol     arrange function */
        {"[]=", tile},    /* first entry is default */
        {"><>", NULL},    /* no layout function means floating behavior */
        {"[M]", monocle},
};

/* key definitions */
#define Ctrl  ControlMask
#define Alt   Mod1Mask
#define Shift ShiftMask
#define Win   Mod4Mask
#define TAGKEYS(KEY, TAG) \
    { Alt,                  KEY,      view,           {.ui = 1 << TAG} }, \
    { Alt|Ctrl,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { Alt|Shift,            KEY,      tag,            {.ui = 1 << TAG} }, \
    { Alt|Ctrl|Shift,       KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3,
                                 "-sb", col_cyan, "-sf", col_gray4, NULL};
static const char *termcmd[] = {"st", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st", "-t", scratchpadname, "-g", "120x34", NULL};

static Key keys[] = {
        /* modifier                     key        function        argument */
        {Win, XK_space, spawn, {.v = dmenucmd}},
        {Ctrl | Shift, XK_Return, spawn, {.v = termcmd}},
        {Alt, XK_apostrophe, togglescratch, {.v = scratchpadcmd}},
        {Win, XK_b, togglebar, {0}},
        {Alt, XK_Tab, rotatestack, {.i = +1}},
        //{Alt | Shift, XK_k, rotatestack, {.i = -1}},
        {Alt, XK_j, focusstack, {.i = +1}},
        {Alt, XK_k, focusstack, {.i = -1}},
        {Alt, XK_i, incnmaster, {.i = +1}},
        {Alt, XK_d, incnmaster, {.i = -1}},
        {Alt, XK_h, setmfact, {.f = -0.05}},
        {Alt, XK_l, setmfact, {.f = +0.05}},
        {Alt, XK_Return, zoom, {0}},
        // {Alt, XK_Tab, view, {0}},
        // finish the client
        {Ctrl, XK_q, killclient, {0}},
        {Alt, XK_t, setlayout, {.v = &layouts[0]}},
        {Alt, XK_f, setlayout, {.v = &layouts[1]}},
        {Alt, XK_m, setlayout, {.v = &layouts[2]}},
        {Alt | Shift, XK_f, fullscreen, {0}},
        {Alt, XK_space, setlayout, {0}},
        {Alt | Shift, XK_space, togglefloating, {0}},
        {Alt, XK_0, view, {.ui = ~0}},
        {Alt | Shift, XK_0, tag, {.ui = ~0}},
        {Alt, XK_comma, focusmon, {.i = -1}},
        {Alt, XK_period, focusmon, {.i = +1}},
        {Alt | Shift, XK_comma, tagmon, {.i = -1}},
        {Alt | Shift, XK_period, tagmon, {.i = +1}},
        TAGKEYS(XK_1, 0)
        TAGKEYS(XK_2, 1)
        TAGKEYS(XK_3, 2)
        TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4)
        TAGKEYS(XK_6, 5)
        TAGKEYS(XK_7, 6)
        TAGKEYS(XK_8, 7)
        TAGKEYS(XK_9, 8)
        // kill dwm
        {Ctrl | Shift, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
        {ClkLtSymbol,   0,  Button1, setlayout,      {0}},
        {ClkLtSymbol,   0,  Button3, setlayout,      {.v = &layouts[2]}},
        {ClkWinTitle,   0,  Button1, togglewin,      {0}},
        {ClkWinTitle,   0,  Button2, zoom,           {0}},
        {ClkStatusText, 0,  Button2, spawn,          {.v = termcmd}},
        {ClkClientWin, Alt, Button1, movemouse,      {0}},
        {ClkClientWin, Alt, Button2, togglefloating, {0}},
        {ClkClientWin, Alt, Button3, resizemouse,    {0}},
        {ClkTagBar,     0,  Button1, view,           {0}},
        {ClkTagBar,     0,  Button3, toggleview,     {0}},
        {ClkTagBar,    Alt, Button1, tag,            {0}},
        {ClkTagBar,    Alt, Button3, toggletag,      {0}},
};

