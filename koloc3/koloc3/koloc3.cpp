// koloc3.cpp : 
//Pазвернуть связный список используя рекурсию.

#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Функция для развертывания связного списка с использованием рекурсии
Node* reverseLinkedListRecursive(Node* current, Node* prev = nullptr) {
    if (current == nullptr) {
        return prev;
    }

    Node* nextNode = current->next;
    current->next = prev;

    return reverseLinkedListRecursive(nextNode, current);
}

// Функция для печати связного списка
void printLinkedList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Функция для создания связного списка с клавиатуры
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

//#include <iostream>
//
//struct Node {
//    int data;
//    Node* next;
//
//    Node(int value) : data(value), next(nullptr) {}
//};
//
//// Функция для развертывания связного списка с использованием рекурсии
//Node* reverseLinkedListRecursive(Node* current, Node* prev = nullptr) {
//    if (current == nullptr) {
//        return prev;
//    }
//
//    Node* nextNode = current->next;
//    current->next = prev;
//
//    return reverseLinkedListRecursive(nextNode, current);
//}
//
//// Функция для печати связного списка
//void printLinkedList(Node* head) {
//    while (head != nullptr) {
//        std::cout << head->data << " ";
//        head = head->next;
//    }
//    std::cout << std::endl;
//}
//
//int main() {
//    // Создаем пример связного списка: 1 -> 2 -> 3 -> 4 -> 5
//    Node* head = new Node(1);
//    head->next = new Node(2);
//    head->next->next = new Node(3);
//    head->next->next->next = new Node(4);
//    head->next->next->next->next = new Node(5);
//
//    std::cout << "Original Linked List: ";
//    printLinkedList(head);
//
//    // Развертываем связный список
//    head = reverseLinkedListRecursive(head);
//
//    std::cout << "Reversed Linked List: ";
//    printLinkedList(head);
//
//    // Очищаем память, выделенную под связный список
//    while (head != nullptr) {
//        Node* temp = head;
//        head = head->next;
//        delete temp;
//    }
//
//    return 0;
//}