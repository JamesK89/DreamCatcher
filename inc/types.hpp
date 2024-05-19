#ifndef _INCLUDE_DREAMCATCHER_TYPES_H_
#define _INCLUDE_DREAMCATCHER_TYPES_H_

typedef unsigned char DFBYTE;
typedef unsigned short DFWORD;
typedef signed short DFSWORD;
typedef unsigned long DFDWORD;
typedef signed long DFSDWORD;
typedef unsigned long long DFQWORD;
typedef signed long long DFSQWORD;

typedef HBITMAP (WINAPI *LpfnWin32CreateBitmap)(HDC hdc, BITMAPINFO* bmi, void** bits);
typedef HDC (WINAPI *LpfnWin32CreateDC)(LPCSTR lpszDriver, LPCSTR lpszDevice, LPCSTR lpszOutput, const DEVMODEA* lpInitData);
typedef UINT (WINAPI *LpfnWin32SetDIBColorTable)(HDC hdc, UINT iStart, UINT cEntries, const RGBQUAD* prgbq);
typedef BOOL (WINAPI *LpfnWin32BitBlt)(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);

typedef HBITMAP (WINAPI *LpfnGdi32CreateDIBSection)(HDC hdc, const BITMAPINFO* pbmi, UINT usage, VOID** ppvBits, HANDLE hSection, DWORD offset);
typedef UINT (WINAPI *LpfnGdi32SetDIBColorTable)(HDC hdc, UINT iStart, UINT cEntries, const RGBQUAD* prgbq);

typedef BOOL (WINAPI *LpfnGetVersionExA)(LPOSVERSIONINFOA lpVersionInformation);

typedef enum : WORD {
	unknownkind = 0,
	actorkind,
	propkind,
	scenekind,
	flatkind
} DF_Kind;

