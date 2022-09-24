def ShadowSentence(message1, message2):
    duplicates = message1.split()
    if len(message1) != len(message2):
        return False
    else:
        for c in message2:
            if c in duplicates:
                return False
            else:
                return True

def main():
    message1 = input("First Message: ")
    message2 = input("Second Message: ")

    result = ShadowSentence(message1, message2)
    if result:
        print("Is a shadow sentence")
    else:
        print("Not a shadow sentence")


if __name__ == '__main__':
    main()