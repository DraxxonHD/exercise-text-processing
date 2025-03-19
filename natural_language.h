#pragma once

#include <string>
#include <vector>

using namespace std;

class CNatural_Language 
{
    public:
        explicit CNatural_Language(const char* _PathToStopWords, const char* _text);
		~CNatural_Language();
    
        vector<string*>& GetTokens() const;
		string& GetStopWords() const;
    
    private:
        void Process(string& _rinput);  // Full NLP processing pipeline
        void Tokenize(string& _rtext);
        void RemoveStopwords();
        void ApplyStemming();
		string& lemmatizeWord(const string& _rword);
        bool ActivateVirtualEnvAndRunScript();

    private:
		vector<string*>* m_Tokens;
		string* m_StopWords;
};