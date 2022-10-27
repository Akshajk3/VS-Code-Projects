def Check_for_Validation(postalCode):
    if int(postalCode) < 10000 or int(postalCode) > 999999:
        return False
    i = 0
    p = 2

    while p <= len(postalCode):
        i += 1
        p += 1
        if postalCode[i] == postalCode[p]:
            return False

    return True

def main():
    code = input("Input a Postal Code: ")
    result = Check_for_Validation(code)
    if result:
        print("True")
    else:
        print("False")

if __name__ == '__main__':
    main()