from collections import Counter

sentence = input().split()
myDict = Counter(sentence) #turn it into a dictionary

ans = []

for word in sorted(myDict.keys()): #sort cuz alphabetical
    freq = myDict[word] 
    
    if freq < 6:
        ans.extend([word] * (6 - freq))
    
    #otherwise, we don't do anything since its already 6 or more

print(" ".join(ans))
