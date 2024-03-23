import os
import sys
import time
import re 
def Function1():
    try:
        print("Operating System:",os.name)
        print("\nInformation of current operating system: ",os.uname())
        print("\nCurrent Working Directory: ",os.getcwd())
        print("\nList of files and directories in the current directory:")
        print(os.listdir(os.getcwd()))

        os.chdir('/home')
        directory = os.getcwd()
        inaccessible_items = []
        items = os.listdir('.')
        for item in items:
            path = os.path.join(directory, item)
            if not os.access(path, os.R_OK):
                inaccessible_items.append(path)
                
        if inaccessible_items:
            raise ValueError("Inaccessible files and directories in /home:")
        else:
            print("No inaccessible files or directories found in /home")

    except Exception as e:
        print(e)
        for item in inaccessible_items:
            print(item)

def Function2():
    path = input("Enter path: ")
    try:
        stat_info = os.stat(path)

        size = stat_info.st_size
        permissions = stat_info.st_mode
        owner = stat_info.st_uid
        device = stat_info.st_dev
        created = time.ctime(stat_info.st_ctime)
        last_modified = time.ctime(stat_info.st_mtime)
        last_accessed = time.ctime(stat_info.st_atime)

        print("Size:", size, "bytes")
        print("Permissions:", permissions)
        print("Owner:", owner)
        print("Device:", device)
        print("Created:", created)
        print("Last Modified:", last_modified)
        print("Last Accessed:", last_accessed)
    except Exception as e:
        raise ValueError(f"Error: {e}")

def openFile():
    try:
        # file_path = input("Enter the path of the input file: ")
        # output_file = input("Enter the path of the output file: ")
        file_path = "input_excer3.xml"
        output_file ='result_func4.txt'
        with open(file_path, 'r') as file:
            content = file.read()
            return content, output_file
    except FileNotFoundError:
        print("File not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def Function3():
    try:
        content, output_file = openFile()
        # Find and replace with regex
        result_string = re.sub(r"([0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12})", "8a8a8a8a-4b4b-4c4c-4d4d-12e12e12e12e", content)
        with open(output_file, 'w') as file:
            file.write(result_string)
        print("Result written to", output_file)

    except Exception as e:
        raise ValueError(f"Error: {e}")

def count_words(content):
    # Use regular expression to find words after '<' or '</'
    # matches = re.findall(r'</?(\w+-?\w*)>', content)
    matches = re.findall(r'<\/?(\w+(-?\w*)+)>|<\/?(\w+(-?\w*)+)\S', content)

    # Count the frequency of each word
    word_freq = {} # create dict  
    for match in matches:
        if match in word_freq:
            word_freq[match] += 1
        else:
            word_freq[match] = 1
    
    return word_freq

def write_result(word_freq, output_file):
    with open(output_file, 'w') as file:
        # Write the word frequencies to the output file
        for word, freq in word_freq.items():
            file.write(f"{word}: {freq}\n")
    print("Result written to", output_file)

def Function4():
    try:
        content, output_file = openFile()
        # Count word frequencies function
        word_freq = count_words(content)
        if word_freq:
            # Write result to output file
            write_result(word_freq, output_file)
        else:
            print("Nothing matches")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    while True:
        print("Choose function from 1-4:")
        func = int(input())
        if func > 4 and func < 0: 
            print("Choose again.")
            continue
        elif func == 1:
            Function1()
        elif func == 2:
            Function2()        
        elif func == 3:
            Function3()
        elif func == 4:
            Function4()

