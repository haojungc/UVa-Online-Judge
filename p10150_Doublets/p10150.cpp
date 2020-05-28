/* Doublets */
/* PC/UVa IDs: 110307/10150, Popularity: C, Success rate: average, Level: 3 */
#include <iostream>
#include <string>
#include <queue>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::queue;
using std::stack;

/* Type Definitions */
typedef struct {
    string word;
    bool visited;
    int prev;
} Dictionary;

/* Function Protoypes */
void initialize();
void print_sequence(const string&, const string&);      // (start string, end string)
int create_sequence_bfs(const string&, const string&);  // (start string, end string)
int index_of(const string&, int);                       // (string to be searched, length index)
bool is_doublet(const string&, const string&);

/* Global Variables */
const int MAX_LEN = 16;
const int MAX_SIZE = 25150;
Dictionary dict[MAX_LEN][MAX_SIZE];
int word_count[MAX_LEN];    // default: 0
bool first_case = true;
string no_solution_msg = "No solution.";

int main() {
    // Inputs the dictionary
    string tmp;
    while (getline(cin, tmp), tmp != "") {
        int len_index = tmp.length() - 1;
        int count = word_count[len_index]++;

        dict[len_index][count].word = tmp;
    }

    // Inputs a number of word pairs and prints out the sequences
    string start_str, end_str;
    while (cin >> start_str >> end_str) {
        initialize();
        print_sequence(start_str, end_str);
    }

    return 0;
}

void initialize() {
    for (int len_index = 0; len_index < MAX_LEN; ++len_index)
        for (int i = 0; i < word_count[len_index]; ++i) {
            dict[len_index][i].visited = false;
            dict[len_index][i].prev = -1;
        }
}

void print_sequence(const string &start_str, const string &end_str) {
    if (first_case) first_case = false;
    else cout << endl;

    // Different length: no solution
    if (start_str.length() != end_str.length()) {
        cout << no_solution_msg << endl;
        return;
    }
    
    // Uses BFS and gets the index of end_str
    // Returns -1 if there are no solutions
    int last_index = create_sequence_bfs(start_str, end_str);
    
    if (last_index == -1) {
        cout << no_solution_msg << endl;
        return;
    }

    // Creates a sequence
    stack<int> sequence;
    int len_index = start_str.length() - 1;
    int start_str_index = index_of(start_str, len_index);
    
    for (int i = last_index; i != start_str_index; i = dict[len_index][i].prev)
        sequence.push(i);
    sequence.push(start_str_index);

    // Prints the sequence
    while (!sequence.empty()) {
        cout << dict[len_index][sequence.top()].word << endl;
        sequence.pop();
    }

    return;
}

int create_sequence_bfs(const string &start_str, const string &end_str) {
    queue<int> index_queue;
    int len_index = start_str.length() - 1;
    int start_str_index = index_of(start_str, len_index),
        end_str_index = index_of(end_str, len_index);

    // BFS
    index_queue.push(start_str_index);
    dict[len_index][start_str_index].visited = true;
    while (!index_queue.empty()) {
        int front_index = index_queue.front();
        string front_str = dict[len_index][front_index].word;

        for (int i = 0; i < word_count[len_index]; ++i) {
            // Pushes the matched strings into index_queue
            if (!dict[len_index][i].visited && is_doublet(dict[len_index][i].word, front_str)) {
                dict[len_index][i].visited = true;
                dict[len_index][i].prev = front_index;

                // End string found
                if (i == end_str_index) return end_str_index;

                index_queue.push(i);
            } 
        }
        index_queue.pop();
    }

    return -1;  // No solutions
}

int index_of(const string &str, int len_index) {
    // TODO: use radix sort and memorize the indices of each alphabet to enhance performance
    for (int index = 0; index < word_count[len_index]; index++)
        if (dict[len_index][index].word == str) return index;

    return -1;  // Not found
}

// Note: the two strings must have the same lengths
bool is_doublet(const string &s1, const string &s2) {
    int difference = 0,
        len = s1.length();

    for (int i = 0; i < len; ++i)
        if (s1[i] != s2[i]) ++difference;
    
    return difference == 1 ? true : false;
}
