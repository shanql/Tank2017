
// MapEditor.h : MapEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMapEditorApp:
// �йش����ʵ�֣������ MapEditor.cpp
//

class CMapEditorApp : public CWinApp
{
public:
	CMapEditorApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

extern CMapEditorApp theApp;
