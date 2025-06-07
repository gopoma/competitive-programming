import random
import sympy

def generate_keys():
    p = sympy.randprime(10 ** 180, (10 ** (180 + 1)) - 1)
    q = sympy.randprime(10 ** 180, (10 ** (180 + 1)) - 1)
    n = p * q
    phi = (p - 1) * (q - 1)
    print(f"p: {p}")
    print(f"q: {q}")
    print(f"n: {n}")
    print(f"phi: {phi}")

    e = -1
    while e == -1 or sympy.gcd(e, phi) != 1:
        e = random.randint(2, phi - 1)
    d = sympy.mod_inverse(e, phi)
    print(f"e: {e}")
    print(f"d: {d}")

    public_key  = (e, n)
    private_key = (d, n)
    print(f"public_key:", public_key)
    print(f"private_key:", private_key)

    return public_key, private_key

def encrypt(message, public_key):
    e, n = public_key
    return [pow(ord(char), e, n) for char in message]

def decrypt(ciphertext, private_key):
    d, n = private_key
    return ''.join(chr(pow(c, d, n)) for c in ciphertext)



public_key, private_key = generate_keys()

mensaje = "Este es un mensaje secreto"

print("Mensaje a cifrar:", mensaje)

cifrado = encrypt(mensaje, public_key)
print("Mensaje cifrado:", cifrado)

descifrado = decrypt(cifrado, private_key)
print("Mensaje descifrado:", descifrado)
