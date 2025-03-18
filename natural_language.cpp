#include "natural_language.h"
#include "file_handler.h"
#include <algorithm>
#include <sstream>
#include <array>
#include <iostream>

CNatural_Language::CNatural_Language()
{
}

CNatural_Language::~CNatural_Language()
{
}

// Process the input text through the NLP pipeline
vector<string*>& CNatural_Language::Process(string& _rinput)
{
	// Convert the input text to lowercase
	transform(_rinput.begin(), _rinput.end(), _rinput.begin(), ::tolower);
	// Tokenize the input text
	vector<string*>& tokens = Tokenize(_rinput);
	// Remove stopwords from the tokens
	RemoveStopwords(tokens, "german_stopwords.txt");
	// Apply stemming to the tokens
	ApplyStemming(tokens);
	return tokens;
}

// Tokenize the input text
vector<string*>& CNatural_Language::Tokenize(string& _rtext)
{
	vector<string*>* tokens = new vector<string*>();
	// remember last index to know the length of the token
	int last_index = 0;
	// iterate through the text
	for (int index = 0; index < _rtext.size(); index++)
	{
		// if a space or comma is found, create a token from the last index to the current index
		if (' ' == _rtext.at(index) || ',' == _rtext.at(index))
		{
			string* token = new string(_rtext.substr(last_index, index - last_index));
			tokens->push_back(token);
			last_index = index + 1;
		}
		// if the last character is reached, create a token from the last index to the end of the text
		else if (index == _rtext.size() - 1)
		{
			string* token = new string(_rtext.substr(last_index, index - last_index + 1));
			tokens->push_back(token);
		}
	}
	return *tokens;
}

// Remove stopwords from the tokens
void CNatural_Language::RemoveStopwords(vector<string*>& _rtokens, const string _path)
{
	// Read the stopwords from the file
	string* pPath = new string(_path);
	CFile_Handler* pFileHandler = new CFile_Handler(*pPath);
	string& rStopWords = pFileHandler->GetFileContent();
	// Iterate through the tokens
	for (int index = 0; index < _rtokens.size(); index++)
	{
		// If the token is a stopword, remove it from the tokens
		if (string::npos != rStopWords.find(*_rtokens.at(index)))
		{
			delete _rtokens.at(index);
			_rtokens.erase(_rtokens.begin() + index);
		}
	}

	delete pFileHandler;
	delete pPath;
	
}

// Activate the virtual environment and run the script
bool CNatural_Language::ActivateVirtualEnvAndRunScript()
{
	cout << "Activating virtual environment and running script" << endl;
	// Set the environment variable for the virtual environment
	string command = "python -m venv .venv && .venv\\Scripts\\activate";
	cout << "Executing command: " << command << endl;

	// Execute the command
	int result = system(command.c_str());
	if (result != 0)
	{
		cerr << "Failed to execute command: " << command << endl;
		return false;
	}
	cout << "Command executed successfully" << endl;
	return true;
}

// Apply stemming to the tokens
void CNatural_Language::ApplyStemming(vector<string*>& _rtokens)
{
	// check if the virtual environment can be activated and the script can be run
	if (ActivateVirtualEnvAndRunScript())
	{
		// iterate through the tokens and lemmatize each token
		for (int index = 0; index < _rtokens.size(); index++)
		{
			// print the progress
			cout << "Lemmatizing word " << index << "/" << _rtokens.size() << endl;

			// lemmatize the token and replace it in the tokens
			string result = lemmatizeWord(*_rtokens.at(index));
			delete _rtokens.at(index);
			_rtokens.at(index) = &result;
		}
	}
}


// Lemmatize a word
string& CNatural_Language::lemmatizeWord(const string& _rword) 
{
	// create the command to run the script
    string command = ".venv\\Scripts\\activate && python morphy_lemma.py " + _rword;

	// create a buffer to store the result of the script
    const int BufferSize = 256;
    char* pBuffer = new char[BufferSize];
    string* pResult = new string("");

	// open a pipe to run the script and check if it was successful
	FILE* pPipe = _popen(command.c_str(), "r");
	if (!pPipe)
	{
		cerr << "Failed to open pipe" << endl;
		return *pResult;
	}

	// read the output of the script line by line and store it in the result
	while (!feof(pPipe))
	{
		if (fgets(pBuffer, BufferSize, pPipe) != nullptr)
		{
			*pResult += pBuffer;
		}
	}

	// close the pipe and delete the buffer
	_pclose(pPipe);
	delete[] pBuffer;


    return *pResult;
}
