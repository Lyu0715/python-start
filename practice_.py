one2nine = '123456789'

#인풋값을 적으면 10이하로 숫자의 배수의 구구단을 다 나오게.

숫자입력 = int(input())


for 인트수 in one2nine:
    정수들 = int(인트수)
    if 정수들 % 숫자입력 != 0:
        continue
    
    print(f"{정수들}의 곱셈")
    for 곱들 in one2nine:
        인트곱 = int(곱들)
        print(f"\n{정수들} * {인트곱} = {정수들*인트곱} ")