# Define the filename
file_path = "C:/Users/Public/omnetpp-6.0.3-windows-x86_64/omnetpp-6.0.3/samples/assign2/Network.ned"

file_path1 = "C:/Users/Public/omnetpp-6.0.3-windows-x86_64/omnetpp-6.0.3/samples/assign2/client.ned"

# Read the content of the file
with open(file_path, 'r') as file:
    content = file.read()

with open(file_path1, 'r') as file:
    content1 = file.read()

# Take input from the user for the new value of n
new_value_of_n = input("Enter the new value for n: ")

# Modify the value of n in the content
content = content.replace('int n', f'int n = {new_value_of_n};')
content1 = content1.replace('int n', f'int n = {new_value_of_n};')

# Write the modified content back to the file
with open(file_path, 'w') as file:
    file.write(content)

with open(file_path1, 'w') as file:
    file.write(content1)

print(f'Value of n in the file has been changed to {new_value_of_n}.')
