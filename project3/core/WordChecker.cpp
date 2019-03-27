// WordChecker.cpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <iostream>

WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::vector<std::string> wordSuggestions;

    for(int i = 0; i < word.length()-1; ++i){
        for(int j = i+1; j < word.length(); ++j)
        {
            std::string temp = word;
            std::swap(temp[i],temp[j]);
            
            if(wordExists(temp) == true){// && (std::find(wordSuggestions.begin(),wordSuggestions.end(), temp) != wordSuggestions.end()))
          //      std::cout << " done checking" << std::endl;
                if(std::find(wordSuggestions.begin(),wordSuggestions.end(),temp) != wordSuggestions.end()){}

                else
                {
                    wordSuggestions.push_back(temp);
                }
            }
       }
    }



    for(int i = 0; i < word.length(); ++i)
    {
        for(int j = 65; j < 90; ++j)
        {
            std::string temp1 = word;
            char x = (char)(j);
            std::string y(1,x);
            temp1.insert(i,y);
            if(wordExists(temp1) == true){// && (std::find(wordSuggestions.begin(),wordSuggestions.end(),temp1) != wordSuggestions.end()))
                if(std::find(wordSuggestions.begin(),wordSuggestions.end(),temp1) != wordSuggestions.end()){}
                {
                    wordSuggestions.push_back(temp1);
                }
            }
        }
    }



    for(int i = 0; i < word.length(); ++i)
    {
        std::string temp2 = word;
        temp2.erase(i,(i+1));

        if(wordExists(temp2) == true){// && (std::find(wordSuggestions.begin(),wordSuggestions.end(),temp2) != wordSuggestions.end()))
            if(std::find(wordSuggestions.begin(),wordSuggestions.end(),temp2) != wordSuggestions.end()){}
            else
                wordSuggestions.push_back(temp2);
        }
    }




    for(int i = 0; i < word.length(); ++i)
    {
        for(int j = 65; j < 90; ++j)
        {
            std::string temp3 = word;
            char x = (char)(j);
            temp3[i] = (char)x;
        
            if(wordExists(temp3) == true){// && (std::find(wordSuggestions.begin(),wordSuggestions.end(),temp3) != wordSuggestions.end()))
                if(std::find(wordSuggestions.begin(),wordSuggestions.end(),temp3) != wordSuggestions.end()){}
                else
                    wordSuggestions.push_back(temp3);
            }
        }
    }


    for(int i = 0; i < word.length(); ++i)
    {
        std::string temp4 = word;
        std::string temp5 = temp4.substr(i,word.length());
        temp4 = temp4.substr(0, i-1);

        if(wordExists(temp4) == true && wordExists(temp5) == true)// && (std::find(wordSuggestions.begin(),wordSuggestions.end(), temp4) != wordSuggestions.end()))
        {

            if(std::find(wordSuggestions.begin(),wordSuggestions.end(),temp4) != wordSuggestions.end()){}
            else
                wordSuggestions.push_back(temp4);
//        }

 //       if(wordExists(temp4) == true && wordExists(temp5) == true && (std::find(wordSuggestions.begin(),wordSuggestions.end(),temp5) != wordSuggestions.end()))
//        {

                if(std::find(wordSuggestions.begin(),wordSuggestions.end(),temp5) != wordSuggestions.end()){}
            else
                wordSuggestions.push_back(temp5);
        }
    }

    return wordSuggestions;
}

/*
std::vector<std::string> WordChecker::suggestionOne(const std::string& word) const
{
    std::vector<std::string> one;

    for(int i = 0; i < word.length()-1; ++i){
        for(int j = i+1; j < word.length(); ++j)
        {
            std::string temp = word;
            std::swap(temp[i],temp[j]);
            
            if(wordExists(temp) == true)
                one.push_back(temp);
        }
    }

    return one;

}

std::vector<std::string> WordChecker::suggestionTwo(const std::string& word) const
{
    std::vector<std::string> two;

    for(int i = 0; i < word.length(); ++i)
    {
        for(int j = 97; j < 122; ++j)
        {
            std::string temp = word;
            char x = (char)(j);
            std::string y(1,x);

            if(wordExists(temp) == true)
                two.push_back(temp);

        }
    }

    return two;
}

std::vector<std::string> WordChecker::suggestionThree(const std::string& word) const
{
    std::vector<std::string> three;

    for(int i = 0; i < word.length(); ++i)
    {
        std::string temp = word;
        temp.erase(i,(i+1));

        if(wordExists(temp) == true)
            three.push_back(temp);
    }

    return three;
}

std::vector<std::string> WordChecker::suggestionFour(const std::string& word) const
{
    std::vector<std::string> four;

    for(int i = 0; i < word.length(); ++i)
    {
        for(int j = 97; j < 122; ++j)
        {
            std::string temp = word;
            char x = (char)(j);
            temp[i] = (char)x;

            if(wordExists(temp) == true)
                four.push_back(temp);
        }
    }

    return four;
}

std::vector<std::string> WordChecker::suggestionFive(const std::string& word) const
{
    std::vector<std::string> four;

    for(int i = 0; i < word.length(); ++i)
    {
        std::string temp = word;
        std::string temp2 = temp.substr(i,word.length());
        temp = temp.substr(0, i-1);

        if(wordExists(temp) == true && wordExists(temp2) == true)
            five.push_back(temp);
    }
}*/
