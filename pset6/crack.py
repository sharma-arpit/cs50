import crypt
import sys
import time

time_process = 0.0

if len(sys.argv) != 2:
    print("Usage: python crack.py hashed_password")
    exit(1)

salt = str(50)
before = time.process_time()
def main():
    for i in range(65, 65+26+26):
        if i<91:
            w = chr(i)
        else:
            w = chr(i+6)
        for j in range(65, 65+26+26):
            if j<91:
                o = chr(j)
            else:
                o = chr(j+6)
            for k in range(65, 65+26+26):
                if k<91:
                    r = chr(k)
                else:
                    r = chr(k+6)
                for l in range(65, 65+26+26):
                    if l<91:
                        d = chr(l)
                    else:
                        d = chr(l+6)
                    if check(w, o, r, d):
                        after = time.process_time()
                        time_process = after - before
                        print("Time program took while cracking the password = {:.2f} sec.".format(time_process))
                        exit (0)
                    else:
                        continue

    
def check(w, o, r, d):
    word = w+o+r+d
    hash1 = crypt.crypt(word[0:4], salt)
    if hash1 == sys.argv[1]:
        print(word)
        return True
    
    hash2 = crypt.crypt(word[0:3], salt)
    if hash2 == sys.argv[1]:
        print(word[0:3])
        return True
    
    hash3 = crypt.crypt(word[0:2], salt)
    if hash3 == sys.argv[1]:
        print(word[0:2])
        return True

    hash4 = crypt.crypt(word[0:1], salt)
    if hash4 == sys.argv[1]:
        print(word[0:1])
        return True
    return False
before1 = time.process_time()
if __name__ == "__main__":
    main()
