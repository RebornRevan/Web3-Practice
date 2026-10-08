#include "Block.h"
#include "SHA.h"
#include <sstream>


Block::Block(int i, std::string previousHash, std::vector<Transaction> blockData) : index(i), prevHash(previousHash), data(blockData) {
	cTime = time(nullptr);
	hash = calculateHash();
}

void Block::mineBlock(int length) {
	std::string target(length, '0');

	// Finding hash
	while (hash.substr(0, length) != target) {
		nonce++;
		hash = calculateHash();
	}
	std::cout << "Block mined, hash = " << hash << '\n';
}

std::string Block::calculateHash() const {
	std::stringstream result;
	result << index << cTime << prevHash << nonce;
	for (const auto& pair : data) {
		result << pair.getSender() << pair.getReceiver() << pair.getAmount();
	}
	return sha256(result.str());
}
