#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

#include "BST_Tree.h"
#include "deque.h"

class Book{
public:
    std::string title;
    std::string author;
    int count;
    std::tm date;

    Book() : title(""), author(""), count(0){}
    Book(std::string title, std::string author, std::tm date, int count = 0) : title(title), author(author), count(count), date(date){}

    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

std::ostream& operator<<(std::ostream& os, const Book& book) {
    // Wypisanie tytułu i autora
    os << "Title: " << book.title << "\n"
       << "Author: " << book.author << "\n"
       << "Count: " << book.count << "\n"
       << "Date: "
       << std::put_time(&book.date, "%Y-%m-%d") << "\n"; // Formatowanie daty

    return os;
}

bool compareTitle(std::string new_el, std::string old_el){
    int len = std::min(new_el.length(), old_el.length());

    for(int i = 0; i < len; i++){
        if(new_el[i] < old_el[i]) return true;
    }

    return false;
}

struct compareBook {
    bool operator()(const Book& new_book, const Book& old_book) const {
        return compareTitle(new_book.title, old_book.title);
    }
};

class Library{
private:
    BST_Node<Book, compareBook>* _findBookNodeCore(BST_Node<Book, compareBook>* node, std::string title);
public:
    BST_Node<Book, compareBook> books;

    void addBook(std::string title, std::string author, std::tm date);
    void removeBook(std::string title);
    Book* findBook(std::string title);
    BST_Node<Book, compareBook>* findBookNode(std::string title);
    void printBooks();
    Book topTitleBook();
    Book bottomTitleBook();
    Deque<Book> booksFromPeriod(std::tm from, std::tm to);

};

int main(int argc, char const *argv[])
{
    std::tm date = {};
    date.tm_year = 2023 - 1900;  // Year since 1900
    date.tm_mon = 5 - 1;         // Month (0-based, January = 0)
    date.tm_mday = 15; 

    Library lib;
    lib.addBook("aaa", "autor", date);
    lib.addBook("bbb", "autor", date);
    lib.addBook("ccc", "autor", date);

    lib.printBooks();

    std::cout << "asd: \n"<< *lib.findBook("aaa") << std::endl;

    return 0;
}

void Library::addBook(std::string title, std::string author, std::tm date)
{
    Book* b = findBook(title);

    if(!b){
        // dodaj
        this->books.insert(&(this->books), Book(title, author, date));
    }else{
        // count++
        b->count++;
    }
}

void Library::removeBook(std::string title)
{
    BST_Node<Book, compareBook>* dn = this->findBookNode(title);
    this->books.deleteNode(dn);
}

BST_Node<Book, compareBook>* Library::_findBookNodeCore(BST_Node<Book, compareBook>* node, std::string title){
    BST_Node<Book, compareBook>* p = nullptr;
    if(node->left){
        p = _findBookNodeCore(node->left, title);
        if(p) return p;
    }      

    if(node->key.title == title) return node;

    if(node->right){
        _findBookNodeCore(node->right, title);
        if(p) return p;
    }      

    return nullptr;
}

Book *Library::findBook(std::string title)
{
    return &(this->findBookNode(title)->key);
}

BST_Node<Book, compareBook>* Library::findBookNode(std::string title)
{
    return _findBookNodeCore(&(this->books), title);
}

void Library::printBooks()
{
    this->books.printNodeInOrder(&(this->books));
}


Book Library::topTitleBook()
{
    return this->books.min(&(this->books))->key;
}

Book Library::bottomTitleBook()
{
    return this->books.max(&(this->books))->key;
}

void _fromPeriod(BST_Node<Book, compareBook>* node, std::tm from, std::tm to, Deque<Book>* q){
    if(node->left){
        _fromPeriod(node->right, from, to, q);
    }      

    std::time_t time_from = std::mktime(const_cast<std::tm*>(&from));
    std::time_t time_to = std::mktime(const_cast<std::tm*>(&to));
    std::time_t time_this = std::mktime(const_cast<std::tm*>(&node->key.date));

    if(time_from <= time_this && time_this <= time_to) q->front_insert(node->key);

    if(node->right){
        _fromPeriod(node->right, from, to, q);
    }      
}

Deque<Book> Library::booksFromPeriod(std::tm from, std::tm to)
{
    Deque<Book> q;

    _fromPeriod(&(this->books),from, to, &q);

    return Deque<Book>();
}
