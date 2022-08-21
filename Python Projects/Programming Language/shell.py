import sys
import basic


while True:
    text = input('baisc > ')
    result, error = basic.run(text, '<stdin>')

    if text == 'exit()':
        exit()
    elif error:
        print(error.as_string())
    else:
        print(result)