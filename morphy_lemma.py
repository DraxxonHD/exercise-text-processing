import sys
import spacy
from germalemma import GermaLemma

# Load spaCy's German model (optimized: disable unnecessary components)
nlp = spacy.load("de_core_news_sm", disable=["ner", "parser"])
lemmatizer = GermaLemma()

def lemmatize(word):
    """Finds the POS tag of a single word and returns its lemma."""
    doc = nlp(word)  # Tokenization only (faster)
    pos = doc[0].pos_ if doc else "NOUN"  # Get POS, default to NOUN if empty
    return lemmatizer.find_lemma(word, pos) or word  # Lowercase for consistency

if __name__ == "__main__":
    if len(sys.argv) > 1:
        print(lemmatize(sys.argv[1]))
