from collections import Counter

s = input().strip()
freq = Counter(s)

print(max(freq.values()))
