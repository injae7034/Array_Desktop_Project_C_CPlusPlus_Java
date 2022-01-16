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
    public Date(int year, int month, int day)
    {
        this.year = year;
        this.month = Month.of(month);
        this.day = day;
        this.dayOfWeek = LocalDate.of(year, month, day).getDayOfWeek();
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
        return new Date(localDate.getYear(), localDate.getMonth().getValue(),
                localDate.getDayOfMonth());
    }
    //어제 날짜 생성
    public static Date yesterday()
    {
        LocalDate yesterday = LocalDate.now().minusDays(1);
        return  new Date(yesterday.getYear(), yesterday.getMonth().getValue(),
                yesterday.getDayOfMonth());
    }
    //내일 날짜 생성
    public static Date tomorrow()
    {
        LocalDate tomorrow = LocalDate.now().plusDays(1);
        return new Date(tomorrow.getYear(), tomorrow.getMonth().getValue(),
                tomorrow.getDayOfMonth());
    }
    //오늘 날짜기준으로 매개변수로 입력한 날짜만큼 이전 날짜 생성
    public static Date previousDate(int days)
    {
        LocalDate previousDate = LocalDate.now().minusDays(days);
        return new Date(previousDate.getYear(), previousDate.getMonth().getValue(),
                previousDate.getDayOfMonth());
    }
    //오늘 날짜기준으로 매개변수로 입력한 날짜만큼 이후 날짜 생성
    public static Date nextDate(int days)
    {
        LocalDate nextDate = LocalDate.now().plusDays(days);
        return new Date(nextDate.getYear(), nextDate.getMonth().getValue(),
                nextDate.getDayOfMonth());
    }
    //매개변수로 입력받은 Date를 매개변수로 입력한 날짜만큼 이전 날짜 생성
    public static Date previousDate(Date date, int days)
    {
        LocalDate previousDate = LocalDate.of(date.getYear(),
                date.getMonth().getValue(), date.getDay()).minusDays(days);
        return new Date(previousDate.getYear(), previousDate.getMonth().getValue(),
                previousDate.getDayOfMonth());
    }
    //매개변수로 입력받은 Date를 매개변수로 입력한 날짜만큼 이후 날짜 생성
    public static Date nextDate(Date date, int days)
    {
        LocalDate nextDate = LocalDate.of(date.getYear(),
                date.getMonth().getValue(), date.getDay()).plusDays(days);
        return new Date(nextDate.getYear(), nextDate.getMonth().getValue(),
                nextDate.getDayOfMonth());
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
        //Month 자료형을 정수형으로 바꿔줌
        int month = this.month.getValue();
        String stringMonth;
        //month가 한 자리수이면
        if(month<10)
        {
            //앞에 0을 붙여줌
            stringMonth = new String("0" + month);
        }
        else
        {
            stringMonth = Integer.toString(month);
        }
        String stringDay;
        //day가 한자리 수이면
        if(this.day < 10)
        {
            //앞에 0을 붙여줌
            stringDay = new String("0" + this.day);
        }
        else
        {
            stringDay = Integer.toString(this.day);
        }
        return new String(this.year + "-" + stringMonth + "-" +
                stringDay + "-" + this.dayOfWeek);
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
