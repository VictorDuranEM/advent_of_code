import bisect

def count_numbers_between(numbers, start, end):
    i = bisect.bisect_right(numbers, start)
    j = bisect.bisect_left(numbers, end)
    return j - i if j - i >= 0 else 0

numbers = [1, 3, 6, 8, 20, 45]
a = 3
b = 3
if b > a:
    print(count_numbers_between(numbers, a, b))
else:
    print(count_numbers_between(numbers, b, a))