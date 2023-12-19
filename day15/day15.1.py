import day15

boxes = [[] for _ in range(256)]
labels = []
def main():
    with open("input.txt", "r") as file:
        list_data = file.read().split(',')
    for element in list_data:
        if "=" in element:
            label = element.split('=')[0]
            if label not in labels:
                labels.append(label)
            power = int(element.split('=')[1])
            label_hash = day15.calculate_hash(label)
            box = boxes[label_hash]
            if len(box) == 0:
                box.append([label, power])
            else:
                found = False
                for lens in box:
                    if lens[0] == label:
                        lens[1] = power
                        found = True
                        break
                if not found:
                    box.append([label, power])
                        
        else:
            label = element.split('-')[0]
            label_hash = day15.calculate_hash(label)
            box = boxes[label_hash]
            for lens in box:
                if lens[0] == label:
                    box.remove(lens)
                    labels.remove(label)
        
    total = 0
    for label in labels:
        label_hash = day15.calculate_hash(label)
        box = boxes[label_hash]
        slot_number = 0
        power = 0
        for i, lens in enumerate(box):
            if lens[0] == label:
                slot_number = i + 1
                power = lens[1]
                break
        total += (1 + label_hash) * slot_number * power
      
    print(total)
            
    # for box in boxes:
    #     if len(box) != 0:
    #         print(box)
    
    
main()