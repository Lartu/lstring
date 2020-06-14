/*  _     _        _             
   | |   | |      (_)            
   | |___| |_ _ __ _ _ __   __ _ 
   | / __| __| '__| | '_ \ / _` |
   | \__ \ |_| |  | | | | | (_| |
   |_|___/\__|_|  |_|_| |_|\__, |
   A simple, UTF8 string      | |
   library for C++ by Lartu  _/ | 
   github.com/lartu/lstring |_*/

/*
Usage:
// Initializing a new lstring:
lstring foo1;
lstring foo2 = "Hello world";
lstring foo3 = -18.22;
lstring foo4 = (string)"Hi there!";

// Getting the length of an lstring:
size_t len = lstring.length();

// Using an lstring with a stream;
lstring myLstring = "Hello world!";
stream << myLstring << endl;

// Appending values to an lstring
myLstring.append(foo2);
myLstring.append("Bye!");
myLstring.append((string)"Bye again!");
myLstring.append(67.5);

// Obtaining grapheme at given index
lstring helloWorldChinese = "你好，世界！";
lstring firstGraph = helloWorldChinese.graphat(0);
// firstGraph now equals "你"

// Obtaining substrings
lstring worldInChinese = helloWorldChinese.substr(3, 2);
// worldInChinese now equals "世界"

// Obtaining a string from an lstring
string world_in_chinese = worldInChinese;

// Obtaining a double from an lstring
lstring numericValue = 123.456;
double myVal = numericValue;
*/

#ifndef __lstring__
#define __lstring__
#include <string>
#include <vector>
#include <iostream>

class lstring
{
private:
    std::vector<char> characters;

    void append_cstr(const char * str)
    // Appends a C string to this lstring.
    // Complexity: O(n)
    // Where n is the length of str
    {
        size_t i = 0;
        size_t grapheme_length;
        unsigned char code_unit;
        while(true)
        {
            code_unit = str[i];
            if(code_unit == '\0') break;
            // Get total length of grapheme
            if(code_unit <= 127)
                grapheme_length = 1;
            else if((code_unit & 0xE0) == 0xC0) 
                grapheme_length = 2;
            else if((code_unit & 0xF0) == 0xE0) 
                grapheme_length = 3;
            else if((code_unit & 0xF8) == 0xF0) 
                grapheme_length = 4;
            // Push every code point in the grapheme
            for(size_t gc = 0; gc < 4; ++gc)
            {
                if(gc < grapheme_length)
                {
                    this->characters.push_back(str[i + gc]);
                }
                else
                {
                    this->characters.push_back(0);
                }
            }
            i += grapheme_length;
        }
    }

    std::string str_to_num(const double & number)
    {
        std::string number_string = std::to_string(number);
        number_string.erase(number_string.find_last_not_of('0') + 1, std::string::npos);
        number_string.erase (number_string.find_last_not_of('.') + 1, std::string::npos);
        return number_string;
    }

public:
    lstring()
    // Creates a new, empty lstring.
    // Complexity: O(1)
    {
    }
    
    lstring(const std::string & str)
    // Creates a new lstring from a C++ string.
    // Complexity: O(n)
    // Where n is the length of str
    {
        this->characters.clear();
        append_cstr(str.c_str());
    }
    
    lstring(const char * str)
    // Creates a new lstring from a C string.
    // Complexity: O(n)
    // Where n is the length of str
    {
        this->characters.clear();
        append_cstr(str);
    }

    lstring(const double & number)
    // Creates a new lstring from a double.
    // Complexity: >= O(n)
    // Where n is the length of str
    {
        this->characters.clear();
        append_cstr(str_to_num(number).c_str());
    }

    size_t length()
    // Returns the number of graphemes in this lstring
    // Complexity: O(1)
    {
        return this->characters.size() / 4;
    }

    friend std::ostream & operator << (std::ostream &out, const lstring &str)
    // Pushes every grapheme in this lstring, code point by
    // code point, into an output stream.
    // Complexity: O(n)
    // Where n is the number of graphemes in this lstring.
    {
        for(const char & code_unit : str.characters)
        {
            out << code_unit;
        }
        return out;
    }

    void append(const lstring & str)
    // Appends the contents of the lstring str to this lstring.
    // Complexity: O(n)
    // Where n is the number of graphemes in str.
    {
        for(const char & code_unit : str.characters)
        {
            this->characters.push_back(code_unit);
        }
    }

    void append(const std::string & str)
    // Appends the contents of the C++ string str to this lstring.
    // Complexity: O(n)
    // Where n is the length of str.
    {
        this->append_cstr(str.c_str());
    }

    void append(const char * str)
    // Appends the contents of the C string str to this lstring.
    // Complexity: O(n)
    // Where n is the length of str.
    {
        this->append_cstr(str);
    }
    

    void append(const double & number)
    // Creates a new lstring from a double.
    // Complexity: >= O(n)
    // Where n is the length of str
    {
        append_cstr(str_to_num(number).c_str());
    }

    lstring substr(size_t from, size_t count)
    // Returns an lstring with 'count' graphemes,
    // from the 'from' grapheme of this lstring.
    // If not enough graphemes can be obtained, it returns
    // as much graphemes as it can.
    // Complexity: O(count)
    {
        from = from * 4;
        count = count * 4;
        lstring new_lstring;
        for(size_t i = 0; i < count; ++i)
        {
            if(from + i < this->characters.size())
            {
                new_lstring.characters.push_back(
                    this->characters[from + i]
                );
            }
            else break;
        }
        return new_lstring;
    }

    lstring graphat(size_t index)
    // Returns the grapheme at the given index from this lstring.
    // If the given index is bigger than the length of this
    // lstring, an empty lstring is returned instead.
    // Complexity: O(1)
    {
        return this->substr(index, 1);
    }

    operator std::string() const
    // Converts this lstring to a C++ string.
    // Complexity: O(n)
    // Where n is the length of this lstring.
    {
        std::string return_value = "";
        for(const char & code_unit : this->characters)
        {
            if(code_unit != 0) return_value += code_unit;
        }
        return return_value;
    }

    operator double() const
    // Converts this lstring to a double.
    // If the conversion fails, an exception is risen.
    // Complexity: O(n)
    // Where n is the length of this lstring.
    {
        std::cout << "STOD: " << ((std::string) *this) << std::endl;
        return std::stod((std::string) *this);
    }
};

#endif
