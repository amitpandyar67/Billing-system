#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
int ftotal = 0;
class item {
public:
  string itemname;
  int price;
  int quantity;

  item(string itemname, int price, int quantity) {
    this->itemname = itemname;
    this->price = price;
    this->quantity = quantity;
  }

  void display() const {
    cout << setw(15) << this->itemname << setw(15) << this->price << setw(15)
         << this->quantity << endl;
  }

  void cdisplay() {
    cout << setw(15) << this->itemname << setw(15) << this->quantity
         << "   *   " << setw(10) << this->price << "   =   "
         << this->quantity * this->price << endl;
    ftotal += this->price * this->quantity;
  }

  // less-than operator to sort items by names
  bool operator<(const item &other) const {
    return this->itemname < other.itemname;
  }
};

void Inventory(const vector<item> &v) {
  cout << setw(5) << "SNo" << setw(15) << "Item Name" << setw(15) << "Price"
       << setw(15) << "Quantity" << endl;
  cout << "**************************************************" << endl;
  for (int i = 0; i < v.size(); i++) {
    cout << setw(5) << i + 1;
    v[i].display();
    cout << "--------------------------------------------------" << endl
         << endl;
  }
}

int main() {
  vector<item> v;
  vector<item> cart;
  while (true) {
    int choice;
    cout << "Enter 1 for customer and 2 for employee: ";
    cin >> choice;
    if (choice == 1) {
      int x = 1;
      while (x == 1) {
        cout << "1-> Add items to cart" << endl
             << "2-> Remove items from cart" << endl
             << "3-> View cart" << endl
             << "4-> Generate bill and exit" << endl;
        cin >> x;
        cout << endl;
        switch (x) {
        case 1: {
          Inventory(v);
          cout << "Enter the number of Items you want to add into cart: ";
          int num;
          cin >> num;
          for (int i = 0; i < num; i++) {
            cout << "Enter ItemNo. and Units: ";
            int no;
            int units;
            cin >> no >> units;
            if (v[no - 1].quantity >= units) {
              cart.push_back({v[no - 1].itemname, v[no - 1].price, units});
              v[no - 1].quantity -= units;
            } else {
              cout << "Only " << v[no - 1].quantity
                   << " Units Available and added to cart" << endl;
              cart.push_back(
                  {v[no - 1].itemname, v[no - 1].price, v[no - 1].quantity});
              v[no - 1].quantity = 0;
              v.erase(v.begin() + no - 1);
            }
          }
          sort(cart.begin(), cart.end());
          break;
        }
        case 2: {
          // logic to display the cart first
          int num = cart.size();
          cout << setw(5) << "SNo" << setw(15) << "Item Name" << setw(15)
               << "Units"
               << "   *   " << setw(10) << "Price"
               << "   =   "
               << "Total" << endl;
          cout << "*****************************************************"
               << endl;
          for (int i = 0; i < num; i++) {
            cout << setw(5) << i + 1;
            cart[i].cdisplay();
            cout << "-----------------------------------------------------"
                 << endl
                 << endl;
          }

          // logic to remove items from cart
          cout << "Enter the number of items you want ot remove from cart: ";
          int n;
          cin >> n;
          for (int i = 0; i < n; i++) {
            cout << "Enter Item no. and no. of units you want to drop: ";
            int no, units;
            cin >> no >> units;
            if (units > cart[no - 1].quantity) {
              cout << "Not enough units in cart, please again enter the right "
                      "value"
                   << endl;
              i--;
              continue;
            }
            cart[no - 1].quantity -= units;
            int check = 0;

            // logic to add removed items from cart back to the store
            for (int j = 0; j < v.size(); j++) {
              if (v[j].itemname == cart[no - 1].itemname) {
                v[j].quantity += units;
                check = 1;
              }
            }
            // Incase item was completely vanished from store on adding to the
            // cart
            if (check == 0) {
              v.push_back({cart[no - 1].itemname, cart[no - 1].price, units});
              sort(v.begin(), v.end());
            }

            // Incase item was completely vanished from cart on removing
            if (cart[no - 1].quantity == 0) {
              cart.erase(cart.begin() + no - 1);
            }
          }
          break;
        }
        case 3: {
          int num = cart.size();
          cout << setw(5) << "SNo" << setw(15) << "Item Name" << setw(15)
               << "Units"
               << "   *   " << setw(10) << "Price"
               << "   =   "
               << "Total" << endl;
          cout << "*****************************************************"
               << endl;
          for (int i = 0; i < num; i++) {
            cout << setw(5) << i + 1;
            cart[i].cdisplay();
            cout << "-----------------------------------------------------"
                 << endl
                 << endl;
          }
          break;
        }
        case 4: {
          int num = cart.size();
          ftotal = 0;
          cout << setw(5) << "SNo" << setw(15) << "Item Name" << setw(15)
               << "Units"
               << "   *   " << setw(10) << "Price"
               << "   =   "
               << "Total" << endl;
          cout << "*****************************************************"
               << endl;
          for (int i = 0; i < num; i++) {
            cout << setw(5) << i + 1;
            cart[i].cdisplay();
            cout << "-----------------------------------------------------"
                 << endl;
          }
          cout << setw(50) << "Total: " << ftotal << endl;
          break;
        }
        }
      }
    } else {
      int y = 1;
      while (y == 1) {
        cout << "1-> Add items to store" << endl
             << "2-> View Inventory" << endl
             << "3-> Exit" << endl;
        cin >> y;
        cout << endl;

        switch (y) {
        case 1: {
          cout << "Enter the number of items you want to add: ";
          int num;
          cin >> num;
          for (int i = 0; i < num; i++) {
            string name;
            int p;
            int q;
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter price: ";
            cin >> p;
            cout << "Enter quantity: ";
            cin >> q;
            item it(name, p, q);
            v.push_back(it);
          }
          sort(v.begin(), v.end());
          break;
        }
        case 2: {
          Inventory(v);
          break;
        }
        case 3: {
          break;
        }
        }
      }
    }
  }
}
