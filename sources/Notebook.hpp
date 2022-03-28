#include<iostream>
#include "Direction.hpp"
#include<string>
#include <stdexcept>
#include<map>

namespace ariel{
    class Notebook{
    public:
    std::map<int,std::map<int,std::string>> notebook;
    //Constructor
    Notebook(){}
    //deConstructor
    ~Notebook(){}

    void write(int page, int row, int column, Direction dir, std::string const &text);
    void erase(int page, int row, int column, Direction dir, int len);
    std::string read(int page, int row, int column, Direction dir, int len);
    void show(int page);
    };
    
}