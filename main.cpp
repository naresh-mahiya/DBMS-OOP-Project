#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <set>

using namespace std;

class Record
{
    vector<string> fields;

public:
    Record(const vector<string> &fields) : fields(fields) {}

    const vector<string> &getFields() const
    {
        return fields;
    }

    virtual void displayRecord() const
    {
        for (const auto &field : fields)
        {
            cout << field << " ";
        }
        cout << endl;
    }

    const string &getField(size_t index) const
    {
        return fields.at(index);
    }

    void updateField(size_t index, const string &newValue)//*
    {
        if (index < fields.size())
        {
            fields[index] = newValue;
        }
        else
        {
            cout << "Invalid field index." << endl;
        }
    }

    size_t getFieldCount() const
    {
        return fields.size();
    }
};
/*
class EmployeeRecord : public Record
{
public:
    EmployeeRecord(const vector<string> &fields) : Record(fields) {}

    void displayRecord() const override
    {
        cout << "Employee Record: ";
        Record::displayRecord();
    }
};
*/
class Table
{
    string name;
    vector<string> fields;
    vector<unique_ptr<Record>> records;
    set<string> uniqueFields; 

public:
    Table(const string &name, const vector<string> &fields) : name(name), fields(fields) {}

    const string &getName() const
    {
        return name;
    }

    const vector<string> &getFields() const
    {
        return fields;
    }

    void addUniqueConstraint(const string &fieldName)
    {
        auto it = find(fields.begin(), fields.end(), fieldName);
        if (it != fields.end())
        {
            size_t index = distance(fields.begin(), it);
            uniqueFields.insert(fieldName);
            cout << "Added unique constraint on field: " << fieldName << endl;
        }
        else
        {
            cout << "Field not found!" << endl;
        }
    }

    bool isUniqueField(const string &fieldName, const string &value) const//*
    {
        for (const auto &record : records)
        {
            auto it = find(fields.begin(), fields.end(), fieldName);
            if (it != fields.end())
            {
                size_t index = distance(fields.begin(), it);
                if (record->getField(index) == value)
                {
                    return false; // Not unique
                }
            }
        }
        return true;
    }

    void addRecord(unique_ptr<Record> record)
    {
        for (const auto &uniqueField : uniqueFields)
        {
            auto it = find(fields.begin(), fields.end(), uniqueField);
            if (it != fields.end())
            {
                size_t index = distance(fields.begin(), it);
                if (!isUniqueField(uniqueField, record->getField(index)))
                {
                    cout << "Error: Duplicate entry for unique field '" << uniqueField << "'" << endl;
                    return;
                }
            }
        }
        records.push_back(move(record));
    }

    void saveToFile(const string &filename) const
    {
        ofstream outFile(filename, ios::trunc);

        if (!outFile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto &field : fields)
        {
            outFile << field << ",";
        }
        outFile << endl;

        for (const auto &record : records)
        {
            for (const auto &field : record->getFields())
            {
                outFile << field << ",";
            }
            outFile << endl;
        }

        outFile.close();
    }

