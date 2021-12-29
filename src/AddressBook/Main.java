package AddressBook;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public  class Main
{
    public static void main(String[] args) throws IOException
    {
        //메인테스트 시나리오
        //1. AddressBook객체를 생성한다.
        AddressBook addressBook = new AddressBook();
        //2. 외부파일이 있으면 외부파일에 있는 Personal 객체정보를 load한다.
        addressBook.load();
        //3. 메뉴화면을 출력한다.
        displayMenu();
        //4. 콘솔창에서 menu 번호를 입력을 받는다.
        Scanner scanner = new Scanner(System.in);
        int menuNumber = scanner.nextInt();
        //5. 입력한 menu 번호로 이동한다.
        while (menuNumber != 0)
        {
            switch (menuNumber)
            {
                case 1: formFoRecording(addressBook); break;
                case 2: formFoFinding(addressBook); break;
                case 3: formFoCorrecting(addressBook); break;
                case 4: formFoErasing(addressBook); break;
                case 5: formFoArranging(addressBook); break;
                case 6: formFoViewingAll(addressBook); break;
                default: break;
            }
            displayMenu();
            menuNumber = scanner.nextInt();
        }
        addressBook.save();
    }

    public static void displayMenu()
    {
        System.out.printf("\t주소록\n");
        System.out.printf("\t====================\n");
        System.out.printf("\t[1] 기재하기\n");
        System.out.printf("\t[2] 찾    기\n");
        System.out.printf("\t[3] 고 치 기\n");
        System.out.printf("\t[4] 지 우 기\n");
        System.out.printf("\t[5] 정리하기\n");
        System.out.printf("\t[6] 전체보기\n");
        System.out.printf("\t[0] 끝 내 기\n");
        System.out.printf("\t--------------------\n");
        System.out.printf("\t메뉴를 선택하십시오! ");
    }
    //[1] 기재하기
    public static void formFoRecording(AddressBook addressBook) throws IOException
    {
        Scanner scanner = new Scanner(System.in);
        String going = "Y";
        while (going.equals("Y") == true || going.equals("y") == true)
        {
            System.out.println();
            System.out.printf("\t주소록 - 기재하기\n");
            System.out.printf("\t==============================================\n");
            System.out.printf("\t성    명 : ");
            String name = scanner.nextLine();
            System.out.printf("\t주    소 : ");
            String address = scanner.nextLine();
            System.out.printf("\t전화 번호 : ");
            String telephoneNumber = scanner.nextLine();
            System.out.printf("\t이메일주소 : ");
            String emailAddress = scanner.nextLine();
            System.out.printf("\t----------------------------------------------\n");
            System.out.printf("\t기재하시겠습니까?(Y/N) ");
            String recording = scanner.nextLine();
            if (recording.equals("Y") == true || recording.equals("y") == true)
            {
                int index = addressBook.record(name, address, telephoneNumber, emailAddress);
                System.out.printf("\t========================================================================\n");
                System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
                System.out.printf("\t------------------------------------------------------------------------\n");
                System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index+1,
                        addressBook.getPersonals().get(index).getName(),
                        addressBook.getPersonals().get(index).getAddress(),
                        addressBook.getPersonals().get(index).getTelephoneNumber(),
                        addressBook.getPersonals().get(index).getEmailAddress());
            }
            System.out.printf("\t============================================================================\n");
            System.out.printf("\t계속하시겠습니까?(Y/N) ");
            going = scanner.nextLine();
        }
    }
    //[2] 찾기
    public static void formFoFinding(AddressBook addressBook)
    {
        Scanner scanner = new Scanner(System.in);
        int index = 0;
        String going = "Y";
        while (going.equals("Y") == true || going.equals("y") == true)
        {
            System.out.println();
            System.out.printf("\t주소록 - 찾기\n");
            System.out.printf("\t================================================================================\n");
            System.out.printf("\t성명 : ");
            String name = scanner.nextLine();
            System.out.printf("\t================================================================================\n");
            System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
            System.out.printf("\t--------------------------------------------------------------------------------\n");
            ArrayList<Integer> indexes = addressBook.find(name);
            index = 0;
            while (index < indexes.size())
            {
                System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index + 1,
                        addressBook.getPersonals().get(indexes.get(index)).getName(),
                        addressBook.getPersonals().get(indexes.get(index)).getAddress(),
                        addressBook.getPersonals().get(indexes.get(index)).getTelephoneNumber(),
                        addressBook.getPersonals().get(indexes.get(index)).getEmailAddress());
                index++;
            }
            System.out.printf("\t================================================================================\n");
            System.out.printf("\t계속하시겠습니까?(Y/N) ");
            going = scanner.nextLine();
        }
    }
    //[3] 고치기
    public static void formFoCorrecting(AddressBook addressBook)
    {
        Scanner scanner = new Scanner(System.in);
        int index = 0;
        String going = "Y";
        while (going.equals("Y") == true || going.equals("y") == true)
        {
            System.out.println();
            System.out.printf("\t주소록 - 고치기\n");
            System.out.printf("\t====================================================================================\n");
            System.out.printf("\t성명 : ");
            String name = scanner.nextLine();
            System.out.printf("\t=====================================================================================\n");
            System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
            System.out.printf("\t------------------------------------------------------------------------------------\n");
            ArrayList<Integer> indexes = addressBook.find(name);
            index = 0;
            while (index < indexes.size())
            {
                System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index + 1,
                        addressBook.getPersonals().get(indexes.get(index)).getName(),
                        addressBook.getPersonals().get(indexes.get(index)).getAddress(),
                        addressBook.getPersonals().get(indexes.get(index)).getTelephoneNumber(),
                        addressBook.getPersonals().get(indexes.get(index)).getEmailAddress());
                index++;
            }
            //찾은 게 있으면
            if (indexes.size() > 0)
            {
                System.out.printf("\t================================================================================\n");
                System.out.printf("\t번호 : ");
                //nextInt대신에 nextLine을 써야 뒤에서 탈이 안남.
                String stringIndex = scanner.nextLine();
                index = Integer.valueOf(stringIndex);
                System.out.printf("\t--------------------------------------------------------------------------------\n");
                System.out.println("\t변경할 사항만 입력하시고, 변경하지 않는 사항은 Enter키를 입력해주세요.");
                System.out.printf("\t--------------------------------------------------------------------------------\n");
                index = index - 1;//배열첨자는 실제입력받은 숫자보다 1이 작기때문에
                System.out.printf("\t주      소 : %s ",
                        addressBook.getPersonals().get(indexes.get(index)).getAddress());
                String address = scanner.nextLine();
                if (address.equals("") == true)
                {
                    address = addressBook.getPersonals().get(indexes.get(index)).getAddress();
                }
                System.out.printf("\t전화  번호 : %s ",
                        addressBook.getPersonals().get(indexes.get(index)).getTelephoneNumber());
                String telephoneNumber = scanner.nextLine();
                if (telephoneNumber.equals("") == true)
                {
                    telephoneNumber = addressBook.getPersonals().get(indexes.get(index)).getTelephoneNumber();
                }
                System.out.printf("\t이메일주소 : %s ",
                        addressBook.getPersonals().get(indexes.get(index)).getEmailAddress());
                String emailAddress = scanner.nextLine();
                if (emailAddress.equals("") == true)
                {
                    emailAddress = addressBook.getPersonals().get(indexes.get(index)).getEmailAddress();
                }
                System.out.printf("\t---------------------------------------------------------------------------------\n");
                System.out.printf("\t고치시겠습니까?(Y/N) ");
                String correcting = scanner.nextLine();
                if (correcting.equals("Y") == true || correcting.equals("y") == true)
                {
                    index = addressBook.correct(indexes.get(index), address, telephoneNumber, emailAddress);
                    System.out.printf("\t==============================================================================\n");
                    System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
                    System.out.printf("\t------------------------------------------------------------------------------\n");
                    System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index + 1,
                            addressBook.getPersonals().get(index).getName(),
                            addressBook.getPersonals().get(index).getAddress(),
                            addressBook.getPersonals().get(index).getTelephoneNumber(),
                            addressBook.getPersonals().get(index).getEmailAddress());
                }
            }
            System.out.printf("\t======================================================================================\n");
            System.out.printf("\t계속하시겠습니까?(Y/N) ");
            going = scanner.nextLine();
        }
    }
    //[4] 지우기
    public static void formFoErasing(AddressBook addressBook)
    {
        Scanner scanner = new Scanner(System.in);
        int index = 0;
        String going = "Y";
        while (going.equals("Y") == true || going.equals("y") == true)
        {
            System.out.println();
            System.out.printf("\t주소록 - 지우기\n");
            System.out.printf("\t====================================================================================\n");
            System.out.printf("\t성명 : ");
            String name = scanner.nextLine();
            System.out.printf("\t=====================================================================================\n");
            System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
            System.out.printf("\t------------------------------------------------------------------------------------\n");
            ArrayList<Integer> indexes = addressBook.find(name);
            index = 0;
            while (index < indexes.size())
            {
                System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index + 1,
                        addressBook.getPersonals().get(indexes.get(index)).getName(),
                        addressBook.getPersonals().get(indexes.get(index)).getAddress(),
                        addressBook.getPersonals().get(indexes.get(index)).getTelephoneNumber(),
                        addressBook.getPersonals().get(indexes.get(index)).getEmailAddress());
                index++;
            }
            if (indexes.size() > 0)
            {
                System.out.printf("\t================================================================================\n");
                System.out.printf("\t번호 : ");
                //nextInt대신에 nextLine을 써야 뒤에서 탈이 안남.
                String stringIndex = scanner.nextLine();
                index = Integer.valueOf(stringIndex);
                System.out.printf("\t--------------------------------------------------------------------------------\n");
                index = index - 1;
                System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
                System.out.printf("\t------------------------------------------------------------------------------\n");
                System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index + 1,
                        addressBook.getPersonals().get(indexes.get(index)).getName(),
                        addressBook.getPersonals().get(indexes.get(index)).getAddress(),
                        addressBook.getPersonals().get(indexes.get(index)).getTelephoneNumber(),
                        addressBook.getPersonals().get(indexes.get(index)).getEmailAddress());
                System.out.printf("\t================================================================================\n");
                System.out.printf("\t지우시겠습니까?(Y/N) ");
                String erasing = scanner.nextLine();
                if (erasing.equals("Y") == true || erasing.equals("y") == true)
                {
                    index = addressBook.erase(indexes.get(index));
                    System.out.printf("\t--------------------------------------------------------------------------------\n");
                    System.out.printf("\t지워졌습니다.\n");
                }
            }
            System.out.printf("\t================================================================================\n");
            System.out.printf("\t계속하시겠습니까?(Y/N) ");
            going = scanner.nextLine();
        }
    }
    //[5] 정리하기
    public static void formFoArranging(AddressBook addressBook)
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println();
        System.out.printf("\t주소록 - 정리하기\n");
        System.out.printf("\t================================================================================\n");
        System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
        System.out.printf("\t--------------------------------------------------------------------------------\n");

        addressBook.arrange();
        int i = 0;
        int index = 0;
        while (index < addressBook.getPersonals().size())
        {
            i = 1;
            while (i <= 5 && index < addressBook.getPersonals().size())
            {
                System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index+1,
                        addressBook.getPersonals().get(index).getName(),
                        addressBook.getPersonals().get(index).getAddress(),
                        addressBook.getPersonals().get(index).getTelephoneNumber(),
                        addressBook.getPersonals().get(index).getEmailAddress());
                index++;
                i++;
            }
            System.out.printf("\t================================================================================\n");
            System.out.printf("\t아무 키나 누르세요!");
            scanner.nextLine();
        }
    }
    //[6] 전체보기
    public static void formFoViewingAll(AddressBook addressBook)
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println();
        System.out.printf("\t주소록 - 전체보기\n");
        System.out.printf("\t================================================================================\n");
        System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
        System.out.printf("\t--------------------------------------------------------------------------------\n");
        int i = 0;
        int index = 0;
        while (index < addressBook.getPersonals().size())
        {
            i = 1;
            while (i <= 5 && index<addressBook.getPersonals().size())
            {
                System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index+1,
                        addressBook.getPersonals().get(index).getName(),
                        addressBook.getPersonals().get(index).getAddress(),
                        addressBook.getPersonals().get(index).getTelephoneNumber(),
                        addressBook.getPersonals().get(index).getEmailAddress());
                index++;
                i++;
            }
            System.out.printf("\t================================================================================\n");
            System.out.printf("\t아무 키나 누르세요!");
            scanner.nextLine();
        }
    }
}



