import math
import sys

f = open('191IT142_IT352_P8_Output_TC6.txt','w')
def rsa():
    p = None
    q = None

    for i in range(2, n+1):
        for j in range(2, n+1):
            if i*j == n:
                p = i
                q = j
                break

    if p is None or q is None:
        print("d does not exist")
        f.write("d does not exist")
        return

    print(f"p = {p}")
    f.write("p = " +str(p)+"\n")
    print(f"q = {q}")
    f.write("q = " +str(q)+"\n")

    l = (p-1)*(q-1)

    d = pow(e, -1, l)
    print(f"d = {d}")

    print("Encryption operation")
    f.write("Encryption operation\n")
    cipher = []
    for m in message:
        cipher.append(pow(ord(m), e, n))

    print(f"cipher = {cipher}")
    f.write("cipher = " +str(cipher)+"\n")

    plaintext = []
    print("Decryption operation")
    f.write("Decryption operation\n")
    for c in cipher:
        plaintext.append(pow(c, d, n))

    print(f"plaintext = {plaintext}")
    f.write("plaintext = " +str(plaintext)+"\n")
    print(f"plaintext = {''.join([chr(p) for p in plaintext])}")


if __name__ == '__main__':
	e = int(input("Enter Public Key(e) = "))
	n = int(input("Enter Private Key(n) = "))
	message = input("Enter Message = ")
	rsa()
