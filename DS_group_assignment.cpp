// Group(2022BCSE027-2022BCSE034)

#include <bits/stdc++.h>
using namespace std;

// Function for token size and stop word remove
vector<string> tokenize(const string &text, const set<string> &stopWords) {
    istringstream stream(text);
    string word;
    vector<string> tokens;
    
    while (stream >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // For Removing punctuation
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        //For Removing stop words
        if (stopWords.find(word) == stopWords.end()) {
            tokens.push_back(word);
        }
    }
    return tokens;
}

// Class for Document
class Document {
public:
    int id;
    string text;
    
    Document(int id, const string &text) : id(id), text(text) {}
};

// Class For Inverted Index
class InvertedIndex {
public:
    unordered_map<string, unordered_map<int, int>> termFrequency;
    unordered_map<string, int> documentFrequency;
    int totalDocuments = 0;
    
    void addDocument(const Document &doc, const set<string> &stopWords) {
        totalDocuments++;
        vector<string> tokens = tokenize(doc.text, stopWords);
        set<string> uniqueTokens(tokens.begin(), tokens.end());
        
        for (const string &token : tokens) {
            termFrequency[token][doc.id]++;
        }
        for (const string &token : uniqueTokens) {
            documentFrequency[token]++;
        }
    }
};

// Class to compute TF-IDF scores

class TFIDFCalculator {
public:
    static double computeTF(int termCount, int totalTerms) {
        return static_cast<double>(termCount) / totalTerms;
    }
    
    static double computeIDF(int totalDocuments, int documentFrequency) {
        return log(static_cast<double>(totalDocuments) / documentFrequency);
    }
    
    static unordered_map<string, double> computeTFIDF(
        const unordered_map<string, int> &termFreq,
        const InvertedIndex &index) {
        
        unordered_map<string, double> tfidfScores;
        int totalTerms = 0;
        for (const auto &pair : termFreq) {
            totalTerms += pair.second;
        }
        
        for (const auto &pair : termFreq) {
            double tf = computeTF(pair.second, totalTerms);
            double idf = computeIDF(index.totalDocuments, index.documentFrequency.at(pair.first));
            tfidfScores[pair.first] = tf * idf;
        }
        return tfidfScores;
    }
};

// Function For search queries
vector<int> searchQuery(const string &query, const vector<Document> &documents, const InvertedIndex &index, const set<string> &stopWords) {
    vector<string> queryTokens = tokenize(query, stopWords);
    unordered_map<string, int> queryTermFreq;
    
    for (const string &token : queryTokens) {
        queryTermFreq[token]++;
    }
    
    TFIDFCalculator calculator;
    unordered_map<string, double> queryTFIDF = calculator.computeTFIDF(queryTermFreq, index);
    
    vector<pair<int, double>> docScores;
    
    for (const Document &doc : documents) {
        unordered_map<string, int> docTermFreq;
        
        vector<string> docTokens = tokenize(doc.text, stopWords);
        for (const string &token : docTokens) {
            docTermFreq[token]++;
        }
        
        unordered_map<string, double> docTFIDF = calculator.computeTFIDF(docTermFreq, index);
        
        double score = 0.0;
        for (const auto &pair : queryTFIDF) {
            if (docTFIDF.find(pair.first) != docTFIDF.end()) {
                score += pair.second * docTFIDF[pair.first];
            }
        }
        
        docScores.push_back({doc.id, score});
    }
    
    sort(docScores.begin(), docScores.end(), [](const pair<int, double> &a, const pair<int, double> &b) {
        return a.second > b.second;
    });
    
    vector<int> result;
    for (const auto &pair : docScores) {
        result.push_back(pair.first);
    }
    return result;
}

int main() {
    // Stop words list
    set<string> stopWords = {"the", "is", "at", "of", "on", "and", "a"};
    
    // Sample documents
    vector<Document> documents = {
        Document(1, "The quick brown fox jumps over the lazy dog"),
        Document(2, "Never jump over the lazy dog quickly"),
        Document(3, "A quick brown dog outpaces a quick fox")
    };
    
    // Create inverted index
    InvertedIndex index;
    for (const Document &doc : documents) {
        index.addDocument(doc, stopWords);
    }
    
    // Search query
    string query = "quick brown dog";
    vector<int> result = searchQuery(query, documents, index, stopWords);
    
    // Print search results
    cout << "Search results for query: \"" << query << "\"" << endl;

    for (int docId : result) {
        cout << "Document ID: " << docId << endl;
    }
    
    return 0;

}