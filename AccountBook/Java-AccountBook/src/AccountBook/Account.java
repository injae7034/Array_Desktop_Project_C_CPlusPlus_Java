package AccountBook;

import java.text.NumberFormat;
import java.util.Currency;
import java.util.Locale;

public abstract class Account
{
    //인스턴스 필드 멤버
    protected Date date;
    protected String briefs;
    protected int amount;
    protected int balance;
    protected String remarks;

    //디폴트 생성자
    public Account()
    {
        this.date = new Date();
        this.briefs = "";
        this.amount = 0;
        this.balance = 0;
        this.remarks = "";
    }

    //매개변수를 가지는 생성자
    public Account(Date date, String briefs, int amount, int balance, String remarks)
    {
        this.date = date;
        this.briefs = briefs;
        this.amount = amount;
        this.balance = balance;
        this.remarks = remarks;
    }

    //equals 오버라이딩
    @Override
    public boolean equals(Object obj)
    {
        boolean ret = false;
        if(obj instanceof Account)
        {
            if(this.date.equals(((Account)obj).date) == true &&
                    this.briefs.compareTo(((Account)obj).briefs) == 0
                    && this.amount == ((Account)obj).amount &&
                    this.balance == ((Account)obj).balance &&
                    this.remarks.compareTo(((Account)obj).remarks) == 0)
            {
                ret = true;
            }
        }
        return ret;
    }

    //toString 오버라이딩
    @Override
    public String toString()
    {
        //통화에 원화표시를 해주고, 세자리수마다 콤마(,)를 찍어줌.
        String amount = NumberFormat.getCurrencyInstance(Locale.KOREA).format(this.amount);
        String balance = NumberFormat.getCurrencyInstance(Locale.KOREA).format(this.balance);
        return new String("일자 : " + this.date.toString() + ", 적요 : "
                + this.briefs + ", 금액 : " + amount + ", 잔액 : "
                + balance + ", 비고 : " + this.remarks);
    }

    //추상메소드 clone(자손인 Income이나 Outgo에서 구현함)
    public abstract Account clone();

    //잔액(balance) 계산하기 메소드
    public abstract int calculateBalance(Account account);
    public abstract int calculateBalance(int amount);

    //getter
    public Date getDate() {return this.date;}
    public String getBriefs() {return this.briefs;}
    public int getAmount() {return this.amount;}
    public int getBalance() {return this.balance;}
    public String getRemarks() {return this.remarks;}

    //setter
    //추상메소드 setAmount(자손인 Income이나 Outgo에서 구현함)
    public abstract void setAmount(int amount);
    public void setBalance(int balance)
    {
        this.balance = balance;
    }
}
