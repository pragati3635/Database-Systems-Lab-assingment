#include <iostream>
#include <windows.h>
#include<sstream>
#include <mysql.h>

using namespace std;
const char* hostname="172.30.17.71";
const char* username="sandip";
const char* password="Sandip123@";
const char* database="sandip";
unsigned int port=0;
const char* usocket=NULL;
unsigned long clientflag=0;


MYSQL *connect_database()
{
    MYSQL *conn;

    conn=mysql_init(0);

    conn=mysql_real_connect(conn,hostname,username,password,database,port, usocket, clientflag);//user replace with adain and replace with adain

    if(conn)
    {
        cout<<"Database is connected"<<endl;
        return conn;
    }
    else
    {
        cout<<"Database is not connected"<<endl;
        return conn;
    }
}
void insertion_Employee(MYSQL *conn) {

    int qstate = 0;

    stringstream ss;
    string emp_name,email,contact_number,department;

    cout<<"Enter emp_name "<<endl;

    cin>>emp_name;

    cout<<"Enter employee_email"<<endl;
    cin>>email;
    cout<<"Enter contact detail "<<endl;

    cin>>contact_number;

    cout<<"Enter employee_department"<<endl;
    cin>>department;
    ss << "INSERT INTO employee_q3 VALUES ('"+emp_name+"', '"+email+"', '"+contact_number+"', '"+department+"')";

    string query=ss.str();

    const char* q= query.c_str();

    qstate = mysql_query(conn, q);
    if (qstate ==0)
    {

        cout<<"Record inserted... \n";
    }
    else
    {
        cout << "Failed to insert... \n";
    }
}
void insertion_Department(MYSQL *conn) {

    int qstate = 0;

    stringstream ss;
    string emp_name,salary,designation;

    cout<<"Enter emp_name "<<endl;

    cin>>emp_name;

    cout<<"Enter employee_salary"<<endl;
    cin>>salary;
    cout<<"Enter emp_designation "<<endl;

    cin>>designation;


    ss << "INSERT INTO department VALUES ('"+emp_name+"', '"+salary+"', '"+designation+"')";

    string query=ss.str();

    const char* q= query.c_str();

    qstate = mysql_query(conn, q);
    if (qstate ==0)
    {

        cout<<"Record inserted... \n";
    }
    else
    {
        cout << "Failed to insert... \n";
    }
}
void insertion_Awardee(MYSQL *conn) {

    int qstate = 0;

    stringstream ss;
    string emp_name,email,department,experience;

    cout<<"Enter emp_name "<<endl;

    cin>>emp_name;

    cout<<"Enter employee_email"<<endl;
    cin>>email;
    cout<<"Enter emp_department "<<endl;

    cin>>department;
    cout<<"Enter emp_experience "<<endl;

    cin>>experience;

    ss << "INSERT INTO awardee VALUES ('"+emp_name+"', '"+email+"', '"+department+"', '"+experience+"')";

    string query=ss.str();

    const char* q= query.c_str();

    qstate = mysql_query(conn, q);
    if (qstate ==0)
    {

        cout<<"Record inserted... \n";
    }
    else
    {
        cout << "Failed to insert... \n";
    }
}

void connect (MYSQL *conn)
{

    MYSQL_ROW row;
    MYSQL_RES* res;

    if(conn)
    {

        int qstate = mysql_query(conn, " SELECT * FROM employee_q3 e INNER JOIN department d ON e.emp_name=d.emp_name INNER JOIN awardee a ON e.emp_name=a.emp_name;");

        if(!qstate)
        {

            res= mysql_store_result (conn);

            int count = mysql_num_fields (res);

            while (row=mysql_fetch_row(res))
            {

                for(int i=0; i<count; i++)
                {
                    cout<<"\t"<<row[i];
                }
                cout<<endl;
            }
        }
    }
    else
    {
        cout<<"Failed to fetch ";
    }
}

void no_of_awardeees (MYSQL *conn)
{

    MYSQL_ROW row;
    MYSQL_RES* res;

    if(conn)
    {

        int qstate = mysql_query(conn, " SELECT department,COUNT(*) FROM awardee GROUP BY department;");

        if(!qstate)
        {

            res= mysql_store_result (conn);

            int count = mysql_num_fields (res);

            while (row=mysql_fetch_row(res))
            {

                for(int i=0; i<count; i++)
                {
                    cout<<"\t"<<row[i];
                }
                cout<<endl;
            }
        }
    }
    else
    {
        cout<<"Failed to fetch ";
    }
}

void display (MYSQL *conn)
{

    MYSQL_ROW row;
    MYSQL_RES* res;

    if(conn)
    {

        int qstate = mysql_query(conn, "SELECT * FROM awardee");
        if(!qstate)
        {

            res= mysql_store_result (conn);

            int count = mysql_num_fields (res);

            while (row=mysql_fetch_row(res))
            {

                for(int i=0; i<count; i++)
                {
                    cout<<"\t"<<row[i];
                }
                cout<<endl;
            }
        }
    }
    else
    {
        cout<<"Failed to fetch ";
    }
}
int main()
{
     MYSQL* conn=connect_database();
    // for(int i=0;i<5;i++){
      //  insertion_Employee(conn);
     //}
     //display(conn);
     //connect(conn);
     no_of_awardeees(conn);
    return 0;
}
