// windirstat.h	- Main header for the windirstat application
//
// WinDirStat - Directory Statistics
// Copyright (C) 2003 Bernhard Seifert
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Author: bseifert@users.sourceforge.net, bseifert@daccord.net

#pragma once

#include "resource.h" 
#include "myimagelist.h"
#include "osspecific.h"
#include "globalhelpers.h"
#include "options.h"
#include "mountpoints.h"
#include "helpmap.h"

typedef CMap<CString, LPCTSTR, COLORREF, COLORREF> CExtensionColorMap;	// ".bmp" -> color

class CMainFrame;
class CDirstatApp;

// Frequently used "globals"
CMainFrame *GetMainFrame();
CDirstatApp *GetApp();
CMyImageList *GetMyImageList();

// Other application related globals
CString GetAuthorEmail();
CString GetWinDirStatHomepage();

void AddRidge(const CRect& rc, double *surface, double h);
void RenderRectangle(CDC *pdc, const CRect& rc, const double *surface, COLORREF col);
void RenderCushion(CDC *pdc, const CRect& rc, const double *surface, COLORREF col);

//
// CDirstatApp. The MFC application object. 
// Knows about RAM Usage, Mount points, Help files and the CMyImageList.
//
class CDirstatApp : public CWinApp
{
public:
	CDirstatApp();
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	LANGID GetBuiltInLanguage() ;
	LANGID GetLangid();

	void ReReadMountPoints();
	bool IsMountPoint(CString path);

	CString GetCurrentProcessMemoryInfo();

	CMyImageList *GetMyImageList();
	void UpdateRamUsage();

	void DoContextHelp(DWORD topic);

	void GetAvailableResourceDllLangids(CArray<LANGID, LANGID>& arr);

protected:
	CString FindResourceDllPathByLangid(LANGID& langid);
	CString FindHelpfilePathByLangid(LANGID langid);
	CString FindAuxiliaryFileByLangid(LPCTSTR prefix, LPCTSTR suffix, LANGID& langid, bool checkResource);
	bool ScanResourceDllName(LPCTSTR name, LANGID& langid);
	bool ScanAuxiliaryFileName(LPCTSTR prefix, LPCTSTR suffix, LPCTSTR name, LANGID& langid);
	#ifdef _DEBUG
		void TestScanResourceDllName();
	#endif
	bool IsCorrectResourceDll(LPCTSTR path);

	CString ConstructHelpFileName();
	
	bool UpdateMemoryInfo();

	virtual BOOL OnIdle(LONG lCount);		// This is, where scanning is done.

	CSingleDocTemplate* m_pDocTemplate;		// MFC voodoo.

	LANGID m_langid;						// Language we are running
	CMountPoints m_mountPoints;				// Mount point information
	CMyImageList m_myImageList;				// Out central image list
	CPsapi m_psapi;							// Dynamically linked psapi.dll (for RAM usage)
	LONGLONG m_workingSet;					// Current working set (RAM usage)
	LONGLONG m_pageFaults;					// Page faults so far (unused)

	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
	afx_msg void OnHelpManual();
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateHelpReportbug(CCmdUI *pCmdUI);
	afx_msg void OnHelpReportbug();
};
