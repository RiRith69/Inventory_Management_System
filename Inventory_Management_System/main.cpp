#include<iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<cctype>
#include<conio.h>
using namespace std;

class Inventory {
    private:
        int id;
        string name;
        int quantity;
        int price;
    public:
        Inventory(int ID, string Name, int Quantity, int Price) {
            id = ID;
            name = Name;
            quantity = Quantity;
            price = Price;
        }
        int getID() const {
            return id;
        }
        string getName() const {
            return name;
        }
        int getQuantity() const {
            return quantity;
        }
        int getPrice() const {
            return price;
        }
        void setQuantity(int newQuantity) {
            if (newQuantity > 0) {
                quantity = newQuantity;
            } else {
                cout << "Quantity must be positive" << endl;
            }
        }
        void setPrice(int newPrice) {
            if (newPrice > 0) {
                price = newPrice;
            } else {
                cout << "Price must be positive" << endl;
            }
        }
        string toString() {
            return "ID:" + to_string(id) + " Name:" + name + " Quantity:" + to_string(quantity) + " Price:" + to_string(price);
        }
};

class OwnerInventory {
    private:
        vector<Inventory> inventory;
    public:
        const vector<Inventory>& getInventory() {
            return inventory;
        }
        int BinarySearch(int value) {
            sort(inventory.begin(), inventory.end(), [](const Inventory& a, const Inventory& b) {
                return a.getID() < b.getID();
            });
            int left = 0;
            int right = inventory.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (value == inventory[mid].getID()) {
                    return mid;
                } else if (value > inventory[mid].getID()) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return -1;
        }
        bool isSorted() {
            return is_sorted(inventory.begin(), inventory.end(), [](const Inventory& a, const Inventory& b) {
                return a.getID() < b.getID();
            });
        }
        void writeTofile(const string& filename) {
            ofstream file(filename, ios::app);
            if (!file.is_open()) {
                cout << "Error opening file!" << endl;
                return;
            }
            file << "--------------------------------------------\n";
            file << "|   ID   |   Name  |  Quantity  |  Price   |\n";
            file << "--------------------------------------------\n";
            for (const auto& item : inventory) {
                file << "|" << setw(6) << item.getID() << "  | "
                     <<  setw(7) << item.getName()<< " |"
                     << setw(9)  << item.getQuantity() << "   | "
                     << setw(5)  << item.getPrice() << "$" << "   | " << "\n";
            }
            file << "--------------------------------------------\n";
            file.close();
        }
        bool readFromFile(string& filename, int ID) {
            ifstream file(filename);
            if (!file.is_open()) {
                cout << "Error! Can't open file" << endl;
                return false;
            }
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                int id;
                ss >> id;
                if (id == ID) {
                    return true;
                }
            }
            file.close();
            return false;
        }
        void InsertItem(int id, string name, int quantity, int price, const string& filename) {
            inventory.push_back(Inventory(id, name, quantity, price));
            sort(inventory.begin(), inventory.end(), [](const Inventory& a, const Inventory& b) {
                return a.getID() < b.getID();
            });
            cout << "Insert Successful" << endl;
        }
        void deleteItem(int deleteValue, const string& filename) {
            sort(inventory.begin(), inventory.end(), [](const Inventory& a, const Inventory& b) {
                return a.getID() < b.getID();
            });
            int index = BinarySearch(deleteValue);
            if (index >= 0 && inventory.size()) {
                inventory.erase(inventory.begin() + index);
                cout << "Item deleted successfully!" << endl;
                writeTofile(filename);
            } else {
                cout << "Item not found!" << endl;
            }
        }
        void Update(int newID, int newQuantity, int newPrice, const string& filename) {
            bool found = false;
            for (auto& item : inventory) {
                if (item.getID() == newID) {
                    item.setQuantity(newQuantity);
                    item.setPrice(newPrice);
                    found = true;
                    break;
                }
            }
            if (found) {
                writeTofile(filename);
                cout << "Item updated successfully" << endl;
            } else {
                cout << "ID not found" << endl;
            }
        }
        void display() {
            cout << "--------------------------------------------\n";
            cout << "|   ID   |   Name  |  Quantity  |  Price   |\n";
            cout << "--------------------------------------------\n";
            for (const auto& item : inventory) {
                cout << "|" << setw(6) << item.getID() << "  | "
                     <<  setw(7) << item.getName()<< " |"
                     << setw(9)  << item.getQuantity() << "   | "
                     << setw(5)  << item.getPrice() << "$" << "   | " << "\n";
            }
            cout << "--------------------------------------------\n";
        }
};

