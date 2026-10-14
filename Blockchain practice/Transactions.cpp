#include "Transaction.h"
#include "Account.h"

std::vector<Transaction> dataBaseForTransactions;


Transaction::Transaction(std::string s, std::string r, double a) : sender(s), receiver(r), amount(a) {}

std::string Transaction::getSender() const { return sender; }

std::string Transaction::getReceiver() const { return receiver; }

double Transaction::getAmount() const { return amount; }

void Transaction::transferMoney() {
	if (sender == receiver) {
		throw std::invalid_argument("The receiver can't be you!\n");
	}
	if (!UserInformation::hasUser(sender)) {
		throw std::runtime_error("The sender doesn't exist in the system\n");
	}
	if (!UserInformation::hasUser(receiver)) {
		throw std::runtime_error("The receiver doesn't exist in the system\n");
	}

	UserInformation::proccessTransfer(sender, receiver, amount);

	message = "The sender <" + sender + "> had sent " + std::to_string(amount) + "$ to the receiver<" + receiver + ">\n";
	std::cout << message;
	dataBaseForTransactions.push_back(*this);
}
