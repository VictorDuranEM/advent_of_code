from colorama import Fore, Style, Back

def main():
    with open('input.txt', 'r') as file:
        array = [[char for char in line.strip()] for line in file]
        curr_location = find_start(array)
        prev_location = curr_location
        locations = [curr_location]
        loop_len = 0;
        while True:
            temp = curr_location
            curr_location = find_next(array, curr_location, prev_location)
            prev_location = temp
            loop_len += 1
            locations.append(curr_location)
            if array[curr_location[0]][curr_location[1]] == "S":
                array[curr_location[0]][curr_location[1]] = "F"
                break
        # print(loop_len)
        print(count_inner(array, locations))
        # print_color(array, locations)
        
        
def count_inner(array, locations):
    count = 0
    inside_loop = False
    f_touched = False
    l_touched = False
    for i, row in enumerate(array):
        for j, element in enumerate(row):
            if (i, j) in locations:
                if element == "|":
                    inside_loop = not inside_loop
                elif element == "F":
                    f_touched = True
                elif element == "L":
                    l_touched = True
                elif element == "7":
                    if l_touched:
                        inside_loop = not inside_loop
                        l_touched = False
                    else:
                        f_touched = False
                elif element == "J":
                    if f_touched:
                        inside_loop = not inside_loop
                        f_touched = False
                    else:
                        l_touched = False
                print_element_color(element, "red")
            elif inside_loop:
                count += 1
                print_element_color(element, "blue")
            else:
                print_element_color(element, "normal")
        print()
        f_touched = False
        l_touched = False
    return count


def print_color(array, locations):
    for i, row in enumerate(array):
        for j, element in enumerate(row):
            if ((i, j) in locations):
                if element == "F":
                    element = "┌"
                elif element == "7":
                    element = "┐"
                elif element == "L":
                    element = "└"
                elif element == "J":
                    element = "┘"
                print(Fore.RED + element + Style.RESET_ALL, end='')
            else:
                print(".", end='')
        print()
        
        
def print_element_color(element, color):
    if element == "F":
        element = "┌"
    elif element == "7":
        element = "┐"
    elif element == "L":
        element = "└"
    elif element == "J":
        element = "┘"
    
    if color == "red":
        print(Back.RED + element + Style.RESET_ALL, end='')
    elif color == "blue":
        print(Back.BLUE + element + Style.RESET_ALL, end='')
    else:
        print(element, end='')
        
    
def find_start(array):
    for i, row in enumerate(array):
        for j, element in enumerate(row):
            if element == "S":
                return (i, j)
            

def find_next(array, curr_location, prev_location):
    ci = curr_location[0]
    cj = curr_location[1]
    pi = prev_location[0]
    pj = prev_location[1]
    c = array[ci][cj]
    if c == "S":
        if array[ci - 1][cj] in ["|", "7", "F"]:
            return (ci - 1, cj)
        elif array[ci + 1][cj] in ["|", "L", "J"]:
            return (ci + 1, cj)
        elif array[ci][cj - 1] in ["-", "J" "7"]:
            return (ci, cj - 1)
        elif array[ci][cj + 1] in ["-", "L", "F"]:
            return (ci, cj + 1)
    elif c == "|":
        if ci > pi:
            return (ci + 1, cj)
        else:
            return (ci - 1, cj)
    elif c == "-":
        if cj > pj:
            return (ci, cj + 1)
        else:
            return (ci, cj - 1)
    elif c == "L":
        if ci > pi:
            return (ci, cj + 1)
        else:
            return (ci - 1, cj)
    elif c == "J":
        if ci > pi:
            return (ci, cj - 1)
        else:
            return (ci - 1, cj)
    elif c == "7":
        if ci < pi:
            return (ci, cj - 1)
        else:
            return (ci + 1, cj)
    elif c == "F":
        if ci < pi:
            return (ci, cj + 1)
        else:
            return (ci + 1, cj)
    

main()