/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static int gaps                            = 1;  /* 1 means gaps between windows are added */
static const unsigned int gappx            = 14; /* gap pixel between windows */
static const unsigned int borderpx         = 3;  /* border pixel of windows */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"CaskaydiaMono Nerd Font:size=12"};
static const float rootcolor[]             = COLOR(0x110b1aff);
static const int trayspacing               = 4; /* Spacing between icons in system tray */
static const int traymargins               = 4; /* System tray inner margins */
static const float bordercolor[]           = COLOR(0x282836ff);
static const float focuscolor[]            = COLOR(0xb586f3ff);
static const float urgentcolor[]           = COLOR(0xff5569ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xfceeffff, 0x100e21dd, 0x282836ff },
	[SchemeSel]  = { 0xfceeffff, 0x682aabdd, 0xb586f3ff },
	[SchemeUrg]  = { 0xfceeffff,          0xce4559dd,          0xff5569ff },
};

enum {
	EXECUTE,
    POWER,
    SCREENSHOT_ROOT,
    SCREENSHOT_CLIP,
    SCREENSHOT_FILE,
};

const char *modes_labels[] = {
	"execute",
    "power",
    "screenshot",
    "screenshot/clipboard",
    "screenshot/file",
};

/* tagging - TAGCOUNT must be no greater than 31 */
//#define TAGCOUNT (9)
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const unsigned int default_tags = 1 << 1;

/* logging */
static int log_level = WLR_ERROR;

/* Autostart */
static const char *const autostart[] = {
    "dunst", NULL,
    "swaybg", "-i", "/home/tiffany/Pictures/Wallpapers/cool_madeline_wallpaper.png", NULL,
    "gammastep", NULL,
    "foot", NULL,
    "firefox", NULL,
    "vesktop", NULL,
    "aplay", "/home/tiffany/Sounds/PlayStation 1 Startup.wav", NULL,
    "sh", "-c", "systemctl --user import-environment WAYLAND_DISPLAY XDG_CURRENT_DESKTOP && dbus-update-activation-environment --systemd WAYLAND_DISPLAY XDG_CURRENT_DESKTOP=dwl", NULL,
        NULL /* terminate */
};

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor */
	/* examples: */
	{ "Gimp_EXAMPLE",     NULL,       0,            1,           -1 }, /* Start on currently visible tags floating, not tiled */
	{ "vesktop",     NULL,       1 << 2,            0,           -1 }, /* Start on currently visible tags floating, not tiled */
	{ "discord",     NULL,       1 << 2,            0,           -1 }, /* Start on currently visible tags floating, not tiled */
	{ NULL,  "Mozilla Firefox",       1,       0,           -1 }, /* Start on ONLY tag "3" */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ "eDP-1",       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

