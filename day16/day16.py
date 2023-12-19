NORTH = "north"
SOUTH = "south"
WEST = "west"
EAST = "east"

def main():
    with open("input.txt", "r") as file:
        tiles = [[{"tile": tile, "is_energized": False, "directions": []} for tile in row.strip()] for row in file]
    follow_beam(tiles, EAST, 0, 0)
    print(count_energized_tiles(tiles))

    
def follow_beam(tiles, direction, i, j):
    while True:
        if i > len(tiles) - 1 or i < 0 or j > len(tiles[0]) - 1 or j < 0:
            break
        
        tile = tiles[i][j]
        if tile["is_energized"] and direction in tile["directions"]:
            break
        
        tile["is_energized"] = True
        if tile["tile"] == ".":
            tile["directions"].append(direction)
            if direction == NORTH:
                i -= 1
            elif direction == SOUTH:
                i += 1
            elif direction == EAST:
                j += 1
            elif direction == WEST:
                j -= 1
        elif tile["tile"] == "/":
            if direction == NORTH:
                j += 1
                direction = EAST
            elif direction == SOUTH:
                j -= 1
                direction = WEST
            elif direction == EAST:
                i -= 1
                direction = NORTH
            elif direction == WEST:
                i += 1
                direction = SOUTH
        elif tile["tile"] == "\\":
            if direction == NORTH:
                j -= 1
                direction = WEST
            elif direction == SOUTH:
                j += 1
                direction = EAST
            elif direction == EAST:
                i += 1
                direction = SOUTH
            elif direction == WEST:
                i -= 1
                direction = NORTH
        elif tile["tile"] == "|":
            if direction == NORTH:
                i -= 1
            elif direction == SOUTH:
                i += 1
            elif direction in (EAST, WEST):
                follow_beam(tiles, NORTH, i - 1, j)
                follow_beam(tiles, SOUTH, i + 1, j)
                break
        elif tile["tile"] == "-":
            if direction in (NORTH, SOUTH):
                follow_beam(tiles, WEST, i, j - 1)
                follow_beam(tiles, EAST, i, j + 1)
                break
            elif direction == EAST:
                j += 1
            elif direction == WEST:
                j -= 1
    

def count_energized_tiles(tiles):
    total = 0
    for row in tiles:
        for tile in row:
            if tile["is_energized"]:
                total += 1
    return total
    
    
main()