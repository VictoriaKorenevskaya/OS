#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

Node* reverseLinkedListRecursive(Node* current, Node* prev = nullptr) {
    if (current == nullptr) {
        return prev;
    }

    Node* nextNode = current->next;
    current->next = prev;

    return reverseLinkedListRecursive(nextNode, current);
}

void printLinkedList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

Node* createLinkedListFromInput() {
    Node* head = nullptr;
    Node* current = nullptr;

    int value;
    std::cout << "Enter integers for the linked list (enter -1 to end): ";

    while (true) {
        std::cin >> value;

        if (value == -1) {
            break;
        }

        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}

int main() {
    Node* head = createLinkedListFromInput();

    std::cout << "Original Linked List: ";
    printLinkedList(head);

    head = reverseLinkedListRecursive(head);

    std::cout << "Reversed Linked List: ";
    printLinkedList(head);

    // Очищаем память, выделенную под связный список
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
