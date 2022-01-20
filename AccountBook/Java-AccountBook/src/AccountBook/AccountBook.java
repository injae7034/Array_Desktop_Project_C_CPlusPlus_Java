package AccountBook;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map;

public class AccountBook
{
    //인스턴스 필드 멤버
    private ArrayList<Account> accounts;
    private int length;

    //디폴트생성자
    public AccountBook()
    {
        this.accounts = new ArrayList<Account>();
        this.length = 0;
    }

    //record
    public int record(Date date, String briefs, int amount, String remarks)
    {
        //accountBook에 이전에 기입된 account가 있으면
        Account account = null;
        int balance = 0;
        if(this.length > 0)
        {
            //accountBook에서 가장 최근에 기입된 account를 구한다.
            account = this.accounts.get(this.length - 1);
            //balance(잔액)을 구한다.
            balance = account.getBalance();
        }
        //새로운 balance를 구한다.(누적)
        balance += amount;
        //금액(amount)이 양수이면
        if(amount >= 0)
        {
            account = new Income(date, briefs, amount, balance, remarks);
        }
        //금액(amount)이 음수이면
        else
        {
            account = new Outgo(date, briefs, amount * (-1), balance, remarks);
        }
        //ArrayList에 새로 생성한 account를 추가한다.
        int index = -1;
        boolean doesRecordingSucceed = this.accounts.add(account);
        //가계부(AccountBook)의 account개수를 증가시킨다.
        this.length++;
        //성공적으로 ArrayList에 account가 추가되었으면
        if(doesRecordingSucceed == true)
        {
            //새로 추가된 account의 위치를 구한다.
            index = this.accounts.indexOf(account);
        }
        //위치를 출력한다.
        return index;
    }

    //getAt
    public Account getAt(int index) {return this.accounts.get(index);}

