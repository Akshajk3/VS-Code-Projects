from translate import Translator

def TranslateMessage(message, lan):
    translator = Translator(to_lang=lan)
    result = translator.translate(message)
    return result

def main():
    message = input("What is your message: ")
    language = input("What language do you want to translate to: ")

    result = TranslateMessage(message, language)

    print(result)

if __name__ == '__main__':
    main()