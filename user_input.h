#pragma once


class CUser_Iput
{
	public:
		CUser_Iput();
		~CUser_Iput();
		void Fetch_User_Input();

		const char* GetUserInput();

	private:
		bool CheckInput();

	private:
		char* m_pUserInput;
};