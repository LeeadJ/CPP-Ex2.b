#include "Notebook.hpp" // (includes: Direction.hpp, iostream, string, stdexcept)

// The Notebook is restricted to 100 elements.
const int MAX_COL = 100;

namespace ariel{
    //Constructor
    Notebook::Notebook(){}

    void Notebook::write( int page, int row, int column, Direction dir, std::string const &text){
        if(column > MAX_COL){
            throw std::runtime_error("Column input Exceeds the size Restriction!");
        }
        if((text.length() > MAX_COL && dir == Direction::Horizontal)){
            throw std::runtime_error("Text input Exceeds the Column size Restriction!");
        }
        if(page<0 || row<0 || column<0){
            throw std::runtime_error("Negative input Error!");
        }
    }
    void Notebook::erase( int page, int row, int column, Direction dir, int len){
        if(column > MAX_COL){
            throw std::runtime_error("Column input Exceeds the size Restriction!");
        }
        if((len > MAX_COL && dir == Direction::Horizontal) || (len + column > MAX_COL && dir == Direction::Horizontal)){
            throw std::runtime_error("Erasing length Exceeds the Column size Restriction!");
        }
        if(page<0 || row<0 || column<0 || len<0){
            throw std::runtime_error("Negative input Error!");
        }

    }
    std::string Notebook::read( int page, int row, int column, Direction dir, int len){
        if(column > MAX_COL){
            throw std::runtime_error("Column input Exceeds the size Restriction!");
        }
        if((len > MAX_COL && dir == Direction::Horizontal) || (len + column > MAX_COL && dir == Direction::Horizontal)){
            throw std::runtime_error("Reading length Exceeds the Column size Restriction!");
        }
        if(page<0 || row<0 || column<0 || len<0){
            throw std::runtime_error("Negative input Error!");
        }
        return "Function read";
    }
    void Notebook::show(int page){

    }
}