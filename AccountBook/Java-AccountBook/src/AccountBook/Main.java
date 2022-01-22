package AccountBook;

import java.util.ArrayList;
import java.util.Map;

public class Main
{
    public static void main(String[] args)
    {
        //가계부를 만든다.
        AccountBook accountBook = new AccountBook();
        //1. 수입을 기재한다.
        int index = accountBook.record(new Date("20211125"), "월급",
                2370000, "회사");
        System.out.print("1. 수입 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //2. 지출을 기재한다.
        index = accountBook.record(new Date(2021, 11, 25), "식사",
                -9000, "혼자");
        System.out.print("2. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //3. 지출을 기재한다.
        index = accountBook.record(new Date("20211125"), "식사",
                -12000, "친구");
        System.out.print("3. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //4. 지하철을 기재한다.
        index = accountBook.record(new Date("20211125"), "교통비",
                -55000, "지하철");
        System.out.print("4. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //5. 지출을 기재한다.
        index = accountBook.record(new Date("20211126"), "회식",
                -30000, "친구");
        System.out.print("5. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //6. 수입을 기재한다.
        index = accountBook.record(new Date("20211126"), "캐쉬백",
                7500, "체크카드");
        System.out.print("6. 수입 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //7. 지출을 기재한다.
        index = accountBook.record(new Date("20211127"), "통신비",
                -58000, "핸드폰");
        System.out.print("7. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //8. 지출을 기재한다.
        index = accountBook.record(new Date("20211128"), "쇼핑",
                -49000, "신발");
        System.out.print("8. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //9. 수입을 기재한다.
        index = accountBook.record(new Date("20211129"), "중고판매",
                23000, "신발");
        System.out.print("9. 수입 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //10. 지출을 기재한다.
        index = accountBook.record(new Date("20211129"), "식사",
                -11000, "혼자");
        System.out.print("10. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //11. 지출을 기재한다.
        index = accountBook.record(new Date("20211130"), "식사",
                -13500, "동생");
        System.out.print("11. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //12. 지출을 기재한다.
        index = accountBook.record(new Date("20211130"), "식사",
                -6000, "혼자");
        System.out.print("12. 지출 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //13. 수입을 기재한다.
        index = accountBook.record(new Date("20211130"), "중고판매", 33000, "후라이팬");
        System.out.print("13. 수입 기재 -> ");
        System.out.println(accountBook.getAt(index));
        //14. 날짜로 찾는다.
        System.out.println("14. 날짜로 찾기 : ");
        ArrayList<Integer> indexes = accountBook.find(new Date("20211125"));
        for(int i = 0; i < indexes.size(); i++)
        {
            System.out.println(accountBook.getAt(indexes.get(i)));
        }
        //15. 11/25 날짜로 찾은 것 중에 4번째의 교통비의 금액(amount)을 수정한다.
        System.out.println("15. 금액(amount) 수정 : ");
        //교통비 amount 수정 전에 뒤에 객체들 출력해서 balance 확인하기
        System.out.println("15.1 금액(amount)을 수정하기 전에 이후 객체 전체 출력 : ");
        for(int i = indexes.get(3); i < accountBook.getLength(); i++)
        {
            System.out.println(accountBook.getAt(i));
        }
        index = accountBook.correct(indexes.get(3), -65000);
        System.out.println("15.2 11/25 날짜로 찾은 것 중에 4번째의 교통비의 금액(amount)을 수정 : ");
        System.out.println(accountBook.getAt(index));
        System.out.println("15.3 금액 수정 후에 뒤에 위치한 Account 객체들의 잔액 바뀌는지 확인 : ");
        for(int i = indexes.get(3); i < accountBook.getLength(); i++)
        {
            System.out.println(accountBook.getAt(i));
        }
        //16. 적요("월급")로 찾는다.
        System.out.println("16. 적요로 찾기 : ");
        indexes = accountBook.find("월급");
        for(int i = 0; i < indexes.size(); i++)
        {
            System.out.println(accountBook.getAt(indexes.get(i)));
        }
        //17. 적요("월급")로 찾은 것 중에서 금액(amount)과 비고를 수정한다.
        System.out.println("17. 금액(amount)과 비고(remarks) 수정 : ");
        //교통비 amount 수정 전에 뒤에 객체들 출력해서 balance 확인하기
        System.out.println("17.1 금액(amount)과 비고(remarks) 수정하기 전에 이후 객체 전체 출력 : ");
        for(int i = indexes.get(0); i < accountBook.getLength(); i++)
        {
            System.out.println(accountBook.getAt(i));
        }
        index = accountBook.correct(indexes.get(0), 2400000, "퇴직금");
        System.out.println("17.2 월급 금액(amount)과 비고(remarks) 수정 : ");
        System.out.println(accountBook.getAt(index));
        System.out.println("17.3 월급 금액과 비고 수정 후에 뒤에 위치한 Account 객체들의 잔액 바뀌는지 확인 : ");
        for(int i = indexes.get(0); i < accountBook.getLength(); i++)
        {
            System.out.println(accountBook.getAt(i));
        }
        //18. 날짜(20211125)와 적요(식사)로 찾는다.
        System.out.println("18. 날짜(20211125)와 적요(식사)로 찾기 : ");
        indexes = accountBook.find(new Date(2021, 11, 25), "식사");
        for(int i = 0; i < indexes.size(); i++)
        {
            System.out.println(accountBook.getAt(indexes.get(i)));
        }
        //19. 기간(20211127-20211130)으로 찾는다.
        System.out.println("19. 기간(20211127-20211130)으로 찾기 : ");
        indexes = accountBook.find(new Date("20211127"), new Date("20211130"));
        for(int i = 0; i < indexes.size(); i++)
        {
            System.out.println(accountBook.getAt(indexes.get(i)));
        }
        //20. 기간(20211127-20211130)에서 적요(중고판매)로 찾는다.
        System.out.println("20. 기간(20211127-20211130)에서 적요(중고판매)로 찾기 : ");
        indexes = accountBook.find(new Date(2021, 11, 27),
                new Date(2021, 11, 30), "중고판매");
        for(int i = 0; i < indexes.size(); i++)
        {
            System.out.println(accountBook.getAt(indexes.get(i)));
        }
        //21. 전체기간동안 가계부를 계산한다.
        System.out.print("21. 전체기간동안 가계부 계산하기 : ");
        Map<String, Integer> totalOutcomes = accountBook.calculate(new Date("20211125"),
                new Date(2021, 11, 30));
        System.out.println(totalOutcomes);
        //22. 총수입을 구해서 출력한다.
        System.out.println("22. 총수입 : " + totalOutcomes.get("totalIncome"));
        //23. 총지출을 구해서 출력한다.
        System.out.println("23. 총지출 : " + totalOutcomes.get("totalOutgo"));
        //24. 총잔액을 구해서 출력한다.
        System.out.println("24. 총잔액 : " + totalOutcomes.get("totalBalance"));
        //25. 비고만 수정하기
        index = accountBook.correct(indexes.get(0), "퇴직금");
        System.out.print("25. 비고만 수정하기 : ");
        System.out.println(accountBook.getAt(index));
        //26. 가계부 전체를 출력한다.
        System.out.println("26. 가계부 전체 출력하기 : ");
        accountBook.printAllAccounts();
    }
}
