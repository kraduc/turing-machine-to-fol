# Turing Machine to First Order Logic

This project aims to investigate the undecidability of first order logic (FOL) by converting a Turing Machine into FOL statements.

## Installation

Due to technical limitations of our ability, the program is currently only usable in the command line. Type `make` into your terminal once you've navigated to the folder this project resides.

## Usage

To use the program you would need to prepare the following two files:
* A `.xml` file representation of the Turing Machine, you can generate this file by clicking "Save XML" in the [Turing Machine Software](https://github.com/Bram-Hub/OwenTMS).
* A `.txt` file representation of the Turing Machine Tape, you can generate this file by clicking "Save Tape" in the [Turing Machine Software](https://github.com/Bram-Hub/OwenTMS).

Use the command `./tm-to-fol turing-machine.xml turing-machine-tape.txt` to run the program. After the program has terminated, you will be able to find `turing-machine.bram` in your folder. This will be the First Order Logic statements that describe the Turing Machine along with its tape you have put in.

The output file of this program follows the [Bram File Format](https://github.com/Bram-Hub/Bram-File-Format) and can be viewed using [Aris](https://github.com/Bram-Hub/aris). Note that even with small Turing machines, the output file can contain a lot of symbols which will take some time for Aris to load.

## Known Issues
* Due to the inability to represent negative integers, this program can only translate Turing Machines with the assumption that the read-write head will never move to the left of its initial position. If it does, it will just go back to its initial position.

## Interested Contributors
For those who are taking Computability and Logic and wanting to contribute to project. Here are possible improvements one could make to the program:
* Creating a Graphical User Interface
* Coming up with a way to represent the integers (both positive and negative) in formal logic.
