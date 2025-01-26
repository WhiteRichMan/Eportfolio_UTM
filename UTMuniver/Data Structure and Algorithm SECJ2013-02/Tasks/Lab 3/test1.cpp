#include <iostream>
#include <string>
using namespace std;

// Define class Node
class Node {
public:
    string name;
    Node* prev;
    Node* next;

    Node(string data) : name(data), prev(nullptr), next(nullptr) {}
};

// Functions for Doubly Linked List Operations
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Task 1: Create the list (given)
    void createList() {
        string names[] = {"Ali", "Baba", "Chan", "Diana", "Ely"};
        for (int i = 0; i < 5; i++) {
            insertAtEnd(names[i]);
        }
    }

    // Task 1.1 Helper function to insert at the end
    void insertAtEnd(string name) {
        Node* newNode = new Node(name);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Task 2: Count and display nodes
    void countAndDisplay() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            cout << "Node " << ++count << ": " << current->name << endl;
            current = current->next;
        }
        cout << "Total Nodes: " << count << endl;
    }

    // Task 3: Delete the last node
    void deleteLastNode() {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
    }

    // Task 4: Insert at the second position
    void insertAtSecond(string name) {
        Node* newNode = new Node(name);
        if (head == nullptr || head->next == nullptr) {
            cout << "Cannot insert at second position, the list has less than two nodes." << endl;
            delete newNode;
            return;
        }
        Node* second = head->next;
        head->next = newNode;
        newNode->prev = head;
        newNode->next = second;
        second->prev = newNode;
    }

    // Display the list
    void displayList() {
        Node* current = head;
        int index = 1;
        while (current != nullptr) {
            cout << "Node " << index++ << ": " << current->name << endl;
            current = current->next;
        }
    }
};

int main() {
    DoublyLinkedList dll;

    // Task 1: Create the list
    dll.createList();

    // Task 2: Count and display nodes
    dll.countAndDisplay();

    // Task 3: Delete the last node
    dll.deleteLastNode();
    cout << "\nList after deleting last node:" << endl;
    dll.displayList();

    // Task 4: Insert a node at the second position
    dll.insertAtSecond("Dina");
    cout << "\nList after inserting 'Dina' at second position:" << endl;
    dll.displayList();

    return 0;
}
