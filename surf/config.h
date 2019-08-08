#include "surf-configh-ignore.h"
#define HOMEPAGE "file:///home/hmps/usr/startpage/index2.html"
const static char *searchengine = "https://duckduckgo.com/html/?q=";
const static SearchEngine searchengines[] = {
    { "d",      "https://duckduckgo.com/html/?q=%s" },
    { "g",      "https://google.se/search?q=%s"   },
    { "git",    "https://github.com/search?utf8=&q=%s&type=" },
    { "ugit",   "https://github.com/%s" },
    { "gist",   "https://gist.github.com/search?q=%s" },
    { "wiki",   "https://en.wikipedia.org/wiki/%s" },
    { "w",      "https://en.wikipedia.org/wiki/%s" },
    { "arch",   "https://wiki.archlinux.org/index.php?search=%s" },
    { "gentoo", "https://wiki.gentoo.org/index.php?search=%s" },
    { "r",      "https://reddit.com/r/%s" },
    { "4",      "https://boards.4chan.org/%s" },
    { "u",      "https://reddit.com/u/%s" },
    { "yt",     "https://youtube.com/results?search_query=%s" },
    { "image",  "https://duckduckgo.com/html/?q=!image %s" },
    { "reddit", "https://reddit.com/search?q=%s" },
    { "torrent","https://torrentz2.eu/search?f=%s" },
    { "think",  "https://thinkwiki.org/w/index.php?search=%s" },
    { "prisjakt","https://www.prisjakt.nu/search?search=%s&searchInProps=true" },
    { "dict",   "https://thefreedictionary.com/%s" },
    { "thes",   "https://thesaurus.com/browse/%s" },
    { "wine",   "https://www.winehq.org/search?q=%s" },
};

static char *scriptfile = "/home/hmps/etc/suckless/surf/script.js";
static char *styledir   = "/home/hmps/etc/suckless/surf/styles";
static char *cachedir   = "/home/hmps/.cache/surf";
static char *cookiefile = "/home/hmps/var/tmp/surf-cookies.txt";

static SiteSpecific styles[] = { "ljfadslfksaldflskfd", };

/* static char *fulluseragent  = "Mozilla/5.0"; */
static char *fulluseragent  = "Mozilla/5.0 (X11; Linux x86_64)";
/* static char *fulluseragent  = "Mozilla/5.0 (X11; Linux x86_64; rv:10.0) Gecko/20100101 Firefox/10.0"; */
/* static char *fulluseragent  = "Mozilla/5.0 (X11; rv:10.0) Gecko/20100101 Firefox/10.0"; */

static UriParameters uriparams[] = {
    // no css
    { "(://|\\.)reddit\\.com(/|$)",       { [Style] = { { .i = 0 }, 0 }, }, },
    // strict TLS
    { "(://|\\.)d2l.sdbor\\.edu(/|$)",    { [StrictTLS] = { { .i = 0 }, 0 }, }, },
    { "(://|\\.)dsu\\.edu(/|$)",          { [StrictTLS] = { { .i = 0 }, 0 }, }, },
    // zoom
    { "(://|\\.)discordapp\\.com(/|$)",   { [ZoomLevel] = { { .f = 1.0 }, 1.0 }, }, },
    { "(://|\\.)discord\\.gg(/|$)",       { [ZoomLevel] = { { .f = 1.0 }, 1.0 }, }, },
    // no javascript
    { "(://|\\.)suckless\\.org(/|$)",     { [JavaScript] = { { .i = 0 }, 1 }, }, },
    { "(://|\\.)googleads\\.com(/|$)",    { [JavaScript] = { { .i = 0 }, 1 }, }, },
    // no DNS prefetch
    { "(://|\\.)ebay\\.*(/|$)",           { [DNSPrefetch] = { { .i = 0 }, 0 }, }, },
    { "(://|\\.)amazon\\.*(/|$)",         { [DNSPrefetch] = { { .i = 0 }, 0 }, }, },
    /* { "(://|\\.)youtube\\.*(/|$)",        { [DNSPrefetch] = { { .i = 0 }, 0 }, }, }, */
};

