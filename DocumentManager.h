#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

class DocumentManager{
    private:
        std::unordered_map<int, std::pair<std::string, int>> documentMap;
        std::unordered_map<int, std::vector<std::string>> patronMap;
        std::unordered_map<std::string, int> documentMapSearch;
    public:
        void addDocument(std::string name, int id, int license_limit){
            documentMap.insert(std::make_pair(id, std::make_pair(name, license_limit)));
            documentMapSearch.insert(std::make_pair(name, id));
        };
        void addPatron(int patronID){
            patronMap.insert(std::make_pair(patronID, std::vector<std::string>{}));
        };
        bool borrowDocument(int docid, int patronID){
            auto docFind = documentMap.find(docid);
            auto patronFind = patronMap.find(patronID);
            if (docFind != documentMap.end() && docFind->second.second > 0 && patronFind != patronMap.end()){
                docFind->second.second--;
                patronFind->second.push_back(docFind->second.first);
                return true;
            } else {
                return false;
            }
        };
        void returnDocument(int docid, int patronID){
            auto docFind = documentMap.find(docid);
            auto patronFind = patronMap.find(patronID);
            if (docFind != documentMap.end() && patronFind != patronMap.end()){
                auto& patronDocs = patronFind->second;
                auto docName = docFind->second.first;

                auto findDoc = std::find(patronDocs.begin(), patronDocs.end(), docName);
                if (findDoc != patronDocs.end()){
                    patronDocs.erase(findDoc);
                    docFind->second.second++;
                }
                
            }
        }
        int search(std::string name){
            std::unordered_map<std::string,int>::const_iterator got = documentMapSearch.find(name);
            if (got != documentMapSearch.end()){
                return got->second;
            } else {
                return 0;
            }

        }
        DocumentManager(){

        };
};

#endif