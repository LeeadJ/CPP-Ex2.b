#include<iostream>
#include "Direction.hpp"
#include<string>
#include <stdexcept>
#include<map>
#include "Notebook.hpp" 

// The Notebook is restricted to 100 elements.
const int MAX_COL = 100;
const int AUTO_ROW = 10;

void  ariel::Notebook::write(int page, int row, int column, Direction dir, std::string const &text){
    //Here I added cases which throw errors:
    if(text=="\n"){
        throw std::runtime_error("Write Error: Special Characters!");
    }
    if(column >= MAX_COL){
        throw std::runtime_error("Write Error: Column input Exceeds the size Restriction!");
    }
    if(text.length() > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Write Error: Text size Exceeds the Column size Restriction!");
    }
    if((unsigned int)column + text.length() > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Write Error: Text size of (input + starting column) Exceeds the Column size Restriction!");
    }
    if(page<0 || row<0 || column<0){
        throw std::runtime_error("Write Error: Negative page/row/column Input!");
    }
    for(int i=0; i<text.length(); i++){
        if(text[(unsigned int)i] < ' ' || text[(unsigned int)i] >= '~'){
            throw std::runtime_error("Write Error: Text is not Valid!");
        }
    }
    if(this->check_overWrite(page, row, column, dir, text)){
        throw std::runtime_error("Write Error: Can NOT Over-Write!");
    }
    
    //If the page doesn't exist:
    if(this->notebook.count(page) == 0){
        this->create_newPage(page);
    }
    //If the row doesn't exist:
    if(this->notebook[page].count(row) == 0){
        this->create_newRow(page, row);
    }
    
    if(space_Occupied(page, row, column, dir, text)){
        throw std::runtime_error("Current space occupied. Can not over-write wanted text!");
    }

    //If the function reached this line, the space is NOT occupied.
    //Checking direction:
    int text_index=0;
    if(dir == Direction::Horizontal){
        for(int i = column; i<(unsigned int)column+text.length(); i++, text_index++){ 
             this->notebook[page][row][(unsigned int)i] = text[(unsigned int)text_index];
            }
        }
    //Direction is Vertical:
    else{
        for(int i=row; i< (unsigned int)row+text.length(); i++, text_index++){
            //If the row doesn't exist:
            if(this->notebook[page].count(i) == 0){
                this->create_newRow(page, i);
            }
            this->notebook[page][i][(unsigned int)column] = text[(unsigned int)text_index];
        }
    }
}
/*Function to check if the wanted spot to write is occupied.
Returns true if the space is occupied and false if not.*/
bool ariel::Notebook::space_Occupied(int page, int row, int column, Direction dir, std::string const &text){
    if(dir==Direction::Horizontal){
        //Looping over the wanted indexes in the row and checking if they are occupied:
        for(int i=column; i < (text.length()+(unsigned int)column); i++){
            if(this->notebook[page][row][(unsigned int)i] != '_'){
                return true;
            }
        }
    }
    //The direction is Vertical:
    else{
        //Looping through all the potential rows. I check here ONLY the rows that currently exist:
        for(int i=row; i < ((unsigned int)row+text.length()); i++){
            if(this->notebook[page].count(i) != 0){ //If the row count isn't 0, the row exists.
                if(this->notebook[page][i][(unsigned int)column] != '_'){
                    return true;
                }
            } 
        }
    }
    return false; 
}

void ariel::Notebook::erase( int page, int row, int column, Direction dir, int len){
    if(column >= MAX_COL){
        throw std::runtime_error("Erase Error: Column input Exceeds the size Restriction!");
    }
    if(len > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Erase Error: length Input Exceeds the Column size Restriction!");
    }
    if(column + len > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Erase Error: Column + length Exceeds the Column size Restriction!");
    }
    if(page<0 || row<0 || column<0 || len<0){
        throw std::runtime_error("Erase Error: Negative page/row/column/len Input!");
    } 

    //Initializing Page and Row in case it doesn't exist:
    if(this->notebook.count(page) == 0){
        this->create_newPage(page);
    }
    if(this->notebook[page].count(row) == 0){
        this->create_newRow(page, row);
    }

    if(dir == Direction::Horizontal){
        for(int i=column; i< column+len; i++){
            this->notebook[page][row][(unsigned int)i] = '~';
        }
    }
    //The Direction is Vertical:
    else{
        // std::cout<<"here"<<std::endl;
        for(int i=row; i<(unsigned int)row+(unsigned int)len; i++){
            if(this->notebook[page].count(i) == 0){
                this->create_newRow(page, i);
            }
            this->notebook[page][i][(unsigned int)column] = '~';
        }
    }
}

