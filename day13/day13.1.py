import copy

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
    
    original_values = []
    get_original_values(inputs, original_values)
    original_values_first = copy.deepcopy(original_values)
    
    print(calculate_total(original_values))
    
    for input_id, input in enumerate(inputs):
        break_out = False
        for i, row in enumerate(input):
            if break_out:
                break
            for j, _ in enumerate(row):
                switch_element(input, i, j)
                # print(input)
                if update_values(input, input_id, original_values):
                    break_out = True
                    break
                switch_element(input, i, j)
    
    print(calculate_total(original_values))
    
    for i in range(len(original_values)):
        if original_values_first[i]["type"] == original_values[i]["type"] and original_values_first[i]["count"] == original_values[i]["count"]:
            print(i)
    
    print(len(original_values))
    
def calculate_total(values):
    total = 0
    for value in values:
        if value["type"] == "col":
            total += value["count"]
        else:
            total += value["count"] * 100
    return total


def get_original_values(inputs, original_values):
    for input in inputs:
        rows_above = get_rows_above(input)
        if rows_above != -1:
            original_values.append({"type": "row", "count": rows_above})
            continue
        columns_to_left = get_columns_to_left(input)
        if columns_to_left != -1:
            original_values.append({"type": "col", "count": columns_to_left})
    
    
def switch_element(input, i, j):
    if input[i][j] == ".":
        input[i] = replace_char(input[i], j, "#")
    else:
        input[i] = replace_char(input[i], j, ".")
        
    
def replace_char(s, i, char):
    return s[:i] + char + s[i+1:]
    

def update_values(input, input_id, original_values):
    original_value = original_values[input_id]
    rows_above = rows_above_starting_from_top(input)
    if rows_above != -1:
        if original_value["type"] == "row" and original_value["count"] != rows_above:
            original_value["count"] = rows_above
            return True
        elif original_value["type"] == "col":
            original_value["type"] = "row"
            original_value["count"] = rows_above
            return True
    
    rows_above = rows_above_starting_from_bottom(input)
    if rows_above != -1:
        if original_value["type"] == "row" and original_value["count"] != rows_above:
            original_value["count"] = rows_above
            return True
        elif original_value["type"] == "col":
            original_value["type"] = "row"
            original_value["count"] = rows_above
            return True
        
    cols = []
    for j in range(len(input[0])):
        col = ""
        for i in range(len(input)):
            col += input[i][j]
        cols.append(col)
    
    columns_to_left = rows_above_starting_from_top(cols)
    if columns_to_left != -1:
        if original_value["type"] == "col" and original_value["count"] != columns_to_left:
            original_value["count"] = columns_to_left
            return True
        elif original_value["type"] == "row":
            original_value["type"] = "col"
            original_value["count"] = columns_to_left
            return True
        
    columns_to_left = rows_above_starting_from_bottom(cols)
    if columns_to_left != -1:
        if original_value["type"] == "col" and original_value["count"] != columns_to_left:
            original_value["count"] = columns_to_left
            return True
        elif original_value["type"] == "row":
            original_value["type"] = "col"
            original_value["count"] = columns_to_left
            return True
    
    return False
        

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