char crossbones_ascii[] = "/home/hmps/usr/bin/ascii/crossbones";

#define PROMPT_GO   "Go:"
#define PROMPT_FIND "Find:"

/* ------------------------------------------------------- */ 
// This sets all the ids for the opening terminal to 'curl'.
// This way you can set that 'curl' terminal to be opened floating
// Which stops the annoying flashing/moving around of windows on a download.
#define DOWNLOAD(u, r) { \
        .v = (const char *[]){ "st", "-T", "surf-download", "-n", "surf-download", "-e", \
             "/bin/sh", "-c", "cd ${HOME}/var/downloads && wget \"$@\" && exit", \
             "surf-download", u, r, NULL \
        } \
}

             /* "/bin/sh", "-c", "cd ${HOME}/var/downloads && curl -A 'Mozilla/5.0' -c '${HOME}/.surf/cookies.txt' -4 -L -O \"$@\" && exit", \ */
        /* "st -e /bin/sh -c \"aria2c -U '$1'" \ */
        /* " --referer '$2' --load-cookies $3 --save-cookies $3 '$0';" \ */
/* } */
/* ------------------------------------------------------- */ 

#define VIDEOPLAY(u) {\
        .v = (const char *[]){ "/bin/sh", "-c", \
             "pkill -9 mpv ; mpv --really-quiet --gapless-audio \"$0\"", u, NULL \
        } \
}

#define BM_ADD { .v = (char *[]){ "/bin/sh", "-c", \
    "BMKS=\${HOME}/var/files/bookmarks/bookmarks.txt ; \
    (echo `xprop -id $0 _SURF_URI | cut -d '\"' -f 2` && \
    cat \${BMKS}) | sort -u > \${BMKS}_new && \
    mv \${BMKS}_new \${BMKS}", \
    winid, NULL } }

#define GO_HOME { .v = (char *[]){ "/bin/sh", "-c", \
    "xprop -id $0 -f _SURF_GO 8s -set _SURF_GO \
    \${HOME}/usr/startpage/index.html || exit 0", \
    winid, NULL } }

#define YOUTUBEDL {.v = (char *[]){ "/bin/sh", "-c", \
        " kill $(pgrep mpv | grep -v $(pgrep -P $(cat ${HOME}/.cache/mpvbg.pid))) > /dev/null 2>&1 ; \
        mpv --really-quiet $(xprop -id $0 _SURF_URI | cut -d \\\" -f 2) &", \
        winid, NULL } }

/* --------- function to launch arbitrary commands ---------------- */
#define SH(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* ------------------------------------------------------------------ */

