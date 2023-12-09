def main():
    total_sum = 0
    with open("./input.txt", 'r') as f:
        lines = f.readlines()
        for line in lines:
            nums = [int(x) for x in line.split(' ')]
            # total_sum += next_number(nums)
            total_sum += previous_number(nums)
    print(total_sum)
    
    
def next_number(nums):
    if all(num == 0 for num in nums):
        return 0
    next_nums = []
    for i in range(len(nums) - 1):
        next_nums.append(nums[i + 1] - nums[i])
    return nums[-1] + next_number(next_nums)

def previous_number(nums):
    if all(num == 0 for num in nums):
        return 0
    next_nums = []
    for i in range(len(nums) - 1):
        next_nums.append(nums[i + 1] - nums[i])
    return nums[0] - previous_number(next_nums)

main()