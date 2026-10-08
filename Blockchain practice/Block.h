#pragma once
#include <vector>
#include <string>
#include <ctime>
#include "Transaction.h"

class Block {
public:
	int index;		//Index of block, индекс блока
	std::string prevHash;	//Hash of previous block, хэш прошлого блока
	std::vector<Transaction> data;		//Data of block(transactions), данные блока(переводы)
	std::string hash;		//Hash of current block, хэш с блоком, с которым мы работаем
	time_t cTime;		//Time of adding block, время, когда добавили блок
	unsigned long long nonce = 0;		//number for PoW, число для PoW(не знаю как это будет на русском)


	// Constructor, конструктор
	Block(int i, std::string previousHash, std::vector<Transaction> blockData);

	// Realization of Proof of Work(PoW), реализация PoW
	void mineBlock(int length);

	//Calculating hash using data of transactions, index, nonce, previous hash, Считаем хэш исходя от времени, noncа, прошлого хэша, индекса, данных транзакций
	std::string calculateHash() const;
};