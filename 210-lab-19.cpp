// COMSC-210 | Lab 19 | Mamadou Sissoko
// IDE used: Visual Studio Code
// Vector of movies, each storing a linked list of reviews with file input and randomized ratings

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <vector>
using namespace std;

// Node structure for review
struct Node {
    double rating;
    string comment;
    Node* next;
};

// Movie structure holding title and head pointer
struct Movie {
    string title;
    Node* head;
};

// Adds review at head of linked list
void addHead(Node*& head, double rating, const string& comment) {
    Node* newNode = new Node{rating, comment, head};
    head = newNode;
}

// Displays all reviews and average rating
void display(Node* head) {
    cout << "\nOutputting all reviews:\n";
    int count = 0;
    double total = 0.0;
    for (Node* curr = head; curr; curr = curr->next) {
        count++;
        total += curr->rating;
        cout << "    > Review #" << count << ": " << fixed << setprecision(1)
             << curr->rating << ": " << curr->comment << endl;
    }
    if (count > 0)
        cout << "    > Average: " << fixed << setprecision(1) << total / count << endl;
    else
        cout << "    > No reviews available.\n";
}

// Generate random rating 1.0–5.0
double randomRating() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(1.0, 5.0);
    return round(dis(gen) * 10) / 10.0;
}

void loadReviews(Movie& movie, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: could not open file '" << filename << "'. Please try again.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        addHead(movie.head, randomRating(), line);
    }
}

int main() {
    vector<Movie> movies = {
        {"Star Wars", nullptr},
        {"Back To The Future", nullptr},
        {"The Avengers", nullptr},
        {"Tron: Legacy", nullptr}
    };

    // User input starts here (file-driven)
    vector<string> files = {
        "starwars_reviews.txt", "backtothefuture_reviews.txt", "avengers_reviews.txt", "tronlegacy_reviews.txt"
    };

    for (size_t i = 0; i < movies.size(); ++i)
        loadReviews(movies[i], files[i]);
    // End of user input

    for (auto& movie : movies) {
        cout << "\nMovie: " << movie.title;
        display(movie.head);
    }

    return 0;
}