typedef enum : WORD {
	_endmarker = 0x0,
	_unknown = 0x1,
	_logic = 0x2,
	_text = 0x3,
	_number = 0x4,
	_name = 0x5,
	_retmarker = 0x6,
	___minreserved___ = 0xfa0,
	_code = 0xfa1,
	_global = 0xfa2,
	_local = 0xfa3,
	_endcode = 0xfa4,
	_exitcode = 0xfa5,
	_if = 0xfa6,
	_endif = 0xfa7,
	_else = 0xfa8,
	_switch = 0xfa9,
	_endswitch = 0xfaa,
	_case = 0xfab,
	_for = 0xfac,
	_to = 0xfad,
	_step = 0xfae,
	_endfor = 0xfaf,
	_while = 0xfb0,
	_endwhile = 0xfb1,
	_leftparn = 0xfb2,
	_rightparn = 0xfb3,
	_comma = 0xfb4,
	_true = 0xfb5,
	_false = 0xfb6,
	_not = 0xfb7,
	_return = 0xfb8,
	_passcode = 0xfb9,
	_me = 0xfba,
	_target = 0xfbb,
	_dumplocal = 0xfbc,
	_dumpglobal = 0xfbd,
	_permanent = 0xfbe,
	_dumppermanent = 0xfbf,
	___maxreserved___ = 0xfc0,
	___minoperator___ = 0x1f40,
	_plus = 0x1f41,
	_minus = 0x1f42,
	_times = 0x1f43,
	_divide = 0x1f44,
	_and = 0x1f45,
	_or = 0x1f46,
	_concat = 0x1f47,
	_equal = 0x1f48,
	_notequal = 0x1f49,
	_greater = 0x1f4a,
	_less = 0x1f4b,
	_greatequal = 0x1f4c,
	_lessequal = 0x1f4d,
	___maxoperator___ = 0x1f4e,
	___mincommand___ = 0x2ee0,
	_message = 0x2ee1,
	_hidecursor = 0x2ee2,
	_showcursor = 0x2ee3,
	_delay = 0x2ee4,
	_makeloop = 0x2ee5,
	_walktostar = 0x2ee6,
	_makeball = 0x2ee7,
	_exportclut = 0x2ee8,
	_visualeffect = 0x2ee9,
	_stopwalk = 0x2eea,
	_stoploop = 0x2eeb,
	_stopball = 0x2eec,
	_opencastfile = 0x2eed,
	_closecastfile = 0x2eee,
	_actorscript = 0x2eef,
	_sendtoactor = 0x2ef0,
	_playmovie = 0x2ef1,
	_openpuppetfile = 0x2ef2,
	_opentrackfile = 0x2ef3,
	_closetrackfile = 0x2ef4,
	_playtheme = 0x2ef5,
	_singlesound = 0x2ef6,
	_multiplesound = 0x2ef7,
	_dualsound = 0x2ef8,
	_bothsound = 0x2ef9,
	_voicesound = 0x2efa,
	_plugin = 0x2efb,
	_haltsound = 0x2efc,
	_halttheme = 0x2efd,
	_haltvoice = 0x2efe,
	_bootscript = 0x2eff,
	_opensetfile = 0x2f00,
	_closesetfile = 0x2f01,
	_sendtoscene = 0x2f02,
	_setscript = 0x2f03,
	_scenescript = 0x2f04,
	_paintingscript = 0x2f05,
	_clut = 0x2f06,
	_cursor = 0x2f07,
	_debugger = 0x2f08,
	_puppetclear = 0x2f09,
	_closepuppetfile = 0x2f0a,
	_puppetspeak = 0x2f0b,
	_puppetbevel = 0x2f0c,
	_sendtopuppet = 0x2f0d,
	_puppetscript = 0x2f0e,
	_castscript = 0x2f0f,
	_sendtocast = 0x2f10,
	_blacktoscreen = 0x2f11,
	_screentoblack = 0x2f12,
	_blackscreen = 0x2f13,
	_forceupdate = 0x2f14,
	_error = 0x2f15,
	_propscript = 0x2f16,
	_sendtoprop = 0x2f17,
	_openshopfile = 0x2f18,
	_closeshopfile = 0x2f19,
	_shopscript = 0x2f1a,
	_sendtoshop = 0x2f1b,
	_openstagefile = 0x2f1c,
	_closestagefile = 0x2f1d,
	_gotoflat = 0x2f1e,
	_stagescript = 0x2f1f,
	_flatscript = 0x2f20,
	_buttonscript = 0x2f21,
	_sendtopainting = 0x2f22,
	_sendtoset = 0x2f23,
	_sendtobutton = 0x2f24,
	_sendtoflat = 0x2f25,
	_sendtostage = 0x2f26,
	_quit = 0x2f27,
	_turntodeg = 0x2f28,
	_flushevents = 0x2f29,
	_puppetgrab = 0x2f2a,
	_actorinstance = 0x2f2b,
	_propinstance = 0x2f2c,
	_savegame = 0x2f2d,
	_opengame = 0x2f2e,
	_notedialog = 0x2f2f,
	_drawstring = 0x2f30,
	_sendtoboot = 0x2f31,
	_mixclut = 0x2f32,
	_puppetscramble = 0x2f33,
	_puppetsubtitle = 0x2f34,
	_actorwarm = 0x2f35,
	_propwarm = 0x2f36,
	_shopwarm = 0x2f37,
	_castwarm = 0x2f38,
	_postscript = 0x2f39,
	_sendtopost = 0x2f3a,
	_serverscript = 0x2f3b,
	_sendtoserver = 0x2f3c,
	_actordelete = 0x2f3d,
	_propdelete = 0x2f3e,
	_netconnect = 0x2f3f,
	_netdisconnect = 0x2f40,
	_netbroadcast = 0x2f41,
	_netjoingroup = 0x2f42,
	_netleavegroup = 0x2f43,
	_walkonpath = 0x2f44,
	_walktoxyz = 0x2f45,
	_walkonroad = 0x2f46,
	_walkonframes = 0x2f47,
	_actorhide = 0x2f48,
	_prophide = 0x2f49,
	_reboot = 0x2f4a,
	_actorlock = 0x2f4b,
	_proplock = 0x2f4c,
	_shoplock = 0x2f4d,
	_castlock = 0x2f4e,
	_actorsound = 0x2f4f,
	_propsound = 0x2f50,
	_deletefile = 0x2f51,
	_buildfilenames = 0x2f52,
	___maxcommand___ = 0x2f53,
	___mindualpurp___ = 0x3e80,
	_actorvisible = 0x3e81,
	_actordeg = 0x3e82,
	_actorxyz = 0x3e83,
	_actorxy = 0x3e84,
	_actoris3d = 0x3e85,
	_actorstar = 0x3e86,
	_setvisible = 0x3e87,
	_stagevisible = 0x3e88,
	_path = 0x3e89,
	_result = 0x3e8a,
	_currentdir = 0x3e8b,
	_actordist = 0x3e8c,
	_propdist = 0x3e8d,
	_actorpose = 0x3e8e,
	_propvisible = 0x3e8f,
	_propdeg = 0x3e90,
	_propxyz = 0x3e91,
	_propxy = 0x3e92,
	_propis3d = 0x3e93,
	_propstar = 0x3e94,
	_actorset = 0x3e95,
	_framerate = 0x3e96,
	_actorspeed = 0x3e97,
	_actorscale = 0x3e98,
	_propview = 0x3e99,
	_propspeed = 0x3e9a,
	_propset = 0x3e9b,
	_propscale = 0x3e9c,
	_currentscene = 0x3e9d,
	_variable = 0x3e9e,
	_currentdeg = 0x3e9f,
	_propowner = 0x3ea0,
	_wavevolume = 0x3ea1,
	_currentcd = 0x3ea2,
	_camerahi = 0x3ea3,
	_actorturn = 0x3ea4,
	_menuvisible = 0x3ea5,
	_soundpan = 0x3ea6,
	_soundloop = 0x3ea7,
	_soundvol = 0x3ea8,
	_themevol = 0x3ea9,
	_propvalue = 0x3eaa,
	_actorowner = 0x3eab,
	_actorvalue = 0x3eac,
	_keyaborts = 0x3ead,
	_pauseloop = 0x3eae,
	_pauseball = 0x3eaf,
	_pausewalk = 0x3eb0,
	_puppetparam = 0x3eb1,
	_puppetvisible = 0x3eb2,
	_actorzclip = 0x3eb3,
	_propzclip = 0x3eb4,
	_puppetbase = 0x3eb5,
	_themepan = 0x3eb6,
	_setparam = 0x3eb7,
	_stageparam = 0x3eb8,
	___maxdualpurp___ = 0x3eb9,
	___minfunction___ = 0x4e20,
	_random = 0x4e21,
	_pointx = 0x4e22,
	_pointy = 0x4e23,
	_makepoint = 0x4e24,
	_button = 0x4e25,
	_mouse = 0x4e26,
	_stilldown = 0x4e27,
	_tick = 0x4e28,
	_iswalk = 0x4e29,
	_isloop = 0x4e2a,
	_isball = 0x4e2b,
	_countactors = 0x4e2c,
	_indextoactor = 0x4e2d,
	_countsounds = 0x4e2e,
	_indextosound = 0x4e2f,
	_sounddone = 0x4e30,
	_pointinpainting = 0x4e31,
	_countpaintings = 0x4e32,
	_countscenes = 0x4e33,
	_indextoscene = 0x4e34,
	_sendtopostfx = 0x4e35,
	_indextopainting = 0x4e36,
	_actorexists = 0x4e37,
	_propexists = 0x4e38,
	_stringtonum = 0x4e39,
	_numtostring = 0x4e3a,
	_freemem = 0x4e3b,
	_puppetevent = 0x4e3c,
	_countcasts = 0x4e3d,
	_indextocast = 0x4e3e,
	_countprops = 0x4e3f,
	_indextoprop = 0x4e40,
	_countshops = 0x4e41,
	_indextoshop = 0x4e42,
	_countflats = 0x4e43,
	_indextoflat = 0x4e44,
	_flattoindex = 0x4e45,
	_currentflat = 0x4e46,
	_pointinactor = 0x4e47,
	_pointinprop = 0x4e48,
	_pointinset = 0x4e49,
	_pointinstage = 0x4e4a,
	_pointinbutton = 0x4e4b,
	_countbuttons = 0x4e4c,
	_indextobutton = 0x4e4d,
	_countpuppets = 0x4e4e,
	_indextopuppet = 0x4e4f,
	_currentstage = 0x4e50,
	_currentpuppet = 0x4e51,
	_type = 0x4e52,
	_countglobals = 0x4e53,
	_indextoglobal = 0x4e54,
	_currentset = 0x4e55,
	_findword = 0x4e56,
	_substring = 0x4e57,
	_stringlength = 0x4e58,
	_putword = 0x4e59,
	_optionkey = 0x4e5a,
	_shiftkey = 0x4e5b,
	_commandkey = 0x4e5c,
	_calcvectx = 0x4e5d,
	_calcvecty = 0x4e5e,
	_cameraxyz = 0x4e5f,
	_playerxyz = 0x4e60,
	_machinetype = 0x4e61,
	_machinespeed = 0x4e62,
	_fileexists = 0x4e63,
	_questiondialog = 0x4e64,
	_textdialog = 0x4e65,
	_hittest = 0x4e66,
	_calcdeg = 0x4e67,
	_calcturn = 0x4e68,
	_starxyz = 0x4e69,
	_frame = 0x4e6a,
	_counttracks = 0x4e6b,
	_indextotrack = 0x4e6c,
	_currentsound = 0x4e6d,
	_currentvoice = 0x4e6e,
	_currenttheme = 0x4e6f,
	_soundrate = 0x4e70,
	_calcdist = 0x4e71,
	_calcmod = 0x4e72,
	_actionframe = 0x4e73,
	_sendtoactorfx = 0x4e74,
	_sendtoscenefx = 0x4e75,
	_sendtopuppetfx = 0x4e76,
	_sendtocastfx = 0x4e77,
	_sendtopropfx = 0x4e78,
	_sendtoshopfx = 0x4e79,
	_sendtopaintingfx = 0x4e7a,
	_sendtosetfx = 0x4e7b,
	_sendtobuttonfx = 0x4e7c,
	_sendtoflatfx = 0x4e7d,
	_sendtostagefx = 0x4e7e,
	_sendtobootfx = 0x4e7f,
	_scenexyz = 0x4e80,
	_voicedone = 0x4e81,
	_pluginfx = 0x4e82,
	_walkdest = 0x4e83,
	_sendtoserverfx = 0x4e84,
	_indextoball = 0x4e85,
	_indextoloop = 0x4e86,
	_indextowalk = 0x4e87,
	_countballs = 0x4e88,
	_countloops = 0x4e89,
	_countwalks = 0x4e8a,
	_countbevels = 0x4e8b,
	_sqrtx = 0x4e8c,
	_pluginexists = 0x4e8d,
	_networkon = 0x4e8e,
	_netcountmembers = 0x4e8f,
	_netindextomember = 0x4e90,
	_netourid = 0x4e91,
	_netmessagesender = 0x4e92,
	_netmessagegroup = 0x4e93,
	_roadahead = 0x4e94,
	_stringwidth = 0x4e95,
	_countviews = 0x4e96,
	_indextoview = 0x4e97,
	_sysmem = 0x4e98,
	_heapsize = 0x4e99,
	_spacebar = 0x4e9a,
	_countpermanents = 0x4e9b,
	_indextopermanent = 0x4e9c,
	_volumename = 0x4e9d,
	_filename = 0x4e9e,
	_diskspace = 0x4e9f,
	_countfilenames = 0x4ea0,
	_indextofilename = 0x4ea1,
	_isdebugging = 0x4ea2,
	_actororder = 0x4ea3,
	_proporder = 0x4ea4,
	___maxfunction___ = 0x4ea5,
	___mineffect___ = 0x5dc0,
	_barndoorclose = 0x5dc1,
	_barndooropen = 0x5dc2,
	_irisclose = 0x5dc3,
	_irisopen = 0x5dc4,
	_scrolldown = 0x5dc5,
	_scrollup = 0x5dc6,
	_scrollright = 0x5dc7,
	_scrolleft = 0x5dc8,
	_venetian = 0x5dc9,
	_wipedown = 0x5dca,
	_wipeup = 0x5dcb,
	_wiperight = 0x5dcc,
	_wipeleft = 0x5dcd,
	_plain = 0x5dce,
	_turnright = 0x5dcf,
	_turnleft = 0x5dd0,
	_turnup = 0x5dd1,
	_turndown = 0x5dd2,
	_nodraw = 0x5dd3,
	___maxeffect___ = 0x5dd4
} DF_ScriptNames;

