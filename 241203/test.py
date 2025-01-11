# A necklace contains 2*m number of rubies and 2*n number of diamonds.
# We want to evenly distribute the necklace to 2 people, you can at most make two cuts.
# How would you make the cut(s)?
# Example: DRRDDRDRRR -> DRRD|DRDRR|R

# DRRD | DRDRR | R


# one cut: DRRDR | DRDRR
# two cuts: DRRD | RDRRDR | RR

def solution(necklace):
    res = []
    m, n = 0, 0
    for stone in necklace:
        if stone == 'R':
            m += 1
        else:
            n += 1
    min_, max_ = m, n
    min_stone, max_stone = 'R', 'D'
    if min_ > max_:
        min_, max_ = max_, min_
        min_stone, max_stone = max_stone, min_stone

    half_min, half_max = min_ // 2, max_ // 2
    count_m, count_n = 0, 0
    idx = 0
    for i in range(len(necklace)):
        stone = necklace[i]
        if stone == 'R':
            count_m += 1
        else:
            count_n += 1
        if min_stone == 'R' and count_m == half_min:
            res.append(i)
            idx = i
            break
        if min_stone == 'D' and count_n == half_min:
            res.append(i)
            idx = i
            break
    if idx + 1 != len(necklace) // 2:
        count_m, count_n = 0, 0
        for i in range(idx + 1, len(necklace)):
            stone = necklace[i]
            if stone == 'R':
                count_m += 1
            else:
                count_n += 1
            if max_stone == 'R' and count_m == half_max:
                res.append(i)
                break
            if max_stone == 'D' and count_n == half_max:
                res.append(i)
                break
    print(res)
    return res


def _solution(necklace):
    res = []
    m, n = 0, 0
    for stone in necklace:
        if stone == "R":
            m += 1
        else:
            n += 1
    min_ = m
    max_ = n
    stone = 'R'
    if min_ > n:
        min_ = n
        max_ = m
        stone = 'D'
    print("min_:", min_)

    next_ = stone
    count_m, count_n = 0, 0
    for i, n in enumerate(necklace):
        print(i, n, stone, count_m, count_n, min_, res)
        if n == 'R' and stone == 'R':
            count_m += 1
        elif m == 'D' and stone == 'M':
            count_n += 1
        if count_m == min_ // 2 and next_ == 'R':
            res.append(i)
            count_n = 0
            count_m = -min_
            next_ = "D"
        if count_n == min_ // 2 and next_ == 'D':
            res.append(i)
            count_m = 0
            count_n = -min_
            next_ = "R"
        if next_ == "D" and count_n == max_ // 2:
            res.append(i)
            break
        if next_ == "R" and count_m == max_ // 2:
            res.append(i)
            break
        # else:
        #     if count_n == min_ // 2:
        #         res.append(i)
        #         count_m = 0
        #     if count_m == min_ // 2:
        #         res.append(i)
        #         break

    print(res)

    return res

input = "DRRDDRDRRR"
solution(input)
input = "DRRRDDRDRR"
solution(input)
input = "DRRDRDRRDRRR"
solution(input)

def solution_2(necklace):
    res = []
    m, n = 0, 0
    # Count the total number of rubies (R) and diamonds (D)
    for stone in necklace:
        if stone == "R":
            m += 1
        else:
            n += 1

    # Check if the necklace can be evenly divided
    if (m % 2 != 0 or n % 2 != 0):
        print("Cannot evenly divide the necklace into two parts")
        return []

    half_rubies = m // 2
    half_diamonds = n // 2

    # Use counters to track stones for each part
    count_r, count_d = 0, 0
    for i, stone in enumerate(necklace):
        if stone == "R":
            count_r += 1
        else:
            count_d += 1

        # Check if the first cut can be made
        if count_r == half_rubies and count_d == half_diamonds:
            res.append(i)
            count_r, count_d = 0, 0  # Reset counters for the next segment

    # Verify if the cuts produce valid parts
    if len(res) == 1:  # Single cut case
        print("One cut is enough:", res)
    elif len(res) == 2:  # Two cuts case
        print("Two cuts made at:", res)
    else:
        print("Failed to make valid cuts.")

    return res

input = "DRRDDRDRRR"
solution_2(input)
input = "DRRRDDRDRR"
solution_2(input)
input = "DRRDRDRRDRRR"
solution_2(input)

def solution_3(necklace):
    total_r = necklace.count('R')  # Total Rubies
    total_d = necklace.count('D')  # Total Diamonds

    # Verify that the rubies and diamonds can be evenly split
    if total_r % 2 != 0 or total_d % 2 != 0:
        print("Failed to make valid cuts: Uneven rubies or diamonds.")
        return []

    target_r = total_r // 2  # Target rubies per person
    target_d = total_d // 2  # Target diamonds per person

    count_r, count_d = 0, 0  # Track rubies and diamonds
    cuts = []  # Indices for the cuts

    for i, stone in enumerate(necklace):
        if stone == 'R':
            count_r += 1
        else:
            count_d += 1

        # Make a cut when a part reaches half of the target distribution
        if (count_r == target_r or count_d == target_d) and len(cuts) < 2:
            cuts.append(i)
            count_r, count_d = 0, 0  # Reset counts for the next part

    # Final validation to ensure we made the correct cuts
    if len(cuts) == 2:
        print("Cuts made at indices:", cuts)
        return cuts
    else:
        print("Failed to make valid cuts.")
        return []

input = "DRRDDRDRRR"
solution_3(input)
input = "DRRRDDRDRR"
solution_3(input)
input = "DRRDRDRRDRRR"
solution_3(input)

def solution_4(necklace):
    total_r = necklace.count('R')  # Total rubies
    total_d = necklace.count('D')  # Total diamonds

    # Check if counts are even to allow equal splits
    if total_r % 2 != 0 or total_d % 2 != 0:
        print("Cannot make valid cuts")
        return []

    target_r = total_r // 2
    target_d = total_d // 2

    count_r, count_d = 0, 0  # Counters for rubies and diamonds
    cuts = []  # To store cut indices

    for i, stone in enumerate(necklace):
        if stone == 'R':
            count_r += 1
        else:
            count_d += 1

        # First cut: Stop when half of rubies or diamonds are found
        if len(cuts) == 0 and (count_r == target_r or count_d == target_d):
            cuts.append(i)
        # Second cut: Stop when the remaining half is found
        elif len(cuts) == 1 and (count_r == target_r and count_d == target_d):
            cuts.append(i)
            break  # Stop early after two cuts

    return cuts


input = "DRRDDRDRRR"
solution_4(input)
input = "DRRRDDRDRR"
solution_4(input)
input = "DRRDRDRRDRRR"
solution_4(input)

# class Person:
#     def __init__(self, name, age):
#         self.name = name
#         self.age = age

#     def introduce(self):
#         return f"My name is {self.name} and I am {self.age} years old."

# if __name__ == "__main__":
#     person = Person("Alice", 30)
#     print(person.introduce())