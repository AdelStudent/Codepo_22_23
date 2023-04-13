# Open the file for reading
with open('script.js', 'r') as file, open('simple_cote.txt', 'w') as f_out:
    # Read the entire contents of the file into a string
    input_string = file.read()
    output_string = input_string.replace('"', '\\"')
    f_out.write(output_string)



symbol_number = 0


with open('simple_cote.txt', 'r') as f_in, open('test_string.cpp', 'w') as f_out:
    page = "my_page"
    f_out.write(f'  String my_page = "";')
    f_out.write("\n")
    for line in f_in:
        symbol_number+=len(line)
        f_out.write(f'  {page}+= "{line.rstrip()}";')
        f_out.write("\n")
    
    #last_string = "writeFile(SPIFFS, \"/script.js\", my_page);"
    #f_out.write(f'{last_string}')
print(f"La taille total du String vaut : {symbol_number}")
