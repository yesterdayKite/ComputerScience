> [명품 JAVA Programming](https://book.naver.com/bookdb/book_detail.nhn?bid=13650995) 을 보고 정리한 글입니다.

# 패키지
**서로 관련있는 클래스나 인터페이스의 컴파일된 클래스(.class)파일들을 한 곳에 묶어 놓은 것**

### 패키지의 필요성
![](https://images.velog.io/images/yesterdaykite/post/42969ccb-f82e-4c0a-a6c3-95ff53767630/image.png)
- 3명의 개발자가 3개의 패키지를 각자 개발할 수 있다.
- 다음과같이 Tools.class 파일이 중복되어도, 패키지가 달라서 괜찮다.


### 주의
- .java소스파일이 컴파일되어 생기는 __.class클래스파일은 반드시 패키지에 소속되어야한다.__
  - 클래스가 소속될 패키지명은 소스파일 최상단에 `package 패키지명;` 로 선언한다하여 , '패키지명' 패키지에 저장할 것을 지시한다.
- 패키지 선언하지 않으면 __디폴트 패키지에 소속시킴__
  - 디폴트 패키지 = 현재 디렉터리
- 자바 JDK의 기본 패키지 = 자바API

# 컬렉션 collection
![](https://images.velog.io/images/yesterdaykite/post/1adab3f2-08f4-4ded-b8e3-43d6c2cc57cd/image.png)
배열이 가진 고정크기의 단점을 극복하기 위해
__객체들을 쉽게 삽입, 삭제, 검색할 수 있는 가변크기 컨테이너이다.__


### 특징
- generics 기법으로 만들어져있다.
  - `Vector<E>` 에서 `E` 대신 Integer와 같이 구체적 타입 지정 가능
  - 이런 `E` 를 일반화시킨 타입 혹은 generic type이라고 부른다.
- collection __요소는 객체들만 가능__하다.
  - int, char, double등 기본타입 불가능
  - Integer 등 Wrapper 클래스 객체를 사용해야함
  - 기본타입 값 삽입되면 auto boxing되긴 함.

# 제네릭 generic
**모든 종류의 타입을 다룰 수 있도록, 클래스나 메소드를 generic type을 이용하여 선언하는 기법**

### 제네릭으로 구현된 컬렉션 사용

예시)
```java
// 제네릭 스택 클래스
class Stack<E>{
 ...
 void push(E element){...}
 E pop() {...}
 ...
 }

 // 정수로 활용!
 Vector<Integer> v = new Vector<Integer>();
 void push(Integer element) {...}
 Integer pop() {...}

 // 문자열로 활용!
 Vector<String> v = new Vector<String>();
 void push(String element) {...}
 String pop() {...}

```

- 관례적으로 사용하는 문자 정리
  - E : element. 컬렉션 요소임을 나타냄
  - T : type
  - V : value
  - K : key


### 제네릭 클래스 만들기

- 제네릭 클래스 작성
클래스 이름 다음, generic type 매개변수를 <>에 추가함
```java
public class MyClass<T> {
	T val; // 변수 val의 타입은 T
    void set(T a) {
      val = a;
    }
    T get () {
      return val;
    }
}
```

- 제네릭 클래스에 대한 레퍼런스 변수 선언 & 구체화
```java
MyClass<String> s = new MyClass<String>(); // <T>를 String으로 구체화
List<Integer> li=new List<Integer>(); // <E>를 Integer로 구체화
```
__기본타입이 아닌, wrapper 타입만 가능함을 기억하자!!__

- 제너릭 타입 객체 생성은 불가능
```java
public class MyVector<E>{
  E create() {
    E a = new E(); // 컴파일 오류. 제너릭타입의 객체 생성 불가능
    return a;
  }
}
```

### 제네릭 장점
- 동적으로 타입 결정되지 않고, 컴파일시에 타입이 결정되므로 보다 안전한 프로그래밍 가능
- 런타임 타입 충돌 문제 방지
- 개발 시 타입 캐스팅 절차 불필요
- ClasscastException 방지
