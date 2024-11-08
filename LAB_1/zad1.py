# ZADANIE 1 / 2024.10.1
from math import sqrt

class Position():
    def __init__(self, x:int, y:int) -> None:
        self.x = x
        self.y = y

def distance(p1:Position, p2:Position):
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2))
    
# SPECYFIKACJA FUNKCJI
# n - int [1, MAX_INT]
# m - int [1, MAX_INT]
# x - int [0, n-1]
# y - int [0, m-1]
# output: 
# pozycja najbardziej oddalona od figury k
# obiekt typu Position
def fun(n:int, m:int, x:int, y:int):
    if n < 1 or m < 1:
        raise Exception("Błędna wielkość tablicy")
    
    if x < 0 or x >= n:
        raise Exception("Błędna pozycja x")
    
    if y < 0 or y >= m:
        raise Exception("Błędna pozycja y")
    
    if n == 1 and m == 1:
        return Position(0,0)

    # najdalej zawsze będą znajdowały się wierzchołki planszy więc wystarczy tylko je sprawdzić
    # (0,0) (0,m-1) (n-1,0) (n-1,m-1)

    verticles = [Position(0,0), Position(0, m-1), Position(n-1,0), Position(n-1,m-1)]
    max_distance = 0
    max_position = None
    k_pos = Position(x=x, y=y)
    for verticle in verticles:
        dist = distance(verticle, k_pos)
        if dist > max_distance:
            max_distance = dist
            max_position = verticle

    return max_position

def main():
    pos = fun(10,10,8,7)
    print(f"Pozycja: x:{pos.x}, y:{pos.y}")

if __name__ == "__main__":
    main()