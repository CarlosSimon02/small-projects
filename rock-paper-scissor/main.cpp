#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <vector>
#include <iomanip>

#define log(x) std::cout << x << std::endl

void displayData(int rounds, std::vector<double> data)
{
	double matchresult = 0;
	std::cout << "ROUND     YOU     COM" << std::endl;

	for (int i = 1; i <= rounds; i++)
	{
		std::cout << std::setw(10) << std::left << i << std::setw(8) << std::left << data[i - 1] << 1 - data[i - 1] << std::endl;
		matchresult += data[i - 1];
	}
	std::cout << "--------------------------------" << std::endl;
	std::cout << std::setw(10) << std::left << "Total" << std::setw(8) << std::left << matchresult << rounds - matchresult << std::endl;
}

double roundWinner(int playerWeapon, int aiWeapon)
{
	if (playerWeapon == aiWeapon)
	{
		std::cout << "\tit's a tie\n";
		return 0.5;
	}
	else if (playerWeapon > aiWeapon && playerWeapon != 0)
	{
		std::cout << "\tYou win\n";
		return 1.0;
	}
	else if (playerWeapon == 0 && aiWeapon == 2)
	{
		std::cout << "\tYou win\n";
		return 1.0;
	}
	else
	{
		std::cout << "\tYou lose\n";
		return 0;
	}
}

void play()
{
	double matchResult = 0;
	std::vector <double> standing;
	std::string weapon;
	std::string weaponList[] = { "Rock","Paper","Scissor" };
	std::string rounds;
	const int maxRounds = 10;

	std::cout << "Choose how many rounds you want to play. ("
		<< maxRounds << " max): ";
	std::getline(std::cin, rounds);
	system("cls");
	int rnds = std::stoi(rounds);

	if (rnds <= 10 && rnds >= 0)
	{
		log("Choose a weapon by typing a corresponding number:");
		log("\t1. Rock");
		log("\t2. Paper");
		log("\t3. Scissor\n");

		for (int i = 1; i <= rnds; i++)
		{
		askUser:
			std::cout << "ROUND " << i << ". Choose weapon: ";
			std::getline(std::cin, weapon);

			if (weapon == "1" || weapon == "2" || weapon == "3")
			{
				int aiWeapon = 0;
				std::cout << "\t" << weaponList[(std::stoi(weapon)) - 1] << "(you) ";
				for (int i = 0; i <= 5; i++)
				{
					std::cout << "=";
					Sleep(250);
				}
				aiWeapon = rand() % 3;
				std::cout << " " << weaponList[aiWeapon] << "(AI)\n";
				standing.push_back(roundWinner(std::stoi(weapon) - 1, aiWeapon));
				matchResult += standing[i-1];
			}
			else
			{
				std::cout << "\x1b[1A" << "\x1b[2K";
				goto askUser;
			}
		}
	}
	else
	{
		log("\nInvalid input");
		system("cls");
	}

	std::cout << "\nProcessing Data";
	for (int j = 0; j < 2; j++)
	{
		for (int i=0; i < 3; i++)
		{
			std::cout << ".";
			Sleep(350);
		}
		std::cout << "\b\b\b";
	}
	std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	displayData(rnds, standing);

	std::cout << "\nGAME FINISH. ";
	if (matchResult == std::stoi(rounds) / 2.0) std::cout << "The match is draw. Press any key\n";
	else if (matchResult > std::stoi(rounds) / 2.0) std::cout << "Congratulations!! You won the game. Press any key";
	else if (matchResult < std::stoi(rounds) / 2.0) std::cout << "You lose. Press any key";
	std::cin.get();
	system("cls");
	
}

int main()
{
	std::string chosenNum = "0";

	do
	{
		log("ROCK PAPER SCISSOR GAME\n");
		log("\t1. Play");
		log("\t2. Quit\n\n");
		
		std::cout << "Please choose. Type 1 to play or 2 to quit: ";

		std::getline(std::cin, chosenNum);

		if (chosenNum == "1")
		{
			system("cls");
			play();
		}
		else if (chosenNum == "2")
		{
			system("cls");
			log("Thanks for playing!");
			break;
		}
		else
		{
			system("cls");
			log("Invalid input. Please try again.");
			Sleep(2000);
			system("cls");
		}


	} while (true);
}