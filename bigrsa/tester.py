import os

os.system("podman build -t bigrsa .")

print()

command = "gcc " + input('File to compile: ') + " -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2 -lgmp; ./a.out " + input('Test input: ')

print()

os.system('podman run bigrsa /bin/bash -c "' + command + '"')
