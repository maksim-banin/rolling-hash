# Output a string that breaks hashes mod 2**n
from sys import argv

def bit_count(x):
    ans = 0
    while x > 0:
        if x % 2 == 1:
            ans += 1
        x /= 2
    return ans

# print argv
ans = ""
for i in range(int(argv[1])):
    ans += chr(ord('a') + bit_count(i))
print ans
