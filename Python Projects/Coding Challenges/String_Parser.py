def parseString(message):
    first_name = ""
    last_name = ""
    id = ""

    i = 0

    while i < 2:
        for letter in message:

            if letter == "0":
                i += 1
                
            if i == 0:
                first_name += letter
            elif i == 1:
                last_name += letter
            elif i == 2:
                id += letter

    string = {"first_name": first_name , "last_name": last_name , "id": id }
    
    return string
    


def main():
    encoded_string = input("What is your encoded string: ")
    result = parseString(encoded_string)
    print(result)

if __name__ == "__main__":
    main()