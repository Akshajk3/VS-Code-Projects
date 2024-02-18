def natural_log(x, terms=100):
    result = 0.0
    for n in range(1, terms + 1):
        result += ((-1) ** (n - 1)) * ((x - 1) ** n) / n
    return result

x = 2.0

print("Natural Log of", x, "is: ", natural_log(x))
