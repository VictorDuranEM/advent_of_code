def main():
    with open("input.txt", "r") as file:
        list_data = file.read().split(',')
    total = 0
    for element in list_data:
        total += calculate_hash(element)
    print(total)
    

def calculate_hash(string):
    total = 0
    for char in string:
        total += ord(char)
        total *= 17
        total %= 256 
    return total

if __name__ == "__main__":
    main()