typedef struct df_filedata_t
{
	WORD refnum;
	DWORD cursorpos;
	WORD canasync;
} DF_FileData;

typedef struct df_rect_t
{
	WORD top;
	WORD left;
	WORD bottom;
	WORD right;
} DF_Rect;

typedef struct df_point_t
{
	WORD v;
	WORD h;
} DF_Point;

typedef struct df_posit_t
{
	WORD pic;
	POINT pos;
} DF_Posit;

typedef struct df_rgbcolor_t
{
	WORD red;
	WORD green;
	WORD blue;
} DF_RGBColor;

typedef struct df_freeobject_t
{
	DWORD off;
	DWORD size;
} DF_FreeObject;

#define DF_CacheInfo_OffsetSize 128

typedef struct df_cacheinfo_t
{
	DWORD page;
	DWORD time;
	WORD changed;
	DWORD offsets[DF_CacheInfo_OffsetSize];
} DF_CacheInfo;

#define DF_StarHead_FillerSize 118
#define DF_StarHead_FreeListSize 64

typedef struct df_starhead_t
{
	DWORD version;
	DWORD filesize;
	DWORD freesize;
	DWORD numfree;
	DWORD dirobjects;
	DWORD numobjects;
	DWORD delobjects;
	DWORD delchain;
	DWORD filetype;
	DWORD filecreator;
	DWORD filler[DF_StarHead_FillerSize];
	DF_FreeObject freelist[DF_StarHead_FreeListSize];
} DF_StarHead;

