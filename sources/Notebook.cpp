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

//Helper Functions:

/*Function to create a new page.*/
void ariel::Notebook::create_page(int page){
    this->notebook[page] = std::map<int,std::string>();
}

// /*Function to create a new row.*/
// void ariel::Notebook::create_row(int page, int row_num){
//     std::string row(100, '_');
//     // this->notebook[page].insert()
//     row.replace(10, 6, "Leead");
//     std::cout<<row<<std::endl;
//     std::cout << row.length()<<std::endl;
//     std::cout<<typeid(row).name()<<std::endl;
// }
// int main(){
//     using namespace ariel;
//     Notebook n;
//     n.create_page(10);
//     n.create_page(3);
//     n.create_page(160);
//     n.create_page(30);
//     for(auto itr = n.notebook.begin(); itr != n.notebook.end(); itr++){
//         std::cout << itr->first <<std::endl;
//     } 

//     return 0;
// }
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