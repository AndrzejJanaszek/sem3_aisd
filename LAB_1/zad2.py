# NxM
# k
#
import random   


# arr - 2d tablica
# n - rows
# m - cols
# k - ilosc kolorow 
#
# return: index koloru / kolor
def naj_sasiady(arr:list, n:int, m:int, k:int):
    count = [0 for i in range(k)]
    # [0;k-1] indexy kolorow

    for row in range(n):
        for col in range(m):
            current_color = arr[col][row]

            if col-1 >= 0 and arr[col-1][row] == current_color:
                count[current_color] += 1
            if col+1 < m and arr[col+1][row] == current_color:
                count[current_color] += 1

    max_count = 0
    max_color = 0
    for i in range(k):
        if max_count < count[i]:
            max_color = i
            max_count = count[i]

    print("kolor: ",max_color)
    print("ilosc: ",max_count)
    return max_color

def print_array(arr,n,m):
    print("array:")
    for row in range(n):
        for col in range(n):
            print(arr[col][row], end=" ") 
        
        print()

def main():
    n = 4
    m = 4
    k = 3
    arr = []
    for row in range(n):
        arr.append([])
        for col in range(n):
            arr[row].append(random.randrange(k))

    print_array(arr,n,m)

    naj_sasiady(arr,n,m,k)

if __name__ == "__main__":
    main()