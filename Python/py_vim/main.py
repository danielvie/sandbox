import os
import tempfile

def get_text_from_vim():
    # template
    template_file = """
name: 
street: 
state: 
postal code: 
country: 

please fill in the details
"""

    # create a temporary file
    with tempfile.NamedTemporaryFile(suffix=".tmp", delete=False, mode="w") as tf:
        tf.write(template_file)
        temp_file_name = tf.name
    
    # open the temporary file with vim
    os.system(f'nvim {temp_file_name}')
    
    # read the contents of the temporary file
    with open(temp_file_name, 'r') as tf:
        content = tf.read()
        
    # delete the temporary file
    os.remove(temp_file_name)
    
    return content


if __name__ == '__main__':
    text = get_text_from_vim()
    print("you entered:")
    print(text)