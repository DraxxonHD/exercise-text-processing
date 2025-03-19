#include "file_handler.h"
#include "natural_language.h"
#include <algorithm>
#include <iostream>

CNatural_Language::CNatural_Language(const char* _PathToStopWords, const char* _text)
	: m_Tokens(new vector<string*>())
{
	// Read the stopwords from the file
	string* pPath = new string(_PathToStopWords);
	CFile_Handler* pFileHandler = new CFile_Handler(*pPath);
	m_StopWords = new string(pFileHandler->GetFileContent());

	delete pFileHandler;
	delete pPath;

	// Process the input text
	string* pText = new string(_text);
	Process(*pText);
	delete pText;
}

CNatural_Language::~CNatural_Language()
{
	// Delete the tokens
	while (!m_Tokens->empty())
	{
		delete m_Tokens->back();
		m_Tokens->pop_back();
	}
	delete m_Tokens;

	// Delete the stopwords
	delete m_StopWords;
}

// Process the input text through the NLP pipeline
void CNatural_Language::Process(string& _rinput)
{
	// Convert the input text to lowercase
	transform(_rinput.begin(), _rinput.end(), _rinput.begin(), ::tolower);
	// Tokenize the input text
	Tokenize(_rinput);
	// Remove stopwords from the tokens
	RemoveStopwords();
	// Apply stemming to the tokens
	ApplyStemming();
}

vector<string*>& CNatural_Language::GetTokens() const
{
	if (nullptr == m_Tokens)
	{
		cerr << "Tokens are empty" << endl;
	}
	return *m_Tokens;
}

string& CNatural_Language::GetStopWords() const
{
	if (nullptr == m_StopWords)
	{
		cerr << "Stopwords are empty" << endl;
	}
	return *m_StopWords;
}

// Tokenize the input text
void CNatural_Language::Tokenize(string& _rtext)
{
	// remember last index to know the length of the token
	int last_index = 0;
	// iterate through the text
	for (int index = 0; index < _rtext.size(); index++)
	{
		// if a space or comma is found, create a token from the last index to the current index
		if (' ' == _rtext.at(index) || ',' == _rtext.at(index))
		{
			string* pToken = new string(_rtext.substr(last_index, index - last_index));
			m_Tokens->push_back(pToken);
			last_index = index + 1;
		}
		// if the last character is reached, create a token from the last index to the end of the text
		else if ( _rtext.size() - 1 == index)
		{
			string* pToken = new string(_rtext.substr(last_index, index - last_index + 1));
			m_Tokens->push_back(pToken);
		}
	}
}

// Remove stopwords from the tokens
void CNatural_Language::RemoveStopwords()
{
	// Iterate through the tokens
	int TokenSize = m_Tokens->size();
	for (int index = 0; index < TokenSize; index++)
	{
		// If the token is a stopword, remove it from the tokens
		if (string::npos != m_StopWords->find(*m_Tokens->at(index)))
		{
			delete m_Tokens->at(index);
			m_Tokens->erase(m_Tokens->begin() + index);
			--index;
			--TokenSize;
		}
	}	
}

// Activate the virtual environment and run the script
bool CNatural_Language::ActivateVirtualEnvAndRunScript()
{
	cout << "Activating virtual environment and running script" << endl;
	// Set the environment variable for the virtual environment
	string command = "python -m venv .venv";
	cout << "Executing command: " << command << endl;

	// Execute the command
	int result = system(command.c_str());
	if (0 != result)
	{
		cerr << "Failed to execute command: " << command << endl;
		return false;
	}
	cout << "Command executed successfully" << endl;
	return true;
}

// Apply stemming to the tokens
void CNatural_Language::ApplyStemming()
{
	// check if the virtual environment can be activated and the script can be run
	if (ActivateVirtualEnvAndRunScript())
	{
		// iterate through the tokens and lemmatize each token
		for (int index = 0; index < m_Tokens->size(); index++)
		{
			// print the progress
			cout << "Lemmatizing word " << index+1 << "/" << m_Tokens->size() << endl;

			// lemmatize the token and replace it in the tokens
			string& rResult = lemmatizeWord(*m_Tokens->at(index));
			delete m_Tokens->at(index);
			m_Tokens->at(index) = &rResult;
		}
	}
}


// Lemmatize a word
string& CNatural_Language::lemmatizeWord(const string& _rword) 
{
	// create the command to run the script
    string Command = ".venv\\Scripts\\activate && python morphy_lemma.py " + _rword;

	// create a buffer to store the result of the script
    const int BufferSize = 256;
    char* pBuffer = new char[BufferSize];
    string* pResult = new string("");

	// open a pipe to run the script and check if it was successful
	FILE* pPipe = _popen(Command.c_str(), "r");
	if (!pPipe)
	{
		cerr << "Failed to open pipe" << endl;
		return *pResult;
	}

	// read the output of the script line by line and store it in the result
	while (!feof(pPipe))
	{
		if (nullptr != fgets(pBuffer, BufferSize, pPipe))
		{
			*pResult += pBuffer;
		}
	}

	// close the pipe and delete the buffer
	_pclose(pPipe);
	delete[] pBuffer;


    return *pResult;
}
