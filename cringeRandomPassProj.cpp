#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <conio.h>

//by mark "awful" tyrkba

class RandPassGen
{
private:
    std::vector<std::string> words{ "TRY MY BRAND NEW PASSWORD GENERATOR" };
    std::vector<std::size_t> indexes{0};
    std::size_t index = 0;
    bool isInList, RINVALID_INDEX , LINVALID_INDEX;

public:
    const void keyUp()
    {
#ifdef DEBUG
        std::cout << index + 1 << std::endl;
#endif
        index++;
        indexes.push_back(index);
        generateRandomString();
        std::cout << words[words.size() - 1] << std::endl;
    }

    const void keyLeft()
    {
#ifdef DEBUG
        std::cout << index - 1 << std::endl;
#endif
        if (words.empty())
        {
            std::cout << "Words ARRAY is empty"<<std::endl;
            return;
        }
        
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

        else if (index > 0 && index <= words.size() && !words.empty())
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

    const void keyRight()
    {
#ifdef DEBUG
        std::cout << index + 1 << std::endl;
#endif
        if (words.empty())
        {
            std::cout << "Words ARRAY is empty" << std::endl;
        }
        
        else if (LINVALID_INDEX)
        {
            index = 0;
            std::cout << words[index];
            LINVALID_INDEX = false;
            return;
        }
        
        else if (RINVALID_INDEX)
        {
            index = words.size() - 1;
            std::cout << words[index];
            RINVALID_INDEX = false;
            return;
        }

        else if (index >= 0 && index < words.size() - 1 && !words.empty())
        {
            index++;
            indexes.push_back(index);
            std::cout << words[index] << std::endl;
            return;
        }

        else
        {
            RINVALID_INDEX = true;
            std::cout << "INVALID_INDEX" << std::endl;
            return;
        }
    }

    const std::string generateRandomString()
    {
        std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::mt19937 generator(static_cast<unsigned int>(time(0)));
        std::uniform_int_distribution<int> distribution(0, charset.size() - 1);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> sizeDistribution(1, 25);

        std::size_t size = sizeDistribution(gen);

        std::string result;

        for (int i = 0; i < size; ++i)
        {
            result += charset[distribution(generator)];
        }

        words.push_back(result);

        return result;
    }

    const void wordsList()
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

    const void indexesList()
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
        if (isInList)
        {
            if (index >= 0 && index < words.size())
            {
                std::cout << words[index];
                return;
            }
            else
            {
                std::cout << "INVALID_INDEX" << std::endl;
            }
        }
        else if(!isInList)
        {
            std::cout << "YOU'RE NOT IN THE LIST MODE" << std::endl;
            return;
        }
    }

    const void welcome() const
    {
        std::cout << "TRY MY BRAND NEW PASSWORD GENERATOR" << std::endl;
        return;
    }

    void clearWords()
    {
        words.clear();
        index = 0;
        words.reserve(1);
        return;
    }

    void clearIndexes()
    {
        indexes.clear();
        return;
    }

    const void showCommands() const
    {
        std::cout << "Available commands:" << std::endl << "-------------------" << std::endl 
            << "Arrow Up: Move index up" << std::endl << "Arrow Down: Show list of words" 
            << std::endl << "Arrow Left: Move index left" << std::endl << "Arrow Right: Move index right" 
            << std::endl << "C: Clear console" <<std::endl << "I: Show list of indexes" 
            << std::endl << "Q: Quit list mode" << std::endl << "S: Delete all past words" 
            << std::endl << "J: Delete all past indices" << std::endl << "Esc: Exit the program";
        
        return;
    }

    void processKey(char key)
    {
        std::system("cls");
        
        switch (key)
        {
        case 27: // Esc key
            std::cout << "Exit completed successfully";
            break;
            return;
        case 72: // Up arrow
            keyUp();
            break;
        case 75: // Left arrow
            keyLeft();
            break;
        case 77: // Right arrow
            keyRight();
            break;
        case 80: // Down arrow
            wordsList();
            break;
        case 74: // J key
        case 106:
            clearIndexes();
            std::cout << "INDEXES HAVE BEEN CLEARED";
            break;
        case 83: // S key
        case 115:
            clearWords();
            std::cout << "WORDS HAVE BEEN CLEARED";
            break;
        case 99: // C key
            // Clearing cmd
            break;
        case 105: // I key
            indexesList();
            break;
        case 108: // L key
            showCommands();
            break;
        case 113: // Q key
            quitList();
            break;
        default:
            std::cout << "Invalid command. Maybe you can try to change YOUR keyboard layout" << std::endl;
        }
    }
};

int main()
{
    RandPassGen yar;

    yar.welcome();

    char key;

    for (;true;)
    {
        key = _getch();
        yar.processKey(key);
    }

    return 0;
}
