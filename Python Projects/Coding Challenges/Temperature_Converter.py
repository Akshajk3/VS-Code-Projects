def c_to_f(celcius):
    farenheight = (celcius * (9/5)) + 32
    return farenheight

temp_c = int(input("what is your temeprature: "))
temp_f = c_to_f(temp_c)
print(temp_f)