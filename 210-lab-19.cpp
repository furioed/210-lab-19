// COMSC-210 | Lab 19 | Mamadou Sissoko
// IDE used: Visual Studio Code
// Linked list storing movie reviews via file input and randomized ratings

#include <iostream>
#include <string>
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

// Adds review at tail of linked list
void addTail(Node*& head, double rating, const string& comment) {
    Node* newNode = new Node{rating, comment, nullptr};
    if (!head) head = newNode;
    else {
        Node* curr = head;
        while (curr->next) curr = curr->next; // go to last node
        curr->next = newNode;
    }
}

// Displays all reviews and average rating
void display(Node* head) {
    cout << "\nOutputting all reviews:\n";
    int count = 0;
    double total = 0.0;
    for (Node* curr = head; curr; curr = curr->next) {
        count++;
        total += curr->rating;
        cout << "    > Review #" << count << ": " << curr->rating
             << ": " << curr->comment << endl;
    }
    if (count > 0)
        cout << "    > Average: " << total / count << endl;
}

// Get a validated decimal rating between 0.0 and 5.0
double getValidatedRating() {
    double rating;
    while (true) {
        cout << "Enter review rating 0-5: ";
        cin >> rating;
        if (!cin.fail() && rating >= 0.0 && rating <= 5.0) {
            cin.ignore();
            return rating;
        }
        cout << "Invalid rating! Enter a value between 0.0 and 5.0.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int main() {
    Node* head = nullptr;
    int choice;

    cout << "Which linked list method should we use?\n";
    cout << "    [1] New nodes are added at the head of the linked list\n";
    cout << "    [2] New nodes are added at the tail of the linked list\n";
    cout << "    Choice: ";
    cin >> choice;
    cin.ignore();

    char again = 'y';

    // User input starts here
    while (tolower(again) == 'y') {
        double rating = getValidatedRating();
        string comment;

        cout << "Enter review comments: ";
        getline(cin, comment);

        if (choice == 1) addHead(head, rating, comment);
        else addTail(head, rating, comment);

        cout << "Enter another review? Y/N: ";
        cin >> again;
        cin.ignore();
    }

    display(head);
    return 0;
}
