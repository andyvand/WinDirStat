// ModalApiShuttle.cpp	- Implementation of CModalApiShuttle
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

#include "stdafx.h"
#include "windirstat.h"
#include "ModalApiShuttle.h"


IMPLEMENT_DYNAMIC(CModalApiShuttle, CDialog)

CModalApiShuttle::CModalApiShuttle(CWnd* pParent /*=NULL*/)
	: CDialog(CModalApiShuttle::IDD, pParent)
{
}

CModalApiShuttle::~CModalApiShuttle()
{
}

BEGIN_MESSAGE_MAP(CModalApiShuttle, CDialog)
END_MESSAGE_MAP()


BOOL CModalApiShuttle::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc;
	AfxGetMainWnd()->GetWindowRect(rc);
	rc.right= rc.left;
	rc.bottom= rc.top;

	MoveWindow(rc, false);

	EnableWindow(true);
	ShowWindow(SW_SHOW);

	DoOperation();

	EndDialog(IDOK);
	return TRUE;
}
