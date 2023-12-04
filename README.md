# EECS-348 Term Project

This is the repository for the Term Project for KU EECS-348 (Software Engineering I).

## Project Description

> In this project, you will build a versatile arithmetic expression evaluator using C++. The program
> will take an arithmetic expression as input, parse it, and calculate the result according to the order
> of operations (PEMDAS). This project will help you reinforce your understanding of parsing
> techniques, data structures, and algorithm design.

## Installation
Two methods of installation
- [Releases Page](https://github.com/codyduong/EECS-348-Project/releases)
  - For specific versions of the software, download the source and build from source. No binaries are provided due to security concerns, 
  the product is not mature enough to dictate targets for various OSes with checksums. As such seek to [Build from Source](#build-from-source) instead.
- [Build from Source](#build-from-source)
<!-- - [Docker]() -->

## Quickstart Guide
These are quickstart examples. For in-depth usage/FAQ/troubleshooting please read the [User-Manual](/docs/user-manual).
```console
user@desktop:~$ expression_parser "1+1"
2
user@desktop:~$ expression_parser "1+1" -c
-c/--configuration flag is mutually exclusive with an arithmetic input. Please specify one or the other.
user@desktop:~$ expression_parser -c
Enter an arithmetic expression (type 'quit', 'exit', or press CTRL+D to exit loop): 1+1
2
Enter an arithmetic expression (type 'quit', 'exit', or press CTRL+D to exit loop): 1/2
0.5
Enter an arithmetic expression (type 'quit', 'exit', or press CTRL+D to exit loop): -7%-3
2
# View User-Manual Section 7. FAQ 5: Why does modulo/modulus always return a positive number
Enter an arithmetic expression (type 'quit', 'exit', or press CTRL+D to exit loop): quit
```

### Flags
- Without the `-c` or `--continuous` flag, the program will expect a provided algebraic expression as the input. Example input: `expression_parser 1+1`.
- With the `-c` or `--continuous` flag, the program will run in continuous prompt mode. Errors will not exit the program, and will prompt the user for algebraic expressions to evaluate until exiting the program by typing `exit`, `exit()`, `q`, `quit`, `quit()`, or pressing CTRL+D. This mode is mutually exclusive with a provided expression. Example input: `expression_parser -c`
- With the `-d` or `--debug` flag. Displays debug information for developers such as evaluated input and parsed abstract syntax tree (AST).
- With the `-v` flag. Will not evaluate any other flags or a provided expression and will simply display version information.

## Build from Source

### Dependencies
Install through your preferred format, on your preferred operating system

- [LLVM](https://www.llvm.org/)
  Note: For any confusion about this "Clang \[clang++, clang-format\] is released as part of regular LLVM releases. Clang is also provided in all major BSD or GNU/Linux distributions as part of their respective packaging systems. From Xcode 4.2, Clang is the default compiler for Mac OS X." -[Clang - Getting Started](https://clang.llvm.org/get_started.html)
  - [clang++](https://clang.llvm.org/)
  - [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [CMake](https://cmake.org/)
- [Google Test](https://github.com/google/googletest)

Provided are CLI instructions for building from source:
- [For Linux/Ubuntu](#linux)
- [For macOS](#macos)
- [For Windows](#windows)<br></br>
[File a issue](https://github.com/codyduong/EECS-348-Project/issues) if anything does not work. Also, these are provided as a courtesy examples, and may vary
greatly dependent on version of OS, et. cetera.

### Build Artifacts
Build artifacts are at `/build/expression_parser` or `/build/expression_parser.exe` as well as `build/tests` and `build/tests.exe` depending on compile target.

### Linux
Dependencies
```bash
sudo apt-get install cmake
sudo apt install clang
sudo apt-get install libgtest-dev
```

Build
```bash
mkdir build
cmake -S . -B build && make -C build
```

Run
```bash
./build/expression_parser
```

### macOS
Dependencies
```bash
brew install cmake
brew install clang
brew install gtest
```

Build
```bash
mkdir build
cmake -S. -B build && make -C build
```

Run
```bash
./build/expression_parser
```

### Windows
Using [wsl](https://learn.microsoft.com/en-us/windows/wsl/install) and go to [Linux Installation Instructions](#linux)

Alternatively, using your choice of installation for gcc and cmake.
```powershell
cmake -S. -B build && make -C build
```

## Documentation

Documentation can be found in [/docs](/docs/). Of note:
* [Meeting Notes](/docs/meetings)
* [UPEDU Project Plan](/docs/project-plan)
  + The evergreen version is found at [`./Software Development Plan.docx`](/docs/project-plan/Software%20Development%20Plan.docx)
  + Each revision is saved as a pdf here in the format `SDPv*.*`
* [Software Requirements](/docs/software-requirements-spec/)
  + The evergreen version is found at [`./Software-Requirements-Spec.docx`](/docs/software-requirements-spec/Software-Requirements-Spec.docx)
  + Each revision is saved as a pdf here in the format `SRSv*.*`
* [Software Architecture](/docs/software-architecture)
  + The evergreen version is found at [`./Software-Architecture.docx`](/docs/software-architecture/Software-Architecture.docx)
  + Each revision is saved as a pdf here in the format `SADv*.*`
* [Test Cases](/docs/test-cases/)
  + The evergreen version is found at [`./Test-Cases.docx`](/docs/user-manual/Test-Cases.docx)
  + Each revision is saved as a pdf here in the format `TCv*.*`
* [User Manual](/docs/user-manual)
  + The evergreen version is found at [`./User-Manual.docx`](/docs/user-manual/User-Manual.docx)
  + Each revision is saved as a pdf here in the format `UMv*.*`

## The Team

| Team Member    | Role(s)                   | Availability                                                                |
| -------------- | ------------------------- | --------------------------------------------------------------------------- |
| Cody Duong     | Project leader, Developer | M/W/F 1:00PM-9:00PM</br>T/Th 6:00PM-9:00PM                                  |
| Tuan Vu        | Q/A Engineer, Developer   | M 6:30PM-9PM</br>T/Th 5:30PM-7:30PM</br>W 5:00-9:00PM<br/>F 3:00PM-9:00PM   |
| Zia Hosainzada | Secretary, Developer      | M/T/Th/F 9:00AM-11:00AM<br/>M/T/W/Th/F 12:00PM-2:00PM                       |
| Kyle Moore     | Q/A Engineer, Developer   | M/W/F 1:00PM-5:00PM                                                         |
| Kobe Jordan    | DevOps, Developer         | M/W 5:00PM-9:00PM<br/>T/Th 6:00PM-9:00PM<br/>F 8:00AM-11:00AM               |
| Max Djafarov   | DevOps, Developer         | M/W 4:00PM-10:00PM<br/>T 5:00PM-10PM<br/>Th 4:00PM-10:PM<br/>F 9:00-11:00AM |
