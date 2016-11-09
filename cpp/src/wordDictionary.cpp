#include <unordered_set>
#include <map>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;


class WordDictionary {
    public:
        bool isEnd;
        map<char, WordDictionary> m;

        WordDictionary()
        {
            isEnd = false;
        }
        // Adds a word into the data structure.
        void addWord(string word) {
            add_help(word, 0);
        }

        void add_help(string &word, int idx){
            if(idx==word.length()-1){
                isEnd=true;
            }
            if(m.find(word[idx]) == m.end()){
                m[word[idx]] = WordDictionary();
            }
            if(idx<word.length()-1)
                m[word[idx]].add_help(word, idx+1);    
        }

        // Returns if the word is in the data structure. A word could
        // contain the dot character '.' to represent any one letter.
        // bo
        bool search(string word) {
            return search_help(word, 0);
        }

        bool search_help(string &word, int idx){
            bool ret = false;

            if(idx==word.length()) 
                if(isEnd)
                    return true;
                else
                    return false;

            if(word[idx] == '.'){
                for(auto x : m)
                    if(x.second.search_help(word, idx+1))
                        return true;
            }
            else {
                if(m.find(word[idx])==m.end()) return false;
                ret = m[word[idx]].search_help(word, idx+1);
            }
            return ret;
        }
};

int main(int argc, char*argv[]){
    WordDictionary d;
    FILE *reader = fopen("test1.txt", "r");
    int line_num = 0;
    fscanf(reader, "%d\n", &line_num);
    for(int i=0; i<line_num;i++){
        char str1[128];
        char str2[128];

        fscanf(reader, "%s %s\n", str1, str2);
        string s1 = str1;
        string s2 = str2;
        if(s1=="a"){
            //cout<<"add "<<s2<<endl;
            d.addWord(s2);
        }
        if(s1=="s"){
            d.search(s2);
        }
    }

    fclose(reader);
    return 1;
}
