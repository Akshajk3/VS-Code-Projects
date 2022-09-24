def charDifference(input1, input2):
    og = []
    difference = []
    for c in input1:
        og.append(c)
    for c in input2:
        if c not in og:
            difference.append(c)
    
    return difference

def listToString(s):
    str1 = " "
    return (str1.join(s))

def main():
    message1 = input("First Message: ")
    message2 = input("Second Message: ")

    result = charDifference(message1, message2)
    print(listToString(result))


if __name__ == '__main__':
    main()