    //Find(date)
    public ArrayList<Integer> find(Date date)
    {
        //date로 찾은 Account 객체들의 위치를 저장할 위치ArrayList 생성하기
        ArrayList<Integer> indexes = new ArrayList<>();
        //가계부(AccountBook)의 처음부터 끝까지 반복한다.
        for(int i = 0; i < this.length; i++)
        {
            //해당 위치의 Account 객체의 date가 찾고자 하는 date와 같으면
            if(date.equals(this.accounts.get(i).getDate()) == true)
            {
                //위치를 저장한다.
                indexes.add(i);
            }
        }
        //위치배열을 출력한다.
        return indexes;
    }
    //find(briefs)
    public ArrayList<Integer> find(String briefs)
    {
        //briefs로 찾은 Account 객체들의 위치를 저장할 위치ArrayList 생성하기
        ArrayList<Integer> indexes = new ArrayList<>();
        //가계부(AccountBook)의 처음부터 끝까지 반복한다.
        for(int i = 0; i < this.length; i++)
        {
            //해당 위치의 Account 객체의 briefs가 찾고자 하는 briefs와 같으면
            if(briefs.compareTo(this.accounts.get(i).getBriefs()) == 0)
            {
                //위치를 저장한다.
                indexes.add(i);
            }
        }
        //위치배열을 출력한다.
        return indexes;
    }
    //find(date, briefs)
    public ArrayList<Integer> find(Date date, String briefs)
    {
        //같은 date를 가진 Account 객체들의 위치배열을 받환받는다.
        ArrayList<Integer> sameDates = this.find(date);
        //같은 date를 가진 Account 객체들 중에서 같은 briefs를 가진
        //Account 객체들의 위치를 저장할 위치ArrayList 생성하기
        ArrayList<Integer> indexes = new ArrayList<>();
        //같은 date를 가진 Account 객체들의 위치배열 처음부터 끝까지 반복한다.
        for(int i = 0; i < sameDates.size(); i++)
        {
            //가계부에서 같은 date를 가진 Account 객체의 briefs가 찾고자 하는 briefs와 같으면
            if(briefs.compareTo(this.accounts.get(sameDates.get(i)).getBriefs()) == 0)
            {
                //위치를 저장한다.
                indexes.add(sameDates.get(i));
            }
        }
        //같은 date를 가진 Account 객체들 중에서 같은 briefs를 가진
        //Account 객체들의 위치배열을 반환한다.
        return indexes;
    }
    //find(date, date)
    public ArrayList<Integer> find(Date fromDate, Date toDate)
    {
        //Account 객체들 중에서 fromDate부터 toDate까지
        //Account 객체들의 위치를 저장할 위치ArrayList 생성하기
        ArrayList<Integer> indexes = new ArrayList<>();
        //같은 date들의 위치를 저장할 임시공간인 ArrayList 생성하기
        ArrayList<Integer> sameDates = null;
        //fromDate가 toDate보다 작거나 같은동안 반복한다.
        while(fromDate.isGreaterThan(toDate) == false)
        {
            //가계부(AccountBook)에서 fromDate와 같은 Account객체들의
            //위치를 찾아서 그 위치를 저장한 배열을 반환한다.
            sameDates = this.find(fromDate);
            //같은 dates의 위치를 저장한 배열의 처음부터 마지막까지 반복한다.
            for(int i = 0; i < sameDates.size(); i++)
            {
                //같은 dates의 위치를 저장한다.
                indexes.add(sameDates.get(i));
            }
            //fromDate를 1일 증가시켜준다.
            fromDate = Date.nextDate(fromDate, 1);
        }
        return indexes;
    }
    //find(date, date, briefs)
    public ArrayList<Integer> find(Date fromDate, Date toDate, String briefs)
    {
        //Account 객체들 중에서 fromDate부터 toDate까지 Account 객체들 중에서
        //같은 briefs를 가진 Account 객체들의 위치를 저장할 위치ArrayList 생성하기
        ArrayList<Integer> indexes = new ArrayList<>();
        //같은 date들의 위치를 저장할 임시공간인 ArrayList 생성하기
        ArrayList<Integer> sameDates = null;
        //fromDate가 toDate보다 작거나 같은동안 반복한다.
        while(fromDate.isGreaterThan(toDate) == false)
        {
            //가계부(AccountBook)에서 fromDate와 같은 date를 가진
            //Account객체들의 위치를 찾아서 그 위치를 저장한 배열을 반환한다.
            sameDates = this.find(fromDate);
            //같은 dates의 위치를 저장한 배열의 처음부터 마지막까지 반복한다.
            for(int i = 0; i < sameDates.size(); i++)
            {
                //가계부에서 같은 date를 가진 Account 객체의 briefs가 찾고자 하는 briefs와 같으면
                if(briefs.compareTo(this.accounts.get(sameDates.get(i)).getBriefs()) == 0)
                {
                    //위치를 저장한다.
                    indexes.add(sameDates.get(i));
                }
            }
            //fromDate를 1일 증가시켜준다.
            fromDate = Date.nextDate(fromDate, 1);
        }
        return indexes;
    }

