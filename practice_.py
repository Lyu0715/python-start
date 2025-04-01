text = 'Python_Data-Analysis!'
완성전문자 = ""

for char in text:
    if char in text: 
        if char.isalpha():
            완성된문자 += 완성전문자
        else:
            쓰레기 +=  char    


쓰레기 = ""
완성된문자 = ""

print(f"기타문자모음:{쓰레기}\n")
("포함된 자음{완성된문자}")
