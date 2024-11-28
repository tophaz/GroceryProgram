#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct GroceryItem {
    int itemId;
    string name;
    int quantity;
    double price;
    double total;
};

void createSampleInputFile() {
    ofstream outputFile("grocery_inputs.txt");

    if (outputFile.is_open()) {
        outputFile << "10011 Avocado 3 20.00" << endl;
        outputFile << "10012 Tomato 6 5.00" << endl;
        outputFile << "10013 Orange 9 15.50" << endl;
        outputFile << "10014 Mango 6 25.00" << endl;
        outputFile << "10015 Guava 7 5.00" << endl;

        outputFile.close();
        cout << "Sample data written to grocery_inputs.txt successfully!" << endl;
    } else {
        cout << "Error creating file." << endl;
    }
}

void readDataFromFile(const string &filename, vector<GroceryItem> &items) {
    ifstream inputFile(filename.c_str());

    if (!inputFile) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }

    GroceryItem item;
    while (inputFile >> item.itemId >> item.name >> item.quantity >> item.price) {
        item.total = item.quantity * item.price;
        items.push_back(item);
    }

    inputFile.close();
}

void calculateTotals(const vector<GroceryItem> &items, double &subTotal, double &tax, double &grandTotal) {
    subTotal = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        subTotal += items[i].total;
    }
    tax = subTotal * 0.16;
    grandTotal = subTotal + tax;
}

void printReceipt(const vector<GroceryItem> &items, double subTotal, double tax, double grandTotal) {
    cout << fixed << setprecision(2);
    cout << "----------------------------------" << endl;
    cout << "         Shopping Receipt         " << endl;
    cout << "----------------------------------" << endl;
    cout << left << setw(10) << "Item ID" << setw(15) << "Name" << setw(8) << "Qty" << setw(10) << "Price" << setw(10) << "Total" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        const GroceryItem &item = items[i];
        cout << left << setw(10) << item.itemId << setw(15) << item.name << setw(8) << item.quantity << setw(10) << item.price << setw(10) << item.total << endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Subtotal: " << setw(26) << right << subTotal << endl;
    cout << "Tax (16%): " << setw(25) << right << tax << endl;
    cout << "Grand Total: " << setw(22) << right << grandTotal << endl;
}

void writeDataToFile(const string &filename, const vector<GroceryItem> &items, double subTotal, double tax, double grandTotal) {
    ofstream outputFile(filename.c_str());

    if (!outputFile) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }

    outputFile << fixed << setprecision(2);
    outputFile << "----------------------------------" << endl;
    outputFile << "         Shopping Receipt         " << endl;
    outputFile << "----------------------------------" << endl;
    outputFile << left << setw(10) << "Item ID" << setw(15) << "Name" << setw(8) << "Qty" << setw(10) << "Price" << setw(10) << "Total" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        const GroceryItem &item = items[i];
        outputFile << left << setw(10) << item.itemId << setw(15) << item.name << setw(8) << item.quantity << setw(10) << item.price << setw(10) << item.total << endl;
    }
    outputFile << "----------------------------------" << endl;
    outputFile << "Subtotal: " << setw(26) << right << subTotal << endl;
    outputFile << "Tax (16%): " << setw(25) << right << tax << endl;
    outputFile << "Grand Total: " << setw(22) << right << grandTotal << endl;

    outputFile.close();
}

int main() {
    // Create a sample input file if it doesn't exist
    createSampleInputFile();

    vector<GroceryItem> items;
    string inputFilename, outputFilename;
    double subTotal, tax, grandTotal;

    // Prompt the user for the input file name
    cout << "Enter the input file name: ";
    cin >> inputFilename;
    readDataFromFile(inputFilename, items);
    calculateTotals(items, subTotal, tax, grandTotal);
    printReceipt(items, subTotal, tax, grandTotal);

    // Prompt the user for the output file name
    cout << "Enter the output file name: ";
    cin >> outputFilename;
    writeDataToFile(outputFilename, items, subTotal, tax, grandTotal);

    return 0;
}