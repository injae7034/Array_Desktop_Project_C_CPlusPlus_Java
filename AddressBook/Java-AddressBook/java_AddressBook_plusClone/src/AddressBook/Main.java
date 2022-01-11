package AddressBook;

import java.util.ArrayList;

public class Main
{

    public static void main(String[] args) throws CloneNotSupportedException
    {

        System.out.println("Personal 메인테스트");
        //1. 기본생성자 호출
        Personal original = new Personal();
        System.out.printf("1. 기본생성자 호출: ").println(original);
        //2. 매개변수를 가지는 생성자 호출
        original = new Personal("홍길동", "서울시 서초구",
                "022345678", "Hong@naver.com");
        System.out.printf("2. 매개변수생성자 호출: ").println(original);
        //3. 복사생성자 호출
        Personal copyFromConstructor = new Personal(original);
        System.out.printf("3. 복사생성자 호출: ").println(copyFromConstructor);
        //4. 서로 다른지 확인
        boolean answer = original.isNotEqual(copyFromConstructor);
        System.out.printf("4. 복사본과 서로 다른지 확인: %s\n", answer);
        //5. clone 호출
        Personal copyFromClone = original.clone();
        System.out.printf("5. clone 호출: ").println(copyFromClone);
        //6. 서로 같은지 확인
        answer = original.isEqual(copyFromClone);
        System.out.printf("6. 복사본과 서로 같은지 확인: %s\n", answer);
        //7. 원본 내용 변경 후 복사생성자로 생성한 copy와 clone으로 생성한 copy의 내용이 바뀌는지 확인
        System.out.println("7. 원본 내용 변경 후 복사생성자로 생성한 copy와" +
                " clone으로 생성한 copy의 내용이 바뀌는지 확인");
        original.setAddress("서울시 중구");
        original.setTelephoneNumber("029998888");
        original.setEmailAddress("Hong@gmail.com");
        System.out.printf("7.1 원본내용: ").println(original);
        System.out.printf("7.2 복사생성자 복사본내용: ").println(copyFromConstructor);
        System.out.printf("7.3 clone 복사본 내용: ").println(copyFromClone);



        System.out.println();
        System.out.println("AddressBook 메인테스트");
        //1. AddressBook 기본생성자 호출
        AddressBook originalAddressBook = new AddressBook();
        System.out.println("1. AddressBook 기본생성자 호출 : " + originalAddressBook.getPersonals());
        //2. 주소록에 홍길동, 서울시 중구, 021766710, Hong@naver.com 을 기재한다.
        int index = originalAddressBook.record("홍길동", "서울시 중구",
                "021766710", "Hong@naver.com");
        Personal personal = originalAddressBook.getAt(index);
        System.out.printf("2. 주소록에 Record한 내용 GetAt : ").println(personal);
        //3. 고길동, 서울시 성동구, 029575976, Go@naver.com 을 기재한다.
        index = originalAddressBook.record("고길동", "서울시 성동구",
                "029575976", "Go@naver.com");
        personal = originalAddressBook.getAt(index);
        System.out.printf("3. 주소록에 Record한 내용 GetAt : ").println(personal);
        //4. 홍길동, 인천시 연수구, 0313267926, Hong@gmail.com 을 기재한다.
        index = originalAddressBook.record("홍길동", "인천시 연수구",
                "0313267926", " Hong@gmail.com");
        personal = originalAddressBook.getAt(index);
        System.out.printf("4. 주소록에 Record한 내용 GetAt : ").println(personal);
        //5. 최길동, 서울시 용산구, 023517134, Choi@를 기재한다.
        index = originalAddressBook.record("최길동", "서울시 용산구",
                "023517134", "Choi@naver.com");
        personal = originalAddressBook.getAt(index);
        System.out.printf("5. 주소록에 Record한 내용 GetAt : ").println(personal);
        //6. 정길동, 서울시 종로구, 024366751, Jung@를 기재한다.
        index = originalAddressBook.record("정길동", "서울시 종로구",
                "024366751", "Jung@naver.com");
        personal = originalAddressBook.getAt(index);
        System.out.printf("6. 주소록에 Record한 내용 GetAt : ").println(personal);
        //7. 나길동, 서울시 강서구, 0215749903, Na@naver.com 을 다시 기재한다.
        index = originalAddressBook.record("나길동", "서울시 강서구",
                "0215749903", "Na@naver.com");
        personal = originalAddressBook.getAt(index);
        System.out.printf("7. 주소록에 Record한 내용 GetAt : ").println(personal);
        //8. 원본 내용 출력하기
        System.out.printf("\n");
        System.out.printf("8. 원본 내용 출력하기 : \n");
        originalAddressBook.printAddressBook(8);
        //9. 복사생성자를 이용한 복사본 출력하기
        //AddressBook copyAddressBook = new AddressBook(originalAddressBook);
        AddressBook copyAddressBook = originalAddressBook.clone();
        System.out.printf("\n");
        System.out.printf("9. 복사생성자를 이용한 복사본 출력하기 : \n");
        copyAddressBook.printAddressBook(9);

        // 원본과 복사본의 주소값비교
        System.out.println();
        System.out.println("원본과 복사본의 주소값비교");
        boolean flag = originalAddressBook.equals(copyAddressBook);
        System.out.println(flag);

        //10. 이름을 기준으로 복사본을 오름차순 정렬하기
        System.out.printf("\n");
        System.out.println("10. 이름을 기준으로 복사본을 오름차순 정렬하기 : 복사본 정렬됨");
        copyAddressBook.arrange();
        copyAddressBook.printAddressBook(10);
        //11. 복사본 정렬한 후에 원본 출력하기
        System.out.printf("\n");
        System.out.println("11. 복사본 정렬한 후에 원본 출력하기 : 원본 정렬안됨");
       originalAddressBook.printAddressBook(11);
        //12. 나중에 복사본과 원본을 비교할 때 바뀐 사항을 쉽게 확인하기 위해 원본도 정렬하기
        System.out.printf("\n");
        System.out.println("12. 나중에 복사본과 원본을 비교할 때 바뀐 사항을 쉽게 확인하기 위해 원본도 정렬함 : ");
        originalAddressBook.arrange();
        originalAddressBook.printAddressBook(12);
        //13. 복사본의 내용을 변경하기 위해 복사본에서 변경할 배열요소를 이름(홍길동)으로 찾기
        System.out.printf("\n");
        System.out.println("13. 복사본의 내용을 변경하기 위해 복사본에서" +
                " 변경할 배열요소를 이름(홍길동)으로 찾기 : ");
        //int [] indexes = copyAddressBook.find("홍길동");
        ArrayList<Integer> indexes = copyAddressBook.find("홍길동");
        //Integer indexesCount = 0;
        //int [] indexes = copyAddressBook.find("홍길동", indexesCount);
        //int[] indexes = null;
        //int count = copyAddressBook.find("홍길동", indexes);
        /*
        index = 0;
        if(indexes != null)
        {
            while(index < count)
            {
                personal = copyAddressBook.getAt(indexes[index]);
                System.out.printf(" 13.%d %s, %s, %s, %s\n", index+1, personal.getName(), personal.getAddress(),
                        personal.getTelephoneNumber(), personal.getEmailAddress());
                index++;
            }
        }
        */
        //while(indexes != null &&  index < indexes.length)
        index = 0;
        if(indexes.isEmpty() == false)
        {
            while(index < indexes.size())
            {
                personal = copyAddressBook.getAt(indexes.get(index));
                System.out.printf(" 13.%d ", index + 1).println(personal);
                index++;
            }
        }
        //14. 복사본에서 이름(홍길동)으로 찾은 내용 중 1번째 홍길동을 지우고,
        //지운 것을 확인하기 위해 전체 복사본 출력
        System.out.printf("\n");
        System.out.printf("14. 복사본에서 이름(홍길동)으로 찾은 내용 중 1번째 홍길동을 지우고" +
                "지운 것을 확인하기 위해 전체 복사본 출력\n");
        //index = copyAddressBook.erase(indexes[0]);
        index = copyAddressBook.erase(indexes.get(0));
        if(index == -1)
        {
            System.out.printf(" 14.1 첫번째 홍길동이 지워졌습니다.\n");
            System.out.println(" 14.2 홍길동을 지운 후 복사본에 있는 내용 개수 : "
                    + copyAddressBook.getPersonals().size());
            System.out.println(" 14.3 복사본에 저장된 전체 Personal 출력 : " );
            index = 0;
            while(index < copyAddressBook.getPersonals().size())
            {
                personal = copyAddressBook.getAt(index);
                System.out.printf("  14.3.%d ", index + 1).println(personal);
                index++;
            }
        }
        //15. 복사본 내용을 지운 후 원본 내용도 지워졌는지 확인하기 위해 원본 내용도 출력하기
        System.out.printf("\n");
        System.out.println("15. 복사본 내용을 지운 후 원본 내용도 지워졌는지 확인하기 위해 원본 내용도 출력하기 : ");
        System.out.println(" 15.1 복사본에서 홍길동을 지운 후 원본에 있는 내용 개수 : "
                + originalAddressBook.getPersonals().size());
        originalAddressBook.printAddressBook(15);
        //16. 복사본에서 고길동을 찾아서 고길동의 주소와 전화번호 변경하고,
        //변경사항 확인하기 위해 전체 복사본 출력
        System.out.printf("\n");
        System.out.printf("16. 복사본에서 고길동을 찾아서 고길동의 주소와 전화번호 변경하고 " +
                "변경사항 확인하기 위해 전체 복사본 출력\n");
        //indexes = copyAddressBook.find("고길동", indexesCount);
        //count = copyAddressBook.find("고길동", indexes);
        indexes = copyAddressBook.find("고길동");
        //Personal oldPersonal = copyAddressBook.correct(indexes.get(0), "서울시 도봉구",
        //        "021119999", copyAddressBook.getAt(indexes.get(0)).getEmailAddress());

        //변경 전 Personal과 변경 후 Personal 비교
        //System.out.println();
        //System.out.println("변경 전 Personal과 변경 후 Personal 비교");
        //flag = copyAddressBook.getAt(indexes.get(0)).equals(oldPersonal);
        //System.out.println(flag);
        //System.out.printf("\n");
        //index = copyAddressBook.correct(indexes[0], "서울시 도봉구",
        //        "021119999", copyAddressBook.getAt(indexes[0]).getEmailAddress());
        index = copyAddressBook.correct(indexes.get(0), "서울시 도봉구",
                "021119999", copyAddressBook.getAt(indexes.get(0)).getEmailAddress());
       copyAddressBook.printAddressBook(16);
        //17. 복사본 내용 변경 후 원본 내용도 변경됬는지 확인하기 위해 원본 내용도 출력하기
        System.out.printf("\n");
        System.out.println("17. 복사본 내용 변경 후 원본 내용도 변경됬는지 확인하기 위해 원본 내용도 출력하기 : ");
       originalAddressBook.printAddressBook(17);
        //18. 원본과 복사본의 주소값비교
        System.out.println();
        System.out.println("18. 원본과 복사본의 주소값비교");
        flag = originalAddressBook.equals(copyAddressBook);
        System.out.println(flag);
    }
}
