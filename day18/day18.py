cols = 2000
rows = 2000
grid = [["." for _ in range(cols)] for _ in range(rows)]
grid[500][500] = "#"
i = 500
j = 500
def main():
    with open("input.txt", "r") as file:
        for row in file:
            update_grid(row)

    print('\n'.join(''.join(row) for row in grid))
    

def update_grid(move):
    global j, i
    direction = move.split(' ')[0]
    distance = int(move.split(' ')[1])
    if direction == "R":
        for _ in range(distance):
            j += 1
            grid[i][j] = "#"
    elif direction == "L":
        for _ in range(distance):
            j -= 1
            grid[i][j] = "#"
    elif direction == "U":
        for _ in range(distance):
            i -= 1
            grid[i][j] = "#"
    elif direction == "D":
        for _ in range(distance):
            i += 1
            grid[i][j] = "#"


main()
