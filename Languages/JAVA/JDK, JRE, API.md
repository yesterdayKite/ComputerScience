> [명품 JAVA Programming](https://book.naver.com/bookdb/book_detail.nhn?bid=13650995) 을 보고 정리한 글입니다.

### JDK와 JRE
- JDK
  - Java Development Kit
  - 자바 개발자에게 배포
  - compiler, JRE, class library, sample source 등
- JRE
  - Java Runtime Kit
  - 자바 실행시 필요한 키트
  - 일반 사용자도 사용


### JDK 디렉터리 구조

- jdk 1.8.0_131
  - bin : 자바 개발, 실행하는데 필요한 도구와 유틸리티
  - db : 자바로 DB응용프로그램을 개발하는데 필요한 도구
  - include : 네이티브 코드 프로그래밍에 필요한 헤더 파일
  - jre : 자바 런타임 환경. JVM, 클래스 라이브러리등 실행에 필요한 파일
    - bin
    - lib
  - lib : JDK의 기본 라이브러리 외 추가 클래스 라이브러리와 개발 도구에서 필요로하는 여러 파일
  - javafx-src : javafx 샘플 소스
  - src : 자바 API클래스들에 대한 자바 소스


### Java API
- package
  - 자바에서 클래스 파일들을 서로 관련된 것 끼리 묶어놓은 것
- 자바 API
  - 주요 기능들을 미리 작성하고 컴파일하여 클래스 파일들로 묶어둔 패키지들
  - JDK에 포함되어 제공된다.
  - 개발자는 java API를 통해 쉽고 빠르게 개발 가능
