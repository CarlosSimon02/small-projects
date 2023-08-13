#include <iostream>
#include <string>

void play();


int main()
{
	std::string choice;
	

	do
	{
		std::cout << "WELCOME TO WORD SEARCH" << std::endl;
		std::cout << "1. Play\n2. Quit" << std::endl;
		std::cout << "Please enter the number of your choice: ";
		std::getline(std::cin, choice);

		if (choice == "1")
		{
			play();
		}

		else if (choice == "2")
		{
			std::cout << "Thanks for visiting." << std::endl;
			return 0;
		}

		else std::cout << "Invalid input. Please choose between 1 or 2 only.\n" << std::endl;
	} while (choice != "2");
}

void play()
{
	std::string answers[] = { "ACE", "GRAPES", "SKATE", "RAKE", "APE", "PLATE" };
	std::string correctAns[6];
	std::string userAns;
	int answers_size = sizeof(answers) / sizeof(std::string);
	int lives = 5;
	int trigger = 0;
	int finished = 0;

	std::cout << "\nROUND 1\n" << std::endl;

	std::cout << "K E J P B F A" << std::endl;
	std::cout << "A P L A T E P" << std::endl;
	std::cout << "A T A C E H E" << std::endl;
	std::cout << "G R A P E S Z" << std::endl;
	std::cout << "G A Q G I D M" << std::endl;
	std::cout << "L K A C A R B" << std::endl;
	std::cout << "S E S K A T E" << std::endl;

	std::cout << "\nYou have " << lives << " lives to find all the words. GOODLUCK!!";

	do
	{
		std::cout << "\nPlease enter the word that you found or type QUIT to end the game: " << std::endl;
		std::getline(std::cin, userAns);

		for (int x = 0; x < 6 && userAns != "QUIT"; x++)
		{
			if (userAns == answers[x] && userAns != correctAns[x])
			{
				trigger = 1;
				correctAns[x] = userAns;
				finished ++;
			}
			else if (userAns == correctAns[x]) trigger = 2;

		}

		if (trigger == 1)
		{
			if (finished != 6) std::cout << "You found one. Try another." << std::endl;
			else if (finished == 6) std::cout << "You found them all. You can now move to the next round" << std::endl;
		}
		
		else if (trigger == 2) std::cout << --lives << " lives. You found that already. Try another one." << std::endl;
		else if (trigger == 0) std::cout << --lives << " lives. Word not found. Try another one." << std::endl;
			
			

		if (userAns == "QUIT")
		{
			std::cout << "Thanks for playing. See you later!" << std::endl;
		}

		if (lives == 0)
		{
			std::cout << "GAME OVER\n\n\n\n\n" << std::endl;
			break;

		}

		trigger = 0;

	} while (userAns != "QUIT");


}
