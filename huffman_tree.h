#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <sstream>


struct character{
    char mychar;
    int count;
    character* left;
    character* right;
    bool isChar;


    character();

};

class compareIt {
public:
    int operator() (character* one, character* two);

};

class huffman_tree {
private:
    character* huffman;
    std::vector<std::pair<char, std::vector<int>> > codes;
    std::vector<int> fakeStack;
public:
    huffman_tree(const std::string &file_name);
    ~huffman_tree();


    void visit(character* root);
    std::string get_character_code(char character) const;
    std::string encode(const std::string &file_name) const;
    std::string decode(const std::string &string_to_decode) const;


};

#endif