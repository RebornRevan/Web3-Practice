#pragma once
#include "Block.h"


class BlockChain {
private:
	std::vector<Block> blockchain;
	int length;		//Count of '0' in the beginning of hash, кол-во нулей в начале хеша

public:
	BlockChain(int len);

	//Generating genesis block, создание генезис(первого) блока
	Block createGenBlock();

	//Get last block from vector, геттер на последний блок
	Block getLastBlock() const;

	void createBlock();

	// Checks if hash was calculated right and if it is the same hash as hash of previous one, Проверяет правильно ли посчитан хэш и совпадает ли он с хэшом прошлого блока
	bool isHashValid() const;


	void printBlockChain() const;
};
