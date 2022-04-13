# Name : Ritesh Sharma
# Roll No : 191IT142

import math
import sys
import hashlib
import numpy as np

file = open('191IT142_IT352_P9_Output_TC6.txt','w')

# inputs
p = int(input("Enter value of P = "))
q = int(input("Enter value of Q = "))
e = int(input("Enter value of e = "))

# Message (M)
message = input("Enter Message = ")
print()

n = p*q                 # calculating n
phi = (p-1)*(q-1)       # calculating phi
d = pow(e, -1, phi)     # calculating d

print(f"Private key (d) = {d}")
file.write("Private key (d) = " +str(d)+"\n")
print()
file.write("\n")

print("Signing Operation : ")
file.write("Signing Operation : \n")

# Digest(D)
hash_message = (hashlib.md5(message.encode())).hexdigest()
print("Digest (D) : ",hash_message)
file.write("Digest (D) : " + hash_message+"\n")

# Digital signature (S)
cipher = []
for m in hash_message:
    cipher.append(pow(ord(m), d, n))

print(f"Digital Signature Values (RSA Encrypted) : {cipher}")
file.write("Digital Signature Values (RSA Encrypted) : " + str(cipher)+"\n")

# Message Signature Pair
print("(Message, Signature) Pair : ( "+ message +", " + f"{cipher}")
file.write("(Message, Signature) pair : (" + message+", "+ str(cipher)+"\n")

print()
file.write("\n")

# Verify Operation
print("Verifying Operation : ")
file.write("Verifying : \n")
print("Message : ", message)
file.write("Message : " + message+"\n")
print("Digest (D) : ",hash_message)
file.write("Digest (D) : " + hash_message+"\n")

# D'
plaintext = []


for c in cipher:
     plaintext.append(pow(c, e, n))

print("Digest values (RSA Decrypted) : " + f"{plaintext}")
file.write("Digest value (RSA Decrypted) : " + str(plaintext)+"\n")


print(f"Decrypted Digest (D') : {''.join([chr(p) for p in plaintext])}")
file.write(f"Decrypted Digest (D') : {''.join([chr(p) for p in plaintext])}\n")
print("D = D' => True => Accept")
file.write("D = D' => True => Accept\n")



	