package AddressBook;

public class Personal implements Cloneable
{
    //디폴트 생성자
    public Personal()
    {
        this.name = "";
        this.address = "";
        this.telephoneNumber = "";
        this.emailAddress = "";
    }
    //매개변수를 가지는 생성자
    public Personal(String name, String address, String telephoneNumber, String emailAddress)
    {
        this.name = name;
        this.address = address;
        this.telephoneNumber = telephoneNumber;
        this.emailAddress = emailAddress;
    }
    //복사생성자
    public Personal(Personal source)
    {
        this.name = source.name;
        this.address = source.address;
        this.telephoneNumber = source.telephoneNumber;
        this.emailAddress = source.emailAddress;
    }
    //같은 Personal 객체인지 확인하기
    public boolean isEqual(Personal other)
    {
        boolean ret = false;
        if(this.name.compareTo(other.name)==0
                && this.address.compareTo(other.address)==0
                && this.telephoneNumber.compareTo(other.telephoneNumber)==0
                && this.emailAddress.compareTo(other.emailAddress)==0)
        {
            ret = true;
        }
        return ret;
    }
    //다른 Personal 객체인지 확인하기
    public boolean isNotEqual(Personal other)
    {
         boolean ret = false;
         if(this.name.compareTo(other.name)!=0
                 || this.address.compareTo(other.address)!=0
                 || this.telephoneNumber.compareTo(other.telephoneNumber)!=0
                 || this.emailAddress.compareTo(other.emailAddress)!=0)
         {
             ret = true;
         }
         return  ret;
    }
    //Cloneable 의 clone 메소드 오버라이딩하기(구현하기)
    @Override
    public Personal clone() throws CloneNotSupportedException
    {
        return (Personal)super.clone();
    }

    //이름 정보 가져오기
    public String getName()
    {
        return this.name;
    }
    //주소 정보 가져오기
    public String getAddress()
    {
        return this.address;
    }
    //전화번호 정보 가져오기
    public String getTelephoneNumber()
    {
        return this.telephoneNumber;
    }
    //이메일 정보 가져오기
    public String getEmailAddress()
    {
        return this.emailAddress;
    }
    //이름은 수정할 수 없기 때문에 따로 setter 를 만들지 않음.
    //주소 정보 수정하기
    public void setAddress(String address)
    {
        this.address = address;
    }
    //전화번호 정보 수정하기
    public void setTelephoneNumber(String telephoneNumber)
    {
        this.telephoneNumber = telephoneNumber;
    }
    //이메일주소 정보 수정하기
    public void setEmailAddress(String emailAddress)
    {
        this.emailAddress = emailAddress;
    }

    /**
     * 멤버 필드 확인 용도로 재정의한다.
     */
    @Override
    public String toString()
    {
        //return String.format("name = %s, address = %s, telephoneNumber = %s, emailAddress = %s",
        //        this.name, this.address, this.telephoneNumber, this.emailAddress);
        return new String(this.name + ", " + this.address + ", " + this.telephoneNumber + ", "
                        + this.emailAddress);
    }

    //인스턴스 필드
    private String name;
    private String address;
    private String telephoneNumber;
    private String emailAddress;
}
