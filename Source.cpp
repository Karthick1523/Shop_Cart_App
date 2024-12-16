#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // for std::fixed and std::setprecision
#include <map>
using namespace std;

// Structure to store product details
struct Product {
    int id;
    string name;
    double price;
};

// Structure to store cart item details
struct CartItem {
    Product product;
    int quantity;
};

class ShoppingCart {
private:
    vector<CartItem> cart;
    map<int, Product> productCatalog; // Store available products with their IDs as keys

public:
    // Add a product to the catalog
    void addProductToCatalog(int id, const string& name, double price) {
        Product newProduct = {id, name, price};
        productCatalog[id] = newProduct;
    }

    // Display the product catalog
    void displayCatalog() {
        cout << "\nAvailable Products:" << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
        cout << string(40, '-') << endl;
        for (map<int, Product>::const_iterator it = productCatalog.begin(); it != productCatalog.end(); ++it) {
            const Product& product = it->second;
            cout << left << setw(10) << product.id
                 << setw(20) << product.name
                 << setw(10) << fixed << setprecision(2) << product.price << endl;
        }
    }

    // Add an item to the shopping cart
    void addToCart(int productId, int quantity) {
        if (productCatalog.find(productId) == productCatalog.end()) {
            cout << "\nProduct with ID " << productId << " does not exist." << endl;
            return;
        }

        // Check if the product is already in the cart
        for (vector<CartItem>::iterator it = cart.begin(); it != cart.end(); ++it) {
            if (it->product.id == productId) {
                it->quantity += quantity;
                cout << "\nUpdated quantity for " << it->product.name << " in the cart." << endl;
                return;
            }
        }

        // Add new item to the cart
        CartItem newItem = {productCatalog[productId], quantity};
        cart.push_back(newItem);
        cout << "\nAdded " << productCatalog[productId].name << " to the cart." << endl;
    }

    // Remove an item from the shopping cart
    void removeFromCart(int productId) {
        for (vector<CartItem>::iterator it = cart.begin(); it != cart.end(); ++it) {
            if (it->product.id == productId) {
                cout << "\nRemoved " << it->product.name << " from the cart." << endl;
                cart.erase(it);
                return;
            }
        }
        cout << "\nProduct with ID " << productId << " is not in the cart." << endl;
    }

    // Display the cart contents
    void displayCart() {
        if (cart.empty()) {
            cout << "\nYour cart is empty." << endl;
            return;
        }

        cout << "\nYour Shopping Cart:" << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price"
             << setw(10) << "Quantity" << setw(10) << "Total" << endl;
        cout << string(60, '-') << endl;

        double grandTotal = 0.0;
        for (vector<CartItem>::const_iterator it = cart.begin(); it != cart.end(); ++it) {
            const CartItem& item = *it;
            double total = item.product.price * item.quantity;
            grandTotal += total;

            cout << left << setw(10) << item.product.id
                 << setw(20) << item.product.name
                 << setw(10) << fixed << setprecision(2) << item.product.price
                 << setw(10) << item.quantity
                 << setw(10) << fixed << setprecision(2) << total << endl;
        }

        cout << string(60, '-') << endl;
        cout << "Grand Total: " << fixed << setprecision(2) << grandTotal << endl;
    }

    // Clear the cart
    void clearCart() {
        cart.clear();
        cout << "\nThe cart has been cleared." << endl;
    }
};

int main() {
    ShoppingCart cart;

    // Add products to the catalog
    cart.addProductToCatalog(1, "Laptop", 55000.00);
    cart.addProductToCatalog(2, "Smartphone", 15000.00);
    cart.addProductToCatalog(3, "Headphones", 2000.00);
    cart.addProductToCatalog(4, "Keyboard", 1000.00);

    int choice;
    do {
        cout << "\n----- Shopping Cart Menu -----" << endl;
        cout << "1. View Product Catalog" << endl;
        cout << "2. Add Product to Cart" << endl;
        cout << "3. Remove Product from Cart" << endl;
        cout << "4. View Cart" << endl;
        cout << "5. Clear Cart" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cart.displayCatalog();
                break;
            case 2: {
                int productId, quantity;
                cout << "\nEnter Product ID: ";
                cin >> productId;
                cout << "Enter Quantity: ";
                cin >> quantity;
                cart.addToCart(productId, quantity);
                break;
            }
            case 3: {
                int productId;
                cout << "\nEnter Product ID to remove: ";
                cin >> productId;
                cart.removeFromCart(productId);
                break;
            }
            case 4:
                cart.displayCart();
                break;
            case 5:
                cart.clearCart();
                break;
            case 6:
                cout << "\nThank you for using the Shopping Cart. Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
