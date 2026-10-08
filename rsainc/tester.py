import os

os.system("podman build -t rsainc .")

print()

command1 = "gcc keygen.c -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2 -o keygen.out && ./keygen.out"
command2 = "gcc rsainc.c -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2 -o rsainc.out && ./rsainc.out " + input('Test input: ')

print()

os.system('podman run rsainc /bin/bash -c "' + command1 + " && " + command2 + '"')