int main() {
    OwnerInventory owner;
    int option;
    int id;
    string name;
    int quantity;
    int price;
    string filename = "data.txt";
    // ofstream file("data.txt", ios::app);
    // file << "----------------------------------------------\n";
    // file << "|   ID   |    Name    |  Quantity  |  Price  |\n";
    // file << "----------------------------------------------\n";
    // file.close();
    do {
        cout << "\n+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=+" << endl;
        cout << "|  ---------------------------  |" << endl;
        cout << "|  Inventory Management System  |" << endl;
        cout << "|  ---------------------------  |" << endl;
        cout << "+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=+" << endl;
        cout << "+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=+" << endl;
        cout << "|  1. Insert                    |" << endl;
        cout << "|  2. Delete                    |" << endl;
        cout << "|  3. Update                    |" << endl;
        cout << "|  4. Search                    |" << endl;
        cout << "|  5. Display                   |" << endl;
        cout << "|  6. Exite                     |" << endl; 
        cout << "\n+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=+" << endl;
        
        cout << "\n=->Enter your option:";
        cin >> option;
        switch (option) {
            case 1: {
                system("cls");
                id:
                cout << "\nEnter ID:";
                while (true) {
                    cin >> id;
                    if (id < 0) {
                        cout << "ID must be positive!\nEnter again:";
                    } else {
                        break;
                    }
                }
                // if (owner.readFromFile(filename, id)) {
                //     cout << "This ID is taken" << endl << "Enter again:\n";
                //     goto id;
                // }
                for(const auto& item : owner.getInventory()){
                    if(item.getID() == id){
                        cout << "Error: ID " << id << " is already exist.\nEnter again" << endl;
                        goto id;
                    }
                }
                cin.ignore();
                cout << "\nEnter name:";
                getline(cin, name);
                cout << "\nEnter quantity:";
                cin >> quantity;
                cout << "\nEnter price:";
                cin >> price;
                owner.InsertItem(id, name, quantity, price, filename);
                owner.writeTofile(filename);
                if (owner.isSorted()) {
                    cout << "The inventory is sorted" << endl;
                } else {
                    cout << "The inventory is not sorted" << endl;
                }
                break;
            }
            case 2: {
                system("cls");
                int value;
                cout << "Enter ID to delete the item:\n";
                cin >> value;
                owner.deleteItem(value, "data.txt");
                break;
            }
            case 3: {
                system("cls");
                updateID:
                cout << "Enter ID to update the item:\n";
                cin >> id;
                int index = owner.BinarySearch(id);
                if (index == -1) {
                    cout << "ID not found" << endl;
                    goto updateID;
                } else {
                    cout << "Enter quantity:\n";
                    cin >> quantity;
                    cout << "Enter the price:\n";
                    cin >> price;
                    owner.Update(id, quantity, price, filename);
                }
                break;
            }
            case 4: {
                system("cls");
                cout << "Enter ID to search the item:\n";
                cin >> id;
                int index = owner.BinarySearch(id);
                if (index != -1) {
                    const auto& inventoryList = owner.getInventory();
                    const Inventory& item = inventoryList[index];
                    cout << "Item found!!" << endl;
                    cout << "ID:" << item.getID() << endl;
                    cout << "Name:" << item.getName() << endl;
                    cout << "Quantity:" << item.getQuantity() << endl;
                    cout << "Price:" << item.getPrice() << "$" << endl;
                } else {
                    cout << "Item with ID " << id << " not found" << endl;
                }
                break;
            }
            case 5: {
                system("cls");
                owner.display();
                break;
            }
            case 6: {
                system("cls");
                cout << "Program end...!" << endl;
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    } while (option != 6);
}
