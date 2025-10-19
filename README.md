#TF-IDF Search Engine
A C++ implementation of a TF-IDF (Term Frequency-Inverse Document Frequency) based search engine that processes documents and returns relevant results for search queries.

# Overview
This project implements a simple search engine using:

Tokenization with stop word removal

Inverted Index for efficient document retrieval

TF-IDF scoring for relevance ranking

Cosine similarity for query matching

#Features
Text Processing: Tokenization, lowercase conversion, punctuation removal

Stop Word Filtering: Removes common words to improve search quality

Inverted Index: Efficient storage and retrieval of document terms

TF-IDF Scoring: Calculates term importance based on frequency and document distribution

Relevance Ranking: Returns documents sorted by relevance to query

# Project Structure
text
├── main.cpp              # Main implementation file
├── README.md            # Project documentation
└── (Sample documents included in code)
# Implementation Details
Classes and Functions
Document: Represents a document with ID and text content

InvertedIndex: Builds and maintains the search index

TFIDFCalculator: Computes TF-IDF scores for terms

tokenize(): Preprocesses text into tokens

searchQuery(): Processes search queries and returns ranked results

Key Algorithms
Tokenization: Splits text into words, converts to lowercase, removes punctuation

Stop Word Removal: Filters out common words (the, is, at, of, etc.)

TF Calculation: TF = (Term Count in Document) / (Total Terms in Document)

IDF Calculation: IDF = log(Total Documents / Documents Containing Term)

Scoring: Uses cosine similarity between query and document vectors

# Example
Input Documents:

"The quick brown fox jumps over the lazy dog"

"Never jump over the lazy dog quickly"

"A quick brown dog outpaces a quick fox"

Search Query: "quick brown dog"

Results: Documents ranked by relevance (Document 3, 1, 2)




