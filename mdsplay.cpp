/* •¶šƒR[ƒh‚Í‚r‚i‚h‚r ‰üsƒR[ƒh‚Í‚b‚q‚k‚e */
/* $Id$ */

#include <windows.h>
#include <stdio.h>
#include <dshow.h>
#include <comdef.h>

_COM_SMARTPTR_TYPEDEF(IGraphBuilder, IID_IGraphBuilder);
_COM_SMARTPTR_TYPEDEF(IMediaControl, IID_IMediaControl);
_COM_SMARTPTR_TYPEDEF(IMediaEvent, IID_IMediaEvent);

void usage(void);
void PlayMedia(const char *filename) throw(_com_error);
void Message(bool error, const char *fmt, ...);

void usage(void)
{
	Message(false,
		"Minimal DirectShow Player 1.0.0\n"
		"Copyright (c) 2013 UMEZAWA Takeshi\n\n"
		"Licensed under GNU General Public License version 2 or later.\n");
	exit(255);
}

#ifdef CONSOLE
int main(int, char **)
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	if (__argc != 2)
		usage();

	try
	{
		PlayMedia(__argv[1]);
		return 0;
	}
	catch (_com_error e)
	{
		Message(true, "Cannot play media: %s\n", __argv[0], e.ErrorMessage());
		return 1;
	}
}

void PlayMedia(const char *pszFileName) throw(_com_error)
{
	HRESULT hr;
	IGraphBuilderPtr pGraphBuilder;
	IMediaControlPtr pMediaControl;
	IMediaEventPtr pMediaEvent;
	WCHAR wszFileName[MAX_PATH];
	LONG lEventCode;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	pGraphBuilder.CreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC);

	wsprintfW(wszFileName, L"%S", pszFileName);
	hr = pGraphBuilder->RenderFile(wszFileName, NULL);
	if (!SUCCEEDED(hr))
		_com_raise_error(hr);

	pMediaControl = pGraphBuilder;
	pMediaEvent = pGraphBuilder;

	hr = pMediaControl->Run();
	if (!SUCCEEDED(hr))
		_com_raise_error(hr);

	hr = pMediaEvent->WaitForCompletion(INFINITE, &lEventCode);
	if (!SUCCEEDED(hr))
		_com_raise_error(hr);
}

void Message(bool error, const char *fmt, ...)
{
	va_list args;
	char buf[256];

	va_start(args, fmt);
	vsnprintf(buf, _countof(buf), fmt, args);
	va_end(args);

#ifdef CONSOLE
	fprintf(stderr, "%s", buf);
#else
	MessageBox(NULL, buf, "Minimal DirectShow Player", error ? MB_ICONERROR : MB_OK);
#endif
}
