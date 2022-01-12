package AddressBook;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.sql.*;

public class Main
{
    private static AddressBook addressBook;
    public static void main(String[] args) throws IOException
    {
        //메인테스트 시나리오
        //1. AddressBook객체를 생성한다.
        addressBook = new AddressBook();
        //2. 외부파일이 있으면 외부파일에 있는 Personal 객체정보를 load한다.
        //addressBook.load();
        //2. MySQL에서 파일을 불러온다.
        load();
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
                case 1: formFoRecording(); break;
                case 2: formFoFinding(); break;
                case 3: formFoCorrecting(); break;
                case 4: formFoErasing(); break;
                case 5: formFoArranging(); break;
                case 6: formFoViewingAll(); break;
                default: break;
            }
            displayMenu();
            menuNumber = scanner.nextInt();
        }
        //addressBook.save();
        save();
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
    public static void formFoRecording() throws IOException
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
                insert(index);
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
    public static void formFoFinding()
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
    public static void formFoCorrecting()
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
                while(true)
                {
                    System.out.printf("\t================================================================================\n");
                    System.out.printf("\t번호 : ");
                    //nextInt대신에 nextLine을 써야 뒤에서 탈이 안남.
                    String stringIndex = scanner.nextLine();
                    index = Integer.valueOf(stringIndex);
                    index = index - 1;//배열첨자는 실제입력받은 숫자보다 1이 작기때문에
                    //번호를 제대로 눌렀으면(번호가 배열길이를 넘지 않고 음수가 아니면)
                    if(index < indexes.size() && index >= 0)
                    {
                        System.out.printf("\t--------------------------------------------------------------------------------\n");
                        System.out.println("\t변경할 사항만 입력하시고, 변경하지 않는 사항은 Enter키를 입력해주세요.");
                        System.out.printf("\t--------------------------------------------------------------------------------\n");
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
                            update(index);
                            System.out.printf("\t==============================================================================\n");
                            System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
                            System.out.printf("\t------------------------------------------------------------------------------\n");
                            System.out.printf("\t%d\t\t%s\t%s\t\t%s\t\t%s\n", index + 1,
                                    addressBook.getPersonals().get(index).getName(),
                                    addressBook.getPersonals().get(index).getAddress(),
                                    addressBook.getPersonals().get(index).getTelephoneNumber(),
                                    addressBook.getPersonals().get(index).getEmailAddress());
                        }
                        break;//무한반복문 탈출함.
                    }
                    //번호를 잘못눌렀으면
                    else
                    {
                        System.out.println("\t번호를 잘못 선택하셨습니다.");
                        System.out.println("\t다시 번호를 선택해주세요.");
                    }
                }
            }
            System.out.printf("\t======================================================================================\n");
            System.out.printf("\t계속하시겠습니까?(Y/N) ");
            going = scanner.nextLine();
        }
    }
    //[4] 지우기
    public static void formFoErasing()
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
                while(true)
                {
                    System.out.printf("\t================================================================================\n");
                    System.out.printf("\t번호 : ");
                    //nextInt대신에 nextLine을 써야 뒤에서 탈이 안남.
                    String stringIndex = scanner.nextLine();
                    index = Integer.valueOf(stringIndex);
                    index = index - 1;//배열첨자는 실제입력받은 숫자보다 1이 작기때문에
                    //번호를 제대로 눌렀으면(번호가 배열길이를 넘지 않고 음수가 아니면)
                    if(index < indexes.size() && index >= 0)
                    {
                        System.out.printf("\t--------------------------------------------------------------------------------\n");
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
                            addressBook.erase(indexes.get(index));
                            delete(indexes.get(index));
                            System.out.printf("\t--------------------------------------------------------------------------------\n");
                            System.out.printf("\t지워졌습니다.\n");
                        }
                        break;//무한반복문 탈출함.
                    }
                    //번호를 잘못눌렀으면
                    else
                    {
                        System.out.println("\t번호를 잘못 선택하셨습니다.");
                        System.out.println("\t다시 번호를 선택해주세요.");
                    }
                }
            }
            System.out.printf("\t================================================================================\n");
            System.out.printf("\t계속하시겠습니까?(Y/N) ");
            going = scanner.nextLine();
        }
    }
    //[5] 정리하기
    public static void formFoArranging()
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println();
        System.out.printf("\t주소록 - 정리하기\n");
        System.out.printf("\t================================================================================\n");
        System.out.printf("\t번호\t\t성명\t\t주소\t\t\t\t전화번호\t\t\t이메일주소\n");
        System.out.printf("\t--------------------------------------------------------------------------------\n");

        addressBook.arrange();
        replace();
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
    public static void formFoViewingAll()
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

    //데이터베이스 응용프로그래밍 시작
    //load
    public static void load()
    {
        //Personal테이블에 저장되어 있는 전체 Personal객체를 출력하는 쿼리문을 String에 저장
        String sql = "SELECT Personal.name, Personal.address," +
                " Personal.telephoneNumber, personal.emailAddress FROM Personal;";
        try(//Connection(데이터베이스와 연결을 위한 객체)생성 - getConnection(연결문자열, DB-ID, DB-PW)
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306" +
                    "/AddressBook?serverTimezone=Asia/Seoul", "root", "1q2w3e");
            //Statement(일회성 SQL 문을 데이터베이스에 보내기위한 객체)생성
            Statement stmt = con.createStatement();
            //sql 문장을 실행하고 결과를 리턴
            //( stmt.excuteQuery(sql) : select
            // stmt.excuteUpdate(sql) : insert, update, delete ...)
            //ResultSet(SQL 질의에 의해 생성된 테이블을 저장하는 객체)
            //이제 rs에는 쿼리문에 의해서 찾은 Personal의 전체 정보가 저장됨.
            ResultSet rs = stmt.executeQuery(sql))
        {
            //rs에 저장된 정보를 읽어들이기 위해 rs.next()를 이용함.
            while(rs.next())//rs.next()는 rs.next()==true랑 같은뜻 다음이 있을때까지 계속해서 읽어들이고 다음이 없으면 반복에서 빠져나옴.
            {//rs의 첫번째 위치는 0번째줄이므로 rs.next()를 처음하면 처음줄로 이동하고, 두번 째 rs.next()를 하면 2번째 순서로 이동
                // rs.next()를 통해 다음데이터로 이동했는데 다음데이터가 유효한 데이터가 아니면 Load메소드를 종료시켜버림.
                //rs로부터 얻은 정보를 바탕으로 주소록에 기재하기
                addressBook.record(rs.getString(1), rs.getString(2),
                        rs.getString(3), rs.getString(4));
            }
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
    }

    //save
    public static void save()
    {
        try(//Connection(데이터베이스와 연결을 위한 객체)생성 - getConnection(연결문자열, DB-ID, DB-PW)
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306" +
                    "/AddressBook?serverTimezone=Asia/Seoul", "root", "1q2w3e");
            //Statement(일회성 SQL 문을 데이터베이스에 보내기위한 객체)생성
            Statement stmt = con.createStatement();
            //ResultSet(SQL 질의에 의해 생성된 테이블을 저장하는 객체)생성
            //rs는 Personal의 전체 코드를 가지게 됨.
            ResultSet rs = stmt.executeQuery("SELECT Personal.code FROM Personal;");
            //PreStatement(여러번 SQL 문을 데이터베이스에 보내기위한 객체)생성
            PreparedStatement pstmt = con.prepareStatement("DELETE FROM Personal;"))
        {
            //DB에 있는 Personal 객체 정보들을 모두 지움.
            pstmt.executeUpdate();
            String sql;
            //명함철의 명함개수만큼 반복한다.
            for (Personal personal : addressBook.getPersonals())
            {
                //rs를 다음으로 이동시키고 다음데이터가 있으면
                if(rs.next())
                {

                    //DB에 명함철에서 읽은 개인정보를 추가한다.
                    sql = String.format("INSERT INTO Personal(code, name, address, telephoneNumber," +
                                    " emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');",
                            rs.getString(1), personal.getName(), personal.getAddress(),
                            personal.getTelephoneNumber(), personal.getEmailAddress());
                    pstmt.executeUpdate(sql);
                }
            }
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
    }
    //getCode
    public static String getCode()
    {
        String code = "P0000";
        String newCode = null;
        //내림차순으로 개인코드 정렬하기
        String sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
        try(//Connection(데이터베이스와 연결을 위한 객체)생성 - getConnection(연결문자열, DB-ID, DB-PW)
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306" +
                    "/AddressBook?serverTimezone=Asia/Seoul", "root", "1q2w3e");
            // Statement 객체 생성
            Statement stmt = con.createStatement();
            //ResultSet(SQL 질의에 의해 생성된 테이블을 저장하는 객체)생성
            //rs는 Personal의 전체 코드를 내림차순으로 가지게 됨.
            ResultSet rs = stmt.executeQuery(sql))
        {
            //데이터가 있으면
            if(rs.next())
            {
                code = rs.getString(1);//마지막코드를 읽어들임
            }
            code = code.substring(1,5);//5-1=4 가 되어야 숫자 4개를 가져옴 (1,4)는 앞에 0만 3개 가져오므로 오류가남.
            int number = Integer.parseInt(code);
            number++;
            newCode = String.format("P%04d", number);
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
        return newCode;
    }
    /*
    //getCode
    public static String getCode()
    {
        String code = "P0000";
        String newCode = null;
        //String code = null;//DELETE했을 경우에 코드 중복문제 생김
        String sql = "SELECT Personal.code FROM Personal;";
        try(//Connection(데이터베이스와 연결을 위한 객체)생성 - getConnection(연결문자열, DB-ID, DB-PW)
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306" +
                    "/AddressBook?serverTimezone=Asia/Seoul", "root", "1q2w3e");
            // Statement 객체 생성 및 move를 단방향이 아닌 자유롭게 할 수 있도록 하기 위한 조치
            Statement stmt = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
            //ResultSet(SQL 질의에 의해 생성된 테이블을 저장하는 객체)생성
            //rs는 Personal의 전체 코드를 가지게 됨.
            ResultSet rs = stmt.executeQuery(sql);)
        {
             // DELETE했을 경우에 문제가 생김
             //rs.last();
             //int number = rs.getRow();
             //number++;
             //code = String.format("P%04d", number);

            //int number;
            if(rs.last())//마지막으로 이동한뒤에 그 데이터가 유효하면 선택문에 들어가게됨
            //rs.last()는 rs.last()==true와 같은 뜻
            //마지막으로 이동한뒤에 그 데이터가 유효하면 true이므로 선택문에 들어가게 되고
            //마지막으로 이동했는데 데이터가 없으면 false이므로 선택문에 들어가지않음
            {
              //  code = rs.getString(1);//마지막코드를 읽어들임
            }
            //code = code.substring(1,5);//5-1=4 가 되어야 숫자 4개를 가져옴 (1,4)는 앞에 0만 3개 가져오므로 오류가남.
            //number = Integer.parseInt(code);
            //number++;
            //newCode = String.format("P%04d", number);
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
        return newCode;
    }
    */

    public static void insert(int index)
    {
        String sql = "INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress)" +
                " VALUES(?, ?, ?, ?, ?);";
        try(Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306" +
                "/AddressBook?serverTimezone=Asia/Seoul", "root", "1q2w3e");
            PreparedStatement pstmt = con.prepareStatement(sql))
        {
            Personal personal = addressBook.getAt(index);
            // PreParedStatement 객체 생성, 객체 생성시 SQL 문장 저장
            pstmt.setString(1, getCode());
            pstmt.setString(2, personal.getName());
            pstmt.setString(3, personal.getAddress());
            pstmt.setString(4, personal.getTelephoneNumber());
            pstmt.setString(5, personal.getEmailAddress());
            //PreParedStatement 객체 생성, 객체 생성시 SQL 문장 저장
            pstmt.executeUpdate();
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
    }

    public static void update(int index)
    {
        String sql = "SELECT Personal.code FROM Personal;";
        try(Connection con = DriverManager.getConnection("jdbc:mysql:" +
                "//localhost:3306/AddressBook?serverTimezone=Asia/Seoul",
                "root", "1q2w3e");
            PreparedStatement pstmt = con.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery())
        {
            Personal personal = addressBook.getAt(index);
            String code = null;
            int i= 0;
            while(i <= index)
            {
                //rs를 다음으로 이동시키고 다음이 있으면
                if(rs.next())
                {
                    //개인 코드를 구한다.
                    code = rs.getString(1);
                }
                i++;
            }
            sql = String.format("UPDATE Personal SET address='%s'," +
                            " telephoneNumber='%s', emailAddress='%s'" +
                            " WHERE code='%s';",
                    personal.getAddress(), personal.getTelephoneNumber(),
                    personal.getEmailAddress(), code);
            pstmt.executeUpdate(sql);
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
    }
/*
    public static void update(int index)
    {
        String sql = "SELECT Personal.code FROM Personal;";
        try(Connection con = DriverManager.getConnection("jdbc:mysql:" +
                        "//localhost:3306/AddressBook?serverTimezone=Asia/Seoul",
                "root", "1q2w3e");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(sql);)
        {
            Personal personal = addressBook.getAt(index);
            String code = null;
            int i= 0;
            while(i <= index)
            {
                rs.next();
                code = rs.getString(1);
                i++;
            }
            sql = String.format("UPDATE Personal SET address='%s'," +
                            " telephoneNumber='%s', emailAddress='%s'" +
                            " WHERE code='%s';",
                    personal.getAddress(), personal.getTelephoneNumber(),
                    personal.getEmailAddress(), code);
            //이미 앞의 sql에 저장된 코드를 다 이용한 뒤이므로, 이때는 stmt를 통해서 문장을 실행시켜도됨
            //앞에서 저장한 코드를 더이상 이용할 일이 없기때문에 rs에 저장된 코드들이 지워져도 상관없음.
            stmt.executeUpdate(sql);
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
    }
 */

    public static void delete(int index)
    {
        String sql = "SELECT Personal.code FROM Personal;";
        try(Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306" +
                "/AddressBook?serverTimezone=Asia/Seoul", "root", "1q2w3e");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(sql))
        {
            String code = null;
            int i= 0;
            while(i <= index)
            {
                //rs를 다음으로 이동시키고 다음이 있으면
                if(rs.next())
                {
                    //개인 코드를 구한다.
                    code = rs.getString(1);
                }
                i++;
            }
            sql = String.format("DELETE FROM Personal WHERE code = '%s';", code);
            stmt.executeUpdate(sql);
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
    }
    public static void replace()
    {
        try(//Connection(데이터베이스와 연결을 위한 객체)생성 - getConnection(연결문자열, DB-ID, DB-PW)
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306" +
                    "/AddressBook?serverTimezone=Asia/Seoul", "root", "1q2w3e");
            //Statement(일회성 SQL 문을 데이터베이스에 보내기위한 객체)생성
            Statement stmt = con.createStatement();
            //ResultSet(SQL 질의에 의해 생성된 테이블을 저장하는 객체)생성
            //rs는 Personal의 전체 코드를 가지게 됨.
            ResultSet rs = stmt.executeQuery("SELECT Personal.code FROM Personal;");
            //PreStatement(여러번 SQL 문을 데이터베이스에 보내기위한 객체)생성
            PreparedStatement pstmt = con.prepareStatement("DELETE FROM Personal;"))
        {
            //DB에 있는 Personal 객체 정보들을 모두 지움.
            pstmt.executeUpdate();
            String sql;
            //명함철의 명함개수만큼 반복한다.
            for (Personal personal : addressBook.getPersonals())
            {
                //rs를 다음 항목으로 이동시킨다.
                rs.next();
                //DB에 명함철에서 읽은 개인정보를 추가한다.
                sql = String.format("INSERT INTO Personal(code, name, address, telephoneNumber," +
                                " emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');",
                        rs.getString(1), personal.getName(), personal.getAddress(),
                        personal.getTelephoneNumber(), personal.getEmailAddress());
                pstmt.executeUpdate(sql);
            }
        }
        catch (SQLException e)
        {
            System.out.println("[SQL Error : " + e.getMessage() +"]");
        }
    }
    //데이터베이스 응용프로그래밍 끝
}
