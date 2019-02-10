
// Chap6_PWG.h: Chap6_PWG 응용 프로그램의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CChap6PWGApp:
// 이 클래스의 구현에 대해서는 Chap6_PWG.cpp을(를) 참조하세요.
//

class CChap6PWGApp : public CWinAppEx
{
public:
	CChap6PWGApp();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChap6PWGApp theApp;