    void loadFromFile(const string &filename)
    {
        ifstream inFile(filename);

        if (!inFile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        //records.clear();

        string line;
        if (getline(inFile, line))
        {
            fields.clear();
            string field;

            istringstream ss(line);
            while (getline(ss, field, ','))
            {
                fields.push_back(field);
            }
        }

        while (getline(inFile, line))
        {
            vector<string> recordFields;
            string field;
            istringstream ss(line);

            while (getline(ss, field, ','))
            {
                recordFields.push_back(field);
            }

            if (!recordFields.empty())
            {
                records.emplace_back(make_unique<Record>(recordFields));
            }
        }

        inFile.close();
    }

    void displayTable() const
    {
        cout << "Table: " << name << endl;

        for (const auto &field : fields)
        {
            cout << field << " ";
        }
        cout << endl;

        for (const auto &record : records)
        {
            record->displayRecord();
        }
    }

    void deleteRecord(size_t index)
    {
        if (index < records.size())
        {
            records.erase(records.begin() + index);
        }
        else
        {
            cout << "Invalid record index." << endl;
        }
    }

    void updateRecord(size_t index, const string &fieldName, const string &newValue)
    {
        if (index < records.size())
        {
            auto it = find(fields.begin(), fields.end(), fieldName);
            if (it != fields.end())
            {
                size_t fieldIndex = distance(fields.begin(), it);
                records[index]->updateField(fieldIndex, newValue);
                cout << "Record updated successfully." << endl;
            }
            else
            {
                cout << "Field not found." << endl;
            }
        }
        else
        {
            cout << "Invalid record index." << endl;
        }
    }

    // void exportToCSV(const string &filename) const
    // {
    //     ofstream outFile(filename, ios::trunc);

    //     if (!outFile)
    //     {
    //         cerr << "Error opening file: " << filename << endl;
    //         return;
    //     }

    //     for (const auto &field : fields)
    //     {
    //         outFile << field << ",";
    //     }
    //     outFile << endl;

    //     for (const auto &record : records)
    //     {
    //         for (const auto &field : record->getFields())
    //         {
    //             outFile << field << ",";
    //         }
    //         outFile << endl;
    //     }

    //     outFile.close();
    //     cout << "Table exported to CSV: " << filename << endl;
    // }
     size_t getRecordCount() const
    {
        return records.size();
    }


    void query(const unordered_map<string, string> &criteria) const
    {
        cout << "Query Results:" << endl;
        bool found = false;


        for (const auto &record : records)
        {
            bool match = true;


            for (const auto &entry : criteria)
            {
                const string &fieldName = entry.first; // this is the copy of the first objeect
                const string &value = entry.second; // copy of the second object


                auto it = find(fields.begin(), fields.end(), fieldName); //keyword that allows the compiler to automatically deduce the data type of a variable
                if (it != fields.end())
                {
                    size_t index = distance(fields.begin(), it);
                    if (record->getField(index) != value)
                    {
                        match = false;
                        break;
                    }
                }
                else
                {
                    cout << "Field '" << fieldName << "' not found in table." << endl;
                    match = false;
                    break;
                }
            }


            if (match)
            {
                record->displayRecord();
                found = true;
            }
        }


        if (!found)
        {
            cout << "No records found matching the criteria." << endl;
        }
    }
};

class Database
{
private:
    vector<unique_ptr<Table>> tables;

public:
    void addTable(unique_ptr<Table> table)
    {
        tables.push_back(move(table));
    }

    void loadAllTablesFromFile(const string &dbName)
    {
        for (auto &table : tables)
        {
            string filename = "./data/" + dbName + "_" + table->getName() + ".txt";
            table->loadFromFile(filename);
        }
    }

    void saveAllTablesToFile(const string &dbName) const
    {
        for (const auto &table : tables)
        {
            string filename = "./data/" + dbName + "_" + table->getName() + ".txt";
            table->saveToFile(filename);
        }
    }

    void displayAllTableContents() const
    {
        cout << "Displaying all table contents:\n";
        for (const auto &table : tables)
        {
            cout << "Table Name: " << table->getName() << endl;
            table->displayTable();
            cout << endl;
        }
    }

    Table *findTable(const string &tableName)
    {
        for (auto &table : tables)
        {
            if (table->getName() == tableName)
            {
                return table.get();
            }
        }
        return nullptr;
    }

