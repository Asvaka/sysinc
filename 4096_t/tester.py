import os

os.system("podman build -t 4096_t .")

print()

command = "gcc " + input('File to compile: ') + " -lm -Wall -Wextra -Werror -Wpedantic -O2; ./a.out " + input('Test input: ')

print()

os.system('podman run 4096_t /bin/bash -c "' + command + '"')
