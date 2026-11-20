## Project Updates (Completed)

- ~~Finished goals written as comments~~
- ~~Create a system for logging in and using secretKeys (seed phrases) for recovery~~
- Added user authentication (login) and account access recovery via 6-word secret keys.
- Implemented JSON export for registered accounts (`users.json`) and mined block transactions (`transactions.json`).
- Expanded console menu options to support authentication and recovery.
- Rebranded user management into a special `UserInformation` namespace.
- Change the README.md for better sight
---

## Future Goals & Roadmap

### Phase 1: Smart Contract Implementation - Now
- **Core Ledger Contract (Solidity):** Develop a smart contract to manage test balances and transfers using Ethereum wallet addresses (`address`).
- **Smart Contracts:** Develop core smart contracts and enforce contract validation rules.
- **Remix VM Testing:** Compile, deploy, and test the contract in Remix VM (to verify both successful transfers and to reject invalid operations).

### Phase 2: Testnet Deployment
- **Testnet Deployment:** Deploy the verified contract to the **Sepolia** testnet and initiate transactions using **MetaMask**.
- **Parsing JSON:** Build an external script (Python) to parse the exported `users.json` and `transactions.json` in order to enter test data into the contract, and compare state results.
