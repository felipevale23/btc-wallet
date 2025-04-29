# Crypto Wallet C

Version: **0.1.0**

A minimal implementation of BIPs 32, 39, and 44 in C — generate Bitcoin wallets from mnemonics, derive keys, and manage seeds with no heavy libraries.

---

## Summary
- [About](#about)
- [Features](#features)
- [Folder Structure](#folder-structure)
- [Usage](#usage)
- [Build Instructions](#build-instructions)
- [License](#license)

---
## About
The code is built entirely with basic C libraries, avoiding external dependencies wherever possible.
It demonstrates the full process of wallet creation — from random entropy to mnemonic, seed, private key, and public key derivation.

## Features
- BIP-39 mnemonic generation
- BIP-32 HD Wallet key derivation
- BIP-44 multi-account path support
- Minimal SHA-256 and PBKDF2 implementation
- Works only with basic C libraries

## Folder Structure
btc-wallet-c/
├── src/              # C source files
│   ├── main.c        # Program entry point
│   ├── sha256.c      # SHA-256 mini implementation
│   ├── pbkdf2.c      # PBKDF2-HMAC-SHA512 (seed generation)
│   ├── bip39.c       # Mnemonic generation and handling
│   ├── bip32.c       # HD Wallet (key derivation)
│   └── utils.c       # Randomness, base conversions, helpers
│
├── include/          # Header files
│   ├── sha256.h
│   ├── pbkdf2.h
│   ├── bip39.h
│   ├── bip32.h
│   └── utils.h
│
├── wordlist/         # English BIP-39 wordlist file
│   └── english.txt
│
├── build/            # Compiled binaries (gitignore this folder)
│
├── README.md         # Project overview
├── LICENSE           # MIT license (recommended)
├── Makefile          # Simple build automation (optional but pro)
└── .gitignore        # Ignore build artifacts


### 📦 Short explanation of folders:
src/ → all your .c implementation files.

include/ → all your .h header files.

wordlist/ → the 2048 BIP-39 words (english.txt).

build/ → where your compiled crypto-wallet-c binary goes.

Top level → README, license, makefile, and config files.

## Build
``` bash
make
```
## Usage
```bash
./crypto-wallet-c 128   # 128 bits entropy (12 words)
./crypto-wallet-c 256   # 256 bits entropy (24 words)
```
### 🔥 Most direct comparison:
- 128 bits (12 words)
    - It is already very secure.
    - Attacking a key is practically impossible today.
    - Easier to write down/memorize.
    - Widely used in wallets such as Electrum, Ledger, Trezor.

- 256 bits (24 words)
    - Absurd security (it is “overkill” today).
    - Takes much longer to generate and process.
    - Harder to write down (more chance of error).
    - Requires more patience from the user.

### Relation between Entropy and Number of Words (BIP-39)

| Entropy (bits) | Checksum (bits) | Total bits | Number of words |
|:--------------:|:---------------:|:----------:|:---------------:|
| 128            | 4               | 132        | 12              |
| 160            | 5               | 165        | 15              |
| 192            | 6               | 198        | 18              |
| 224            | 7               | 231        | 21              |
| 256            | 8               | 264        | 24              |

#### Formulas used

- `checksum_bits = entropy_bits / 32`
- `total_bits = entropy_bits + checksum_bits`
- `words = total_bits / 11`

#### Quick summary

- **128 bits** → **12 words**
- **160 bits** → **15 words**
- **192 bits** → **18 words**
- **224 bits** → **21 words**
- **256 bits** → **24 words**

## Project Goals
Learn and demonstrate how Bitcoin key derivation works at the byte level
Create a minimalistic implementation without external cryptographic libraries
Help others understand BIP-32, BIP-39, and BIP-44 through readable C code

## Roadmap
 ✅ Entropy generation and checksum

 ✅ Mnemonic creation from wordlist

 🔳 Seed derivation with PBKDF2-HMAC-SHA512

 🔳 Full master key + chain code generation (BIP-32)

 🔳 Child key derivation (hardened and non-hardened)

 🔳 Wallet paths (m/44'/0'/0'/0/0) (BIP-44)

 🔳 Address generation (P2PKH / P2WPKH)

### BIPs
| BIP     | Nome                                                | O que implementamos?                                          |
|---------|-----------------------------------------------------|---------------------------------------------------------------|
| BIP-39  | Mnemonic code for generating deterministic keys    | ✅ Geramos a mnemônica a partir de entropia + checksum + wordlist |
| BIP-32  | Hierarchical Deterministic Wallets                 | ⚠️ Em andamento (derivar chave privada da seed)               |
| BIP-44  | Multi-account hierarchy for deterministic wallets  | ❌ Ainda não implementado                                      |


## License
MIT License.