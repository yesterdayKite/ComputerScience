> [명품 JAVA Programming](https://book.naver.com/bookdb/book_detail.nhn?bid=13650995) 을 보고 정리한 글입니다.

# 상속
```java
public class Person{...} // super class

public class Student extends Person{...} // 상속받음!
```


- 상속시 접근 범위
  - 서브 클래스는 슈퍼클래스의 private 멤버를 제외하고 모든 멤버에 접근할 수 있다.
  - private는 오직 현재 클래스의 멤버들에게만 접근 허용
  - 디폴트의 경우, 서브클래스라도 다른 패키지에 있다면 접근 불가능
  - protected의 경우, 같은 패키지에 속한 모든 클래스 OR 같은 패키지던 다른 패키지던 상속받는 서브클래스라면 접근 가능

|슈퍼 클래스 멤버에 접근하는 클래스 종류|private|default|protected|public|
|---|---|---|---|---|
|같은 패키지에 있는 서브 클래스|X|O|O|O|
|다른 패키지에 있는 서브 클래스|X|X|O|O|


- 상속의 특징
  - extends 다음에는 클래스 이름을 하나만 지정 가능 (다중상속 불가능)
  - 계층 구조의 최상위에 java.lang.Object클래스가 있다.

### 상속시의 생성자

- 서브클래스 객체가 생성될때, 슈퍼클래스의 생성자가 먼저 실행된 후 서브클래스의 생성자가 실행된다.
  ![](https://images.velog.io/images/yesterdaykite/post/382ee5f5-e361-469d-a13f-3dee4e1c3b39/image.png)

- __슈퍼클래스에 꼭 기본생성자가 명시되어야한다!!__
  ![](https://images.velog.io/images/yesterdaykite/post/ba53e70c-7169-4e86-8b62-6416fd37386d/image.png)
  슈퍼클래스 A에 기본생성자가 없어서 오류 발생
  `Implicit super constructor A() is undefined. Must explicitly invoke another constructor.`
  ![](https://images.velog.io/images/yesterdaykite/post/7ce38173-80a9-4b9b-9519-e8c3f25e6a96/image.png)
  이렇게 기본생성자 있어야한다.

- **super()를 이용하여 명시적으로 슈퍼클래스의 생성자 선택**
  - 반드시 생성자의 첫 라인에 사용되어야한다.
  - ![](https://images.velog.io/images/yesterdaykite/post/5a1fc758-05ec-4800-9dfa-c7eb68c8a46d/image.png)


# casting
- **업캐스팅**
  - 서브클래스의 객체에 대한 레퍼런스를, 슈퍼클래스 타입으로 변환하는 것
  - ```java
Person p;
Student s = new Student;
p = s; // 업캐스팅. 더 큰 단위에 작은 단위 넣기
p.grade = "A"; // 컴파일 오류. grade는 Person의 멤버가 아님.```
  - 없는 부분에 접근할 수 있어 위험하다
- **다운캐스팅**
  - `Student s = (Student)p; // 다운 캐스팅. `
  - 업캐스팅과 달리 () 안에 명시적으로 타입변환 표시해줘야한다.
- **instanceof 연산자**
  - `if (jee instanceof Student) {...}` 이런식으로 레퍼런스가 가리키는 객체가 어떤 클래스 타입인지 구분할 수 있다.
  - 클래스에만 적용되므로, `if (3 instanceof int)` 는 컴파일 오류

# overriding
> 슈퍼클래스와 서브클래스의 메소드 사이에 발생하는 관계로서,
__슈퍼클래스에 선언된 메소드와 같은이름, 같은 리턴타입, 같은 매개변수 리스트를 갖는 메소드를, !! 서브클레스!! 에서 재작성하는 것이다.__

호출시, 제일 자식에 있는 오버라이딩된 메소드가 실행된다.

![](https://images.velog.io/images/yesterdaykite/post/ae54be7f-5941-4420-871d-719be36707e2/image.png)
업캐스팅시에도, 동적바인딩 되어 제일 자식의 메소드를 호출한다.

__@Override__는 오버라이딩 메소드 앞에 붙이는 것으로, 컴파일러에게 오버라이딩이 정확한지 확인하도록 지시한다.

- 제약사항
  - 슈퍼클래스의 메소드와 동일한 원형으로 작헝해야함
  - 슈퍼클래스의 메소드의 접근지정자보다 접근의 범위를 좁여 오버라이딩 할 수 없다.
  - satic, private, final로 선언된 메소드는 서브클래스에서 오버라이딩할 수 없다.

- 동적바인딩
  - 실행할 메소드를 compile time이 아닌, run-time에 결정
  ![](https://images.velog.io/images/yesterdaykite/post/46328622-0e2f-431e-8971-84cd34ba1d39/image.png)
- 슈퍼클래스의 메소드를 사용하고 싶다면? __super__
  - `super.슈퍼클래스의 멤버` 처럼, 정적바인딩을 통해 슈퍼클래스의 멤버에 접근 가능
  - ``` java
name = "Circle";
super.name = "Shape" // shape클래스의 name에 기록
super.draw(); // shape 클래스의 draw() 호출. 정적바인딩```
  - 정리하자면, `this.객체내의_멤버` 와 `super.객체내_슈퍼클래스의_멤버` 이다.

### 정리
|비교 요소|메소드 오버로딩|메소드 오버라이딩|
|---|---|---|
|선언|같은 클래스나 상속관계에서 동일한 이름의 메소드 중복 작성|서브클래스에서 슈퍼클래스에 있는 메소드와 동일한 이름의 메소드 재작성|
|관계|동일한 클래스 내 혹은 상속 관계 | 상속 관계|
|조건|메소드 이름은 반드시 동일하되, 매개변수의 타입이나 갯수가 달라야 성립|메소드의 이름, 매개변수 타입과 갯수, 리턴타입이 모두 동일하여야 성립|
|바인딩|정적바인딩. 호출될 메소드는 컴파일시 결정|동적바인딩. 실행시간에 오버라이딩된 메소드 찾아 호출|


# Abstract
- **추상 메소드**
  - 선언은 되어있으나, 코드가 구현되어있지 않은 껍데기
  - `public abstract void setName(String s);`
  - `public abstract String fall() {return "bye";}` 는 코드가 작성되어있으므로, 컴파일 오류가 난다.
- **추상 클래스**
  - 종류
    - 추상 메소드를 포함하는 클래스
    (추상 메소드를 가지고 있으면 반드시 추상 클래스로 선언되어야한다!)
    - 추상 메소드는 없지만 abstract로 선언한 클래스
  - 추상 클래스는 객체(인스턴스) 생성 불가능
  - 추상클래스를 상속받으면 추상클래스가 됨
    ```java
    abstract class Shape { //추상 클래스
      public Shape() {}
      public void paint() {draw();}
      abstract public void draw(); // 추상메소드
    }
    abstract class Line extends Shape{ // 추상클래스를 상속받아 자식도 추상클래스가 된다.
      public String toString() {return "Line";
    }```
     - 자동으로 추상클래스가 되지만, abstract키워드를 사용하여 명시해주자
- abstract 사용 이유
  - 추상 메소드 통해 서브클래스가 구현할 메소드를 명료하게 알려주는 목차 역할을 함 (__개발자들은 서브클래스에서 추상클래스에 선언된 추상메소드는 모두 구현해야한다.__)
  -

![](https://images.velog.io/images/yesterdaykite/post/32d8d03e-91a8-4696-aa80-80e672d08adc/image.png) 원래라면 draw()를 오버라이딩하지 않아도 무관하나, abstract를 붙임으로서 반드시 상속받는 클래스에서 draw()를 오버라이딩해야한다.

- 예시코드
```java
public class GoodCalc extends Calculator {
	@Override
	public int add(int a, int b){ // 추상 메소드 구현
		return a+b;
	}
	@Override
	public double average(int[] a){ //추상 메소드 구현
		double sum = 0;
		for (int i = 0 ; i < a.length ; i++)	sum+=a[i];
		return sum/a.length;
	}

	public static void main(String[] args){
		GoodCalc c = new GoodCalc();
		System.out.println(c.add(2,3)); // 5
		System.out.println(c.average(new int [] {2,3,4})); // 3.0
	}
}
```

# 인터페이스
인터페이스 = 서로다른 하드웨어 장치들이 데이터를 주고받을 수 있는 규격
자바에선, `interface` 키워드를 사용하여 클래스 선언하듯이 선언한다.

- 특징
  - 상수와 추상 메소드만으로 구성되어있음
  - 지정하든 생력하든 상수는 모두 public static final 타입
  - 매소드는 모두 abstract public 타입(생략 가능)
  - 인터페이스는 new를 사용하여 객체를 생성할 수 없다
  - 다른 인터페이스에 상속될 수 있다.
  - 인터페이스 타입의 레퍼런스 변수는 선언 가능하다. (할당시키는 순간 오류가 날뿐)
  - **다중상속 허용**

- 예시
```java
interface MP3Interface{
  int MAXMUM_SIZE=5; // public static final 생략됨
  void play(); // 모든 메소드는 abstract public이며, 생략 가능
  void stop(); // abstract public 생략됨
  }
```

- 목적
  - 스펙을 줘서, 클래스들이 그 기능을 서로 다르게 구현할 수 있도록 하는 클래스의 규격선언 -> 다형성 실현
  - 다른 코드와의 연결 보장

- 복잡 예시
```java
 // 인터페이스 작성
interface PhoneInterface {
	int BUTTONS = 20;
	void sendCall();
	void receiveCall();
}

// 인터페이스 상속
interface MobilePhoneInterace extends PhoneInterface {
	void sendSMS();
	void receiveSMS();
}

// 인터페이스 작성
interface MP3Interface {
	public void play();
	public void stop();
}

class PDA {
	public int calculate(int x, int y){
		return x+1y;
	}
}

// SmartPhone 클래스는 PDA를 상속하고,
// MobilePhoneInterface와 MP3Interface 인터페이스에 선언된 메소드를 모두 구현한다.
// 상속돠 동시에 구현!
class SmartPhone extends PDA implements MobilePhoneInterace, MP3Interface{

	// MobilePhoneInterface의 추상 메소드 구현
	@Override
	public void sendCall(){
		System.out.println("전화걸기");
	}
	@Override
	public void receiveCall(){
		System.out.println("전화받기");
	}
	@Override
	public void sendSMS(){
		System.out.println("문자보내기");
	}
	@Override
	public void receiveSMS(){
		System.out.println("문자받기");
	}

	//MP3Interface의 추상메소드 구현
	@Override
	public void play(){
		System.out.println("음악재생");
	}
	@Override
	public void stop(){
		System.out.println("재생중지");
	}

	// 추가 작성 메소드 (고유 메소드)
	public void schedule(){
		System.out.println("일정관리");
	}
}


// 활용 예시
public class InterfaceEx{
	public static void main(String[] args){
		SmartPhone p = new SmartPhone();
		p.sendCall();
		p.play();
		System.out.println(p.calculate(3, 5));
		p.schedule();
	}
}
```


### 인터페이스와 추상 클래스의 비교

- 유사점
  - 객체 생성 불가능 (상속을 위한 슈퍼클래스로만 사용됨)
  - 클래스의 다형성을 실현하기 위한 목적

- 차이점

|비교|목적|구성|
|---|---|---|
|__추상클래스__|서브 클래스에서 필요로하는 대부분의 기능을 구현하여 두고, 서브클래스가 상속받아 활용할 수 있도록 하되, __구현할수밖에 없는 기능만을 추상메소드로 선언하여__ 서브클래스에서 구현하도록 강제하는 목적 (다형성)| 추상메소드와 일반메소드 모두 포함 , 상수,변수 필드 모두 포함 , 다중상속 불가능|
|**인터페이스**|객체의 기능을 모두 공개한 표준화 문서와 같은 것. 개발자에게 인터페이스 상속받는 클래스의 목적에 따라 인터페이스의 모든 추상 메소드를 만들도록하는 목적 (따형성) | **추상 메소드와 상수 필드만**, 다중상속 지원|

