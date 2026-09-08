import os

os.system("podman build -t printb .")

print()

command = "gcc " + input('File to compile: ') + " -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2; ./a.out " + input('Test input: ')

print()

os.system('podman run printb /bin/bash -c "' + command + '"')
