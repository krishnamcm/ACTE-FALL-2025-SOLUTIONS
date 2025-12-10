s = input()
n = len(s)

min_cats = 0
max_cats = 0

i = 0
while i <= n - 3:
    triple = s[i:i+3]

    if (triple[0] == 'C' or triple[0] == '#') and \
       (triple[1] == 'A' or triple[1] == '#') and \
       (triple[2] == 'T' or triple[2] == '#'):
        max_cats += 1

        if triple[0] == 'C' and triple[1] == 'A' and triple[2] == 'T':
            min_cats += 1

        i += 3  
    else:
        i += 1


for x in range(min_cats, max_cats + 1):
    print(x)
