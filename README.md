# <span style="color:#e8a87c;">simple Shell</span>

Custom Shell is a simple implementation of a command-line shell in C programming language. It provides a basic shell environment where users can enter commands, which are then executed by the shell.

## Features

- Accepts user commands and executes them.
- Supports basic command-line operations like executing external programs.
- Handles process creation and management using `fork()` and `exec()` functions.
- Supports basic input/output redirection.

## Getting Started

To get started with Custom Shell, follow these steps:

1. Clone the repository: `git clone https://github.com/NourMellal/simple_shell.git`
2. Navigate to the project directory: `cd custom-shell`
3. Compile the code: `gcc custom-shell.c -o custom-shell`
4. Run the shell: `./custom-shell`

## Usage

Once the shell is running, you can enter commands just like in any other shell. Here are a few examples:

- Execute an external program:
  
shell
  Shell> ls -l
  Shell> gcc -o myprogram myprogram.c
  
- Change directory:
  
shell
  Shell> cd /path/to/directory
  
- Redirect input/output:
  
shell
  Shell> command < input.txt
  Shell> command > output.txt
  
- Exit the shell:
  
shell
  Shell> exit
  
## Limitations

- Custom Shell has limited functionality compared to full-fledged shells like Bash or Zsh. It does not support advanced features such as piping, environment variables, command history, etc.
- Error handling is minimal in this implementation, and error messages may not be very descriptive.

## Contributing

Please follow the [contributing guidelines](CONTRIBUTING.md) to contribute to this project.

## License

This project is licensed under the alx program.

## Acknowledgements

This project was inspired by the desire to understand the internals of a shell and learn more about process management in Unix-like systems.

## Contact

For any questions or inquiries, please contact nour mellal & houssam benassi.

Email: 55205houssam@gmail.com, mellalnour9@gmail.com


Feel free to adjust the styling as per your preference.
