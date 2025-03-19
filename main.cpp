#include "natural_language.h"
#include <iostream>

int main()
{
	const char* pText = ("Die singen einfach so, weil die eine höhere Stimme hat."); // - Der Mummum
	CNatural_Language* pNLP = new CNatural_Language("german_stopwords.txt", pText);

	vector<string*>& rTokens = pNLP->GetTokens();

	for (int index = 0; index < rTokens.size(); index++)
	{
		cout << *rTokens.at(index) << " " << endl;
	}

	delete pNLP;
	return 0;
}