    void manageTable(const string &dbName)
    {
        string tableName;

        // Get table name from the user
        cout << "Enter the name of the table: ";
        getline(cin, tableName);

        Table *userTable = findTable(tableName);
        if (!userTable)
        {
            // Create new table
            vector<string> fields;
            int numFields;
            cout << "Enter the number of fields: ";

            cin >> numFields;
            cin.ignore();

            for (int i = 0; i < numFields; ++i)
            {
                string field;
                cout << "Enter field " << (i + 1) << ": ";
                getline(cin, field);
                fields.push_back(field);
            }

            auto newTable = make_unique<Table>(tableName, fields);
            userTable = newTable.get();
            addTable(move(newTable));
        }

        int option;
        do
        {
            cout << "\n--- Table Menu ---\n";
            cout << "1. Add Record\n";
            cout << "2. Query Records\n";
            cout << "3. Delete Record\n";
            cout << "4. Display Table\n";
            cout << "5. Save Table\n";
            cout << "0. Exit\n";
            cout << "Choose an option: ";
            cin >> option;
            cin.ignore();

            switch (option)
            {
            case 1:
            {
                vector<string> recordFields;
                for (const string &field : userTable->getFields())
                {
                    string value;
                    cout << "Enter " << field << ": ";
                    getline(cin, value);
                    recordFields.push_back(value);
                }

                userTable->addRecord(make_unique<Record>(recordFields)); // Use base Record
                break;
            }
            case 2:
            {
                unordered_map<string, string> criteria;
                string fieldName, value;
                char moreQueries;


                do
                {
                    cout << "Enter the field name to query: ";
                    getline(cin, fieldName);
                    cout << "Enter the value for " << fieldName << ": ";
                    getline(cin, value);
                    criteria[fieldName] = value;


                    cout << "Do you want to add another query? (y/n): ";
                    cin >> moreQueries;
                    cin.ignore();
                } while (moreQueries == 'y');


                userTable->query(criteria);
                break;
            }
            
            case 3:
            {
                size_t index;
                cout << "Enter the record index to delete: ";
                cin >> index;
                userTable->deleteRecord(index);
                break;
            }
            case 4:
            {
                userTable->displayTable();
                break;
            }
            case 5:
            {
                string filename;
                cout << "Enter filename to save the table: ";
                getline(cin, filename);
                userTable->saveToFile(filename);
                break;
            }
            case 0:
                cout << "Exiting Table Menu...\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
            }
        } while (option != 0);
    }
};

class 


Databases
{
private:
    unordered_map<string, Database> databases;


public:
    void createDatabase(const string &dbName)
    {
        if (databases.find(dbName) == databases.end())
        {
            databases[dbName] = Database();
            cout << "Database '" << dbName << "' created successfully." << endl;
        }
        else
        {
            cout << "Database '" << dbName << "' already exists." << endl;
        }
    }


    void displayDatabases() const
    {
        cout << "Databases:\n";
        for (const auto &entry : databases)
        {
            cout << entry.first << endl;
        }
    }


    void manageDatabase(const string &dbName)
    {
        if (databases.find(dbName) != databases.end())
        {
            databases[dbName].manageTable(dbName);
        }
        else
        {
            cout << "Database '" << dbName << "' not found." << endl;
        }
    }


    void loadAllDatabases(const string &dbName)
    {
        if (databases.find(dbName) != databases.end())
        {
            databases[dbName].loadAllTablesFromFile(dbName);
        }
        else
        {
            cout << "Database '" << dbName << "' not found." << endl;
        }
    }


    void saveAllDatabases(const string &dbName) const
    {
        if (databases.find(dbName) != databases.end())
        {
            databases.at(dbName).saveAllTablesToFile(dbName);
        }
        else
        {
            cout << "Database '" << dbName << "' not found." << endl;
        }
    }
};


int main()
{
    Databases dbManager;
    int option;


    do
    {
        cout << "\n--- Database Management System ---\n";
        cout << "1. Create Database\n";
        cout << "2. Display Databases\n";
        cout << "3. Manage Database\n";
        //cout << "4. Load All Tables\n";
        cout << "4. Save All Tables\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore();


        string dbName;
        switch (option)
        {
        case 1:
            cout << "Enter the name of the database: ";
            getline(cin, dbName);
            dbManager.createDatabase(dbName);
            break;
        case 2:
            dbManager.displayDatabases();
            break;
        case 3:
            cout << "Enter the name of the database: ";
            getline(cin, dbName);
            dbManager.manageDatabase(dbName);
            break;
      /*  case 4:
            cout << "Enter the name of the database: ";
            getline(cin, dbName);
            dbManager.loadAllDatabases(dbName);
            break;*/
        case 4:
            cout << "Enter the name of the database: ";
            getline(cin, dbName);
            dbManager.saveAllDatabases(dbName);
            break;
        case 0:
            cout << "Exiting the application." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 0);


    return 0;
}