#include "file_handler.h"
#include "user_input.h"

int main()
{
	std::string* Path = new std::string("knowledge.txt");
	CFile_Handler* pFileHandler = new CFile_Handler(*Path);
	CUser_Input* pUserInput = new CUser_Input();

	pFileHandler->PrintFileContent();

	pFileHandler->WipeFileContent();
	pFileHandler->WriteTextToFile(pUserInput->GetUserInput());

	pFileHandler->PrintFileContent();

	delete pFileHandler;
	delete Path;
	delete pUserInput;
	return 0;
}
