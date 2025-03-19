#include "file_handler.h"
#include <iostream>

CFile_Handler::CFile_Handler(string& _FilePath)
	:m_FilePath(_FilePath)
	, m_pReadFile(nullptr)
	, m_pFile(nullptr)
{
	fopen_s(&m_pFile, _FilePath.c_str(), "r+");
	if (!m_pFile)
	{
		cout << "File cannot be opened!" << endl;
	}
	else
	{
		cout << "File opened!" << endl;
	}
}

CFile_Handler::~CFile_Handler()
{
	if (m_pFile)
	{
		fclose(m_pFile);
	}
	if (nullptr != m_pReadFile)
	{
		delete m_pReadFile;
	}
}

void CFile_Handler::WriteTextToFile(string _text, EPosition _position, long _offset)
{
	if (m_pFile)
	{
		fseek(m_pFile, 0, (int)_position);
		fwrite(_text.c_str(), sizeof(char), _text.size(), m_pFile);
	}
	else
	{
		cout << "File is not opened!" << endl;
	}
}

void CFile_Handler::PrintFileContent()
{
	if (m_pFile)
	{
		fseek(m_pFile, 0, SEEK_END);
		long long* FileSize = new long long(ftell(m_pFile));
		fseek(m_pFile, 0, SEEK_SET);
		if (nullptr != m_pReadFile)
		{
			delete m_pReadFile;
		}
		m_pReadFile = new string(*FileSize, '\0');
		fread(&m_pReadFile->front(), sizeof(char), *FileSize, m_pFile);
		cout << *m_pReadFile << endl;
		delete FileSize;
	}
	else
	{
		cout << "File is not opened!" << endl;
	}
}

void CFile_Handler::WipeFileContent()
{
	if (m_pFile)
	{
		fseek(m_pFile, 0, SEEK_END);
		long FileSize = ftell(m_pFile);
		fseek(m_pFile, 0, SEEK_SET);
		fwrite("", sizeof(char), FileSize, m_pFile);
	}
	else
	{
		cout << "File is not opened!" << endl;
	}
}

string& CFile_Handler::GetFileContent()
{
	if (nullptr != m_pReadFile)
	{

		return *m_pReadFile;
	}
	else
	{
		fseek(m_pFile, 0, SEEK_END);
		long long* FileSize = new long long(ftell(m_pFile));
		fseek(m_pFile, 0, SEEK_SET);
		if (nullptr != m_pReadFile)
		{
			delete m_pReadFile;
		}
		m_pReadFile = new string(*FileSize, '\0');
		fread(&m_pReadFile->front(), sizeof(char), *FileSize, m_pFile);
		return *m_pReadFile;
	}
}