    /*
    //correct(다형성을 적용하여 오버라이딩 메소드 만들지 않을 경우)
    public int correct(int index, int amount, String remarks)
    {
        //매개변수로 입력 받은 위치의 Account객체를 구한다.
        Account account = this.accounts.get(index);
        int balance = 0;//잔액을 저장할 임시공간
        //account가 수입(Income)이면
        if(account instanceof Income)
        {
            //balance를 구한다.
            balance = account.getBalance() + (amount - account.getAmount());
        }
        //account가 지출(Outgo)이면
        else
        {
            //balance를 구한다.
            balance = account.getBalance() + (account.getAmount() + amount);
        }
        //Account객체의 금액(amount)을 변경해준다.
        account.setAmount(amount);
        //Account객체의 잔액(balance)을 변경해준다.
        account.setBalance(balance);
        //Account객체의 비고(remarks)를 변경해준다.
        account.setRemarks(remarks);
        //Account객체의 잔액이 수정되었기 때문에 수정된 Account객체
        //이후의 Account객체들의 잔액들도 모두 수정해줘야함.
        //수정된 Account객체 이후부터 가계부의 마지막 Account객체까지 반복한다.
        Account afterAccount = null;
        for(int i = index + 1; i < this.length; i++)
        {
            //잔액을 수정한 Account객체를 구한다.
            account = this.accounts.get(i - 1);
            //잔액을 수정한 Account객체의 다음 Account객체를 구한다.
            afterAccount = this.accounts.get(i);
            //afterAccount가 수입(Income)이면
            if(afterAccount instanceof Income)
            {
                //수정할 잔액을 구한다.
                balance = account.getBalance() + afterAccount.getAmount();
            }
            //afterAccount가 지출(Outgo)이면
            else
            {
                //수정할 잔액을 구한다.
                balance = account.getBalance() - afterAccount.getAmount();
            }
            //잔액을 수정한 Account객체의 다음 Account객체의 잔액을 수정한다.
            afterAccount.setBalance(balance);
        }
        return index;
    }
     */

/*
    //correct
    public int correct(int index, int amount, String remarks)
    {
        //매개변수로 입력 받은 위치의 Account객체를 구한다.
        Account account = this.accounts.get(index);
        //변경할 금액을(amount) 바탕으로 변경될 잔액을 구한다.
        int balance = account.calculateBalance(amount);
        //Account객체의 금액(amount)을 변경해준다.
        account.setAmount(amount);
        //Account객체의 잔액(balance)을 변경해준다.
        account.setBalance(balance);
        //Account객체의 비고(remarks)를 변경해준다.
        account.setRemarks(remarks);
        //Account객체의 잔액이 수정되었기 때문에 수정된 Account객체
        //이후의 Account객체들의 잔액들도 모두 수정해줘야함.
        //수정된 Account객체 이후부터 가계부의 마지막 Account객체까지 반복한다.
        for(int i = index + 1; i < this.length; i++)
        {
            //잔액을 수정한 Account객체의 다음 Account객체를 구한다.
            account = this.accounts.get(i);
            //수정할 잔액을 구한다.
            balance = account.calculateBalance(this.accounts.get(i - 1));
            //잔액을 수정한다.
            account.setBalance(balance);
        }
        return index;
    }
 */
/*
    //correct(비고만 바꿨을 때 금액과 잔액을 바꾸지 않도록 방지)
    public int correct(int index, int amount, String remarks)
    {
        //매개변수로 입력 받은 위치의 Account객체를 구한다.
        Account account = this.accounts.get(index);
        //매개변수로 입력 받은 remarks로 Account객체의 remarks를 변경해준다.
        account.setRemarks(remarks);
        //금액의 변경이 있으면
        if(amount != account.getAmount())
        {
            //변경할 금액을(amount) 바탕으로 변경될 잔액을 구한다.
            int balance = account.calculateBalance(amount);
            //Account객체의 금액(amount)을 변경해준다.
            account.setAmount(amount);
            //Account객체의 잔액(balance)을 변경해준다.
            account.setBalance(balance);

            //Account객체의 잔액이 수정되었기 때문에 수정된 Account객체
            //이후의 Account객체들의 잔액들도 모두 수정해줘야함.
            //수정된 Account객체 이후부터 가계부의 마지막 Account객체까지 반복한다.
            for(int i = index + 1; i < this.length; i++)
            {
                //잔액을 수정한 Account객체의 다음 Account객체를 구한다.
                account = this.accounts.get(i);
                //수정할 잔액을 구한다.
                balance = account.calculateBalance(this.accounts.get(i - 1));
                //잔액을 수정한다.
                account.setBalance(balance);
            }
        }
        return index;
    }
 */
    //correct 메소드 오버로딩
    public int correct(int index, int amount)
    {
        //매개변수로 입력 받은 위치의 Account객체를 구한다.
        Account account = this.accounts.get(index);
        //변경할 금액을(amount) 바탕으로 변경될 잔액을 구한다.
        int balance = account.calculateBalance(amount);
        //Account객체의 금액(amount)을 변경해준다.
        account.setAmount(amount);
        //Account객체의 잔액(balance)을 변경해준다.
        account.setBalance(balance);

        //Account객체의 잔액이 수정되었기 때문에 수정된 Account객체
        //이후의 Account객체들의 잔액들도 모두 수정해줘야함.
        //수정된 Account객체 이후부터 가계부의 마지막 Account객체까지 반복한다.
        for(int i = index + 1; i < this.length; i++)
        {
            //잔액을 수정한 Account객체의 다음 Account객체를 구한다.
            account = this.accounts.get(i);
            //수정할 잔액을 구한다.
            balance = account.calculateBalance(this.accounts.get(i - 1));
            //잔액을 수정한다.
            account.setBalance(balance);
        }
        return index;
    }
    public int correct(int index, String remarks)
    {
        //매개변수로 입력 받은 위치의 Account객체를 구한다.
        Account account = this.accounts.get(index);
        //매개변수로 입력 받은 remarks로 Account객체의 remarks를 변경해준다.
        account.setRemarks(remarks);
        return index;
    }
    //correct
    public int correct(int index, int amount, String remarks)
    {
        //매개변수로 입력 받은 위치의 Account객체를 구한다.
        Account account = this.accounts.get(index);
        //변경할 금액을(amount) 바탕으로 변경될 잔액을 구한다.
        int balance = account.calculateBalance(amount);
        //Account객체의 금액(amount)을 변경해준다.
        account.setAmount(amount);
        //Account객체의 잔액(balance)을 변경해준다.
        account.setBalance(balance);
        //Account객체의 비고(remarks)를 변경해준다.
        account.setRemarks(remarks);
        //Account객체의 잔액이 수정되었기 때문에 수정된 Account객체
        //이후의 Account객체들의 잔액들도 모두 수정해줘야함.
        //수정된 Account객체 이후부터 가계부의 마지막 Account객체까지 반복한다.
        for(int i = index + 1; i < this.length; i++)
        {
            //잔액을 수정한 Account객체의 다음 Account객체를 구한다.
            account = this.accounts.get(i);
            //수정할 잔액을 구한다.
            balance = account.calculateBalance(this.accounts.get(i - 1));
            //잔액을 수정한다.
            account.setBalance(balance);
        }
        return index;
    }

