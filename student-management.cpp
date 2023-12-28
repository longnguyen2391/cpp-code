#include <bits/stdc++.h> 
using namespace std; 

struct student{
    string id, name; 
    struct gpa{
        float fs, ss, ts; 
        void setGPA(float fs, float ss, float ts){
            if(fs >= 0 && fs <= 10){
                this->fs = fs; 
                if(ss >= 0 && ss <= 10){
                    this->ss = ss;
                    if(ts >= 0 && ts <= 10){
                        this->ts = ts; 
                    } else{
                        cout << "Third score is incorrect\n"; 
                    }
                } else{
                    cout << "Second score is incorrect\n"; 
                    return; 
                }
            } else{
                cout << "First score is incorrect\n"; 
                return; 
            }
        }
        float calculateGPA(){
            float finalGPA = (fs+ss+ts)/3;
            return finalGPA; 
        }
    };
    gpa score;  
    struct date{
        int day, month, year; 
        void setDate(int d, int m, int y){
            if(d > 0 && d < 32){
                this->day = d; 
                if(m > 0 && m < 13){
                    this->month = m; 
                    if(y > 0){
                        this->year = y; 
                    } else{
                        cout << "Year is incorrect\n"; 
                        return;
                    }
                } else{ 
                    cout << "Month is incorrect\n"; 
                    return;
                }
            } else{
                cout << "Day is incorrect\n";
                return;
            }
        }
        void printDate(){
            cout << day << "/" << month << "/" << year;
        }
    };
    date birth; 
};

struct node{
    student data; 
    node* next; 
}; 

node* makeNode(){
    student s; 
    cout << "ID: "; cin >> s.id; 
    cout << "Name: "; cin.ignore(); getline(cin, s.name);
    cout << "Birth: "; cin >> s.birth.day >> s.birth.month >> s.birth.year; 
    s.birth.setDate(s.birth.day, s.birth.month, s.birth.year);
    cout << "First score: "; cin >> s.score.fs; 
    cout << "Second score: "; cin >> s.score.ss; 
    cout << "Third score: "; cin >> s.score.ts;  
    s.score.setGPA(s.score.fs, s.score.ss, s.score.ts);

    node* newNode = new node; 
    newNode->data = s; 
    newNode->next = NULL;
    return newNode; 
}

void printStudentInformation(student s){
    cout << "ID: " << s.id << endl; 
    cout << "Name: " << s.name << endl; 
    s.birth.printDate(); cout << endl; 
    cout << "GPA: " << s.score.calculateGPA() << endl; 
}

void printStudentList(node* head){
    int count = 0; 
    while(head != NULL){
        printStudentInformation(head->data); 
        count++;
        head = head->next; 
    }
    cout << "Total: " << count << endl;
}

int size(node* head){
    int count = 0; 
    while(head != NULL){
        count++;
        head = head->next; 
    }
    return count; 
}

void searchingStudentByID(node* head, string keyID){
    while(head != NULL){
        if(keyID == head->data.id){
            printStudentInformation(head->data); 
            return; 
        }
    } 
    cout << "List doesn't contain student with ID: " << keyID << endl;
}

void sortingStudentbyGPA(node** head){ 
    for(node* i = *head; i != NULL; i = i->next){
        node* minNode = i;
        for(node* j = i->next; j != NULL; j = j->next){
            if(minNode->data.score.calculateGPA() > j->data.score.calculateGPA()){
                minNode = j;
            }
        }
        swap(minNode->data, i->data); 
    }
    cout << "List sorted!" << endl; 
}

void insertHead(node** head){
    if(*head == NULL){
        node* newNode = makeNode(); 
        *head = newNode;
        return; 
    } else{
        node* newNode = makeNode(); 
        newNode->next = *head; 
        *head = newNode; 
    }
} 

void removeHead(node** head){
    if(*head == NULL){
        cout << "CURRENT LIST IS EMPTY\n"; 
        return; 
    } else{ 
        node* deleteNode = *head; 
        *head = (*head)->next; 
        delete deleteNode;
    }
} 


void insertTail(node** head){
    if(*head == NULL){
        node* newNode = makeNode();
        *head = newNode;
        return;
    } else{
        node* newNode = makeNode();
        node* tempHead = *head;
        while(tempHead->next != NULL){
            tempHead = tempHead->next;
        } 
        tempHead->next = newNode; 
    }
}

void removeTail(node** head){
    if(*head == NULL){
        cout << "CURRENT LIST IS EMPTY\n"; 
        return; 
    } else{ 
        node* tempHead = *head;
        while(tempHead->next->next != NULL){
            tempHead = tempHead->next;
        } 
        node* deleteNode = tempHead->next; 
        tempHead->next = NULL;
        delete deleteNode;
    }
}

void insertMiddle(node** head, int pos){
    if(pos < 0 || pos > size(*head) + 1){
        cout << "POSITION OUT OF LIST RANGE\n"; 
        return; 
    } else{
        node* newNode = makeNode(); 
        node* tempHead = *head;
        for(int i = 1; i < pos - 1; i++){
            tempHead = tempHead->next; 
        } 
        newNode->next = tempHead->next; 
        tempHead->next = newNode;  
    }
}

void removeMiddle(node** head, int pos){
    if(pos < 0 || pos > size(*head) + 1){
        cout << "POSITION OUT OF LIST RANGE\n"; 
        return; 
    } else{
        node* tempHead = *head;
        for(int i = 1; i < pos - 1; i++){
            tempHead = tempHead->next; 
        } 
        node* deleteNode = tempHead->next; 
        tempHead->next = deleteNode->next; 
        delete deleteNode;   
    }
}

int main(){
    node* head = NULL; 
    while(true){
        cout << "1. Printing all list\n"; 
        cout << "2. Insert student\n"; 
        cout << "3. Remove student\n"; 
        cout << "4. Searching student by ID\n"; 
        cout << "5. Sorting student by GPA\n"; 
        cout << "0. Exit program\n"; 
        int choice, pos;
        string keyID; 
        cout << "Enter your choice: "; cin >> choice; 
        switch(choice){
            case 1: 
                printStudentList(head); 
                break; 
            case 2: 
                cout << "2.1 Insert head of list\n"; 
                cout << "2.2 Insert tail of list\n"; 
                cout << "2.3 Insert middle of list\n"; 
                int insertChoice; 
                cout << "Enter your choice: "; cin >> insertChoice;
                switch(insertChoice){
                    case 1:
                        insertHead(&head); 
                        break;
                    case 2: 
                        insertTail(&head);
                        break;
                    case 3: 
                        cout << "Enter your position: "; cin >> pos;
                        insertMiddle(&head, pos); 
                        break;
                }
                break;
            case 3: 
                cout << "2.1 Remove head of list\n"; 
                cout << "2.2 Remove tail of list\n"; 
                cout << "2.3 Remove middle of list\n"; 
                int removeChoice; 
                cout << "Enter your choice: "; cin >> removeChoice;
                switch(removeChoice){
                    case 1:
                        removeHead(&head); 
                        break;
                    case 2: 
                        removeTail(&head);
                        break;
                    case 3: 
                        cout << "Enter your position: "; cin >> pos;
                        removeMiddle(&head, pos); 
                        break;
                }
                break;
            case 4: 
                cout << "Enter your ID: "; cin >> keyID; 
                searchingStudentByID(head, keyID); 
                break; 
            case 5: 
                sortingStudentbyGPA(&head); 
                break;
            case 0:
                return 0; 
        }
    }
    return 0; 
}