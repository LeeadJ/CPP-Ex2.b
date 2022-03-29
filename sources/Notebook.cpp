#include<iostream>
#include "Direction.hpp"
#include<string>
#include <stdexcept>
#include<map>
#include "Notebook.hpp" 

// The Notebook is restricted to 100 elements.
const int MAX_COL = 100;

void  ariel::Notebook::write(int page, int row, int column, Direction dir, std::string const &text){
    //Here I added cases which throw errors:
    if(column > MAX_COL){
            throw std::runtime_error("Column input Exceeds the size Restriction!");
    }
    if(text.length() > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Text size Exceeds the Column size Restriction!");
    }
    if(column + text.length() > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Text size of (input + starting column) Exceeds the Column size Restriction!");
    }
    if(page<0 || row<0 || column<0){
        throw std::runtime_error("Negative input Error!");
    }
    if(space_Occupied(page, row, column, dir, text)){
        throw std::runtime_error("Current space occupied. Can not over-write wanted text!");
    }

    //If the function reached this line, the space is NOT occupied.

    //Checking direction:
    int text_index=0;
    //If the page doesn't exist:
    if(this->notebook.count(page) == 0)
        this->create_newPage(page);
    //If the row doesn't exist:
    if(this->notebook[page].count(row) == 0)
        this->create_newRow(page, row);

    if(dir == Direction::Horizontal){
        for(int i=column; i<column+text.length(); i++, text_index++){ 
             this->notebook[page][row][i] = text[text_index];
            }
        }
    //Direction is Vertical:
    else{
        for(int i=row; i<row+text.length(); i++, text_index++){
            //If the row doesn't exist:
            if(this->notebook[page].count(i) == 0)
                this->create_newRow(page, i);
            this->notebook[page][i][column] = text[text_index];
        }
    }
}

void ariel::Notebook::erase( int page, int row, int column, Direction dir, int len){
    if(column > MAX_COL){
        throw std::runtime_error("Column input Exceeds the size Restriction!");
    }
    if((len > MAX_COL && dir == Direction::Horizontal) || (len + column > MAX_COL && dir == Direction::Horizontal)){
        throw std::runtime_error("Erasing length Exceeds the Column size Restriction!");
    }
    if(column + len > MAX_COL && dir == Direction::Horizontal){
        throw std::runtime_error("Erasing length Exceeds the Column size Restriction!");
    }
    if(page<0 || row<0 || column<0 || len<0){
        throw std::runtime_error("Negative input Error!");
    }   

    //Initializing Page and Row in case it doesn't exist:
    if(this->notebook.count(page) == 0)
        this->create_newPage(0);
    if(this->notebook[page].count(row) == 0)
        this->create_newRow(page, row);

    if(dir == Direction::Horizontal){
        for(int i=column; i< column+len; i++){
            this->notebook[page][row][i] = '~';
        }
    }
    //The Direction is Vertical:
    else{
        for(int i=row; i<row+len; i++){
            if(this->notebook[page].count(i) == 0)
                this->create_newRow(page, i);
            this->notebook[page][i][column] = '~';
        }
    }
}

std::string ariel::Notebook::read( int page, int row, int column, Direction dir, int len){
    if(column > MAX_COL){
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
    std::string ans = "";
    //Initializing Page and Row in case it doesn't exist:
    if(this->notebook.count(page) == 0)
        this->create_newPage(page);
    if(this->notebook[page].count(row) == 0)
        this->create_newRow(page, row);

    if(dir==Direction::Horizontal){
        for(int i=column; i<column+len; i++){
            ans += this->notebook[page][row][i];
        }
    }
    //The direction is Vertical:
    else{
        for(int i=row; i<row+len; i++){
            //Initializing row in case it doesn't exist:
            if(this->notebook[page].count(i) == 0)
                this->create_newRow(page, i);
            ans += this->notebook[page][i][column];
        }
    }

    return ans;
}

void ariel::Notebook::show(int page){
    if(page<0)
        throw std::runtime_error("Negative Input Error!");
    //If the page doesn't exist:
    if(this->notebook.count(page) == 0){
        this->create_newPage(page);
        std::cout << "\tPage number: "<< page << "  (This Page is Empty)" << std::endl;
        for(int i=0; i<10; i++){
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

/*Function to check if the wanted spot to write is occupied.
  Returns true if the space is occupied and false if not.*/
bool ariel::Notebook::space_Occupied(int page, int row, int column, Direction dir, std::string const &text){
    bool ans = false;
    //Here I check if the page and row exist by checking if their key count is not 0:    
    if(this->notebook.count(page) != 0){
        if(this->notebook[page].count(row) != 0){
            //Check the direction of the text:
            int text_index=0;
            if(dir == Direction::Horizontal){
                for(int i=column; i<column+text.length(); i++, text_index++){ 
                    if(this->notebook[page][row][i] != '_' && text[text_index] != '_')
                        ans = true;
                }
                // std::string temp = this->notebook[page][row].substr(column, text.length());
                // std::string str(len, '_');
                // if(temp.find(str) == std::string::npos)
                //     ans = true;

            }
            //The direction is Vertical:
            else{
                for(int i=row; i<row + text.length(); i++, text_index++){
                    //Here I check if the row was previously initialzied. If not - no need to check if index is occupied.
                    if(this->notebook[page].count(row) != 0){
                        int index = column;
                        std::string temp_row = (std::string)this->notebook[page][i];
                        if(temp_row.at(index) != '_' && text[text_index] != '_')
                            ans = true;
                    }
                }
            }
        }
    }
    
    // if(ans==false)
    //     std::cout << "Space is Not occupied" << std::endl;
    // else
    //     std::cout << "Space occupied" << std::endl;
    return ans;
}

/*Function to create a new page.*/
void ariel::Notebook::create_newPage(int page){
    this->notebook[page] = std::map<int,std::string>();
}

/*Function to create a new row.*/
void ariel::Notebook::create_newRow(int page, int row_num){
    std::string row(100, '_');
    this->notebook[page][row_num] = row;
}

// /*Function to write in a row.*/
// void ariel::Notebook::write_inRow(int row_num, )

int main(){
    using namespace ariel;
    Notebook n;
    std::string temp = "Leead";
    std::cout <<"show: "<< std::endl;
    n.show(0);

    n.write(1,4,0,Direction::Horizontal, temp);
    n.write(1,0,87,Direction::Vertical, temp);
    std::cout <<"Word: "<< temp<< std::endl;    
    std::cout <<"Read: "<< n.read(0,0,87,Direction::Vertical,10) << std::endl; 

    n.show(1);
    std::cout<<"\nErasing:\n"<<std::endl;
    n.erase(1,4,0,Direction::Horizontal,100);
    n.write(1,42,0,Direction::Horizontal, temp);
    // for(auto itr = n.notebook.begin(); itr != n.notebook.end(); itr++){
    //     std::cout << "\tPage number: "<< itr->first <<std::endl;
    //     for(auto itr_r = n.notebook[itr->first].begin(); itr_r != n.notebook[itr->first].end(); itr_r++){
    //         std::cout << itr_r->first <<": "<<itr_r->second<<std::endl;
    //     }
    // }    
    n.show(1);
    
    
    return 0;
}