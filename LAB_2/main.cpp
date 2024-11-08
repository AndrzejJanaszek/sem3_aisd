#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

class President;
class Node;
class List;

//  function declarations
std::string* split(std::string s, std::string delimiter);
void load_presidents_data(List& list);
List najkrotszy_czas(List& list);
List dana_partia(List& list, std::string party);
President prezydent_w_roku(List& list, short year);

// class definitions
class President{
public:
    std::string name;
    std::string surname;
    int year_start;
    int year_end;
    std::string party;
    
    President(std::string name, std::string surname, int year_start, int year_end, std::string party){
        this->name = name;
        this->surname = surname;
        this->year_start = year_start;
        this->year_end = year_end;
        this->party = party;
    }
};

class Node{
public:
    Node* next;
    President* value;

    Node(President* value){
        this->value = value;
    }

    void print(){
        const int nameWidth = 16;
        const int surnameWidth = 15;
        const int partyWidth = 23;
        const int ptrWidth = 18;

        std::cout << "Node: " << std::left
        << std::setw(nameWidth) << value->name
        << std::setw(surnameWidth) << value->surname
        << value->year_start << "-" << value->year_start << "\t"
        << std::setw(partyWidth) << value->party
        << std::setw(ptrWidth) << this->next
        << std::endl;
    }
};

class List{
public:
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_back(Node* node){
        // if empty
        if(head == nullptr && tail == nullptr){
            head = node;
            tail = node;
        }
        else{ 
            tail->next = node;
            tail = node;
        }
        node->next = nullptr;
    }

    void push_front(Node* node){
        // if empty
        if(head == nullptr && tail == nullptr){
            tail = node;
        }
        node->next = head;
        head = node;
    }

    void insert_after(Node* node, Node* new_node){
        if(node == nullptr) return;

        new_node->next = node->next;
        node->next = new_node;
    }

    void insert_before(Node* node, Node* new_node){
        if(node == nullptr) return;

        insert_after(node, new_node);

        President* tmp = node->value;
        node->value = new_node->value;
        new_node->value = tmp;
    }

    void print_list(){
        int count = 0;
        Node* ptr = this->head;
        std::cout << "LIST:\n";
        while(ptr != nullptr){
            count++;
            ptr->print();
            
            ptr = ptr->next;
        }
        std::cout << "count: " << count << std::endl;
        std::cout << "LIST END\n" << std::endl;
    }

};

int main()
{
    // Load data from file
    List list;
    load_presidents_data(list);

    // Control list print
    std::cout << "Kontrolny wypis zawartości listy:\n";
    list.print_list();

    // --- ZADANIE 1 ---
    // najkrotszy czas
    List results = najkrotszy_czas(list);
    // print result
    std::cout << "\nWYNIK\n1. Napiszfunkcję, która zwróci wszystkich prezydentów o najkrótszym okresie przy władzy:\n";
    results.print_list();
    
    // --- ZADANIE 2 ---
    // dana partia
    results = dana_partia(list, "Republican");
    // print result
    std::cout << "\nWYNIK\n2. Napiszfukcję, która zwróci wszystkich prezydentów należących do danej partii:\n";
    results.print_list();
    
    // --- ZADANIE 3 ---
    // prezydent w roku
    President president = prezydent_w_roku(list, 1843);
    // print result
    std::cout << "\nWYNIK\n3. Napiszfunkcję, która zwróci prezydenta rządzącego w podanym roku\n";
    std::cout << 
    president.name << " " << 
    president.surname << " " <<
    president.year_start << " " << 
    president.year_end << " " << 
    president.party << std::endl;

    /*
    // mini test insert_after, insert_before
    Node node(new President("imie", "nazwisko", 2024,2025,"partia"));
    List insert_list;
    // after tail
    // before head

    //after, before while empty

    insert_list.insert_after(nullptr, new Node(node));
    insert_list.insert_before(nullptr, new Node(node));

    Node* n1 = new Node(new President( *(node.value) ));
    insert_list.push_back(n1);
    insert_list.print_list();


    node.value->name = "1111";
    insert_list.insert_after(n1, new Node(new President( *(node.value) )));
    insert_list.print_list();
    node.value->name = "2222";
    insert_list.insert_before(n1, new Node(new President( *(node.value) )));
    insert_list.print_list();
    */

    return 0;
}

// function definitions
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
    }

    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    buffer[idx] = token;

    return buffer;
}

void load_presidents_data(List& list){
    std::string line;
    std::ifstream file("presidents.txt");

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::string* buffer = split(line, " ");

            // file decoding
            std::string s3 = buffer[2];

            std::string name = buffer[0];
            std::string surname;
            int year_start;
            int year_end;
            std::string party;

            int offset = 0;
            // HANDLE: double name 
            // if date on s3 then set offset => s1 and s2 are names
            char c = s3[0];
            if( !(48 <= c && c <= 57) ){
                name += " " + buffer[1];
                offset = 1;
            }
            surname = buffer[1+offset];
            // data extract:
            // yyyy-yyyy
            // 0-4  5-8
            year_start = std::stoi(buffer[2+offset].substr(0,4));
            year_end = std::stoi(buffer[2+offset].substr(5,4));
            party = buffer[3+offset];
            party.erase(party.length() - 1);    // usunięcie '\r' konca linii

            President* new_president = new President(name, surname, year_start, year_end, party);

            list.push_back(new Node(new_president));
        }
        file.close();
    }
    else std::cout << "Unable to open file";
}

// zadanie 1
List najkrotszy_czas(List& list){
    Node* ptr = list.head;

    int results_count = 0;
    List results;
    int min_time = 9999;
    while(ptr != nullptr){
        int diff = ptr->value->year_end - ptr->value->year_start;
        if(diff < min_time){
            min_time = diff;
            results = List();
            results.push_back(new Node(ptr->value));
            results_count=1;
        }
        else if(diff == min_time){
            results_count++;
            results.push_back(new Node(ptr->value));
        }

        ptr = ptr->next;
    }

    return results;
}

// zadanie 2
List dana_partia(List& list, std::string party){
    Node* ptr = list.head;

    List results;

    while(ptr != nullptr){
        if ( ptr->value->party == party ){
            results.push_back(new Node(ptr->value));
        }

        ptr = ptr->next;
    }

    return results;
}

// zadanie 3
President prezydent_w_roku(List& list, short year){
    President* result;
    Node* node_ptr = list.head;

    while (node_ptr != nullptr)
    {
        if(node_ptr->value->year_start <= year && year <= node_ptr->value->year_end){
            return *(node_ptr->value);
        }

        node_ptr = node_ptr->next;
    }
    
    // std::cerr << "Exception: President not found\n";
    return President("","",0,0,"");
}