std::string ariel::Notebook::read( int page, int row, int column, Direction dir, int len){
    if(column >= MAX_COL){
        throw std::runtime_error("Column input Exceeds the size Restriction!");
    }
    if((len > MAX_COL && dir == Direction::Horizontal) || (len + column > MAX_COL && dir == Direction::Horizontal)){
        throw std::runtime_error("Reading length Exceeds the Column size Restriction!");
    }
    if(column + len > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Reading length Exceeds the Column size Restriction!");
    }
    if(page<0 || row<0 || column<0 || len<0){
        throw std::runtime_error("Negative input Error!");
    }
    std::string ans;
    //Initializing Page and Row in case it doesn't exist:
    if(this->notebook.count(page) == 0){
        this->create_newPage(page);
    }
    if(this->notebook[page].count(row) == 0){
        this->create_newRow(page, row);
    }
    
    if(dir==Direction::Horizontal){
        for(int i=column; i<column+len; i++){
            ans += this->notebook[page][row][(unsigned int)i];
        }
    }
    //The direction is Vertical:
    else{
        for(int i=row; i<row+len; i++){
            //Initializing row in case it doesn't exist:
            if(this->notebook[page].count(i) == 0){
                this->create_newRow(page, i);
            }
            ans += this->notebook[page][i][(unsigned int)column];
        }
    }

    return ans;
}

void ariel::Notebook::show(int page){
    if(page<0){
        throw std::runtime_error("Negative Input Error!");
    }
        
    //If the page doesn't exist:
    if(this->notebook.count(page) == 0){
        this->create_newPage(page);
        std::cout << "\tPage number: "<< page << "  (This Page is Empty)" << std::endl;
        for(int i=0; i<AUTO_ROW; i++){
            this->create_newRow(page, i);
            std::cout << i << ": " << this->notebook[page][i] << std::endl;
        }
    }
    //The page is not empty:
    else{
        std::cout << "\tPage number: "<< page << std::endl;
        for(auto itr_r = this->notebook[page].begin(); itr_r != this->notebook[page].end(); itr_r++){
            std::cout << itr_r->first <<": "<<itr_r->second<<std::endl;
        }    
    }
}

/*Helper Functions:*/
/*Function to create a new page.*/
void ariel::Notebook::create_newPage(int page){
    this->notebook[page] = std::map<int,std::string>();
}

/*Function to create a new row.*/
void ariel::Notebook::create_newRow(int page, int row_num){
    std::string row(MAX_COL, '_');
    this->notebook[page][row_num] = row;
}

bool ariel::Notebook::check_overWrite(int page, int row, int column, Direction dir, std::string const &text){
    if(this->notebook.count(page) != 0){
        if(dir == Direction::Horizontal){
            if(this->notebook[page].count(row) != 0){//The row exists
                for(int i = column; i<(unsigned int)column+text.length(); i++){
                    if(this->notebook[page][row][(unsigned int)i] != '_'){
                        return true;
                    }
                }
            }
        }
        //Direction is Vertical:
        else{
            for(int i=row; i < (unsigned int)row+text.length(); i++){
                if(this->notebook[page].count(i) != 0){//The row exists
                    if(this->notebook[page][i][(unsigned int)column] != '_'){
                        return true;
                    }
                }
            }
        }

    }
    return false;
}
bool ariel::Notebook::check_overErase(int page, int row, int column, Direction dir, int len){
    if(this->notebook.count(page) != 0){
        if(dir == Direction::Horizontal){
            if(this->notebook[page].count(row) != 0){ //The row exists
                for(int i = column; i<(unsigned int)column+(unsigned int)len; i++){ 
                    if(this->notebook[page][row][(unsigned int)i] == '~'){
                        return true;
                    }
                }
            }
        }
        //Direction is Vertical:
        else{
            for(int i=row; i < (unsigned int)row+(unsigned int)len; i++){
                if(this->notebook[page].count(i) != 0){ //The row exists
                     if(this->notebook[page][i][(unsigned int)column] == '~'){
                         return true;
                     }
                }
               
            }
        }
    }
    return false;
}


// int main(){
//     using namespace ariel;
//     Notebook notebook;
//     std::string temp = "Leead";
//     std::string temp2 = "_eead";
//     std::string letter = "G";
//     std::string row(100, 'P');
    
//     n.write(0,0,99,Direction::Horizontal, letter);
//     n.write(0,0,50,Direction::Horizontal, temp);
//     n.write(0,0,1,Direction::Vertical, temp);
//     n.write(0,2,93,Direction::Vertical, temp);
//     n.erase(0,0,99,Direction::Vertical,3);
//     n.erase(0,1,0,Direction::Horizontal,3);

//     n.erase(0,4,80,Direction::Horizontal,20);
      
//     n.show(0);
    
    
//     std::string r = n.read(0,2,0,Direction::Horizontal,100);
//     std::cout<< "\nRead: "<<r<<std::endl;
    
//     notebook.write(1, 1, 10, Direction::Horizontal, "hello world");
//     notebook.erase(1, 1, 10, Direction::Horizontal, 11);
//     // CHECK_NOTHROW(notebook.erase(1, 1, 10, Direction::Horizontal, 11));
//     //     CHECK_NOTHROW(notebook.erase(1, 1, 16, Direction::Horizontal, 5));
//     //     CHECK_NOTHROW(notebook.erase(1, 1, 8, Direction::Horizontal, 3));
//     //     CHECK_NOTHROW(notebook.erase(1, 1, 20, Direction::Horizontal, 3));
//     notebook.show(1);
//     return 0;
// }
