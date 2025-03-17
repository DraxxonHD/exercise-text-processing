#include "natural_language.h"
#include "file_handler.h"
#include <algorithm>

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

void CNatural_Language::ApplyStemming(vector<string*>& rtokens)
{
}

string& CNatural_Language::StemWord(string& word)
{
	return *m_StopWords;
}
