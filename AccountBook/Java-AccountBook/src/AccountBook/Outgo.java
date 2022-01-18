package AccountBook;

public class Outgo extends Account
{
    //디폴트생성자
    public Outgo()
    {
        super();
    }
    //매개변수를 가지는 생성자
    public Outgo(Date date, String briefs, int amount, int balance, String remarks)
    {
        super(date, briefs, amount, balance, remarks);
    }
    //clone 오버라이딩
    @Override
    public Account clone()
    {
        Date date = new Date(this.date.getYear(), this.date.getMonth().getValue(),
                this.date.getDay());
        return new Outgo(date, this.briefs, this.amount, this.balance, this.remarks);
    }

    //잔액(balance) 계산하기 메소드 오버라이딩
    @Override
    public int calculateBalance(Account account)
    {
        return account.balance - this.amount;
    }
    @Override
    public int calculateBalance(int amount)
    {
        return this.balance + (this.amount + amount);
    }

    //setAmount 오버라이딩
    @Override
    public void setAmount(int amount)
    {
        this.amount = amount * (-1);
    }
}
