filename = 'githubSSL.cer'
with open(filename, 'rb') as f:
    content = f.read()

print('// '+filename)
print('const char* test_root_ca = \ ')
outString = '"'
caCertLen = 0


x = len(content)

for i in range(0, x-1):
    first = (chr(content[i]))
    if content[i]==13:
        outString = outString + '\\n" \ '
    outString = outString+first
    if content[i]==10:
        outString = outString + '"'
    
outString = outString[:-2]

print(outString[:-1]+';')
