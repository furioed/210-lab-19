// COMSC-210 | Lab 19 | Mamadou Sissoko
// IDE used: Visual Studio Code
// Linked list storing movie reviews via file input and randomized ratings

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
using namespace std;

// Node structure for review
struct Node {
    double rating;
    string comment;
    Node* next;
};

// Movie class containing title and linked list
class Movie {
private:
    string title;
    Node* head;

public:
    Movie(const string& t) : title(t), head(nullptr) {}

    // Adds review at head of linked list
    void addHead(double rating, const string& comment) {
        Node* newNode = new Node{rating, comment, head};
        head = newNode;
    }

    // Displays all reviews and average rating
    void display() const {
        cout << "\nMovie: " << title << "\nReviews:\n";
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
    }

    Node*& getHead() { return head; }
};

// Generate random rating 1.0–5.0
double randomRating() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(1.0, 5.0);
    return round(dis(gen) * 10) / 10.0;
}

// Reads reviews from a file into the Movie object
void readFile(Movie& movie, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "File \"" << filename << "\" not found. Please try again with a valid file.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        movie.addHead(randomRating(), line);
    }
}

int main() {
    Movie movie("Star Wars");

    // User input starts here (file-driven)
    readFile(movie, "starwars_reviews.txt");
    // End of user input

    movie.display();
    return 0;
}