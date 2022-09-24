/*
Copyright (c) 2017 Ahmad Bashar Eter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//#pragma once
//#define _WINGDIAPI_
//#include <windows.h> 
//#include "C:\MinGW\include\windows.h"

/* 
  @raysan5: To avoid conflicting windows.h symbols with raylib, some flags are defined
  WARNING: Those flags avoid inclusion of some Win32 headers that could be required 
  by user at some point and won't be included...
*/

/* If defined, the following flags inhibit definition of the indicated items.*/
//#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
//#define NOVIRTUALKEYCODES // VK_*
//#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
//#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
//#define NOSYSMETRICS      // SM_*
//#define NOMENUS           // MF_*
//#define NOICONS           // IDI_*
//#define NOKEYSTATES       // MK_*
//#define NOSYSCOMMANDS     // SC_*
//#define NORASTEROPS       // Binary and Tertiary raster ops
//#define NOSHOWWINDOW      // SW_*
//#define OEMRESOURCE       // OEM Resource values
//#define NOATOM            // Atom Manager routines
//#define NOCLIPBOARD       // Clipboard routines
//#define NOCOLOR           // Screen colors
//#define NOCTLMGR          // Control and Dialog routines
//#define NODRAWTEXT        // DrawText() and DT_*
#define NOGDI             // All GDI defines and routines
//#define NOKERNEL          // All KERNEL defines and routines
#define NOUSER            // All USER defines and routines
/*#define NONLS             // All NLS defines and routines*/
//#define NOMB              // MB_* and MessageBox()
//#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
//#define NOMETAFILE        // typedef METAFILEPICT
//#define NOMINMAX          // Macros min(a,b) and max(a,b)
//#define NOMSG             // typedef MSG and associated routines
//#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
//#define NOSCROLL          // SB_* and scrolling routines
//#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
//#define NOSOUND           // Sound driver routines
//#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
//#define NOWH              // SetWindowsHook and WH_*
//#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
//#define NOCOMM            // COMM driver routines
//#define NOKANJI           // Kanji support stuff.
//#define NOHELP            // Help engine interface.
//#define NOPROFILER        // Profiler interface.
//#define NODEFERWINDOWPOS  // DeferWindowPos routines
//#define NOMCX             // Modem Configuration Extensions

/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include <windows.h>

/* Type required by some unused function...  */
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

//#include <objbase.h>
//#include <mmreg.h>
//#include <mmsystem.h>


/* @raysan5: Some required types defined for MSVC/TinyC compiler */
// #if defined(_MSC_VER) || defined(__TINYC__)
//     #include "propidl.h"
// #endif






// #include "C:/MinGW/include/winnt.h"
// #include "C:/MinGW/include/winbase.h"
// #include "C:/MinGW/include/winuser.h"
// #include "C:/MinGW/lib/gcc/mingw32/6.3.0/include/stddef.h"
// #include "C:/MinGW/include/windef.h"
// #include "C:/MinGW/include/string.h"


#define CP_BOUD_RATE_9600 CBR_9600
#define CP_BOUD_RATE_1155 1155
#define CP_BOUD_RATE_4800 CBR_4800
#define CP_BOUD_RATE_19200 CBR_19200

#define CP_DATA_BITS_5 5
#define CP_DATA_BITS_6 6
#define CP_DATA_BITS_7 7
#define CP_DATA_BITS_8 8

#define CP_STOP_BITS_ONE ONESTOPBIT
#define CP_STOP_BITS_TWO TWOSTOPBITS
#define CP_STOP_BITS_ONE_AND_HALF ONE5STOPBITS

#define CP_PARITY_NOPARITY NOPARITY
#define CP_PARITY_ODD ODDPARITY
#define CP_PARITY_EVEN EVENPARITY
#define CP_PARITY_MARK MARKPARITY
#define CP_PARITY_SPACE SPACEPARITY

typedef HANDLE PORT;

// Open com serial port specified by idx.
// returns a handel to the opend port.
// On error returns NULL
PORT OpenPort(int idx);

// Close the handel of the opend port
void ClosePort(PORT com_port);

// Set the boud rate of the specified com_port.
// Returns TRUE if the operation done successfully otherwise returns FALSE.
// NOTE: You can use the values of CP_BOUD_RATE... to feed the rate parameter.
int SetPortBoudRate(PORT com_port, int rate);

// Set the data bits of the specified com_port.
// Returns TRUE if the operation done successfully otherwise returns FALSE.
// NOTE: You can use the values of CP_DATA_BITS... to feed the databits parameter.
// NOTE: Becafrul what you send if you set this other than 8 bits.
int SetPortDataBits(PORT com_port, int databits);

// Set the stop bits of the specified com_port.
// Returns TRUE if the operation done successfully otherwise returns FALSE.
// NOTE: Use the values of CP_STOP_BITS... to feed the stopbits parameter.
int SetPortStopBits(PORT com_port, int stopbits);

// Set the parity type of the specified com_port.
// Returns TRUE if the operation done successfully otherwise returns FALSE.
// NOTE: Use the values of CP_PARITY... to feed the parity parameter.
int SetPortParity(PORT com_port, int parity);

// Get the boud rate of the specified com_port.
int GetPortBoudRate(PORT com_port);

// Get the data bits of the specified com_port.
int GetPortDataBits(PORT com_port);

// Get the stop bits of the specified com_port.
int GetPortStopBits(PORT com_port);

// Get the parity of the specified com_port.
int GetPortParity(PORT com_port);

// Send charchter data throw the com_port.
int SendData(PORT com_port,const char * data);

// Recive charchter data that have been sent throw the com_port.
int ReciveData(PORT com_port, char * databuffer,int bufferlen);