    //Calculate
    public Map<String, Integer> calculate(Date fromDate, Date toDate)
    {
        //반환할 해쉬맵을 생성한다.
        Map<String, Integer> totalOutcomes = new LinkedHashMap<>();
        //같은 date들의 위치를 저장할 임시공간인 ArrayList 생성하기
        ArrayList<Integer> sameDates = null;
        int totalIncome = 0;//총수입을 저장할 공간
        int totalOutgo = 0;//총지출을 저장할 공간
        Account account = null;//Account객체를 담을 임시공간
        //fromDate가 toDate보다 작거나 같은동안 반복한다.
        while(fromDate.isGreaterThan(toDate) == false)
        {
            //가계부(AccountBook)에서 fromDate와 같은 date를 가진
            //Account객체들의 위치를 찾아서 그 위치를 저장한 배열을 반환한다.
            sameDates = this.find(fromDate);
            //같은 dates의 위치를 저장한 배열의 처음부터 마지막까지 반복한다.
            for(int i = 0; i < sameDates.size(); i++)
            {
                //account를 구한다.
                account = this.getAt(sameDates.get(i));
                //account가 수입(Income)이면
                if(account instanceof Income)
                {
                    totalIncome += account.getAmount();
                }
                //account가 지출(Outgo)이면
                else
                {
                    totalOutgo += account.getAmount();
                }
            }
            //fromDate를 1일 증가시켜준다.
            fromDate = Date.nextDate(fromDate, 1);
        }
        //총잔액(totalBalance)을 구한다.
        int totalBalance = totalIncome - totalOutgo;
        //해쉬맵에 결과를 저장한다.
        totalOutcomes.put("totalIncome", totalIncome);
        totalOutcomes.put("totalOutgo", totalOutgo);
        totalOutcomes.put("totalBalance", totalBalance);
        //해쉬맵을 반환한다.
        return totalOutcomes;
    }

    //printAllAccounts
    public int printAllAccounts()
    {
        for(Account account : this.accounts)
        {
            System.out.println(account);
        }
        return this.length;
    }

    //getLength
    public int getLength() {return this.length;}
}
