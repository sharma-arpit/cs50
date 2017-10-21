import cs50
import crypt
import sys

s = sys.argv[1]
crypted_pass = crypt.crypt(s, str(50))
print(crypted_pass)