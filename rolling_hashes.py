P = 100

def build_partials(s):
    ans = [0] * len(s)
    ans [0] = ord(s[0])
    for i in range(1, len(s)):
        ans[i] = ans[i - 1] * P + ord(s[i])
    return ans

def poly_hash(partials, i, j):
    return partials[j] - partials[i] * (P**(j - i))

s = 'abacab'
precomputed = build_partials(s)

print 'partials:', precomputed
for i in range(len(s)):
    for j in range(i, len(s)):
        print i, '..', j, '\t', '"' + s[i : j] + '"', '\t', poly_hash(precomputed, i, j)
