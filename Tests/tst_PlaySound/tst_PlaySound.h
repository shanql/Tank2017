
// tst_PlaySound.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctst_PlaySoundApp:
// �йش����ʵ�֣������ tst_PlaySound.cpp
//

class Ctst_PlaySoundApp : public CWinApp
{
public:
	Ctst_PlaySoundApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctst_PlaySoundApp theApp;