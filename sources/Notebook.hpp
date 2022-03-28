#ifndef NOTEBOOK_CPP
#define NOTEBOOK_CPP

#include <unordered_map>
#include <vector>
#include <string>
#include "Direction.hpp"
struct Page
{
    std::vector<std::unordered_map<int, char>> note;
    int page_number;
    int min_row;
    int max_row;
    int min_col;
    int max_col;
    Page(int page_num) : note(std::vector<std::unordered_map<int, char>>(100))
    {
        page_number = page_num;
        min_row = 0;
        max_row = 0;
        min_col = 100;
        max_col = 0;
    }
};

using ariel::Direction;
namespace ariel
{
    class Notebook
    {
    private:
        char empty_char = '_';
        int upper_bound = 100;
        int lower_bound = 0;
        std::unordered_map<int, Page> notebook;
        void putCharAt(int page_num, int row, int col, char c);
        char getChar(int page_num, int row, int col);
        void setRowsCols(int page_num, int min_row, int max_row, int min_col, int max_col);

    public:
        void write(int page_num, int row_num, int col_num, Direction direction, std::string s);
        std::string read(int page_num, int row_num, int col_num, Direction direction, int length);
        void erase(int page_num, int row_num, int col_num, Direction direction, int length);
        void show(int page_num);
    };
}
#endif