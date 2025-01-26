#include <iostream>
using namespace std;

class Node {
public:
    int item;
    Node *next;

    Node(int d = 0) {
        item = d;
        next = NULL;
    }
};

// To print the list of nodes from head to tail
void print(Node *head) {
    Node *node = head;

    while (node) {
        cout << node->item << "\t";
        node = node->next;
    }
    cout << endl << endl;
}

int main() {
    Node *head, *tail;

    head = tail = new Node(45);

    for (int n = 50; n <= 80; n += 5) {
        tail->next = new Node(n);
        tail = tail->next;
    }

    print(head);

    Node *node;

    //-------------------------------------------------
    // Task 1: Insert a new node (with the item = 111) at the end of the list (3 marks)
    Node *newNode1 = new Node(111);
    tail->next = newNode1;
    tail = newNode1;

    print(head);

    //-------------------------------------------------
    // Task 2: Insert a new node (with the item = 222) between node 65 and node 70 (7 marks)
    Node *current = head;
    while (current != nullptr && current->item != 65) {
        current = current->next;
    }

    if (current != nullptr) {
        Node *newNode2 = new Node(222);
        newNode2->next = current->next;
        current->next = newNode2;
    }

    print(head);

    //-------------------------------------------------
    // Task 3: Delete the first node from the list (3 marks)
    if (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    print(head);

    //-------------------------------------------------
    // Task 4: Swap the positions of the first and last nodes (9 marks)
    if (head != nullptr && head != tail) {
        Node *prev = nullptr, *current = head;
        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }

        current->next = head->next;
        prev->next = head;
        head->next = nullptr;
        tail = head;
        head = current;
    }

    print(head);

    //-------------------------------------------------
    // Task 5: Find a node in the list with the number that you have entered (8 marks)
    int num;
    bool found = false;

    cout << "Enter a number that you want to find in the list: ";
    cin >> num;

    Node *search = head;
    while (search != nullptr) {
        if (search->item == num) {
            found = true;
            break;
        }
        search = search->next;
    }

    cout << num;
    if (found)
        cout << " is in the list" << endl;
    else
        cout << " is NOT in the list" << endl;

    return 0;
}
