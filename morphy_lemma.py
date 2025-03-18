import sys
import spacy
from germalemma import GermaLemma

# Load spaCy's German model (optimized: disable unnecessary components)
nlp = spacy.load("de_core_news_sm", disable=["ner", "parser"])
lemmatizer = GermaLemma()

# Map spaCy POS tags to GermaLemma-compatible tags
POS_MAP = {
    "NOUN": "N",
    "VERB": "V",
    "ADJ": "ADJ",
    "ADV": "ADV",
    # Add more mappings if needed
}

def lemmatize(word):
    """Finds the POS tag of a single word and returns its lemma."""
    doc = nlp(word)  # Tokenization only (faster)
    if not doc:
        return word  # Return the word itself if tokenization fails

    pos = doc[0].pos_  # Get POS tag
    mapped_pos = POS_MAP.get(pos, "N")  # Default to "N" (noun) if not mapped
    try:
        return lemmatizer.find_lemma(word, mapped_pos) or word
    except ValueError:
        return word  # Return the word itself if POS is unsupported

if __name__ == "__main__":
    if len(sys.argv) > 1:
        print(lemmatize(sys.argv[1]))