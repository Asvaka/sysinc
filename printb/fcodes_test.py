import os

codes = ['d','i','o','u','x','e','f','g','s','c','p','n']

with open("fcodes_test.c", "w") as file:
    file.write("""
            #include <stdio.h>

            int main() {

            """)
    for i in codes:
        file.write(f'printf("%{i}\\n", 1==1);\n')

    file.write("""
    return 0;
    }""")

file.close()

os.system("podman build -t printb .")
os.system("podman run -it printb gcc fcodes_test.c")
