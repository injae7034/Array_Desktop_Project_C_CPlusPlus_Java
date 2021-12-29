package AddressBook;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;

public class AddressBook  implements Cloneable
{
    //디폴트생성자
    public AddressBook()
    {
        this.personals = new ArrayList<Personal>();
    }
    //복사생성자
    public AddressBook(AddressBook source)
    {
        //깊은 복사
        Personal deepCopyPersonal = null;
        //기존의 원본을 clone하여 ArrayList를 생성한 뒤에 새로운 객체로 배열요소 수정하기
        this.personals = (ArrayList<Personal>)source.personals.clone();
        for(int i = 0; i < this.personals.size(); i++)
        {
            deepCopyPersonal = new Personal(source.getAt(i));
            this.personals.set(i, deepCopyPersonal);
        }
        /*
        //새로 ArrayList 객체를 생성한 다음 새로은 객체를 배열에 추가하기
        this.personals = new ArrayList<Personal>();
        for (Personal personal : source.personals)
        {
               deepCopyPersonal = new Personal(personal);
               this.personals.add(deepCopyPersonal);
        }
         */
    }
    //personals 가져오기
    public ArrayList<Personal> getPersonals()
    {
        return this.personals;
    }
    //Personal 객체 정보 기재하기
    public  int record(String name, String address, String telephoneNumber, String emailAddress)
    {
        int index = -1;//기재하기 실패할 경우 -1반환
        Personal personal = new Personal(name, address, telephoneNumber, emailAddress);
        boolean doesRecordingSucceed = this.personals.add(personal);
        if(doesRecordingSucceed == true)
        {
            index = this.personals.indexOf(personal);
        }
        return index;
    }
    //Personal 객체 정보 가져오기
    public Personal getAt(int index)
    {
        return this.personals.get(index);
    }
    /*
    //name 으로 Personal 객체 찾기
    public int find(String name, int[] indexes)
    {
        //ArrayList 중에서 같은 이름의 배열요소의 위치를 담을 공간
        indexes = new int[this.personals.size()];
        //ArrayList 의 처음부터 끝까지 반복을 돌리면서 찾으려는 이름이 있는지 확인하기
        int index = 0;//위치배열첨자
        int count = 0;//위치배열에 저장되는 개수
        Personal personal =null;
        for(int i = 0; i < this.personals.size(); i++)
        {
            personal = this.personals.get(i);
            if(name.compareTo(personal.getName())==0)
            {
                //위치를 저장한다.
                indexes[index] = i;
                //위치배열 첨자를 증가시킨다.
                index++;
                //위치배열에 저장되는 개수를 증가시킨다.
                count++;
            }
        }
        return count;
    }
     */
    /*
    public int[] find(String name, Integer count)
    {
        //ArrayList 중에서 같은 이름의 배열요소의 위치를 담을 공간
        int[] indexes = new int[this.personals.size()];
        //ArrayList 의 처음부터 끝까지 반복을 돌리면서 찾으려는 이름이 있는지 확인하기
        count = 0;//같은 배열 개수
        int index = 0;//배열 첨자
        Personal personal =null;
        for(int i = 0; i < this.personals.size(); i++)
        {
            personal = this.personals.get(i);
            if(name.compareTo(personal.getName())==0)
            {
                //위치를 저장한다.
                indexes[index] = i;
                //위치배열 첨자를 증가시킨다.
                index++;
                //개수를 증가시킨다
                count++;
            }
        }
        return indexes;
     */
    //ArrayList는 배열과 달리 capacity가 유동적으로 바뀌기 때문에 ArrayList를 이용하면
    //똑같은 이름을 찾는 행위를 한번만 하면됨.
    public ArrayList<Integer> find(String name)
    {
        //name으로 찾은 Personal 객체들의 위치를 저장할 위치ArrayList 생성하기
        ArrayList<Integer> indexes = new ArrayList<>();
        //주소록의 ArrayList 의 처음부터 끝까지 반복을 돌리면서 name과 같은 배열요소의 위치를 저장한다.
        Personal personal =null;
        for(int i = 0; i < this.personals.size(); i++)
        {
            //해당 위치의 Personal객체를 구한다.
            personal = this.personals.get(i);
            //해당 Personal의 name이 찾고자 하는 name과 같으면
            if(name.compareTo(personal.getName())==0)
            {
                //위치를 저장한다.
                indexes.add(i);
            }
        }
        return indexes;
    }
    /*
    //int[]배열을 이용하기 대신 배열생성 전에 크기를 구하기 위해 찾고자 하는 이름과 같은 이름이 배열에 있는지
    //확인하여 그 개수를 새고 배열을 작성한 뒤에 다시 똑같은 이름을 찾으면서 그 위치를 배열요소에 저장
    //똑같은 이름을 찾는 행위 2번 중복되어 시간낭비가 심함.
    public int[] find(String name)
    {

        //시간 절약 메모리 낭비
        //같은 이름이 없다고 초기화
        boolean isMatched = false;
        //ArrayList 중에서 같은 이름의 배열요소의 위치를 담을 공간
        int[] indexes = new int[this.personals.size()];
        //ArrayList 의 처음부터 끝까지 반복을 돌리면서 찾으려는 이름이 있는지 확인하기
        int index = 0;//배열첨자
        Personal personal =null;
        for(int i = 0; i < this.personals.size(); i++)
        {
            personal = this.personals.get(i);
            if(name.compareTo(personal.getName())==0)
            {
                //위치를 저장한다.
                indexes[index] = i;
                //위치배열 첨자를 증가시킨다.
                index++;
                //찾은게 있다고 표시한다.
                isMatched = true;
            }
        }
        if(isMatched == false)
        {
            indexes = null;
        }
        return indexes;
 */
/*
        //메모리 절약 하지만 시간이 많이 소모됨
        //배열값 초기화
        int[] indexes = null;
        int count = 0;//찾은 개수 초기화
        //ArrayList 의 처음부터 끝까지 찾고자 하는 이름과 비교하여 찾은 개수를 센다.
        for (Personal personal: this.personals)
        {
            if(name.compareTo(personal.getName())==0)
            {
                //찾은 개수를 증가시킨다.
                count++;
            }
        }
        //찾은게 있으면
        if(count > 0)
        {
            //배열을 할당한다.
            indexes = new int[count];
        }
        //ArrayList 의 다시 처음부터 끝까지 반복을 돌리면서 같은 배열요소의 위치를 저장한다.
        int index = 0;//배열첨자
        Personal personal =null;
        for(int i = 0; i < this.personals.size(); i++)
        {
            personal = this.personals.get(i);
            if(name.compareTo(personal.getName())==0)
            {
                //위치를 저장한다.
                indexes[index] = i;
                //배열첨자를 증가시킨다.
                index++;
            }
        }
        return indexes;
    }
    */

