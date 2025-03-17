#include "user_input.h"
#include <iostream>

CUser_Input::CUser_Input()
	: m_pUserInput(nullptr)
{
}

CUser_Input::~CUser_Input()
{
	if (nullptr != m_pUserInput)
	{
		delete m_pUserInput;
	}
}

void CUser_Input::Fetch_User_Input()
{
	if (nullptr != m_pUserInput)
	{
		delete m_pUserInput;
	}
	m_pUserInput = new string();
	getline(cin, *m_pUserInput);
}

string& CUser_Input::GetUserInput()
{
	if (Empty())
	{
		Fetch_User_Input();
	}
	return *m_pUserInput;
}

bool CUser_Input::Empty() const
{
	return nullptr == m_pUserInput || m_pUserInput->empty();
}