#define DF_StarPath_FileNameSize 256

typedef struct df_starpath_t DF_StarPath;

typedef struct df_starpath_t
{
	DF_FileData thefile;
	char pathname[DF_StarPath_FileNameSize];
	DF_StarHead filehead;
	DWORD seed;
	WORD numcache;
	DF_CacheInfo* offcache;
	WORD needsflush;
	DWORD fileid;
	DWORD numvir;
	DWORD actvir;
	DWORD virque;
	DF_StarPath* nextstar;
	DWORD filetype;
	WORD islocked;
	WORD isclosed;
	DF_StarPath* nextclosed;
} DF_StarPath;

typedef struct df_xyzd_t
{
	WORD deg;
	WORD x;
	WORD y;
	WORD z;
} DF_XYZD;

typedef struct df_surface_t
{
	HDC hdc;
	HPEN pen;
	HBRUSH brush;
	HBRUSH backbrush;
	COLORREF forecol;
	DWORD forecolindex;
	COLORREF backcol;
	DWORD backcolindex;
	char pat[8];
	DWORD pensize;
	DWORD penmode;
	DWORD posh;
	DWORD posv;
	DWORD fontnum;
	DWORD fontsize;
	HFONT font;
	DWORD pendirty;
	DWORD fontdirty;
	DWORD patsolid;
	DF_Point origin;
	DWORD unknown;
} DF_Surface;

