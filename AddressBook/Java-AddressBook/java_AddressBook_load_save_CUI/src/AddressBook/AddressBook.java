package AddressBook;
import java.io.*;
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
    //name을 통해 Personal 객체찾기
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
    //해당 index의 Personal 객체 정보 수정하기(주소, 전화번호, 이메일주소 변경 가능, 이름은 변경 불가)
    public int correct(int index, String address, String telephoneNumber, String emailAddress)
    {
        Personal personal = this.personals.get(index);
        personal.setAddress(address);
        personal.setTelephoneNumber(telephoneNumber);
        personal.setEmailAddress(emailAddress);
        //this.personals.set(index, personal);
        index = this.personals.indexOf(personal);
        return  index;
    }
    //해당 index의 Personal 객체 지우기
    public int erase(int index)
    {
        Personal personal = this.personals.remove(index);
        if(personal != null)
        {
            index = -1;
        }
        return index;
    }
    //이름기준으로 오름차순으로 정렬하기
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
    //깊은 복사
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
    /*
    //외부 파일에 있는 정보를 읽어서 AddressBook에 Load하기(substring사용)
    public int load()
    {
        //해당위치에 있는 data를 읽어 File객체를 생성한다.
        File file = new File("AddressBook.txt");
        //해당위치에 파일이 존재하면
        if(file.exists() == true)
        {
            //입력을 위한 스트림을 생성한다.
            try (Reader reader = new FileReader(file);
                 BufferedReader bufferedReader = new BufferedReader(reader);) {
                Personal personal;
                //줄단위(Personal 객체단위)로 읽는다.
                int beginIndex = 0;//시작위치를 저장할 임시공간
                int endIndex = 0;//콤마(,)위치를 저장할 임시공간(,단위로 필드가 구분됨)
                String personalInformation;//한줄단위로 읽은 데이터를 저장할 임시공간
                String name;//한줄단위로 읽은 데이터 중에서 이름을 저장할 임시공간
                String address;//한줄단위로 읽은 데이터 중에서 주소를 저장할 임시공간
                String telephoneNumber;//한줄단위로 읽은 데이터 중에서 전화번호를 저장할 임시공간
                String emailAddress;//한줄단위로 읽은 데이터 중에서 이메일주소를 저장할 임시공간
                while((personalInformation = bufferedReader.readLine()) != null)
                {
                    //시작위치를 초기화한다.
                    beginIndex = 0;
                    //personalInformaion에서 처음부터 시작해서 ","의 위치를 찾는다.
                    endIndex = personalInformation.indexOf(",");
                    //name 문자열을 구한다.
                    name = personalInformation.substring(beginIndex, endIndex);
                    //","위치 다음을 시작위치로 재설정한다.
                    beginIndex = endIndex + 1;
                    //재설정한 시작위치부터 다음 ","위치를 찾는다.
                    endIndex = personalInformation.indexOf(",", beginIndex);
                    //address 문자열을 구한다.
                    address = personalInformation.substring(beginIndex, endIndex);
                    //","위치 다음을 시작위치로 재설정한다.
                    beginIndex = endIndex + 1;
                    //재설정한 시작위치부터 다음 ","위치를 찾는다.
                    endIndex = personalInformation.indexOf(",", beginIndex);
                    //telephone 문자열을 구한다.
                    telephoneNumber = personalInformation.substring(beginIndex, endIndex);
                    //","위치 다음을 시작위치로 재설정한다.
                    beginIndex = endIndex + 1;

                    //재설정한 시작위치부터 다음 ","위치를 찾는다.
                    //endIndex = personalInformation.indexOf(",", beginIndex);

                    //emailAddress 문자열을 구한다.(더이상 ,가 없으므로 personalInformation의 길이가 endIndex임)
                    emailAddress = personalInformation.substring(beginIndex);
                    //새로운 Personal객체를 생성한다.
                    personal = new Personal(name, address , telephoneNumber, emailAddress);
                    //새로 생성한 Personal객체를 ArrayList<Personal>에 추가한다.
                    this.personals.add(personal);
                }
            } catch (IOException e) {e.printStackTrace();}
        }
        //load한 Personal객체 수를 반환한다.
        return this.personals.size();
    }
     */

    //외부 파일에 있는 정보를 읽어서 AddressBook에 Load하기(split사용)
    public int load()
    {
        //해당위치에 있는 data를 읽어 File객체를 생성한다.
        File file = new File("AddressBook.txt");
        //해당위치에 파일이 존재하면
        if(file.exists() == true)
        {
            //입력을 위한 스트림을 생성한다.
            try (Reader reader = new FileReader(file);
                 BufferedReader bufferedReader = new BufferedReader(reader);) {
                Personal personal;
                //줄단위(Personal 객체단위)로 읽는다.
                String personalInformation;//한줄단위로 읽은 데이터를 저장할 임시공간
                String[] tokens = null;//분리된 문자열들을 저장할 배열
                //줄단위(Personal 객체단위)로 파일의 끝까지 읽는다.
                while((personalInformation = bufferedReader.readLine()) != null)
                {
                    //외부파일에서 읽은 한 줄 데이터를 콤마(,)기준으로 분리한다.
                    tokens = personalInformation.split(",");
                    //새로운 Personal객체를 생성한다.
                    personal = new Personal(tokens[0], tokens[1], tokens[2], tokens[3]);
                    //새로 생성한 Personal객체를 ArrayList<Personal>에 추가한다.
                    this.personals.add(personal);
                }
            } catch (IOException e) {e.printStackTrace();}
        }
        //load한 Personal객체 수를 반환한다.
        return this.personals.size();
    }

    //AddressBook에 있는 Personal객체 정보를 외부파일에 저장하기
    public void save()
    {
        //해당위치에 있는 data를 쓸 File객체를 생성한다.
        File file = new File("AddressBook.txt");
        //출력을 위한 스트림을 생성한다.
        try(Writer writer = new FileWriter(file);
            BufferedWriter bufferedWriter = new BufferedWriter(writer);){
            //AddressBook에 저장된 Personal 객체의 수만큼 반복한다.
            int i = 0;
            Personal personal = null;//AddressBook의 personal을 저장하기 위한 임시공간
            while(i < this.personals.size())
            {
                //AddressBook에서 Personal객체를 구한다.
                personal = this.personals.get(i);
                //personal 단위로 외부에 출력한다.
                bufferedWriter.write(new String(personal.getName() + "," +
                        personal.getAddress() + "," + personal.getTelephoneNumber()
                        + "," + personal.getEmailAddress() + "\n"));
                i++;
            }
            bufferedWriter.flush();
        } catch (IOException e) {e.printStackTrace();}
    }
    //AddressBook에 기재된 전체 Personal을 순차적으로 출력하기
    public void printAddressBook(int number)
    {
        Personal personal = null;
        int index = 0;
        while(index < this.personals.size())
        {
            personal = this.getAt(index);
            System.out.printf(" %d.%d %s, %s, %s, %s\n", number, index + 1,
                    personal.getName(), personal.getAddress(),
                    personal.getTelephoneNumber(), personal.getEmailAddress());
            index++;
        }
    }

    //인스턴스 멤버
    private ArrayList<Personal> personals;
}
