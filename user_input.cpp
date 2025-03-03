#include "user_input.h"
#include <iostream>
#include <string>

CUser_Iput::CUser_Iput()
    : m_pUserInput(nullptr)
{
}

CUser_Iput::~CUser_Iput()
{
    if (m_pUserInput) delete[] m_pUserInput;
}

void CUser_Iput::Fetch_User_Input()
{
    std::string input;
    std::cin >> input;
    int InputLength = input.length()+1;
    m_pUserInput = new char[InputLength];
    strcpy_s(m_pUserInput, InputLength, input.c_str());
}

const char* CUser_Iput::GetUserInput()
{
    return const_cast<char*> (m_pUserInput);
}

bool CUser_Iput::CheckInput()
{
    return false;
}
