#include "list.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "profile.h"
#define userCount 5

void menu(LinkedList<std::string, std::string> &commandList, Profile users[userCount]);
void parseCommandFile(LinkedList<std::string, std::string> &commandList);
int playRound(LinkedList<std::string, std::string> &commandList);
void playGame(LinkedList<std::string, std::string> &commandList, Profile users[userCount]);
void addCommand(LinkedList<std::string, std::string> &commandList);
void delCommand(LinkedList<std::string, std::string> &commandList);
void saveCommands(LinkedList<std::string, std::string> &commandList);
void printArray(Profile array[userCount], std::ostream &output);
void initArray(Profile array[userCount]);
void updateUser(Profile array[userCount], std::string User, int points);
Profile* searchArray(Profile array[userCount], std::string Username);
void parseUserFile(Profile users[userCount]);
void saveProfiles(Profile users[userCount]);
void pause();


/* Advantages/Disadvantages of each data structure
Array Advantages
- It is easy to ascess a specific element of the array by its position, as I can just use [n]
- All memory is contigous
Array Disadvantages
- The array has a fixed size, and cannot be changed dynamically.
- The properties of the array make it very difficult to insert at the front, requring a shifting down of every element.

Linked List Advantages
- It is very easy to reorder elements in a linked list, as operations like insert or pop don't require acessing every other element of the list
Linked List Disadvantages
- Memory is not contigous, so it becomes more difficult to search or find a specific [n] element in the list.

*/



int rand_range(int min, int max);


int main() {

    Profile users[userCount];

    srand(time_t());

    LinkedList<std::string, std::string> commandList;
    initArray(users);

    parseCommandFile(commandList);
    parseUserFile(users);
    

    menu(commandList, users);



};

void saveCommands(LinkedList<std::string, std::string> &commandList)
{
    std::ofstream outputFile("../commands.csv");
    commandList.print(outputFile);
    outputFile.close();
}

//will insert or update currently existing user in profile array
void updateUser(Profile array[userCount], std::string User, int points)
{
    for (int i = 0; i < userCount; i++)
    {
        // user does not exist in the list, add user.
        if (array[i].name.empty())
        {
            array[i].name = User;
            array[i].points = points;
            std::cout << "New User " << array[i].name << " points are " << points << "!" << std::endl;
            break;
        }
        // user found, update current points.
        else if (array[i].name == User)
        {
            array[i].points += points;
            std::cout << "User " << array[i].name << " points are " << points << "!" << std::endl;
            break;
        }
        //else current user is not a match
    }
   
}

void initArray(Profile array[userCount])
{
    for (int i = 0; i < userCount; i++)
    {
        array[i].name = "";
        array[i].points = 0; 
    }

}

void delCommand(LinkedList<std::string, std::string> &commandList)
{
    std::string targetCmd;
    std::cout << "Please enter the command you wish to delete\n";
    std::cin >> targetCmd;
    if (commandList.searchNodeD1(targetCmd) == nullptr)
    {
        std::cout << "ERROR!: Command " << targetCmd << " not found!\n";
    }
    else
    {
        commandList.delNode(targetCmd);
        std::cout << "Command " << targetCmd << " sucessfully deleted.";
    }

}


void addCommand(LinkedList<std::string, std::string> &commandList)
{
    std::string newCommand;
    std::string newDesc;
    std::cout << "Enter the name of new command\n";
    std::cin >> newCommand;
    //error checking for duplicate commands
    if (commandList.searchNodeD1(newCommand) != nullptr)
    {
        std::cout << "ERROR: Command already exists!";
        pause();
        return;
    }
    std::cout << "Enter description of new command " << newCommand << std::endl;
    getchar();
    getline(std::cin,newDesc);
    commandList.insertFront(newCommand,newDesc);
}

int rand_range(int min, int max) {
    
    return rand() % (max - min + 1) + min;
}

void printArray(Profile array[userCount], std::ostream &output)
{
    for (int i = 0; i < userCount; i++)
    {
        output << array[i].name << "," << array[i].points << std::endl;  
    }
}


Profile* searchArray(Profile array[100], std::string Username)
{
    for (int i = 0; i < 100; i++)
    {
        if (array[i].name == Username)
        {
            return &array[i];
        }
    }
    return nullptr;
}