/*
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
        System.out.printf("2. 주소록에 Record한 내용 GetAt : " ).println
                (originalAddressBook.getAt(index));
        //3. 고길동, 서울시 성동구, 029575976, Go@naver.com 을 기재한다.
        index = originalAddressBook.record("고길동", "서울시 성동구",
                "029575976", "Go@naver.com");
        System.out.printf("3. 주소록에 Record한 내용 GetAt : " ).println
                (originalAddressBook.getAt(index));
        //4. 홍길동, 인천시 연수구, 0313267926, Hong@gmail.com 을 기재한다.
        index = originalAddressBook.record("홍길동", "인천시 연수구",
                "0313267926", " Hong@gmail.com");
        System.out.printf("4. 주소록에 Record한 내용 GetAt : " ).println
                (originalAddressBook.getAt(index));
        //5. 최길동, 서울시 용산구, 023517134, Choi@를 기재한다.
        index = originalAddressBook.record("최길동", "서울시 용산구",
                "023517134", "Choi@naver.com");
        System.out.printf("5. 주소록에 Record한 내용 GetAt : " ).println
                (originalAddressBook.getAt(index));
        //6. 정길동, 서울시 종로구, 024366751, Jung@를 기재한다.
        index = originalAddressBook.record("정길동", "서울시 종로구",
                "024366751", "Jung@naver.com");
        System.out.printf("6. 주소록에 Record한 내용 GetAt : " ).println
                (originalAddressBook.getAt(index));
        //7. 나길동, 서울시 강서구, 0215749903, Na@naver.com 을 기재한다.
        index = originalAddressBook.record("나길동", "서울시 강서구",
                "0215749903", "Na@naver.com");
        System.out.printf("7. 주소록에 Record한 내용 GetAt : " ).println
                (originalAddressBook.getAt(index));
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
        ArrayList<Integer> indexes = copyAddressBook.find("홍길동");
        index = 0;
        Personal personal = null;
        if(indexes.isEmpty() == false)
        {
            while(index < indexes.size())
            {
                personal = copyAddressBook.getAt(indexes.get(index));
                System.out.printf(" 13.%d %s, %s, %s, %s\n", index+1, personal.getName(), personal.getAddress(),
                        personal.getTelephoneNumber(), personal.getEmailAddress());
                index++;
            }
        }
        //14. 복사본에서 이름(홍길동)으로 찾은 내용 중 1번째 홍길동을 지우고,
        //지운 것을 확인하기 위해 전체 복사본 출력
        System.out.printf("\n");
        System.out.printf("14. 복사본에서 이름(홍길동)으로 찾은 내용 중 1번째 홍길동을 지우고" +
                "지운 것을 확인하기 위해 전체 복사본 출력\n");
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
                System.out.printf("  14.3.%d %s, %s, %s, %s\n", index + 1, personal.getName(), personal.getAddress(),
                        personal.getTelephoneNumber(), personal.getEmailAddress());
                index++;
            }
        }
        //15. 복사본 내용을 지운 후 원본 내용도 지워졌는지 확인하기 위해 원본 내용도 출력하기
        System.out.printf("\n");
        System.out.println("15. 복사본 내용을 지운 후 원본 내용도 지워졌는지 확인하기 위해 원본 내용도 출력하기 : ");
        System.out.println(" 15.1 복사본에서 홍길동을 지운 후 원본에 있는 내용 개수 : "
                + originalAddressBook.getPersonals().size());
        index = 0;
        while(index < originalAddressBook.getPersonals().size())
        {
            personal = originalAddressBook.getAt(index);
            System.out.printf(" 15.2.%d %s, %s, %s, %s\n", index + 1, personal.getName(), personal.getAddress(),
                    personal.getTelephoneNumber(), personal.getEmailAddress());
            index++;
        }
        //16. 복사본에서 고길동을 찾아서 고길동의 주소와 전화번호 변경하고,
        //변경사항 확인하기 위해 전체 복사본 출력
        System.out.printf("\n");
        System.out.printf("16. 복사본에서 고길동을 찾아서 고길동의 주소와 전화번호 변경하고 " +
                "변경사항 확인하기 위해 전체 복사본 출력\n");
        indexes = copyAddressBook.find("고길동");
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
*/