// http://git.gnome.org/browse/gtk+/plain/gdk/gdkkeysyms.h
#define MODKEY GDK_CONTROL_MASK
#define SHIFT GDK_SHIFT_MASK
static const Key keys[] = {
    { MODKEY,               GDK_KEY_g,       spawn,      SETPROP("_SURF_URI", "_SURF_GO", PROMPT_GO) },
    { MODKEY|SHIFT,         GDK_KEY_f,   spawn,      SETSEARCH("_SURF_FIND", "_SURF_FIND", PROMPT_FIND) },
    { SHIFT,                GDK_KEY_7,       find,       { .i = +1 } },
    { MODKEY,               GDK_KEY_r,       reload,     { .i = 0 } },
    { 0,                    GDK_KEY_F5,      reload,     { .i = 0 } },
    { 0,                    GDK_KEY_Escape,  stop,       { 0 } },
    { MODKEY,               GDK_KEY_c,       stop,       { 0 } },

    /* ----------------- Custom Functions ---------------------------- */
    { MODKEY,               GDK_KEY_y,      spawn,      YOUTUBEDL },
    { MODKEY|SHIFT,         GDK_KEY_b,      spawn,      BM_ADD },
    { MODKEY,               GDK_KEY_t,      spawn,      SH("python3.6 ${HOME}/etc/suckless-tools/surf/scripts-surf/surf-translate.py \"$(xsel -o)\"") },
    { MODKEY,               GDK_KEY_space,  spawn,      GO_HOME  },
    /* ----------------- End Custom Functions ------------------------ */

    /* ---------------------- History -------------------------------- */
    { MODKEY,               GDK_KEY_o,   navigate,   { .i = +1 } },
    { MODKEY,               GDK_KEY_i,   navigate,   { .i = -1 } },
    /* --------------------------------------------------------------- */

    /* -------------------- Zooming -------------------------------------- */
    { MODKEY,                GDK_KEY_minus,       zoom,       { .i = -1 } },
    { MODKEY,                GDK_KEY_plus,        zoom,       { .i = +1 } },
    { MODKEY,                GDK_KEY_equal,       zoom,       { .i = +1 } },
    { MODKEY,                GDK_KEY_BackSpace,   zoom,       { .i = +0 } },
    { MODKEY|SHIFT,          GDK_KEY_j,           zoom,       { .i = -1 } },
    { MODKEY|SHIFT,          GDK_KEY_k,           zoom,       { .i = +1 } },
    /* ------------------------------------------------------------------- */

    /* ---------------------- vim mode ----------------------------------- */
    { MODKEY,               GDK_KEY_j,      scroll,     { .i = 'd' } },
    { MODKEY,               GDK_KEY_k,      scroll,     { .i = 'u' } },
    { MODKEY,               GDK_KEY_l,      scroll,     { .i = 'r' } },
    { MODKEY,               GDK_KEY_h,      scroll,     { .i = 'l' } },
    { MODKEY,               GDK_KEY_u,      scroll,     { .i = 'U' } },
    { MODKEY,               GDK_KEY_d,      scroll,     { .i = 'D' } },
    /* -------------------------------------------------------------------------- */

    /* --------------------- Toggles -------------------------------------- */
    { MODKEY|SHIFT,          GDK_KEY_s,      toggle,     { .i = JavaScript } },
    { MODKEY|SHIFT,          GDK_KEY_m,      toggle,     { .i = Style } },
    { MODKEY|SHIFT,          GDK_KEY_t,      toggle,     { .i = StrictTLS } },
    { MODKEY|SHIFT,          GDK_KEY_i,      toggle,     { .i = Images } },
    /* --------------------------------------------------------------------------- */
    { MODKEY,                GDK_KEY_p,      print,      { 0 } },
};

/* target can be OnDoc, OnLink, OnImg, OnMedia, OnEdit, OnBar, OnSel, OnAny */
static Button buttons[] = {
    /* target       event mask      button  function        argument        stop event */
    /* { OnLink,       MODKEY,         1,      clicknewwindow, { .i = 1 },     1 }, */
    /* { OnMedia,      MODKEY,         1,      clickexternplayer, { 0 },       1 }, */
    /* { OnAny,        0,              4,      clicknavigate,  { .i = -1 },    1 }, */
    /* { OnAny,        0,              5,      clicknavigate,  { .i = +1 },    1 }, */
    { OnAny,        0,              4,      scroll,  { .i = 'U' },    0 },
    { OnAny,        0,              5,      scroll,  { .i = 'D' },    0 },

};

static Parameter defconfig[ParameterLast] = {
    [FontSize]            =       { { .i = 14 },    },
    [ZoomLevel]           =       { { .f = 1.1 },   },
    [DNSPrefetch]         =       { { .i = 1 },     },
    [JavaScript]          =       { { .i = 1 },     },
    [StrictTLS]           =       { { .i = 1 },     },
    [Style]               =       { { .i = 1 },     },
    [Images]              =       { { .i = 1 },     },
    [WebGL]               =       { { .i = 1 },     },
};
