#include<iostream>
#include "Direction.hpp"
#include<string>
#include <stdexcept>
#include<map>
using namespace std;

namespace ariel{
    class Notebook{
    public:
    map<int,map<int,string>> notebook;
    //Constructor
    Notebook(){
        
    };


    static void write(int page, int row, int column, Direction dir, string const &text);
    static void erase(int page, int row, int column, Direction dir, int len);
    static string read(int page, int row, int column, Direction dir, int len);
    void show(int page);
    };
    
}