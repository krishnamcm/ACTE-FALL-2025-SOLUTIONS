from collections import Counter
import heapq

def tallest_stack(capys):
    count = Counter(capys)
    result = []
    prev_section_sum = float('inf') 

    max_heap = [-x for x in capys] 
    heapq.heapify(max_heap)

    while max_heap:
        section = []
        section_sum = 0
        last = float('inf')

        used = []

        while max_heap:
            x = -heapq.heappop(max_heap)
            if x < last:
                section.append(x)
                section_sum += x
                last = x
            else:
                used.append(x)

        for x in used:
            heapq.heappush(max_heap, -x)

        if section_sum >= prev_section_sum:
            break

        result.extend(section)
        prev_section_sum = section_sum

    return result

capys = list(map(int, input().split()))
stack = tallest_stack(capys)
print(" ".join(map(str, stack)))
