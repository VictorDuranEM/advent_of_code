def main():
    inputs = []
    with open("input.txt", "r") as f:
        input = []
        for row in f:
            if row == "\n":
                inputs.append(input)
                input = []
                continue
            input.append(row.strip())
        inputs.append(input) # Include last input before EOF
    
    rows_above_list = []
    columns_to_left_list = []
    count = 0
    for input in inputs:
        count += 1
        rows_above = get_rows_above(input)
        if rows_above != -1:
            rows_above_list.append(rows_above)
            continue
        columns_to_left = get_columns_to_left(input)
        if columns_to_left != -1:
            columns_to_left_list.append(columns_to_left)
        else:
            print("no match")
    
    total = sum(columns_to_left_list) + sum(rows_above_list) * 100
    
    # print(columns_to_left_list)
    # print(rows_above_list)
    # print(len(columns_to_left_list) + len(rows_above_list))
    print(total)
        

def get_rows_above(rows):
    rows_above = rows_above_starting_from_top(rows)
    if (rows_above != -1):
        return rows_above
    return rows_above_starting_from_bottom(rows)


def rows_above_starting_from_top(rows):
    match_index = -1
    for i in range (1, len(rows)):
        if rows[i] == rows[0]:
            rows_span = i + 1
            if rows_span % 2 != 0:
                continue
            if is_mirror(rows, 1, i - 1):
                match_index = i
    if match_index != -1:
        return (match_index + 1) // 2
    else:
        return -1


def rows_above_starting_from_bottom(rows):
    match_index = -1
    rows_len = len(rows)
    for i in range(rows_len-2, -1, -1):
        if rows[i] == rows[rows_len - 1]:
            rows_span = rows_len - i        
            if rows_span % 2 != 0:
                continue
            if is_mirror(rows, i + 1, rows_len - 2):
                match_index = i
    if match_index != -1:
        return (rows_len - match_index) // 2 + match_index
    else:
        return -1
            

def is_mirror(rows, start, end):
    for i in range((end - start + 1) // 2):
        if (rows[start + i] != rows[end - i]):
            return False
    return True
    

def get_columns_to_left(rows):
    # First convert columns to rows to be able to use the same functions for rows
    cols = []
    for j in range(len(rows[0])):
        col = ""
        for i in range(len(rows)):
            col += rows[i][j]
        cols.append(col)
    
    cols_to_left = rows_above_starting_from_top(cols)
    if cols_to_left != -1:
        return cols_to_left
    return rows_above_starting_from_bottom(cols)
    

main()
