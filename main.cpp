#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int NUM_PERIODS = 20, START_CUST = 5;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        int i = 1;
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "  " << i << ". " << current->data << endl;
            current = current->next;
            i++;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    string get_data_pos(int pos){
        Node* temp = head;
        for (int i = 1; i < pos; i++){
        
    }
};

/* Linked List Methods (for my convenience)
- insert_after(string val, int pos)
- delete_val(string val)
- delete_pos (int pos)
- push_back(string val)
- push_front (string val)
- pop_back()
- pop_front()
- print()
- print_reverse()
- get_data_pos(int pos) *added by me*
*/

void print_line(DoublyLinkedList l){
    cout << "> Current Line: " << endl;
    l.print();
}

int rand100(){
    return rand() % 100 + 1;
}

int main() {
    srand(time(0));
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS << endl;  // dummy statement to avoid compiler warning
    ifstream customers;
    DoublyLinkedList line;
    customers.open("names.txt");
    if (!customers.good()){
        cout << "Unable to open file" << endl;
        return 0;
    }
    // change next loop to pick random names from list
    cout << "Store Opens:" << endl;
    for (int i = 0; i < START_CUST; i++){ // add 5 customers in first period
        string tempCust;
        customers >> tempCust;
        line.push_back(tempCust);
        cout << "> " << tempCust << " joins the line" << endl;
    }
    print_line(line);

    int p = 0;
    for (int i = 1; i < NUM_PERIODS; i++){ // for 19 periods simulate coffee shop after first 
        // simulate next periods here
        cout << "Period #" << i + 1 << ": " << endl;
        
        // customer being helped
        p = rand100();
        if (p <= 100){
            string cust = line.get_data_pos(1);
            cout << cust << " is served" << endl;
            line.pop_front();
        }

        // new customer joins
        p = rand100();
        if (p <= 60){
            string cust;
            customers >> cust;
            line.push_back(cust);
            cout << cust << " joined the line" << endl;
        }

        // customer at end decides to leave
        p = rand100();
        if (p <= 20){
            // get name of customer at end
            // print customer leaves
            // pop_back()
        }
        print_line(line);
    }
    
    return 0;
}