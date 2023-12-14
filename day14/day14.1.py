import day14
import hashlib

def main():
    total = 0
    loc_per_col = []
    with open("input.txt", "r") as file:
        array = [line.strip() for line in file.readlines()]
        array = [list(row) for row in array]
        
    hashes = []
    original_hex_dig = get_hex_hash(array)
    hashes.append(original_hex_dig)
    
    # print(day14.calculate_load(array))
    for i in range(1000):
        rotate_north(array)
        rotate_west(array)
        rotate_south(array)
        rotate_east(array)
        hex_dig = get_hex_hash(array)
        # print(hex_dig)
        # if hex_dig in hashes:
        #     print(f"Cycles: {i + 1}")
        #     break
        hashes.append(hex_dig)
        print(day14.calculate_load(array))
    
    # print(day14.calculate_load(array))
    
    
    # array = [''.join(row) for row in array]
    # for row in array:
    #     print(row)
    
def get_hex_hash(array):
    single_string = ''.join(''.join(row) for row in array)
    hash_object = hashlib.sha256(single_string.encode())
    return hash_object.hexdigest()
            
            
def rotate_north(array):
    loc_per_col = []
    for i, row in enumerate(array):
        for j, element in enumerate(row):
            if not check_index_exists(loc_per_col, j):
                loc_per_col.append(0)
            if element == "O":
                if loc_per_col[j] != i:
                    array[loc_per_col[j]][j] = "O"
                    array[i][j] = "."
                loc_per_col[j] += 1
            elif element == "#":
                loc_per_col[j] = i + 1
                

def rotate_west(array):
    loc_per_row = []
    for i, row in enumerate(array):
        if not check_index_exists(loc_per_row, i):
            loc_per_row.append(0)
        for j, element in enumerate(row):
            if element == "O":
                if loc_per_row[i] != j:
                    array[i][loc_per_row[i]] = "O"
                    array[i][j] = "."
                loc_per_row[i] += 1
            elif element == "#":
                loc_per_row[i] = j + 1
                

def rotate_south(array):
    loc_per_col = []
    for i, row in reversed(list(enumerate(array))):
        for j, element in enumerate(row):
            if not check_index_exists(loc_per_col, j):
                loc_per_col.append(len(row) - 1)
            if element == "O":
                if loc_per_col[j] != i:
                    array[loc_per_col[j]][j] = "O"
                    array[i][j] = "."
                loc_per_col[j] -= 1
            elif element == "#":
                loc_per_col[j] = i - 1
                

def rotate_east(array):
    loc_per_row = []
    for i, row in enumerate(array):
        if not check_index_exists(loc_per_row, i):
            loc_per_row.append(len(array) - 1)
        for j, element in reversed(list(enumerate(row))):
            if element == "O":
                if loc_per_row[i] != j:
                    array[i][loc_per_row[i]] = "O"
                    array[i][j] = "."
                loc_per_row[i] -= 1
            elif element == "#":
                loc_per_row[i] = j - 1
        

def check_index_exists(array, index):
    try:
        _ = array[index]
        return True
    except IndexError:
        return False
    
    
main()