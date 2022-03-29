#include "Notebook.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;
namespace ariel
{
    // function to put given char at certein entry
    void Notebook::putCharAt(int page_num, int row, int col, char c)
    {
        try
        {
            this->notebook.at(page_num).note[static_cast<std::vector<int>::size_type>(col)][row] = c;
        }
        catch (const std::exception &e)
        {
            cout << "exception at line 15\n";
        }
    }
    // function to get char from certein entry
    char Notebook::getChar(int page_num, int row, int col)
    {
        try
        {
            // check if the entry exists
            if (this->notebook.at(page_num).note[static_cast<std::vector<int>::size_type>(col)].count(row) == 1)
            {
                return this->notebook.at(page_num).note[static_cast<std::vector<int>::size_type>(col)].at(row);
            }
            return Notebook::empty_char;
        }
        catch (const std::exception &e)
        {
            cout << "error at line 25\n";
            return '_';
        }
    }
    // function to set the boundries of given page
    void Notebook::setRowsCols(int page_num, int min_row, int max_row, int min_col, int max_col)
    {
        try
        {
            if (this->notebook.at(page_num).min_row > min_row)
            {
                this->notebook.at(page_num).min_row = min_row;
            }
            if (this->notebook.at(page_num).max_row < max_row)
            {
                this->notebook.at(page_num).max_row = max_row;
            }
            if (this->notebook.at(page_num).min_col > min_col)
            {
                this->notebook.at(page_num).min_col = min_col;
            }
            if (this->notebook.at(page_num).max_col < max_col)
            {
                this->notebook.at(page_num).max_col = max_col;
            }
        }
        catch (const std::exception &e)
        {
            cout << "exception at line 59\n";
        }
    }
    void Notebook::write(int page_num, int row_num, int col_num, Direction direction, std::string s)
    {
        int const char_lower_bound = 32;
        int const char_upper_bound = 126;
        // checking for illegal inputs
        if (page_num < lower_bound || row_num < lower_bound || col_num < lower_bound)
        {
            throw invalid_argument("can't work with negative values");
        }
        if (s.length() < lower_bound || (s.length() > upper_bound && direction == Direction::Horizontal))
        {
            throw invalid_argument("length must be between 0 to 100\n");
        }
        if (col_num < lower_bound || col_num >= upper_bound || row_num < lower_bound)
        {
            throw invalid_argument("rows and cols must be valid arguments!\n");
        }
        if ((int)s.length() + col_num > upper_bound && direction == Direction::Horizontal)
        {
            throw invalid_argument("can't reach to column greater than 100\n");
        }
        if (s.find('\n') < s.length() || s.find('\t') < s.length() || s.find('\r') < s.length())
        {
            throw invalid_argument("bad input\n");
        }
        // check that the page exists
        if (this->notebook.count(page_num) == 0)
        {
            Page page = Page(page_num);
            this->notebook.insert({page_num, page});
        }
        if (s.length() == 0)
        {
            return;
        }
        // write for the case that the direction is horizontal
        if (direction == Direction::Horizontal)
        {
            // run over the length of the string to check for empty entry
            for (unsigned int i = 0; i < s.length(); i++)
            {
                char c = getChar(page_num, row_num, col_num + (int)i);
                char string_char = s.at(i);
                // check that every char of the string is legal
                if (string_char < char_lower_bound || string_char > char_upper_bound)
                {
                    throw invalid_argument("can't put these chars\n");
                }
                if (c != '_' || string_char == '~')
                {
                    throw invalid_argument("cannot override already written char\n");
                }
            }

            try
            {
                // set boundries
                setRowsCols(page_num, row_num, row_num, col_num, col_num + (int)s.length() - 1);
                // write
                for (unsigned int j = 0; j < s.length(); j++)
                {
                    putCharAt(page_num, row_num, col_num + (int)j, s.at(j));
                }
            }
            catch (const std::exception &e)
            {
                cout << "exception at line 101\n";
            }
        }
        // for the case that the direction is vertical
        else
        {
            // check that the entries are empty
            for (unsigned int i = 0; i < s.length(); i++)
            {
                char c = getChar(page_num, row_num + (int)i, col_num);
                char string_char = s.at(i);
                // check that every char of the string is legal
                if (string_char < char_lower_bound || string_char > char_upper_bound)
                {
                    throw invalid_argument("can't put these chars\n");
                }
                if (c != '_' || string_char == '~')
                {
                    throw invalid_argument("cannot override already written char\n");
                }
            }
            try
            {
                // set boundries
                setRowsCols(page_num, row_num, row_num + (int)s.length() - 1, col_num, col_num);
                // write
                for (unsigned int j = 0; j < s.length(); j++)
                {
                    putCharAt(page_num, row_num + (int)j, col_num, s.at(j));
                }
            }
            catch (const std::exception &e)
            {
                cout << "exception at line 131\n";
            }
        }
    }
    std::string Notebook::read(int page_num, int row_num, int col_num, Direction direction, int length)
    {
        // check for illegal inputs
        if (page_num < lower_bound || row_num < lower_bound || col_num < lower_bound || col_num >= upper_bound)
        {
            throw invalid_argument("can't work with negative values");
        }
        if (length < lower_bound || (length > upper_bound && direction == Direction::Horizontal))
        {
            throw invalid_argument("length must be between 0 to 100\n");
        }
        if (length + col_num > upper_bound && direction == Direction::Horizontal)
        {
            throw invalid_argument("can't reach to column greater than 100\n");
        }
        std::string sentance;
        // check that the page exists
        if (this->notebook.count(page_num) == 0)
        {
            Page page = Page(page_num);
            this->notebook.insert({page_num, page});
        }
        // read the string verticaly
        if (direction == Direction::Vertical)
        {

            for (int i = 0; i < length; i++)
            {
                sentance += getChar(page_num, row_num + i, col_num);
            }
        }
        // read the string horizontaly
        else
        {
            for (int i = 0; i < length; i++)
            {
                sentance += getChar(page_num, row_num, col_num + i);
            }
        }
        return sentance;
    }
    void Notebook::erase(int page_num, int row_num, int col_num, Direction direction, int length)
    {
        // check for ilegal values
        if (page_num < lower_bound || row_num < lower_bound || col_num < lower_bound || col_num >= upper_bound)
        {
            throw invalid_argument("can't work with negative values");
        }

        if (length < lower_bound || (length >= upper_bound && direction == Direction::Horizontal))
        {
            throw invalid_argument("length must be between 0 to 100\n");
        }
        if (length + col_num > upper_bound && direction == Direction::Horizontal)
        {
            throw invalid_argument("can't reach to column greater than 100\n");
        }
        if (this->notebook.count(page_num) == 0)
        {
            Page page = Page(page_num);
            this->notebook.insert({page_num, page});
        }
        if (direction == Direction::Vertical)
        {
            setRowsCols(page_num, row_num, row_num, col_num, row_num + length);
            // erase = write ~
            for (int i = 0; i < length; i++)
            {
                putCharAt(page_num, row_num + i, col_num, '~');
            }
        }
        else
        {
            setRowsCols(page_num, row_num, row_num, col_num, col_num + length);
            // erase = write ~
            for (int i = 0; i < length; i++)
            {
                putCharAt(page_num, row_num, col_num + i, '~');
            }
        }
    }

