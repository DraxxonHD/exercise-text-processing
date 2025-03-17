#include "file_handler.h"
#include "user_input.h"

int main()
{
	std::string* Path = new std::string("knowledge.txt");
	CFile_Handler* pFileHandler = new CFile_Handler(*Path);

	pFileHandler->PrintFileContent();

	 



	pFileHandler->WipeFileContent();
	pFileHandler->WriteTextToFile("Testing input");

	pFileHandler->PrintFileContent();

	delete pFileHandler;
	delete Path;
	return 0;
}
