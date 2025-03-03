#include "file_handler.h"
#include "user_input.h"

int main()
{
	const char* Path = "knowledge.txt";
	CFile_Handler* pFileHandler = new CFile_Handler(Path);

	pFileHandler->PrintFileContent();

	CUser_Iput* pInput = new CUser_Iput();

	pInput->Fetch_User_Input();

	pFileHandler->WipeFileContent();
	pFileHandler->WriteTextToFile(pInput->GetUserInput());

	pFileHandler->PrintFileContent();

	delete pInput;
	delete pFileHandler;
	return 0;
}
