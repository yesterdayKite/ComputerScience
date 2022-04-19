> [명품 JAVA Programming](https://book.naver.com/bookdb/book_detail.nhn?bid=13650995) 을 보고 정리한 글입니다.

# 캡슐화
- 클래스 = 틀
  - 객체(instance) = 틀에 찍어낸 실체
- 필드 = 멤버변수
- 메소드 = 멤버함수


# 상속 inherit
- 부모클래스 = super class
- 자식클래스 = sub class

![](https://images.velog.io/images/yesterdaykite/post/eace317c-ad1e-45bf-bf64-f4834959a53b/image.png)

# 다형성 polymorphism
**같은 이름의 메소드가 클래스 혹은 객체에 따르게 동작하도록 구현되는 것 **
- **오버라이딩 Overriding**
  - 슈퍼클래스에 구현된 메소드를 서브 클래스에서 동일한 이름으로 자신의 특징에 맞도록 다시 구현
- **오버로딩 Overloading **
  - 클래스 내에서 이름이 같지만, 서로 다르게 동작하는 메소드를 여러개 만듬


# 클래스 구성과 인스턴스 생성
![](https://images.velog.io/images/yesterdaykite/post/59644e72-fe38-4b92-9d72-b1920d62ccc2/image.png)
![](https://images.velog.io/images/yesterdaykite/post/7795a17d-080f-4283-bbdc-d3dd87ec104a/image.png)
- 주의
  - 객체를 가리키는 __레퍼런스 변수 선언__과 new를 통해 __객체를 생성__하는것은 다른 일이다. (`Circle pizza; <-> pizza = new Circle();`)

- 예시 코드
```java
public class Circle{ // 클래스
	int radius; // 필드
	Stirng name; // 필드

	public Circle(){} // 생성자

	public double getArea() // 메소드
	{return 3.14*radius*radius;}
}

public static void main(String[] args){
	Circle pizza = new Circle();
	pizza.radius = 10;
	pizza.name = "yona pizza";
	double area = pizza.getArea();
	System.out.println(pizza.name+"의 면적은"+area);
}
```


### 객체 치환
**=연산자로 객체를 치환하면 어떻게 될까**
레퍼런스 변수가 가리키는 대상이 달라지게 되는거임
아무 레퍼런스 변수가 가리키지 않는 객체가 생길 수 있고, 이를 garbage라고 부름 (JVM에 의해 자동 수거 됨)
![](https://images.velog.io/images/yesterdaykite/post/7094ad46-6247-4a61-9726-822b05de2006/image.png)


### 객체 배열
```java
Circle[] c = new Circle[5]; // 레퍼런스 배열 생성

// 오류) Circle [5] c; // 컴파일 오류

for (int i = 0 ; i < c.length ; i++)
	c[i] = new ㅊircle(i); // 배열의 각 원소 객체 생성
```
![](https://images.velog.io/images/yesterdaykite/post/44f211a9-1d97-4e34-882d-2cfb92bc7e56/image.png)

### 객체의 소멸
new에 의해 생성된 객체 공간을 JVM에게 돌려주어 가용메모리에 포함시키는 것
Object 클래스의 finalize()가 소멸자와 유사한 기능을 하긴 하지만,
사용되지 않는 객체는 garbage가 되어,  garbage collcetor가 적절한 시점에 자동 수집하여 가용메모리에 반환시킨다.

![](https://images.velog.io/images/yesterdaykite/post/e3401c1e-fe9e-4b46-bcb4-77bcd4270e9e/image.png)

**가비지 컬렉션 강제 요청**
`System.gc();` 메소드 사용시 '요청'은 할 수있다.
하지만 즉시 작동하는 것은 아니라, 자바 플랫폼이 판단했을때 적절한 시점에 작동시킨다.


## 생성자
- 주의사항
  - 생성자는 __new를 통해 한번만 호출__
  - 생성자에 리턴 타입 지정할 수 없다.
    `public void Circle() {....} // 오류. void타입도 리턴할 수 없다.`
  - 생성자내에 return문은 사용 가능
- 기본생성자 (default constructor)
  - 생성자가 하나도 없으면, 컴파일러는 기본생성자를 자동으로 생성 (사용자의 눈에 보이지 않게 삽입됨)
  - 매개변수와 실행코드가 없어 아무일도 하지 않음

## this
__객체 자신에 대한 레퍼런스이다.__
- 매개변수와 필드의 구분
`public Circle(int radius){this.radius = radius;}`
- 객체 자신의 레퍼런스 리턴
`public Circle getMe() {return this;}`


## this()
__클래스 내에서, 생성자가 다른 생성자를 호출할때 사용__
예시코드
```java
public class Book{
	String title;
	String author;

	void show() {System.out.println(title + " " + autor);}

	public Book(){
		this("", ""); // this() 호출!!
		System.out.println("생성자 호출됨");
	}
	public Book(String title){
		this(title, "작자미상"); // this() 호출!!
	}
	public Book(String title, String author){
		this.title = title;
		this.author = author;
	}

	public static void main(String[] args)
	{
		Book littlePrince = new Book("어린왕자", "생텍쥐페리");
		Book loveStory = new Book("춘향전");
		Book emptyBook = new Book();

	}
}
```

- this 사용시 주의사항
  - 반드시 _생성자 코드 내에서만 호출 가능_
  - 반드시 _같은 클래스 내_ 다른 생성자 호출 시 사용
  - 반드시 _생성자의 첫 문장이 되어야함_.


## 메소드
- 매개변수 전달시
  - 기본타입 값 전달시
    - 값이 매개변수에 복사되어 전달됨 (call-by-value)
  - 객체 전달시
    - 객체의 레퍼런스 값 전달
    - 객체가 통체로 복사되지 X
    ![](https://images.velog.io/images/yesterdaykite/post/f37f6a2d-1461-4b5a-85e9-09c29b68e0f9/image.png)

  - 배열 전달시
    - 배열의 레퍼런스 전달

### 메소드 오버로딩
**한 클래스 내에, 이름이 같지만 매개변수의 타입이나 갯수가 다른 여러개의 메소드 중복 작성하는것**
- 조건
  - 메소드 이름이 동일하여야
  - 메소드의 개수나 타입이 서로 달라야
  - 리턴타입, 접근지정자는 관계 없다

# 접근 지정자
private, protected, public , default 4가지가 있다.
default=packege-private 라고도 한다.

**클래스의 경우**
public : 패키지에 상관없이 다른 어떤 클래스에게도 사용 허용
default : _같은 패키지 내의 클래스들에게만_ 사용 하용

**필드(멤버변수)의 경우**

|멤버에 접근하는 클래스|private|default|protected|public|
|---|---|---|---|---|
|같은 패키지의 클래스|X|O|O|O|
|다른 패키지의 클래스|X|X|X|O|
|접근 가능 영역|클래스 내|동일 패키지 내|동일 패키지와 자식 클래스|모든 클래스|
|같은 패키지에 있는 서브 클래스|X|O|O|O|
|다른 패키지에 있는 서브 클래스|X|X|O|O|


# static
![](https://images.velog.io/images/yesterdaykite/post/0c1b510b-ef8e-4315-93bb-36db09d73255/image.png)

|.|non-static 멤버|static 멤버|
|---|---|---|
|선언|`int n; void g(){}` | `static int m; static void g(){}`|
|공간적 특성|멤버는 객체마다 존재(인스턴스 멤버라고도 부름)|멤버는 클래스당 하나 생성. 멤버는 객체 내부가 아닌 별도의 공간(클래스 코드가 적제되는 메모리)에 생성됨. (클래스 멤버라고도 부름)|
|시간적 특성|객체와 생명주기를 가이 한다| 클래스 로딩시 생성 / 객체가 생기기도전에 이미 생성되어있음 / 따라서 객체가 생기기 전에도 사용 가능 / 객체가 사라져도 멤버는 사라지지 않음 / 프로그램이 종료될때 사라진다|
|공유의 특성|공유되지 않음(객체 내에 각각 공간 유지)|동일한 클래스의 모든 객체들에 의해 공유됨|

- 접근방식
  - <객체.static멤버>로 접근
  - <클래스명.static멤버>로 접근

- 활용 케이스
  - 전역변수와 전역함수 역할
  - 공유변수를 만들고 싶을때

- 제약조건
  - static 메소드는 static 멤버만 접근할 수 있다.
    ```java
    static int m;
    static void s1(int x) {n=x;} // 컴파일오류
    // static 메소드는 non-static 필드 사용 불가
    static void s2(int x) {f1(3);} // 컴파일 오류
    // static 메소드는 non-static 메소드 사용 불가

    static void s3(int x) {m = x;} // 정상. static이 static 사용
    static void s4(int x) {s3(3);} // 정상.static이 static 사용```
  - static 메소드는 this 를 사용할 수 없다.
    객체없이도 존재하기 때문

# Final
**final class**
상속받을 수 없는 클래스
`final class FinalClass{...} // 이 클래스는 상속 불가!`
**final method **
상속받을 수 없는 메소드
`protected final int finalMethod(){...} // 자식이 오버라이딩이 불가능한 메소드이다! `
**final 필드**
한번 초기화 되면 값을 변경할 수 없는 상수가 된다.
`pulbic static final double PI = 3.14;`