typedef struct df_bitmap_t
{
	WORD height;
	WORD rowbytes;
	char* baseaddr;
	HBITMAP hbm;
	DF_Surface s;
} DF_Bitmap;

typedef struct df_window_t
{
	HWND hwnd;
	HDC hdc;
	DF_Surface surface;
} DF_Window;

#define DF_GraphData_UnknownSize 100

typedef struct df_graphdata_t
{
	DF_Window* thewind;
	char unknown[DF_GraphData_UnknownSize];
} DF_GraphData;


typedef struct method_info_t
{
	const char* methodName;
	const void** callAddresses;
	const void* newAddress;
	const void* oldAddress;
	struct method_info_t* next;
} MethodInfo;

typedef struct global_state_t
{
	HINSTANCE appInstance;
	HINSTANCE dllInstance;

	FILE* console;

	HWND* mainWindowHandle;
	DF_Window** windows;
	DWORD* numWindows;
	DWORD** unknownWindowValues;

	HMODULE* hGdi;

	HDC* deviceContext;

	BITMAPINFO* clutbmih;

	DWORD* isOSBuildNumberTwo;
	DWORD* isWinGFuncPtrAcquired;

	LpfnWin32CreateBitmap* win32CreateBitmap;
	LpfnWin32CreateDC* win32CreateDC;
	LpfnWin32SetDIBColorTable* win32SetDIBColorTable;
	LpfnWin32BitBlt* win32BitBlt;

	LpfnGdi32CreateDIBSection* gdi32CreateDIBSection;
	LpfnGdi32SetDIBColorTable* gdi32SetDIBColorTable;

	MethodInfo* pMethodInfoList;
} GlobalState;

extern GlobalState Global;

#endif