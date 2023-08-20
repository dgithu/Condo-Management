#include <iostream>
#include <occi.h>

using oracle::occi::Connection;
using oracle::occi::Environment;
using namespace oracle::occi;
using namespace std;

struct Condo
{
    int floor_num{};
    int condo_num;
    string ownername{};
    string condo_type{};
    string address{};
    string postalcode{};
};



void insertCondo(Connection* conn)
{
    Condo condo;
    int err = 0;

    cout << " Floor num: " << endl;
    cin >> condo.floor_num;
    cout << " Condo num: " << endl;
    cin >> condo.condo_num;
    cout << " Owner name: " << endl;
    cin >> condo.ownername;
    cout << " Condo Type: " << endl;
    cin >> condo.condo_type;
    cout << " Address: " << endl;
    cin >> condo.address;
    cout << " Postal code:" << endl;
    cin >> condo.postalcode;


    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("Begin spCondoInsert(:1,:2,:3,:4,:5,:6,:7); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, condo.floor_num);
        stmt->setNumber(3, condo.condo_num);
        stmt->setString(4, condo.ownername);
        stmt->setString(5, condo.condo_type);
        stmt->setString(6, condo.address);
        stmt->setString(7, condo.postalcode);



        stmt->executeUpdate();
        err = stmt->getInt(1);



        if (err > 0)
        {
            cout << "\n SUCCESS: New condo inserted.\n\n";
        }
        else
        {
            cout << "\n ERROR: New condo could not be inserted. The entered condo num may already exist.\n\n";
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException& sqlExcp)
    {
        std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
};


void updateCondo(Connection* conn)
{
    Condo condo;
    int err = 0;

    cout << "\n Input Condo Number to update its details" << endl;
    cin >> condo.condo_num;
    cout << "\n Enter the Postal code" << endl;
    cin >> condo.postalcode;

    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("Begin spCondoUpdate(:1,:2,:3); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, condo.condo_num);
        stmt->setString(3, condo.postalcode);


        stmt->executeUpdate();
        err = stmt->getInt(1);


        if (err > 0)
        {
            cout << "\n Postal Code " << condo.postalcode << " has been updated" << endl;
        }
        else
        {
            cout << "\n ERROR: condo could not be updated.\n\n";
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException& sqlExcp)
    {
        std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
};


void deleteCondo(Connection* conn)
{
    Condo condo;
    int err = 0;

    cout << "\n Input Condo Number to delete its details" << endl;
    cin >> condo.condo_num;

    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("Begin spCondoDelete(:1,:2); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, condo.condo_num);

        stmt->executeUpdate();
        err = stmt->getInt(1);

        if (err > 0)
        {
            cout << "\n Condo deleted successfully.\n\n" << endl;
        }
        else
        {
            cout << "\n ERROR: condo could not be Deleted. The entered condo num may not exist.\n\n";
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException& sqlExcp)
    {
        std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
};


void selectCondo(Connection* conn)
{
    Condo condo;
    int err = 0;

    cout << "Enter the condo number to read its details " << endl;
    cin >> condo.condo_num;




    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spCondoSelect(:1,:2,:3,:4,:5,:6,:7);END;");

        stmt->registerOutParam(1, Type::OCCIINT, sizeof(condo.floor_num));
        stmt->registerOutParam(2, Type::OCCIINT, sizeof(err));
        stmt->setNumber(3, condo.condo_num);
        stmt->registerOutParam(4, Type::OCCISTRING, sizeof(condo.ownername));
        stmt->registerOutParam(5, Type::OCCISTRING, sizeof(condo.condo_type));
        stmt->registerOutParam(6, Type::OCCISTRING, sizeof(condo.address));
        stmt->registerOutParam(7, Type::OCCISTRING, sizeof(condo.postalcode));

        stmt->executeUpdate();
        err = stmt->getInt(2);
        condo.floor_num = stmt->getInt(1);
        condo.ownername = stmt->getString(4);
        condo.condo_type = stmt->getString(5);
        condo.address = stmt->getString(6);
        condo.postalcode = stmt->getString(7);

        if (err > 0)
        {
            cout << "\n Floor Number: " << condo.floor_num << endl;
            cout << "\n Ownername: " << condo.ownername << endl;
            cout << "\n Condo Type: " << condo.condo_type << endl;
            cout << "\n Address: " << condo.address << endl;
            cout << "\n Postal Code: " << condo.postalcode << endl << endl;
        }
        else
        {
            cout << "\n No results could be displayed " << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException& sqlExcp)
    {
        std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }

}



int main(void)
{
    Environment* env = nullptr;
    Connection* conn = nullptr;
    string str;
    string usr = "dbs311_231ncc22";
    string pass = "86628418";
    string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";


    env = Environment::createEnvironment(Environment::DEFAULT);
    conn = env->createConnection(usr, pass, srv);


    int input = 0;
    do
    {

        cout << " 1. Insert Condo" << endl;
        cout << " 2. Select Condo" << endl;
        cout << " 3. Update Condo" << endl;
        cout << " 4. Delete Condo" << endl;
        cout << " 5. Insert Parking" << endl;
        cout << " 6. Select Parking" << endl;
        cout << " 7. Update Parking" << endl;
        cout << " 8. Delete Parking" << endl;
        cout << " 9. Insert Electricity" << endl; 
        cout << " 10. Insert Electricity" << endl;
        cout << " 11. Insert Electricity" << endl;
        cout << " 12. Insert Electricity" << endl;
        cout << " 13. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> input;

        if (input == 1)
        {
            insertCondo(conn);
        }
        else if (input == 2)
        {
            selectCondo(conn);
        }
        else if (input == 3)
        {
            updateCondo(conn);
        }
        else if (input == 4)
        {
            deleteCondo(conn);
        }
        else if (input == 5)
        {
            insertParking(conn);
        }
        else if (input == 6)
        {
            selectParking(conn);
        }
        else if (input == 7)
        {
            updateParking(conn);
        }
        else if (input == 8)
        {
            deleteParking(conn);
        }
        else if (input == 9)
        {
            insertElectricity(conn);
        }
        else if (input == 10)
        {
             selectElectricity(conn);
        }
        else if (input == 11)
        {
            updateElectricity(conn);
        }
        else if (input == 12)
        {
            deleteElectricity(conn);
        }
    } while (input != 13);

    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);
    return 0;
}

