original = input().strip()
final = input().strip()

count = 0
i = 0

while i < len(original):
    max_len = 0
    for l in range(1, len(original) - i + 1):
        substring = original[i:i+l]
        if substring in final:
            max_len = l
        else:
            break
    if max_len > 0:
        count += 1
        i += max_len 
    else:
        i += 1 

print(count)
