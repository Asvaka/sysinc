import os

os.system("podman build -t shainc .")

print()

command = "gcc " + input('File to compile: ') + " -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2; ./a.out " + input('Test input: ')

print()

os.system('podman run shainc /bin/bash -c "' + command + '"')
