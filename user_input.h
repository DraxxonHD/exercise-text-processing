#pragma once
#include <string>

using namespace std;

class CUser_Input
{
	public:
		CUser_Input();
		~CUser_Input();
		void Fetch_User_Input();

		string GetUserInput();

	private:
		bool InputEmpty();

	private:
		 string m_pUserInput;
};