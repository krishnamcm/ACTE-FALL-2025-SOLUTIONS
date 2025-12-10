N = int(input().strip())
for _ in range(N):
    line = input().rstrip("\n") 
    
    stripped = line.lstrip()   
    
    if not (stripped.startswith("for") or
            stripped.startswith("while") or
            stripped.startswith("if")):
        if not line.endswith(";"):
            line += ";"
    
    print(line)