    //Personal 객체 정보 수정하기(주소, 전화번호, 이메일주소 변경 가능, 이름은 변경 불가)
    public int correct(int index, String address, String telephoneNumber, String emailAddress)
    {
        //새로운 객체가 생성되기 때문에 이렇게 하면 안됨
        // Personal personal = new Personal(this.personals.get(index).getName(), address,
        //        telephoneNumber, emailAddress);
        Personal personal = this.personals.get(index);
        personal.setAddress(address);
        personal.setTelephoneNumber(telephoneNumber);
        personal.setEmailAddress(emailAddress);
        //this.personals.set(index, personal);
        index = this.personals.indexOf(personal);
        return  index;
    }

    /*
    public Personal correct(int index, String address, String telephoneNumber, String emailAddress)
    {
        //Personal personal = new Personal(this.personals.get(index).getName(),
        //                           address, telephoneNumber, emailAddress);
        Personal personal = this.personals.get(index);
        personal.setAddress(address);
        personal.setTelephoneNumber(telephoneNumber);
        personal.setEmailAddress(emailAddress);
        //Personal oldPersonal = this.personals.set(index, personal);
        //return  oldPersonal;
        return personal;
    }
     */

    //Erase
    public int erase(int index)
    {
        Personal personal = this.personals.remove(index);
        if(personal != null)
        {
            index = -1;
        }
        return index;
    }
    //Arrange
    public void arrange()
    {
        Collections.sort(this.personals, new Comparator<Personal>() {
            @Override
            public int compare(Personal one, Personal other)
            {
                return one.getName().compareTo(other.getName());
            }
        });
    }
    @Override
    public AddressBook clone() throws CloneNotSupportedException
    {
        //깊은 복사
        //AddressBook addressBook = (AddressBook)super.clone();
        AddressBook addressBook = new AddressBook();
        Personal deepCopyPersonal = null;
        //기존의 원본을 clone하여 ArrayList를 생성한 뒤에 새로운 객체로 배열요소 수정하기
        //addressBook.personals = (ArrayList<Personal>)this.personals.clone();
        addressBook.personals = new ArrayList<Personal>();
        for(int i = 0; i < this.personals.size(); i++)
        {
            deepCopyPersonal = new Personal(this.getAt(i));
            //addressBook.personals.set(i, deepCopyPersonal);
            addressBook.personals.add(deepCopyPersonal);
        }
        return addressBook;
    }
    //인스턴스 멤버
    private ArrayList<Personal> personals;
}
