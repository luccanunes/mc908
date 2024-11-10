# Define file paths
file1_path = 'out'
file2_path = 'node_betweenness'

try:
    with open(file1_path, 'r') as file1, open(file2_path, 'r') as file2:
        line_number = 1
        for line1, line2 in zip(file1, file2):
            try:
                num1 = float(line1.strip())
                num2 = float(line2.strip())
                difference = num1 - num2
                print(f"Difference in line {line_number}: {difference}")
            except ValueError:
                print(f"Error: Non-numeric value encountered on line {line_number}")
            line_number += 1

    # Reopen the files to check for extra lines
    with open(file1_path, 'r') as file1, open(file2_path, 'r') as file2:
        # Skip lines already read by zip
        for _ in range(line_number - 1):
            next(file1, None)
            next(file2, None)

        # Check if there are extra lines in either file
        extra_lines_file1 = any(file1)
        extra_lines_file2 = any(file2)
        if extra_lines_file1 or extra_lines_file2:
            print("Warning: Files have different numbers of lines.")

except FileNotFoundError:
    print("Error: One or both files could not be found.")
