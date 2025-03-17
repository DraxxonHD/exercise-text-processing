#pragma once

#include <string>
#include <vector>

using namespace std;

class CNatural_Language {
    public:
        CNatural_Language();
		~CNatural_Language();
    
        vector<string*>& Process(string& input);  // Full NLP processing pipeline
    
    private:
        vector<string*>& Tokenize(string& text);
        void RemoveStopwords(vector<string*>& rtokens); 
        void ApplyStemming(vector<string*>& rtokens);
        string& StemWord(string& word); 

    private:

		string* m_StopWords;    
};