void pause()
{
    std::cout << "\nPress any key to continue...\n";
    std::cin.get();
}


void playGame(LinkedList<std::string, std::string> &commandList, Profile users[userCount])
{
    int score = 0;
    int roundCount = 0;
    std::string userName;
    std::cout << "Please enter username!" << std::endl;
    std::cin >> userName;

    while (roundCount < 5 || roundCount > 30)
    {
        system("clear");
        std::cout << "How many rounds would you like to play (5-30)" << std::endl;
        std::cin >> roundCount;
    }

    //game loop
    for (int i = 0; i < roundCount; i++)
    {
        score += playRound(commandList);
    }

    system("clear");
    std::cout << "Final Score: " << score << std::endl;
    updateUser(users, userName, score);


}


int playRound(LinkedList<std::string, std::string> &commandList)
{
    int answer = rand_range(0,29);
    int wrong1 = rand_range(0,29);
    int wrong2 = rand_range(0,29);

    std::vector<std::string> Answers;

    Answers.push_back(commandList.retrieveNode(answer)->data2);
    Answers.push_back(commandList.retrieveNode(wrong1)->data2);
    Answers.push_back(commandList.retrieveNode(wrong2)->data2);

    for (int i = 0; i < 10; i++){
    std::swap(Answers[rand_range(0,2)],Answers[rand_range(0,2)]);
    }




    int input = 0;
    while (input < 1 || input > 3) 
    {
        system("clear");
        std::cout << commandList.retrieveNode(answer)->data1 << "\n";
        std::cout << "1. " << Answers[0] << std::endl;
        std::cout << "2. " << Answers[1] << std::endl;
        std::cout << "3. " << Answers[2] << std::endl;
        std::cin >> input;
    }
    if (Answers[input-1] == commandList.retrieveNode(answer)->data2)
    {
        std::cout << std::endl << "Correct!!! +1 points!" << std::endl;
        return 1;
        
    }
    else 
    {
        std::cout << std::endl << "Wrong. :( -1 points!" << std::endl;
        return -1;
    }

    return 0;


}

void parseCommandFile(LinkedList<std::string, std::string> &commandList)
{
        // open file of linux commands
    std::ifstream inputFile("../commands.csv");

    // parse the input and input it into our list
    std::string command;
    std::string description;

    while (inputFile.peek() != EOF)
    {
        getline(inputFile , command, ',');
        getline(inputFile,description);
        description = description.substr(1,description.size()-2);   //slice off the quotation marks
        commandList.insertFront(command, description);
    }
    inputFile.close(); 

}

void parseUserFile(Profile users[userCount])
{
   

    std::ifstream inputFile("../profiles.csv");
    std::string userName;
    int points;
    while (inputFile.peek() != EOF)
    {
        getline(inputFile, userName, ',');
        inputFile >> points;
        userName.erase(remove(userName.begin(), userName.end(), '\n'),userName.end());
        updateUser(users, userName, points);
    }
    inputFile.close();

}

void saveProfiles(Profile users[userCount])
{
    std::ofstream outputFile("../profiles.csv");
    printArray(users, outputFile);
    outputFile.close();


}



void menu(LinkedList<std::string, std::string> &commandList, Profile users[userCount])
{
    // loop over menu function, no need for recursive calls
    while (true) 
    {
    printArray(users, std::cout);
    int input = 0;
    while (input < 1 || input > 6) 
    {
    std::cout << "\n1. Game Rules\n2. Play Game\n3. Load Game\n4. Add Command\n5. Remove Command\n6. Exit\n";
    std::cin >> input;
    system("clear");
    }
    switch (input)
    {
        // rules
        case 1:
        std::cout << "Rules of the game. Given a linux command, input the value (1-3)\n"
                  <<"of the matching correct description. Correct answers are +1 points,\n"
                  <<"  wrong are -1 points. Press any key to continue...\n";
                  pause();
                  
        break;

        // play
        case 2:
        playGame(commandList, users);
        break;

        //load
        case 3:
        break;

        // add command
        case 4:
        addCommand(commandList);
        break;

        // remove command
        case 5:
        delCommand(commandList);
        break;
        
        //quit
        case 6:
        saveCommands(commandList);
        saveProfiles(users);
        exit(0);
        
    }
    }
}