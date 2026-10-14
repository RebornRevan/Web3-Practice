#include "Blockchain.h"
#include "Account.h"
#include "Transaction.h"
using namespace std;

void display() {
	cout << "----------  Menu  ----------\n";
	cout << "1. Register account \n";
	cout << "2. Create transaction(In the data should be 2 users at least)\n";
	cout << "3. Mine of block \n";
	cout << "4. Print all data of users \n";
	cout << "5. Print current blockchain status \n";
	cout << "6. Check the validality of blockchain \n";
	cout << "7. Login into account \n";
	cout << "8. Recover account access \n";
	cout << "            0.EXIT       \n";
	cout << "-----------------------------\n\n";
	cout << " Enter the number:\n\n";
}




int main() {
	
	BlockChain blockchain(4);
	int choiceOfUser;
	while (true) {
		display();
		if (!(cin >> choiceOfUser)) {
			cout << "Wrong input! Input a number from 0 to 8\n";
			cin.clear();										   // This two lines help to clear buffer from constant output of wrong input phrase
			cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Эти две строчки отвечаю за очистку буфера, чтобы при неверном вводе строка не выводила постоянно "Неверный вывод"
			continue;
		}
		if (choiceOfUser == 0) {
			cout << "Exiting from the program, goodbye!\n";
			break;
		}
		try {
			switch (choiceOfUser)
			{
				case 1: {
					string name, password;
					double balance;
					cout << "Enter the name of the account (should be longer than 3 letters): ";
					cin >> name;
					if (UserInformation::hasUser(name)) {
						throw invalid_argument("The username is already used!\n");
					}
					cout << "Enter the balance of the account (should be positive): ";
					cin >> balance;
					cout << "Enter the password of the account (should be longer than or equal 5 letters): ";
					cin >> password;
					Account user(name, password,  balance);
					UserInformation::addUser(user);
					break;
				}
				case 2: {
					if (UserInformation::getUsersCount() < 2) {
						throw out_of_range("The database consists either one or none users! Try to add at least 2 to create a transaction!\n");
					}
					string send, receive;
					double amount;
					cout << "Enter the name of the sender account (should be longer than 3 letters): ";
					cin >> send;
					cout << "Enter the name of the receiver account (should be longer than 3 letters): ";
					cin >> receive;
					cout << "Enter the amount of money you'd like to transfer (should be positive): ";
					cin >> amount;
					Transaction bill(send, receive, amount);
					bill.transferMoney();
					break;
				}
				case 3: {
					cout << "Computing hash.....\n";
					blockchain.createBlock();
					break;
				}
				case 4: {
					UserInformation::printDataUsers();
					break;
				}
				case 5: {
					blockchain.printBlockChain();
					break;
				}
				case 6: {
					if (blockchain.getLastBlock().index == 0) {
						throw invalid_argument("The blockchain only contains the Genesis block! You can't compute the validality of hash of it(");
					}
					cout << "Checking the validality of blockchain....\n";
					cout << (blockchain.isHashValid() ? "Yes, it is valid, nothing wrong\n" : "Something feels odd\n");
					break;
				}
				case 7: {
					if (UserInformation::getUsersCount() == 0) {
						throw runtime_error("No users registered yet! Try to register an account first.\n");
					}
					string name;
					cout << "Enter the name of the account you want to login to: ";
					cin >> name;
					if (!UserInformation::hasUser(name)) {
						throw invalid_argument("This user doesn't exist!\n");
					}
					UserInformation::loginIntoAccount(name);
					break;
				}
				case 8: {
					if (UserInformation::getUsersCount() == 0) {
						throw runtime_error("No users registered yet! Try to register an account first.\n");
					}
					string name;
					cout << "Enter the name of the account you want to recover: ";
					cin >> name;
					if (!UserInformation::hasUser(name)) {
						throw invalid_argument("This user doesn't exist!\n");
					}
					UserInformation::recoverAccountAccess(name);
					break;
				}
				default:
					cout << "Wrong choice, buddy) Try a number in range from 0 to 6!\n";
					break;
			}
		}
		catch (const exception& e) {
			cout << e.what() << '\n';
		}
	}
	return 0;
}