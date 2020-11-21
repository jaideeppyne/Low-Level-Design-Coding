#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <complex>
#include <array>

using namespace std;

class Items {
    public:
        string name;
        int price;
        int count;
};
void checkItemPrice(vector<Items>& inventory) {
    cout << "Displaying items present in the inventory: \n";
    for(auto item : inventory) {
        if(item.count < 1)
            continue;
        cout << "Name: " << item.name << " - Price: " << item.price << " - Count: " << item.count << "\n";
    }
    cout << "\n";
}
int findInputPrice(vector<string>& denom, map<string, int>& denominations) {
    int inputPrice = 0;
    for(auto d: denom) {
        inputPrice += denominations[d];
    }
    return inputPrice;
}
void buyItem(string itemName, vector<string>& denom, vector<Items>& inventory, map<string, int>& denominations) {
    //check if item is available
    int inputItemIndex = 0;
    bool itemFound = false;
    for(int itemIndex = 0;itemIndex < inventory.size();itemIndex++) {
        if(itemName == inventory[itemIndex].name) {
            itemFound = true;
            if(inventory[itemIndex].count < 1) {
                cout << itemName << " is not available\n\n";
                return;
            }
            inputItemIndex = itemIndex;
        }
    }
    if(!itemFound) {
        cout << itemName << " not found\n";
        return;
    }

    //find input price
    int inputPrice = findInputPrice(denom, denominations);

    //compare input price with actual item price
    if(inputPrice < inventory[inputItemIndex].price) {
        cout << "Transaction Failed\n";
        cout << "Price of " << itemName << " is: " << inventory[inputItemIndex].price << "\n";
        cout << "You have entered less price: " << inputPrice << "\n";
    }
    else {
        inventory[inputItemIndex].count--;
        cout << itemName << " purchased successfully\n";
        cout << "Remaining balance: " << inputPrice - inventory[inputItemIndex].price << "\n";
    }
    cout << "\n";
}
int main() {
    //fill the inventory
    vector<Items> inventory;
    inventory.push_back({"Coke",25,1});
    inventory.push_back({"Soda",35,2});
    inventory.push_back({"Pepsi",45,1});

    map<string, int> denominations = {
            {"c1", 1},
            {"c2", 5},
            {"c3", 10},
            {"c4", 25}
    };
    //display items present in inventory
    checkItemPrice(inventory);

    //transaction
    string itemName = "Fanta";
    vector<string> denom = {"c2", "c3"};
    buyItem(itemName, denom, inventory, denominations);
    denom.clear();

    denom.push_back("c4");
    denom.push_back("c4");
    itemName = "Soda";
    buyItem(itemName, denom, inventory, denominations);

    checkItemPrice(inventory);

    return 0;
}
