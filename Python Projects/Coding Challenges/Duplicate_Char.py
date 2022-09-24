def checkForDuplicates(message):
    duplicates = []
    for c in message:
        if c in duplicates:
            return True
        else:
            duplicates.append(c)
    return False

def main():
    message = input("Message: ")
    result = checkForDuplicates(message.lower())
    if result:
        print("Has duplicate character")
    else:
        print("No duplicate characters")


if __name__ == '__main__':
    main()