text = 'Python_Data-Analysis!'

모음들 = "AEIOUaeiou"
모음모음 = ""

for char in text:
    if char in 모음들:
        모음모음 += char
    else:
        print(f"{char}은 모음 아님")

print("모음들",모음모음)