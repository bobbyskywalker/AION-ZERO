import re

text = open("file.txt").read()

values = re.findall(r'0x([0-9a-fA-F]{2})', text)

swapped = []
for i in range(0, len(values), 2):
    swapped.append("0x" + values[i + 1])
    swapped.append("0x" + values[i])

for i in range(0, len(swapped), 16):
    print("    " + ", ".join(swapped[i:i+16]) + ",")