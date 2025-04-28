# Crypto Wallet C

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

## Project Goals
Learn and demonstrate how Bitcoin key derivation works at the byte level
Create a minimalistic implementation without external cryptographic libraries
Help others understand BIP-32, BIP-39, and BIP-44 through readable C code

Roadmap
 ✅ Entropy generation and checksum

 ✅ Mnemonic creation from wordlist

 🔳 Seed derivation with PBKDF2-HMAC-SHA512

 🔳 Full master key + chain code generation (BIP-32)

 🔳 Child key derivation (hardened and non-hardened)

 🔳 Wallet paths (m/44'/0'/0'/0/0) (BIP-44)

 🔳 Address generation (P2PKH / P2WPKH)

License
MIT License.