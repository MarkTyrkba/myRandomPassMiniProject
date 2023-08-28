#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <conio.h>

//by mark "awful" tyrkba

//#define DEBUG

class yarson
{
private:
    std::vector<std::string> words{ "TRY MY BRAND NEW PASSWORD GENERATOR" };
    std::vector<std::size_t> indexes{0};
    std::size_t index = 0;
    bool isInList, RINVALID_INDEX , LINVALID_INDEX;

public:
    void keyUp()
    {
#ifdef DEBUG
        std::cout << index + 1 << std::endl;
#endif
        index++;
        indexes.push_back(index);
        generateRandomString();
        std::cout << words[words.size() - 1] << std::endl;
    }

    void keyLeft()
    {
#ifdef DEBUG
        std::cout << index - 1 << std::endl;
#endif
        if (LINVALID_INDEX)
        {
            index = 0;
            std::cout << words[index];
            LINVALID_INDEX = false;
        }
        else if (RINVALID_INDEX)
        {
            index = words.size() - 1;
            std::cout << words[index];
            RINVALID_INDEX = false;
        }

        else if (index > 0)
        {
            index--;
            indexes.push_back(index);
            std::cout << words[index] << std::endl;
        }
        else
        {
            LINVALID_INDEX = true;
            std::cout << "INVALID_INDEX" << std::endl;
            return;
        }
    }

    void keyRight()
    {
#ifdef DEBUG
        std::cout << index + 1 << std::endl;
#endif
        if (LINVALID_INDEX)
        {
            index = 0;
            std::cout << words[index];
            LINVALID_INDEX = false;
        }
        else if (RINVALID_INDEX)
        {
            index = words.size() - 1;
            std::cout << words[index];
            RINVALID_INDEX = false;
        }

        else if (index < words.size() - 1)
        {
            index++;
            indexes.push_back(index);
            std::cout << words[index] << std::endl;
        }
        else
        {
            RINVALID_INDEX = true;
            std::cout << "INVALID_INDEX" << std::endl;
            return;
        }
    }

    std::string generateRandomString()
    {
        std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::mt19937 generator(static_cast<unsigned int>(time(0)));
        std::uniform_int_distribution<int> distribution(0, charset.size() - 1);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> sizeDistribution(1, 25);

        int size = sizeDistribution(gen);

        std::string result;

        for (int i = 0; i < size; ++i)
        {
            result += charset[distribution(generator)];
        }

        words.push_back(result);

        return result;
    }

    void wordsList()
    {
        isInList = true;
        if (words.empty())
        {
            std::cout << "Words ARRAY is empty";
            return;
        }
        for (std::size_t i = 0; i < words.size(); ++i)
        {
            std::cout << words[i] << std::endl;
        }
    }

    void indexesList()
    {
        isInList = true;
        if (indexes.empty())
        {
            std::cout << "Indexes ARRAY is empty";
            isInList = false;
            return;
        }
        for (std::size_t i = 0; i < indexes.size(); ++i)
        {
            std::cout << indexes[i] << std::endl;
        }
    }

    const void quitList()
    {
        system("cls");
        if (index > 0 && index < words.size())
        {
            std::cout << words[index];
            return;
        }
        else
        {
            std::cout << "YOU'RE NOT IN THE LIST MODE" << std::endl << "INVALID_INDEX";
            return;
        }
    }

    void welcome()
    {
        std::cout << words[0];
        return;
    }

    void clearWords()
    {
        words.clear();
        index = 0;
        words.emplace_back("TRY MY BRAND NEW PASSWORD GENERATOR");
        return;
    }

    void clearIndexes()
    {
        indexes.clear();
        return;
    }

    void showCommands()
    {
        std::cout << "Available commands:" << std::endl << "-------------------" << std::endl 
            << "Arrow Up: Move index up" << std::endl << "Arrow Down: Show list of words" 
            << std::endl << "Arrow Left: Move index left" << std::endl << "Arrow Right: Move index right" 
            << std::endl << "C: Clear console" <<std::endl << "I: Show list of indexes" 
            << std::endl << "Q: Quit list mode" << std::endl << "S: Delete all past words" 
            << std::endl << "J: Delete all past indixes" << std::endl << "Esc: Exit the program";
        
        return;
    }
};

int main()
{
    yarson yar;

    yar.welcome();

    for (;true;)
    {
        char key = _getch();

        if (key == 27)
        {
            break;
        }
        else if (key == 72)
        {
            std::system("cls");
            yar.keyUp();
        }
        else if (key == 75)
        {
            std::system("cls");
            yar.keyLeft();
        }
        else if (key == 77)
        {   
            std::system("cls");
            yar.keyRight();
        }
        else if (key == 80)
        {
            std::system("cls");
            yar.wordsList();
        }
        else if (key == 74 || key == 106)
        {
            std::system("cls");
            yar.clearIndexes();
            std::cout << "INDEXES HAS BEEN CLEARED";
        }
        else if (key == 83 || key == 115) 
        {
            std::system("cls");
            yar.clearWords();
            std::cout<<"WORDS HAS BEEN CLEARED";
        }
        else if (key == 99)
        {
            std::system("cls");
        }
        else if (key == 105)
        {
            std::system("cls");
            yar.indexesList();
        }
        else if (key == 108)
        {
            std::system("cls");
            yar.showCommands();
        }
        else if (key == 113)
        {
            std::system("cls");
            yar.quitList();
        }
    }

    return 0;
}
