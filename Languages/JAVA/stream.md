> [참고 블로그](https://futurecreator.github.io/2018/08/26/java-8-streams/)를 보고 정리한 글입니다.

### 정리계기

```java
        List<TodoEntity> list = this.service.searchAll();
        List<TodoResponse> response = list.stream().map(TodoResponse::new)
                                                    .collect(Collectors.toList());// response로 변환해주기
```
스프링 예제를 따라하다가 stream이 멍미 하고 정리

---
- java 8 이전
  - 컬렉션 인스턴스 다룰때 for, foreach돌면서 하나씩 꺼내 다뤄야함 (=비효율)
- stream 등장
  - '데이터의 흐름'
  - **배열 혹은 컬렉션 인스턴스에 함수 여러개 조합해서, 원하는 결과 필터링하고 결과 얻을 수 있음**
  - 병렬처리(multi-threading)가 가능

- 스트림 활용 절차
  - 1. 생성하기 (스트림 인스턴스 생성)
  - 2. 가공하기 (filtering 혹은 mapping하여 원하는 결과 만드는 중간작업(intermediate operation))
  - 3. 결과 만들기 (최종적으로 결과 만드는 작업(terminal operation))

- 예시
  - 배열 스트림 : `Arrays.stream()` 메소드 사용
  ```java
String[] arr = new String[]{"a", "b", "c"};
    Stream<String> stream = Arrays.stream(arr);
    Stream<String> streamOfArrayPart = Arrays.stream(arr, 1, 3); // 1~2요소. [b,c]
    ```

  - 컬렉션 스트림 : 컬렉션 인터페이스의 디폴트 메소드 `stream()` 사용
  ```java
public interface Collection<E> extends Iterable<E> {
  default Stream<E> stream(spliterator(), false);
  }
}
....
List<String> list = Arrays.asList("a", "b", "c");
Stream<String> stream = list.stream();
Stream<String> parallelStream = list.parallelStream(); // 병렬처리 스트림
```


  - 비어있는 스트림
   ...


 와 오바다 이거 외울수도 없고 다 칠수도 없고
 기억안날때 참고 블로그 들어가자..!


[참고 블로그](https://futurecreator.github.io/2018/08/26/java-8-streams/)
