/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Noto Sans:size=10" };
static const char dmenufont[]       = "Misc Termsyn:size=10";

/* Normal theme! */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";


/* Winter theme! */
//static const char col_gray1[]       = "#DBDBDB";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#383838";
//static const char col_gray4[]       = "#000000";
//static const char col_cyan[]        = "#0090C9";


static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* If tag is 0, then the assigned tag is whatever the current tag is
	 * Else, when you spawn, the rule will stick it where it belongs
	 * monitor = -1 spawns on the focused monitor
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "st",       NULL,       "rcalc",    0,            1,           -1 },
	{ "st",       NULL,       "cal",      0,            1,           -1 },
	{ "st",       NULL,       "goals-st", 0,            1,           -1 },
	// Any jerry-rigged shortcuts go to the 9th space
	{ "st",       NULL,       "funkey",   1 << 8,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
	{ MODKEY|ShiftMask, 		KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      tag,            {.ui = 1 << TAG} },
#define BRTDOWNKEY 0x1008ff03
#define BRTUPKEY 0x1008ff02
#define VMUTEKEY 0x1008ff12
#define VDOWNKEY 0x1008ff11
#define VUPKEY 0x1008ff13

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-b", "-l", "4", "-p", "Run", "-fn", dmenufont, "-nb", "#282a36", "-nf", "#f8f8f2", "-sb", "#1E88E5", "-sf", "#202020" , NULL};
static const char *termcmd[]  		= { "st", NULL };
static const char *browscmd[] 	 	= { "firefox", NULL };
static const char *fbrowscmd[]		= { "st", "-e", "vifm", NULL };
static const char *rcalccmd[]  		= { "st", "-t", "rcalc",    "-g", "80x24+625+325", "-e", "R", "--vanilla", "-q", NULL };
static const char *goalscmd[] 	 	= { "st", "-t", "goals-st", "-g", "80x24+625+325", "-e", "/kbin/check_goals", NULL };
static const char *calcmd[] 	 	= { "st", "-t", "cal", "-g", "20x12+855", "-e", "/kbin/check_cal", NULL };
// Function key commands
static const char *brightdown[]  	= { "st", "-t", "funkey", "-e", "/kbin/sbar_bright.sh", "-U", "5", NULL };
static const char *brightup[]	  	= { "st", "-t", "funkey", "-e", "/kbin/sbar_bright.sh", "-A", "5", NULL };
static const char *brightdownsmall[]  	= { "st", "-t", "funkey", "-e", "/kbin/sbar_bright.sh", "-U", "1", NULL };
static const char *brightupsmall[]  	= { "st", "-t", "funkey", "-e", "/kbin/sbar_bright.sh", "-A", "1", NULL };
static const char *volmute[] 		= { "st", "-t", "funkey", "-e", "/kbin/sbar_audio.sh", "mute", "NULL", NULL };
static const char *voldown[] 		= { "st", "-t", "funkey", "-e", "/kbin/sbar_audio.sh", "-", "5", NULL };
static const char *volup[]  		= { "st", "-t", "funkey", "-e", "/kbin/sbar_audio.sh", "+", "5", NULL };
static const char *voldownsmall[]  	= { "st", "-t", "funkey", "-e", "/kbin/sbar_audio.sh", "-", "1", NULL };
static const char *volupsmall[]  	= { "st", "-t", "funkey", "-e", "/kbin/sbar_audio.sh", "+", "1", NULL };
static const char *prtsc[]	  	= { "st", "-t", "funkey", "-e", "scrot", "-q", "100", NULL };

#include "movestack.c"
static Key keys[] = {
	// Commands from TAGKEYS function
	// MODKEY + KEY 			-> go to tag
	// MODKEY|ShiftMask + KEY		-> add/remove tag to focused window
	// MODKEY|ControlMask + KEY		-> add/remove all windows with tag to/from current view
	// MODKEY|ControlMask|ShiftMask + KEY	-> apply tag to focused window
	/* modifier                     key        function        argument */
	// Window manipulation
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	// Apply all tags to focused window
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	// Send focused window to previous and next screen, when applicable
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	// Custom commands
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_t, 	   spawn,          {.v = termcmd } },
	{ MODKEY,	                XK_f, 	   spawn,          {.v = fbrowscmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browscmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = rcalccmd } },
	{ MODKEY,                       XK_g,      spawn,          {.v = goalscmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = calcmd } },
	//
	// Layout manipulation - Tile, Floating, Monocle
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },
	// Increase number of windows in master area
	{ MODKEY|ControlMask,           XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incnmaster,     {.i = -1 } },
	// Control size of master area (by percent)
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	// View all windows with any tag
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// Switch between screens when applicable
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	//
	// Functions
	// Brightness keys
	{ 0,                            BRTDOWNKEY,spawn,          {.v = brightdown } },
	{ 0,                            BRTUPKEY,  spawn,          {.v = brightup } },
	{ ShiftMask,                    BRTDOWNKEY,spawn,          {.v = brightdownsmall } },
	{ ShiftMask,                    BRTUPKEY,  spawn,          {.v = brightupsmall } },
	// Volume keys
	{ 0,                            VMUTEKEY,  spawn,          {.v = volmute } },
	{ 0,                            VDOWNKEY,  spawn,          {.v = voldown } },
	{ 0,                    	VUPKEY,    spawn,          {.v = volup } },
	{ ShiftMask,                    VDOWNKEY,  spawn,          {.v = voldownsmall } },
	{ ShiftMask,                    VUPKEY,    spawn,          {.v = volupsmall } },
	{ 0,                    	XK_Print,  spawn,          {.v = prtsc } },
	// 
	// Map keys to workspaces
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	// Banished for function key usage
//	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

