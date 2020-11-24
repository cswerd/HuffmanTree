//
// Created by Catherine Swerdloff on 2019-04-18.
//

#include "huffman_tree.h"


character::character() {


    isChar = false;
    count = 0;
    left = nullptr;
    right = nullptr;

}

int compareIt::operator()(character* one, character* two) {

    return one->count > two->count;
}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Reads the contents of file_name and constructs a
				huffman tree based on the character frequencies of the file contents
*/

huffman_tree::huffman_tree(const std::string &file_name){


    std::ifstream myfile (file_name);
    char ch;
    int charCount[128] = {0};
    long count = 0;


    if (myfile.is_open()){
        while (  myfile >> std::noskipws >> ch)
        {
            charCount[(int)ch]++;
            count++;

        }
        myfile.close();
    }
    else
        return;
    //std::cout << "Unable to read file";


    //put items in minHeap

    std::priority_queue < character*, std::vector<character*>, compareIt > minHeap;

    for(int i=0; i < 128; i++) {

        if(charCount[i] != 0) {
            character *tempChar = new character();

            tempChar->isChar = true;
            tempChar->count = charCount[i];
            tempChar->mychar = i;


            minHeap.push(tempChar);

        }

    }


    while (minHeap.size() > 1) {


        character *temp1 = minHeap.top();
        minHeap.pop();
        character *temp2 = minHeap.top();
        minHeap.pop();

        int totalCount = temp1->count + temp2->count;

        character *internal = new character();

        internal->count=totalCount;
        internal->left = temp1;
        internal->right = temp2;


        minHeap.push(internal);


    }

    huffman = minHeap.top();



    visit(minHeap.top());



}

huffman_tree::~huffman_tree(){

}

/*
Preconditions: Character is a character with an ASCII value
				between 0 and 127 (inclusive).
Postconditions: Returns the Huffman code for character if character is in the tree
				and an empty string otherwise.
*/
std::string huffman_tree::get_character_code(char character) const {

    std::string code;

    bool found = false;

    for(unsigned int i=0; i<codes.size(); i++) {

        if(character == codes.at(i).first) {

            std::vector<int> theCode = codes.at(i).second;

            for(i=0; i<theCode.size(); i++) {

                code += std::to_string(theCode.at(i));

            }
            found = true;
            break;
        }

    }

    if(found)
        return code;
    else
        return "";
}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Returns the Huffman encoding for the contents of file_name
				if file name exists and an empty string otherwise.
				If the file contains letters not present in the huffman_tree,
				return an empty string
*/
std::string huffman_tree::encode(const std::string &file_name) const {


    std::ifstream myfile (file_name);
    char ch;
    std::string encoded;
    //char charCount[128];
    //long count = 0;


    if (myfile.is_open()){
        while (  myfile >> std::noskipws >> ch)
        {

            bool found = false;

            for(unsigned int i=0; i<codes.size(); i++) {

                if(ch == codes.at(i).first) {

                    std::vector<int> theCode = codes.at(i).second;

                    for(i=0; i<theCode.size(); i++) {

                        encoded += std::to_string(theCode.at(i));

                    }
                    found = true;
                    break;
                }

            }

            if(!found) {
                encoded = "";
                break;
            }

        }
        myfile.close();
    }


        return encoded;
}

/*
Preconditions: string_to_decode is a string containing Huffman-encoded text
Postconditions: Returns the plaintext represented by the string if the string
				is a valid Huffman encoding and an empty string otherwise
*/
std::string huffman_tree::decode(const std::string &string_to_decode) const {

    std::stringstream ss (string_to_decode);

    if(string_to_decode.compare("") == 0) {
        return "";
    }

    char ch;

    std::string decoded = "";

    character* node = huffman;

    while ( ss >> std::noskipws >> ch) {

        if(!((ch == '0' )|| (ch == '1' ))) {
            decoded = "";
            return decoded;
        }

        if(node->isChar) {
            decoded += node->mychar;
            node = huffman;
        }
        if (ch == '0') {
            if(node->left != nullptr)
                node = node->left;
        }
        if (ch == '1') {
            if(node->right != nullptr)
                node = node->right;
        }

    }

    if(node == nullptr) {
        return decoded;
    }

    else if(node == huffman) {
        return decoded;
    }

    else if(node != huffman && !node->isChar) {

        decoded = "";
    }

    else
        decoded+= node->mychar;


    return decoded;
}

//algorithm (mix of DFS and Post Order Traversal) to assign character codes to unordered map

void huffman_tree::visit(character* root) {

    if(huffman->left == nullptr) {
        std::vector<int> theCode;
        theCode.push_back(1);
        codes.push_back(make_pair(root->mychar, theCode));

    }

    else if(root->isChar) {

        std::vector<int > theCode;
        for(unsigned int i=0; i < fakeStack.size(); i++) {

            theCode.push_back(fakeStack.at(i));

        }

        codes.push_back(make_pair(root->mychar, theCode));


    }

    else {

        fakeStack.push_back(0);
        visit(root->left);
        fakeStack.push_back(1);
        visit(root->right);

    }

    if(!fakeStack.empty())
        fakeStack.pop_back();

    return;
}



