#include "huffman_tree.h"


std::string file_as_string(std::string file){
    std::ifstream in(file);
    std::string string((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());
    return string;
}

void test_encode_decode(const huffman_tree &tree, const std::vector<std::string> &files_to_test) {
    for(std::string file_name: files_to_test) {
        std::string encoded_string = tree.encode(file_name);

//        bool valid_chars = true;
//        for(char c: encoded_string) {
//            valid_chars &= (c == '0') || (c == '1');
//        }
        //CHECK(valid_chars);
        bool check = tree.decode(encoded_string) == file_as_string(file_name);

        std::cout << check;
    }
}


int main() {

    huffman_tree tree("spaces.txt");

        std::string encoded_string = tree.encode("spaces.txt");
       bool check = (encoded_string.length() == 9);

        std::vector<std::string> files_to_test = {"spaces.txt"};
        test_encode_decode(tree, files_to_test);


    return 0;

}