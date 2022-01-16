package Date;
import java.time.Month;
import  java.time.DayOfWeek;
import java.time.LocalDate;

public class Date implements Cloneable
{
    //인스턴스 필드멤버
    private int year;
    private Month month;
    private int day;
    private DayOfWeek dayOfWeek;
    //디폴트생성자
    public Date()
    {
        LocalDate localDate = LocalDate.now();
        this.year = localDate.getYear();
        this.month = localDate.getMonth();
        this.day = localDate.getDayOfMonth();
        this.dayOfWeek = localDate.getDayOfWeek();
    }
    //매개변수를 가지는 생성자
    public Date(int year, Month month, int day, DayOfWeek dayOfWeek)
    {
        this.year = year;
        this.month = month;
        this.day = day;
        this.dayOfWeek = dayOfWeek;
    }
    //문자열을 매개변수로 가지는 생성자
    public Date(String date)
    {
        LocalDate localDate = LocalDate.of(Integer.parseInt(date.substring(0,4)),
                Integer.parseInt(date.substring(4,6)),Integer.parseInt(date.substring(6,8)));
        this.year = localDate.getYear();
        this.month = localDate.getMonth();
        this.day = localDate.getDayOfMonth();
        this.dayOfWeek = localDate.getDayOfWeek();
    }
    //오늘 날짜 생성
    public static Date today()
    {
        LocalDate localDate = LocalDate.now();
        return new Date(localDate.getYear(), localDate.getMonth(),
                localDate.getDayOfMonth(), localDate.getDayOfWeek());
    }
    //어제 날짜 생성
    public static Date yesterday()
    {
        LocalDate yesterday = LocalDate.now().minusDays(1);
        return  new Date(yesterday.getYear(), yesterday.getMonth(),
                yesterday.getDayOfMonth(), yesterday.getDayOfWeek());
    }
    //내일 날짜 생성
    public static Date tommorow()
    {
        LocalDate tommorow = LocalDate.now().plusDays(1);
        return new Date(tommorow.getYear(), tommorow.getMonth(),
                tommorow.getDayOfMonth(), tommorow.getDayOfWeek());
    }
    //매개변수로 입력한 날짜만큼 이전 날짜 생성
    public static Date previousDate(int days)
    {
        LocalDate previousDate = LocalDate.now().minusDays(days);
        return new Date(previousDate.getYear(), previousDate.getMonth(),
                previousDate.getDayOfMonth(),  previousDate.getDayOfWeek());
    }
    //매개변수로 입력한 날짜만큼 이후 날짜 생성
    public static Date nextDate(int days)
    {
        LocalDate nextDate = LocalDate.now().plusDays(days);
        return new Date(nextDate.getYear(), nextDate.getMonth(),
                nextDate.getDayOfMonth(), nextDate.getDayOfWeek());
    }
    //Date끼리 더큰지 비교
    public boolean isGreaterThan(Date other)
    {
        boolean ret = false;
        if (this.year > other.year)
        {
            ret = true;
        }
	    else if (this.year == other.year && this.month.compareTo(other.month) > 0)
        {
            ret = true;
        }
	    else if (this.year == other.year && this.month == other.month && this.day > other.day)
        {
            ret = true;
        }
        return ret;
    }
    //Date끼리 더작은지 비교
    public boolean isLowerThan(Date other)
    {
        boolean ret = false;
        if (this.year < other.year)
        {
            ret = true;
        }
	    else if (this.year == other.year && this.month.compareTo(other.month) < 0)
        {
            ret = true;
        }
    	else if (this.year == other.year && this.month == other.month && this.day < other.day)
        {
            ret = true;
        }
        return ret;
    }
    //Object클래스의 equal메소드 재정의
    @Override
    public boolean equals(Object obj)
    {
        boolean ret = false;
        if(obj instanceof Date)
        {
            if (this.year == ((Date)obj).year && this.month == ((Date)obj).month
                    && this.day == ((Date)obj).day)
            {
                ret = true;
            }
        }
        return ret;
    }
    //테스트 출력용
    @Override
    public String toString()
    {
        return new String(this.year + "-" + this.month + "-" +
                this.day + "-" + this.dayOfWeek);
    }
    //clone
    @Override
    public Date clone() throws CloneNotSupportedException
    {
        return (Date)super.clone();
    }
    //getter
    public int getYear() {return this.year;}
    public Month getMonth() {return this.month;}
    public int getDay() {return this.day;}
    public DayOfWeek getDayOfWeek() {return this.dayOfWeek;}
}
