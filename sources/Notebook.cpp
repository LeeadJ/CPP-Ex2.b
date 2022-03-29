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
    if((text.length() > MAX_COL && dir == Direction::Horizontal)){
        throw std::runtime_error("Text input Exceeds the Column size Restriction!");
    }
    if(page<0 || row<0 || column<0){
        throw std::runtime_error("Negative input Error!");
    }
    if(space_Occupied(page, row, column, dir, text)){
        throw std::runtime_error("Current space occupied. Can not write wanted text!");
    }

    

}
void ariel::Notebook::erase( int page, int row, int column, Direction dir, int len){
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
std::string ariel::Notebook::read( int page, int row, int column, Direction dir, int len){
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
void ariel::Notebook::show(int page){

    }

/*Helper Functions:*/

/*Function to check if the wanted spot to write is occupied.
  Returns true if the space is occupied and false if not.*/
bool ariel::Notebook::space_Occupied(int page, int row, int column, Direction dir, std::string const &text){
    //Checking the actual length of the 'text' in case it starts or ends with '_'
    // len = the actual amount of consecutive indexs of '_' needed for the text.
    int i=0;
    int len = text.length();
    while(text[i]=='_'){
        len--;
        i++;
    }
    int j = text.length();
    while(text[j-1]=='_'){
        len--;
        j--;
    }
    bool ans = false;
    //Here I check if the page and row exist by checking if their key count is not 0:    
    if(this->notebook.count(page) != 0){
        if(this->notebook[page].count(row) != 0){
            //Check the direction of the text:
            if(dir == Direction::Horizontal){
                std::string temp = this->notebook[page][row].substr(column, text.length());
                std::string str(len, '_');
                if(temp.find(str) == std::string::npos)
                    ans = true;
            }
            //The direction is Vertical:
            else{
                int text_index = -1;
                for(int i=row; i<row + text.length(); i++){
                    text_index++;
                    //Here I check if the row was previously initialzied. If not - no need to check if index is occupied.
                    if(this->notebook[page].count(row) == 0)
                        continue;
                    else{
                        int index = column;
                        std::string temp_row = (std::string)this->notebook[page][i];
                        if(temp_row.at(index) != '_' && text[text_index] != '_')
                            ans = true;
                    }
                }
            }
        }
    }
    
    if(ans==false)
        std::cout << "Space is Not occupied" << std::endl;
    else
        std::cout << "Space occupied" << std::endl;
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
    for(int i=0; i<2; i++){
        n.create_newPage(i);
        for(int j=0; j<6; j++)
            n.create_newRow(i,j);
    }
        
    
    n.notebook[0][0].replace(0, 1, "L");
    n.notebook[0][1].replace(0, 1, "e");
    n.notebook[0][2].replace(0, 1, "_");
    n.notebook[0][3].replace(0, 1, "_");
    n.notebook[0][4].replace(0, 1, "d");
    std::string temp = "__ead";
    bool x = n.space_Occupied(0,0,0,Direction::Vertical, temp);
    
    std::cout << temp<< std::endl;    
    
    
    
    
    for(auto itr = n.notebook.begin(); itr != n.notebook.end(); itr++){
        std::cout << "\tPage number: "<< itr->first <<std::endl;
        for(auto itr_r = n.notebook[itr->first].begin(); itr_r != n.notebook[itr->first].end(); itr_r++){
            std::cout << itr_r->first <<": "<<itr_r->second<<std::endl;
        }
    } 
    // std::cout << temp << std::endl;    
    return 0;
}
//using namespace std locally to better understand the code.
// using namespace std;
    // //Checking if the wanted page already exists in the outer map:
    // //If the amount of times the page in the map is 0, then the page doesn't exist.
    // if(this->notebook.count(page) == 0){
    //     //Creating the page in the map:

    // }
    // else{

    // }
    // //Creating an iterator for the outer map(outer map = pages):
    // map<int,map<int,string>>::iterator itr_page = this->notebook.begin();

    // //Looping through the map. Stops if reaching the end of the map or if the wanted page key is found:
    // while(itr_page != this->notebook.end() && itr_page->first != page){
    //     itr_page++;
    // }

    // //If the wanted page hasn't been found, it hasn't been called previously. Create a new page key in the map:
    // if(itr_page == this->notebook.end()){

    // }