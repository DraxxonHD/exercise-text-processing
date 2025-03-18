#include "file_handler.h"
#include "user_input.h"
#include "natural_language.h"

int main()
{
	string Text = "Aber mein Text ist doch cool, weil cool";
	CNatural_Language* pNLP = new CNatural_Language();

	vector<string*>& rTokens = pNLP->Process(Text);

	for (int index = 0; index < rTokens.size(); index++)
	{
		cout << *rTokens.at(index) << " " << endl;
	}

	delete pNLP;
	return 0;
}
