import os

os.system("podman build -t bigadd .")

print()

command = "gcc " + input('File to compile: ') + " -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2; ./a.out " + input('Test input: ')

print()

os.system('podman run bigadd /bin/bash -c "' + command + '"')
