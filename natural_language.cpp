#include "natural_language.h"
#include "file_handler.h"
#include <algorithm>
#include <sstream>
#include <array>
#include <iostream>

CNatural_Language::CNatural_Language()
{
	m_StopWords = new string();
}

CNatural_Language::~CNatural_Language()
{
	if (nullptr != m_StopWords)
	{
		delete m_StopWords;
	}
}

vector<string*>& CNatural_Language::Process(string& input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	vector<string*>& tokens = Tokenize(input);
	RemoveStopwords(tokens);
	ApplyStemming(tokens);
	return tokens;
}

vector<string*>& CNatural_Language::Tokenize(string& text)
{
	vector<string*>* tokens = new vector<string*>();
	int last_index = 0;
	for (int index = 0; index < text.size(); index++)
	{
		if (' ' == text.at(index) || ',' == text.at(index))
		{
			string* token = new string(text.substr(last_index, index - last_index));
			tokens->push_back(token);
			last_index = index + 1;
		}
		else if (index == text.size() - 1)
		{
			string* token = new string(text.substr(last_index, index - last_index + 1));
			tokens->push_back(token);
		}
	}
	return *tokens;
}

void CNatural_Language::RemoveStopwords(vector<string*>& rtokens)
{
	string* pPath = new string("german_stopwords.txt");
	CFile_Handler* pFileHandler = new CFile_Handler(*pPath);
	string& rStopWords = pFileHandler->GetFileContent();
	for (int index = 0; index < rtokens.size(); index++)
	{
		if (string::npos != rStopWords.find(*rtokens.at(index)))
		{
			rtokens.erase(rtokens.begin() + index);
		}
	}

	delete pFileHandler;
	delete pPath;
	
}

bool CNatural_Language::ActivateVirtualEnvAndRunScript()
{
	cout << "Activating virtual environment and running script" << endl;
	// Set the environment variable for the virtual environment
	std::string command = "python -m venv .venv && .venv\\Scripts\\activate";
	cout << "Executing command: " << command << endl;

	// Execute the command

	int result = std::system(command.c_str());
	if (result != 0)
	{
		std::cerr << "Failed to execute command: " << command << std::endl;
		return false;
	}
	std::cout << "Command executed successfully" << std::endl;
	return true;
}

void CNatural_Language::ApplyStemming(vector<string*>& rtokens)
{
	if (ActivateVirtualEnvAndRunScript())
	{
		for (int index = 0; index < rtokens.size(); index++)
		{
			*rtokens.at(index) = lemmatizeWord(*rtokens.at(index), "");
		}
	}
}

string CNatural_Language::StemWord(string& word)
{
	return string();
}




std::string CNatural_Language::lemmatizeWord(const std::string& word, const std::string& pos) 
{
    std::string command = ".venv\\Scripts\\activate && python morphy_lemma.py " + word;

    const int BufferSize = 256;
    char* pBuffer = new char[BufferSize];
    std::string result = "";
	FILE* pPipe = _popen(command.c_str(), "r");
	if (!pPipe)
	{
		std::cerr << "Failed to open pipe" << std::endl;
		return result;
	}

	while (!feof(pPipe))
	{
		if (fgets(pBuffer, BufferSize, pPipe) != nullptr)
		{
			result += pBuffer;
		}
	}



	_pclose(pPipe);
	delete[] pBuffer;
    return result;
}
