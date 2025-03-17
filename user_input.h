#pragma once
#include <string>

using namespace std;

class CUser_Input
{
	public:
		CUser_Input();
		~CUser_Input();

		string& GetUserInput();

	private:
		void Fetch_User_Input();
		bool Empty() const;

	private:
		 string* m_pUserInput;
};