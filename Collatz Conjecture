def solve():
    inp = input().split()
    num = int(inp[0])
    iterations = int(inp[1])
    
    while (num != 4 and iterations != 0):
        if (num % 2 == 0):
            num /= 2
        else:
            num = num * 3 + 1
            
        iterations -= 1
        
    if iterations == 0:
        print(int(num))
        return
        
    if iterations % 3 == 0:
        print(4)
        return
    elif iterations % 3 == 1:
        print(2)
        return
    else:
        print(1)
        return
    
    print(int(num))
    
solve()
