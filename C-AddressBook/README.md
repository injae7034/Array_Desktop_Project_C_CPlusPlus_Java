# C-AddressBook
C언어로 주소록 프로그램 구현했습니다.<br><br>
자료구조는 배열을 사용하였고, AddressBook이라는 구조체와 Personal 구조체를 정의하였습니다.<br><br>
Personal이 레코드이고 name, address, telephoneNumber, emailAddress를 필드로 가집니다.<br><br>
그리고 AddressBook이 파일인데 Personal 자료형의 구조체들을 배열로 관리합니다.<br><br>
관리하는 함수로는 Record(기재하기), Find(이름으로 찾기), Correct(수정하기), Erase(지우기), Arrange(이름을 기준으로 오름차순으로 정렬하기)가 있습니다.<br><br>
콘솔을 이용한 CUI프로그램을 구현하였고, WIN32API를 이용한 GUI프로그램이 구현하였습니다.<br><br>
그리고 load/save 함수를 통해 외부 파일에 입출력하여 불러오고, 저장합니다.<br><br> 
