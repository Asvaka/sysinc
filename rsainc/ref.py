import random

def find_large_prime():
    is_prime = lambda n : all([n % i for i in range(2, int(n **.5))])
    candidate = 6 * random.randint(5460,10000) + 1
    while not is_prime(candidate):
        candidate += 6
    return candidate

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)
    
lcm = lambda a, b: a * b // egcd(a, b)[0]
p, q = find_large_prime(), find_large_prime()
n = p * q
e = 65537
lmdb = lcm(p - 1,  q - 1)
d = egcd(e, lmdb)[1]
while d < 0: # fix sign problem
    d += lcm(p - 1,  q - 1)

print(f"e: {e}")
print(f"lmdb: {lmdb}")
print(f"d: {d}")
