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

int main() {
    Node* head = nullptr;

    // User input starts here (file-driven)
    ifstream file("starwars_reviews.txt");
    if (!file) {
        cout << "Error: could not open file 'starwars_reviews.txt'. Please try again.\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        addHead(head, randomRating(), line);
    }
    // End of user input

    display(head);
    return 0;
}