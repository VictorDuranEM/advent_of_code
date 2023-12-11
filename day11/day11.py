import bisect

N = 1000000
N -= 1

def main():
    with open("input.txt", "r") as f:
        array = [[char for char in line.strip()]for line in f]

    # Obtain empty cols
    empty_cols = []
    for j in range(len(array[0])):
        empty = True
        for i in range(len(array)):
            if array[i][j] != ".":
                empty = False
                break
        if empty:
            empty_cols.append(j)


    # Obtain empty rows
    empty_rows = []
    for i, row in enumerate(array):
        if all(char == "." for char in row):
            empty_rows.append(i)

    # Get positions of all #
    galaxy_pos = []
    for i, row in enumerate(array):
        for j, element in enumerate(row):
            if element == '#':
                galaxy_pos.append((i, j))

    # Generate pairs of galaxies
    galaxy_pairs = []
    for i in range(len(galaxy_pos)):
        for j in range(i + 1, len(galaxy_pos)):
            galaxy_pairs.append((galaxy_pos[i], galaxy_pos[j]))
            
    total = 0
    for pair in galaxy_pairs:
        pair1 = pair[0]
        pair2 = pair[1]
        pair1_i = pair1[0]
        pair1_j = pair1[1]
        pair2_i = pair2[0]
        pair2_j = pair2[1]
        
        if pair2_j > pair1_j:
            empty_cols_between = count_numbers_between(empty_cols, pair1_j, pair2_j)
        else:
            empty_cols_between = count_numbers_between(empty_cols, pair2_j, pair1_j)
        
        if pair2_i > pair1_i:
            empty_rows_between = count_numbers_between(empty_rows, pair1_i, pair2_i)
        else:
            empty_rows_between = count_numbers_between(empty_rows, pair2_i, pair1_i)
        
        x_distance = abs(pair2_j - pair1_j) + empty_cols_between * N
        y_distance = abs(pair2_i - pair1_i) + empty_rows_between * N
        distance = x_distance + y_distance
        total += distance
        
    print(total)

def count_numbers_between(numbers, start, end):
    i = bisect.bisect_right(numbers, start)
    j = bisect.bisect_left(numbers, end)
    return j - i if j - i >= 0 else 0
    
main()