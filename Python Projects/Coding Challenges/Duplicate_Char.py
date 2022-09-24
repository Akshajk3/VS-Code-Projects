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
    print(result)


if __name__ == '__main__':
    main()