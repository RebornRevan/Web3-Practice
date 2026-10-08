#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Account.h"



class Transaction;

extern std::vector<Transaction> dataBaseForTransactions;


class Transaction {
private:
	std::string sender;		//Name of sender of transaction, имя отправителя транзакции
	std::string receiver;	//Name of receiver of transaction, имя получателя транзакции
	double amount;		//Amount of transaction, сумма транзакции
	std::string message;		//Information about transaction, информация о переводе
public:
	Transaction(std::string s, std::string r, double a);

	std::string getSender() const;

	std::string getReceiver() const;

	double getAmount() const;

	void transferMoney();


};