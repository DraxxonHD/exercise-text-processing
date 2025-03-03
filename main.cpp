#include "file_handler.h"


int main()
{
	const char* Path = "knowledge.txt";
	CFile_Handler* pFileHandler = new CFile_Handler(Path);

	pFileHandler->PrintFileContent();


	delete pFileHandler;
	return 0;
}
