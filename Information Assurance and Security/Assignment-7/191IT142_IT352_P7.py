# Name : Ritesh Sharma
# Roll No : 191IT142

# Importing Libraries
import hashlib
import hmac
import numpy as np
from binascii import hexlify


# function to generate random number of size 32 bytes to use it as seed value
def generateRandom():
  return np.random.bytes(32)

# generating seed value
seed = generateRandom()

# taking secret value as input from user
print("Enter Secret Value : ", end = "")
secret = input()

secret = bytes(secret, "utf-8")

result = bytearray()

# section : 1
section1 = hmac.new(secret, msg = None, digestmod = hashlib.md5)
section1.update(seed)

output1 = hmac.new(section1.digest(), digestmod = hashlib.md5)
output1.update(seed)
output1.update(secret)

# appending output of section 1 to result
for i in output1.digest():
  result.append(i)


# Section : 2
section2 = hmac.new(section1.digest(), digestmod = hashlib.md5)
section2.update(secret)

output2 = hmac.new(section2.digest(), digestmod = hashlib.md5)
output2.update(seed)
output2.update(secret)

# appending output of section 2 to result
for i in output2.digest():
  result.append(i)

# Section : 3
section3 = hmac.new(section2.digest(), digestmod = hashlib.md5)
section3.update(secret)

output3 = hmac.new(section3.digest(), digestmod = hashlib.md5)
output3.update(seed)
output3.update(secret)

# appending output of section 3 to result
for i in output3.digest():
  result.append(i)


# printing final output
print("Expanded Secrete is =", result)
with open("191IT142_IT352_P7_Output_TC6.txt", "w") as file:
  file.write("Expanded Secrete is = ")
  file.write(str(result))
