def remove_text(filename):
    with open(filename, 'r+') as f:
        f.truncate(0)

# Example usage
filename = 'detect.txt'
remove_text(filename)

print(f'The contents of {filename} have been removed.')
