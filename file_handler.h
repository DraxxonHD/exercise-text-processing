#pragma once

#include <string>

using namespace std;
enum class EPosition
{
	START,
	CURRENT,
	END,
};

class CFile_Handler
{
	public:
		CFile_Handler(string& _FilePath);
		~CFile_Handler();
	
		void WriteTextToFile(
			string _text,
			EPosition _position = EPosition::START,
			long _offset = 0
		);
	
		void PrintFileContent();
		void WipeFileContent();
		string& GetFileContent();
	
	private:
		FILE* m_pFile;
		string& m_FilePath;
		string* m_pReadFile;
};