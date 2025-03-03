#include "file_handler.h"

CFile_Handler::CFile_Handler(const char*& _FilePath)
	:m_FilePath(_FilePath)
	, m_pReadFile(nullptr)
	, m_pFile(nullptr)
{
	fopen_s(&m_pFile, _FilePath, "rb+");
	if (!m_pFile)
	{
		std::cout << "failed to open File";
	}
}

CFile_Handler::~CFile_Handler()
{
	if (m_pReadFile) delete[] m_pReadFile;
	fclose(m_pFile);
}

void CFile_Handler::WriteTextToFile(const char* _text, EPosition _position, long _offset)
{
	int TextLength = strlen(_text);
	fseek(m_pFile, _offset, int(_position));
	fwrite(_text, sizeof(char), TextLength, m_pFile);
}

void CFile_Handler::GetFileContent()
{
	if (m_pReadFile) delete[] m_pReadFile;
	int ContentLength = GetContentLength();
	unsigned char* pBuffer = new unsigned char[ContentLength + 1];
	fseek(m_pFile, 0, SEEK_SET);
	fread(pBuffer, sizeof(unsigned char), ContentLength, m_pFile);
	pBuffer[ContentLength] = unsigned char('\0');
	m_pReadFile = pBuffer;
}

void CFile_Handler::PrintFileContent()
{
	if (!m_pReadFile)
	{
		GetFileContent();
	}
	std::cout << m_pReadFile << "\n";
}

void CFile_Handler::WipeFileContent()
{
	int ContentLength = GetContentLength();
	fseek(m_pFile, 0, SEEK_SET);
	fwrite("", sizeof(char), ContentLength, m_pFile);
}

long long CFile_Handler::GetContentLength()
{
	fseek(m_pFile, 0, SEEK_END);
	return ftell(m_pFile);
}