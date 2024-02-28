/*
    Compile: g++ vectorsearch.cpp -I/opt/homebrew/include -std=c++11 -o
 vectorsearch

    Current theme: one dark
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
// #include <gsl/gsl_linalg.h>

using std::cout;
using std::string;
using std::vector;

class corpus {
public:
  vector<string> documents;
  std::map<string, int> bow;

  void tf_idf() {
    for (auto &document : documents) {
      std::sort(document.begin(), document.end());
    }
  }

private:
  vector<vector<int>> vctrs;

  // Assumes "document" is sorted
  std::map<string, int> tf(string document) {
    std::map<string, int> term_freq;
    string temp;
    std::stringstream stream(document);
    while (stream >> temp) {
      term_freq[temp] = 0;
    }
    while (stream >> temp) {
      term_freq[temp]++;
    }
    return term_freq;
  }

  std::map<string, int> idf(string document) {}
};

std::map<string, int> bag_of_words(vector<string> words) {

  // Initialize list of stopwords
  vector<string> stopwords = {"the", "of", "and",  "to", "a",    "in",   "for",
                              "is",  "on", "that", "by", "this", "with", "i",
                              "you", "it", "not",  "or", "be",   "are"};

  std::map<string, int> bowtemp;
  std::map<string, int> bow;

  for (auto &word : words) {
    if (!(std::find(stopwords.begin(), stopwords.end(), word) !=
          stopwords.end())) {
      bowtemp[word] = 0;
    }
  }
  for (auto &word : words) {
    if (!(std::find(stopwords.begin(), stopwords.end(), word) !=
          stopwords.end())) {
      bow[word]++;
    }
  }
  for (auto &word : words) {
    if (!(std::find(stopwords.begin(), stopwords.end(), word) !=
          stopwords.end())) {
      if (bowtemp[word] > 1)
        bow[word] = bowtemp[word];
    }
  }
  bowtemp.clear();

  return bow;
}

string string_to_set(string input_string) {
  // Remove duplicates from words vector (creating a set)
  std::sort(input_string.begin(), input_string.end());
  auto it = std::unique(input_string.begin(), input_string.end());
  input_string.erase(it, input_string.end());

  return input_string;
}

vector<string> corpus_generate(string words) {
  vector<string> corpus;

  string wordset = string_to_set(words);

  return corpus;
}

int main() {
  std::fstream in;

  // It is assumed the input text is in lower case, one line (no newlines), and
  // no punctuation
  in.open("2024-2-16.txt");

  // words contains every word from the in file
  vector<string> words;
  string element;

  if (in.is_open()) {
    while (in >> element) {
      words.push_back(element);
    }
  }

  in.close();
  cout << "file length: " << words.size() << "\n";

  std::map<string, int> bag = bag_of_words(words);

  cout << bag["memory"] << "\n";

  return 0;
}
