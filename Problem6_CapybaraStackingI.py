def is_valid_stack(arr):
    prev = arr[0]
    section_sum = arr[0]
    last_section_sum = float('inf')  

    for i in range(1, len(arr)):
        x = arr[i]

        if x < prev: #continues the section
            section_sum += x

        elif x > prev: #new section
            if section_sum >= last_section_sum:
                return False  
            last_section_sum = section_sum #moving onto the next section
            section_sum = x #sets the new section_sum to the first element of new section

        else:
            return False #since we can't have two equal lengths in a row  

        prev = x #so we can move onto the next element

    
    if section_sum >= last_section_sum: #one last check
        return False

    return True


N = int(input()) 
for _ in range(N):
    arr = list(map(int, input().split())) 
    print("VALID" if is_valid_stack(arr) else "INVALID")
