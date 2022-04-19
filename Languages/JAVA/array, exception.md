> [명품 JAVA Programming](https://book.naver.com/bookdb/book_detail.nhn?bid=13650995) 을 보고 정리한 글입니다.

# 배열
### 선언 및 생성
![](https://images.velog.io/images/yesterdaykite/post/28197d37-7d89-454d-9f76-7a9aac531aa7/image.png)


- 주의사항
  - `int intArr[10]; // 컴파일오류` 배열의 크기 지정할 수 X
  - 생성과 동시에 선언  `int intArr[] = new int[5];`
  - 배열 초기화 `int intArr[] = {1,2,3,4};`
    - 자동으로 배열 크기가 4가 된다
  - 배열 원소에 접근하려면, 반드시 배열이 생성(공간할당)되어 있어야한다.
- __for-each문__
  - 배열이나 enumeration의 크기만큼 루프돌면서, 각 원소를 순차적으로 접근
  - `for (변수:배열레퍼런스) {//반복작업물}`
  - ex)
  ```java
int []n = {1,2,3,4,5};
int sum = 0;
for (int k : n) { sum+= k;}```
- __메소드에서 배열 리턴시 배열에 대한 레퍼런스를 리턴하는 것이다.__
  배열 자체를 리턴하는것 X

### 2차원 배열
![](https://images.velog.io/images/yesterdaykite/post/392541e6-937b-4061-a586-f9d1d630a392/image.png)
- 정방형 배열
  `int arr1[][]= new int[4][5];`
- 비정방형 배열
  ```
  int arr2[][] = new int[4][];
  int arr2[0] = new int[3];
  int arr2[1] = new int [2];
  ...
  ```

# exeption
- __compile time errror__ : 문법에 맞지않게 작성된 코드
- **run-time error** : 예측할 수 없고, 멈출 수 없는 경우
  - 무한 루프를 돌다가 스택 오버플로로 JVM 메모리가 부족할때까지 실행되는 등
  - 발생했을때, 시스템이나 사용자에게 해를 주거나 강제 실행종료하지 않으면 멈출 수 없다. (=Try-catch로 핸들링 불가능)
- **exception** : __실행 중 발생__한 오류
  - try-catch로 문제를 바로잡아(recoverable) 계속 실행되게 하거나, 시스템이나 사용자에게 해를 끼치지 않으며 정상적인 방법으로 종료 가능하도록 제어 가능
  - 자주있는 케이스
    - 정수를 0으로 나눔
    - 배열 인덱스 오류
    - 존재하지 않는 파일 읽으려고 시도
    - 정수 입력 기다리는데, 문자를 입력한 경우 등
 - 종료 과정
   1. 실행중 exeption 발생
   2. 자바 플랫폼이 가장 먼저 알게되어, 현재 실행중인 응용프로그램에게 예외 전달
   3. handling 코드가 없다면, 자바 플랫폼은 응용프로그래 곧바로 종료시킴

- 예시
![](https://images.velog.io/images/yesterdaykite/post/1145b9d1-f93a-4026-bd1b-28ed86e55cfe/image.png)


### try-catch-finally
```java
try {
	예외가 발생할 가능성 있는 실행문
    }
catch(처리할 예외 타입 선언){
	예외처리문
}
finally{
	예외 발생여부와 상관없이 무조건 실행되는 문장 (대부분 생략)
}
```
- 특징
  - 타입과 일치하는 catch블록이 없으면 프로그램 강제 종료
  - catch블록 내에 System.exit(0) 호출시, 언제든 프로그램 종료


- 예시1) 0으로 나눌때 발생하는 ArithmeticException
```java
import java.util.Scanner;

public class DivideByZeroHandling{
	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in);

		while(true)
		{
			System.out.print("나뉨수 입력 : ");
			int dividend = scanner.nextInt();
			System.out.print("나눔수 입력 : ");
			int divisor = scanner.nextInt();
			try{
				System.out.println(dividend+"를"+divisor+"로 나누면 몫은"+dividend/divisor + "입니다.");
				break; // 정상적 나누기 완료 후 while 벗어나기
			}
			catch(ArithmeticException e){ // ArithmeticException 예외 처리 코드
				System.out.println("0으로 나눌 수 없습니다. 다시 입력하세요.");
			}
		}
		scanner.close();
	}
}

```
