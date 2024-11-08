import math
import random
from zad2 import print_array

class Point():
    def __init__(self, x:int, y:int) -> None:
        self.x = x
        self.y = y
    
    def add(self, p:'Point'):
        n_x = p.x + self.x
        n_y = p.y + self.y
        return Point(n_x,n_y)
    
    def __str__(self) -> str:
        return "x:" + str(self.x) + ",y:" + str(self.y)

# (horizontal-x, vertical-y)
neighbours = [
    Point(0,1),      # N
    Point(1,1),      # NE
    Point(1,0),      # E
    Point(1,-1),     # SE
    Point(0,-1),     # S
    Point(-1,-1),    # SW
    Point(-1,0),     # W
    Point(-1,1)      # NW
]
# x - horizontal
# y - vertical
# n - rows (ver)
# y - cols (hor)
def is_in_range(p:Point,n,m):
    if p.x < 0 or p.y < 0 or p.x >= m or p.y >= n:
        return False
    return True

def fun(arr, n, m, k):
    # [(Point, value), ...]
    best_points = []
    for row in range(n):
        tmp = row % k
        first = k - tmp if tmp != 0 else 0

        while(first < m):
            current_point = Point(first, row)
            product = 1
            for neighbour in neighbours:
                neighbour_point = current_point.add(neighbour)
                if not is_in_range(neighbour_point, n, m):
                    continue
                
                product*=arr[neighbour_point.y][neighbour_point.x]
            best_points.append( (Point(first,row), product) )
            first+=k

    # find min product point
    min_product = math.inf
    min_point = None
    for point in best_points:
        if point[1] < min_product:
            min_product = point[1]
            min_point = point[0]
    
    return min_point

def main():
    MAX_VALUE = 5
    arr = []
    n = 4
    m = 4
    k = 2

    for row in range(n):
        arr.append([])
        for col in range(m):
            arr[row].append(random.randrange(MAX_VALUE)+1)

    output = fun(arr,n,m,k)
    print("punkt:", output.x, output.y)

    print_array(arr,n,m)


if __name__ == "__main__":
    main()
    # print(is_in_range(Point(1,1), 10,10))