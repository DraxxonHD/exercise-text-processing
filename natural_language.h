#pragma once

#include <string>
#include <vector>

using namespace std;

class CNatural_Language {
    public:
        CNatural_Language();
		~CNatural_Language();
    
        vector<string*>& Process(string& _rinput);  // Full NLP processing pipeline
    
    private:
        vector<string*>& Tokenize(string& _rtext);
        void RemoveStopwords(vector<string*>& _rtokens, const string _path);
        void ApplyStemming(vector<string*>& _rtokens);
		string& lemmatizeWord(const std::string& _rword);
        bool ActivateVirtualEnvAndRunScript();

    private:

};