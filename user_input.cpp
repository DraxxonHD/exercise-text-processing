#include "user_input.h"
#include <iostream>

CUser_Input::CUser_Input()
	:m_pUserInput("")
{
}

CUser_Input::~CUser_Input()
{
	m_pUserInput.clear();
}

void CUser_Input::Fetch_User_Input()
{
	getline(cin, m_pUserInput);
}

string CUser_Input::GetUserInput()
{
	return m_pUserInput;
}

bool CUser_Input::InputEmpty()
{
	return m_pUserInput.empty();
}
