#pragma once

#include <iostream>

enum class EPosition
{
	START,
	CURRENT,
	END,
};

class CFile_Handler
{
	public:
		CFile_Handler(const char*& _FilePath);
		~CFile_Handler();
	
		void WriteTextToFile(
			const char* _text,
			EPosition _position = EPosition::START,
			long _offset = 0
		);
	
		void PrintFileContent();
		void WipeFileContent();
	private:
		void GetFileContent();
		long long GetContentLength();
	
	private:
		FILE* m_pFile;
		const char* m_FilePath;
		unsigned char* m_pReadFile;
};