    void Notebook::show(int page_num)
    {

        if (page_num < lower_bound)
        {
            throw invalid_argument("can't work with negative values");
        }
        if (this->notebook.count(page_num) == 0)
        {
            Page page = Page(page_num);
            this->notebook.insert({page_num, page});
        }
        int const max_bound_curr = 99;
        int const min_bound_curr = 0;
        int min_curr_row = 0;
        int min_curr_col = 0;
        int max_curr_col = 0;
        int max_curr_row = this->notebook.at(page_num).max_row + 1;
        // set the boundries for the show function
        if (this->notebook.at(page_num).min_row == min_bound_curr)
        {
            min_curr_row = 0;
        }
        else
        {
            min_curr_row = this->notebook.at(page_num).min_row;
            min_curr_row--;
        }
        if (this->notebook.at(page_num).min_col == min_bound_curr)
        {
            min_curr_col = 0;
        }
        else
        {
            min_curr_col = this->notebook.at(page_num).min_col;
            min_curr_col--;
        }
        if (this->notebook.at(page_num).max_col == max_bound_curr)
        {
            max_curr_col = max_bound_curr;
        }
        else
        {
            max_curr_col = this->notebook.at(page_num).max_col;
            max_curr_row++;
        }
        // show the page
        for (int i = min_curr_row; i < max_curr_row; i++)
        {
            std::cout << "Row " << i << ":  ";
            for (int j = min_curr_col; j <= max_curr_col; j++)
            {
                std::cout << getChar(page_num, i, j);
            }
            std::cout << "\n";
        }
    }
}