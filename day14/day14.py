def main():
    with open("input.txt", "r") as file:
        array = file.readlines()
    print(calculate_load(array))
    
def calculate_load(array):
    total = 0
    loc_per_col = []
    rows_count = len(array)
    for i, row in enumerate(array):
        for j, element in enumerate(row):
            if not check_index_exists(loc_per_col, j):
                loc_per_col.append(0)
            if element == "O":
                total += rows_count - loc_per_col[j]
                loc_per_col[j] += 1
            elif element == "#":
                loc_per_col[j] = i + 1
    return total
    

def check_index_exists(array, index):
    try:
        _ = array[index]
        return True
    except IndexError:
        return False
    
if __name__ == "__main__":
    main()