static const int cursor_timeout = 16;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "foot", NULL };
static const char *menucmd[] = { "wmenu-run", NULL };
static const char *sleepcmd[] = { "systemctl", "suspend", NULL };
static const char *hibercmd[] = { "systemctl", "hibernate", NULL };
static const char *poweroffcmd[] = { "poweroff", NULL };
static const char *rebootcmd[] = { "reboot", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	//{ MODKEY,                    XKB_KEY_p,          spawn,          {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY, XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_J,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_K,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_I,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_D,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_H,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_L,          setmfact,       {.f = +0.05f} },
	{ MODKEY|WLR_MODIFIER_SHIFT,                    XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	//{ MODKEY,                    XKB_KEY_g,          togglegaps,     {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          killclient,     {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_c,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_T,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_F,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_M,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_e,         togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_E,         togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),

    // Keybinds for rofi, ig
    {MODKEY, XKB_KEY_c, spawn, {.v = (const char*[]) {"rofi", "-show", "run", NULL}}},
    {MODKEY, XKB_KEY_C, spawn, {.v = (const char*[]) {"rofi", "-show", "run", NULL}}},
    {MODKEY, XKB_KEY_s, spawn, {.v = (const char*[]) {"rofi", "-show", "drun", NULL}}},
    {MODKEY, XKB_KEY_S, spawn, {.v = (const char*[]) {"rofi", "-show", "drun", NULL}}},
    {MODKEY, XKB_KEY_semicolon, spawn, {.v = (const char*[]) {"rofimoji", NULL}}},

    // Keybind for toggling night light. TODO: have this setting be persistent between dwl restarts.
    {MODKEY, XKB_KEY_apostrophe, spawn, {.v = (const char*[]) {"toggle-redshift", NULL}}},


	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          entermode,           {.i = POWER} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,          entermode,           {.i = POWER} },
	{ MODKEY,                    XKB_KEY_x,          entermode,      {.i = EXECUTE} },
	{ MODKEY,                    XKB_KEY_X,          entermode,      {.i = EXECUTE} },
	{ MODKEY,                    XKB_KEY_p,          entermode,      {.i = SCREENSHOT_ROOT} },
	{ MODKEY,                    XKB_KEY_P,          entermode,      {.i = SCREENSHOT_ROOT} },

    // Volume control keybinds (might move these out of WM-specific config)
    {0, XKB_KEY_XF86AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%")},
    {0, XKB_KEY_XF86AudioLowerVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%")},
    {WLR_MODIFIER_SHIFT, XKB_KEY_XF86AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +1%")},
    {WLR_MODIFIER_SHIFT, XKB_KEY_XF86AudioLowerVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -1%")},
    {MODKEY, XKB_KEY_equal, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%")},
    {MODKEY, XKB_KEY_minus, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%")},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_plus, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +1%")},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_underscore, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -1%")},
    {0, XKB_KEY_XF86AudioMute, spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle")},
    {0, XKB_KEY_XF86AudioMicMute, spawn, SHCMD("pactl set-source-mute @DEFAULT_SINK@ toggle")},

    // Brightness controls (might move these out of WM-specific config)
    {0, XKB_KEY_XF86MonBrightnessUp, spawn, SHCMD("brightnessctl s +10%")},
    {0, XKB_KEY_XF86MonBrightnessDown, spawn, SHCMD("brightnessctl s 10%-")},
    {WLR_MODIFIER_SHIFT, XKB_KEY_XF86MonBrightnessUp, spawn, SHCMD("brightnessctl s +2%")},
    {WLR_MODIFIER_SHIFT, XKB_KEY_XF86MonBrightnessDown, spawn, SHCMD("brightnessctl s 2%-")},

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	//{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Modekey modekeys[] = {
	/* mode      modifier                  key                 function        argument */
	{ EXECUTE, { 0, XKB_KEY_b, spawn, SHCMD("firefox") } },
	{ EXECUTE, { 0, XKB_KEY_b, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_B, spawn, SHCMD("firefox") } },
	{ EXECUTE, { 0, XKB_KEY_B, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_s, spawn, SHCMD("steam") } },
	{ EXECUTE, { 0, XKB_KEY_s, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_S, spawn, SHCMD("steam") } },
	{ EXECUTE, { 0, XKB_KEY_S, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_d, spawn, SHCMD("vesktop") } },
	{ EXECUTE, { 0, XKB_KEY_d, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_D, spawn, SHCMD("vesktop") } },
	{ EXECUTE, { 0, XKB_KEY_D, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_m, spawn, SHCMD("prismlauncher") } },
	{ EXECUTE, { 0, XKB_KEY_m, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_M, spawn, SHCMD("prismlauncher") } },
	{ EXECUTE, { 0, XKB_KEY_M, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_i, spawn, SHCMD("gimp") } },
	{ EXECUTE, { 0, XKB_KEY_i, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_I, spawn, SHCMD("gimp") } },
	{ EXECUTE, { 0, XKB_KEY_I, entermode, {.i = NORMAL} } },
	{ EXECUTE, { 0, XKB_KEY_Escape, entermode, {.i = NORMAL} } },
    { EXECUTE, {MODKEY, XKB_KEY_x, entermode, {.i = NORMAL}} },
    { EXECUTE, {MODKEY, XKB_KEY_X, entermode, {.i = NORMAL}} },

    {POWER, {0, XKB_KEY_q, quit, {.i = 2}}},
    {POWER, {0, XKB_KEY_Q, quit, {.i = 2}}},
    {POWER, {0, XKB_KEY_w, quit, {.i = 0}}},
    {POWER, {0, XKB_KEY_W, quit, {.i = 0}}},
    {POWER, {0, XKB_KEY_e, quit, {.i = 3}}},
    {POWER, {0, XKB_KEY_E, quit, {.i = 3}}},
    {POWER, {0, XKB_KEY_p, spawn, {.v = poweroffcmd}}},
    {POWER, {0, XKB_KEY_P, spawn, {.v = poweroffcmd}}},
    {POWER, {0, XKB_KEY_r, spawn, {.v = rebootcmd}}},
    {POWER, {0, XKB_KEY_R, spawn, {.v = rebootcmd}}},
    {POWER, {0, XKB_KEY_s, spawn, {.v = sleepcmd}}},
    {POWER, {0, XKB_KEY_s, entermode, {.i = NORMAL}}},
    {POWER, {0, XKB_KEY_S, spawn, {.v = sleepcmd}}},
    {POWER, {0, XKB_KEY_S, entermode, {.i = NORMAL}}},
    {POWER, {0, XKB_KEY_h, spawn, {.v = hibercmd}}},
    {POWER, {0, XKB_KEY_h, entermode, {.i = NORMAL}}},
    {POWER, {0, XKB_KEY_H, spawn, {.v = hibercmd}}},
    {POWER, {0, XKB_KEY_H, entermode, {.i = NORMAL}}},

    {SCREENSHOT_ROOT, {0, XKB_KEY_Escape, entermode, {.i = NORMAL}}},
    {SCREENSHOT_ROOT, {0, XKB_KEY_c, entermode, {.i = SCREENSHOT_CLIP}}},
    {SCREENSHOT_ROOT, {0, XKB_KEY_C, entermode, {.i = SCREENSHOT_CLIP}}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_Escape, entermode, {.i = NORMAL}}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_a, spawn, SHCMD("take_screenshot.sh clipboard all")}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_a, entermode, {.i = NORMAL}}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_A, spawn, SHCMD("take_screenshot.sh clipboard all")}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_A, entermode, {.i = NORMAL}}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_s, spawn, SHCMD("take_screenshot.sh clipboard select")}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_s, entermode, {.i = NORMAL}}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_S, spawn, SHCMD("take_screenshot.sh clipboard select")}},
    {SCREENSHOT_CLIP, {0, XKB_KEY_S, entermode, {.i = NORMAL}}},

    {SCREENSHOT_ROOT, {0, XKB_KEY_f, entermode, {.i = SCREENSHOT_FILE}}},
    {SCREENSHOT_ROOT, {0, XKB_KEY_F, entermode, {.i = SCREENSHOT_FILE}}},
    {SCREENSHOT_FILE, {0, XKB_KEY_Escape, entermode, {.i = NORMAL}}},
    {SCREENSHOT_FILE, {0, XKB_KEY_a, spawn, SHCMD("take_screenshot.sh file all")}},
    {SCREENSHOT_FILE, {0, XKB_KEY_a, entermode, {.i = NORMAL}}},
    {SCREENSHOT_FILE, {0, XKB_KEY_A, spawn, SHCMD("take_screenshot.sh file all")}},
    {SCREENSHOT_FILE, {0, XKB_KEY_A, entermode, {.i = NORMAL}}},
    {SCREENSHOT_FILE, {0, XKB_KEY_s, spawn, SHCMD("take_screenshot.sh file select")}},
    {SCREENSHOT_FILE, {0, XKB_KEY_s, entermode, {.i = NORMAL}}},
    {SCREENSHOT_FILE, {0, XKB_KEY_S, spawn, SHCMD("take_screenshot.sh file select")}},
    {SCREENSHOT_FILE, {0, XKB_KEY_S, entermode, {.i = NORMAL}}},
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
