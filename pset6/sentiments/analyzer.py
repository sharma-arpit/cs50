import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positive = set()
        self.negative = set()
        
        """load positive words"""
        
        file = open(positives, "r")
        for line in file:
            if not line.startswith(';') and not line.startswith(' '):
                self.positive.add(line.rstrip('\n'))
        file.close()
        
        """load negative words"""
        
        file = open(negatives, "r")
        for line in file:
            if not line.startswith(';') and not line.startswith(' '):
                self.negative.add(line.rstrip('\n'))
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        for token in tokens:
            if token.lower() in self.positive:
                score +=1
            elif token.lower() in self.negative:
                score -=1
            else:
                continue
        
        return score