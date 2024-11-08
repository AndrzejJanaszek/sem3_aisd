#include<iostream>

std::string* split(std::string s, std::string delimiter) {

    int pos_start = 0;
    int pos_end;
    int delim_len = delimiter.length();

    std::string token;
    static std::string buffer[10];

    int idx = 0;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {

        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;

        buffer[idx] = token;
        idx++;

        std::cout << idx << std::endl;
    }

    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    buffer[idx] = token;

    std::cout << buffer[0] << std::endl;

    return buffer;

}

class President
{
public:
    std::string name;
    std::string surname;
    short year_start;
    short year_end;
    std::string party;

    President(std::string name, std::string surname, short year_start, short year_end, std::string party){
        this->name = name;
        this->surname = surname;
        this->year_start = year_start;
        this->year_end = year_end;
        this->party = party;
    }

    void print(bool simple = false){
        printf("President:\n");
        printf("name: %s\n", name.c_str());
        printf("surname: %s\n", surname.c_str());
        if(!simple){
            printf("year_start: %d\n", year_start);
            printf("year_end: %d\n", year_end);
            printf("party: %s\n", surname.c_str());
        }
    }
};

class Node{
public:
    Node* next;
    President value;

    void print_node(){
        printf("Node:\n");
        value.print(true);
    };
};

class List{
public:
    Node* head;
    Node* tail;

    List(){
        head = nullptr;
        tail = nullptr;
    }

    void append(Node* node){
        if (head == nullptr){
            head = node;
            tail = node;
        }
        else{
            tail->next = node;
            node->next = nullptr;
        }
    }
    void prepend(Node* node){
        if (head == nullptr){
            head = node;
            tail = node;
        }
        else{
            node->next = head->next;
            head->next = node;
        }
    }
    void print_list(){
        Node* ptr = head;
        while(ptr != nullptr){
            ptr->print_node();
        }
    }
};



int main()
{
    std::string str = "a b c";

    std::string* tab;

    tab = split(str, " ");
    /* code */

// George Washington 1789-1797 Unaffiliated
    President p1 = President("George", "Washington", 1789, 1797, "Unaffiliated");
    // p1.print();
    p1.print(1);
    return 0;
}
