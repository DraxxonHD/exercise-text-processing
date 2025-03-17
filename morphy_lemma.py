from germalemma import GermaLemma
import sys

def lemmatize(word, pos="VERB"):  # Default: Verb lemmatization
    lemmatizer = GermaLemma()
    lemma_dict = lemmatizer.find_lemma(word, pos)  # Correct method to get lemma

    return lemma_dict if lemma_dict else word  # Return lemma or original word

if __name__ == "__main__":
    if len(sys.argv) > 1:
        word = sys.argv[1]
        pos = sys.argv[2] if len(sys.argv) > 2 else "VERB"  # Default to VERB
        print(lemmatize(word, pos))