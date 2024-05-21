#include <stdio.h>

void displayMenu(int n);
float calculateBill(int restaurant, char items[][50], int quantities[], int *itemCount);
int getValidChoice(int min, int max, const char *prompt);
int getValidQuantity(const char *prompt);
void getCustomerDetails(char *name, char *phone);

void displayMenu(int n) {
    system("clear");
    if (n == 1) {
        printf("\nYou chose KFC\n");
        printf("1. Snack box    - 312 BDT\n");
        printf("2. Zinger meal  - 733 BDT\n");
        printf("3. Hot wings    - 460 BDT\n");
        printf("4. Fried chicken- 200 BDT\n");
    } else if (n == 2) {
        printf("\nYou chose Chillox\n");
        printf("1. Mushroom chicken burger - 180 BDT\n");
        printf("2. Beef cheese             - 200 BDT\n");
        printf("3. Naga drums              - 90 BDT\n");
        printf("4. Oreo shake              - 150 BDT\n");
    } else if (n == 3) {
        printf("\nYou chose Pizza Hut\n");
        printf("1. Classic beef pizza - 859 BDT\n");
        printf("2. Beef pepperoni     - 549 BDT\n");
        printf("3. Mushroom pasta     - 329 BDT\n");
        printf("4. Garlic bread slice - 119 BDT\n");
    } else if (n == 4) {
        printf("\nYou chose Crimson Cup\n");
        printf("1. French toast - 200 BDT\n");
        printf("2. Flavored Latte - 200 BDT\n");
        printf("3. Cappuccino     - 180 BDT\n");
        printf("4. Espresso       - 130 BDT\n");
    } else if (n == 5) {
        printf("\nYou chose Sultan's Dine\n");
        printf("1. Kacchi Biriani - 250 BDT\n");
        printf("2. Jali Kabab     - 50  BDT\n");
        printf("3. Mutton Korma   - 460 BDT\n");
        printf("4. Leg Roast      - 150 BDT\n");
    }
}

float calculateBill(int restaurant, char items[][50], int quantities[], int *itemCount) {
    int choice = getValidChoice(1, 4, "Enter item number: ");
    int quantity = getValidQuantity("Enter quantity: ");

    const char *menuItems[5][4] = {
        {"Snack box", "Zinger meal", "Hot wings", "Fried chicken"},
        {"Mushroom chicken burger", "Beef cheese", "Naga drums", "Oreo shake"},
        {"Classic beef pizza", "Beef pepperoni", "Mushroom pasta", "Garlic bread slice"},
        {"French toast", "Flavored Latte", "Cappuccino", "Espresso"},
        {"Kacchi Biriani", "Jali Kabab", "Mutton Korma", "Leg Roast"}
    };

    float prices[5][4] = {
        {312, 733, 460, 200},
        {180, 200, 90, 150},
        {859, 549, 329, 119},
        {200, 200, 180, 130},
        {250, 50, 460, 150}
    };
    float vat = 0.15;
    float total = prices[restaurant - 1][choice - 1] * quantity;
    total += total * vat;

    // Store the item and quantity in the arrays
    strcpy(items[*itemCount], menuItems[restaurant - 1][choice - 1]);
    quantities[*itemCount] = quantity;
    (*itemCount)++;

    printf("Total Amount for %s = %.2f BDT including 15%% VAT\n", menuItems[restaurant - 1][choice - 1], total);
    return total;
}

int getValidChoice(int min, int max, const char *prompt) {
    int choice;
    while (1) {
        printf("%s", prompt);
        scanf("%d", &choice);
        if (choice >= min && choice <= max) {
            return choice;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int getValidQuantity(const char *prompt) {
    int quantity;
    while (1) {
        printf("%s", prompt);
        scanf("%d", &quantity);
        if (quantity > 0) {
            return quantity;
        } else {
            printf("Invalid quantity. Please enter a positive number.\n");
        }
    }
}

void getCustomerDetails(char *name, char *phone) {
    printf("Enter your name: ");
    scanf(" %[^\n]", name); // To read a string with spaces
    printf("Enter your phone number: ");
    scanf("%s", phone);
}

int main() {
    char name[50], phone[15];
    char items[10][50];
    int quantities[10];
    int itemCount = 0;
    float totalAmount = 0.0;

    printf("\t_________________________________________________________\n");
    printf("\t\tWelcome to our online food ordering system\n");
    printf("\t\t    Are you hungry? Want some food?\n");

    getCustomerDetails(name, phone);

    printf("\nChoose a restaurant\n");
    printf("1. KFC \n2. Chillox \n3. Pizza Hut \n4. Crimson Cup \n5. Sultan's Dine\n");

    int restaurantChoice = getValidChoice(1, 5, "Enter your choice by serial number: ");
    displayMenu(restaurantChoice);

    totalAmount += calculateBill(restaurantChoice, items, quantities, &itemCount);

    printf("\nWould you like to order anything else from the same restaurant? (1 for Yes, 0 for No): ");
    int more;
    scanf("%d", &more);
    while (more) {
        displayMenu(restaurantChoice);
        totalAmount += calculateBill(restaurantChoice, items, quantities, &itemCount);
        printf("\nWould you like to order anything else from the same restaurant? (1 for Yes, 0 for No): ");
        scanf("%d", &more);
    }

    printf("\nSelect payment method\n");
    printf("1. Bkash \n2. Cash \n3. Credit card \n4. Rocket \n5. Nagad\n");
    getValidChoice(1, 5, "Enter method number: ");

    printf("\nOrder Details:\n");
    printf("Customer Name: %s\n", name);
    printf("Phone Number: %s\n", phone);
    printf("Items Ordered:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s - Quantity: %d\n", i + 1, items[i], quantities[i]);
    }
    printf("Total Amount: %.2f BDT\n", totalAmount);

    printf("Your order has been successfully received. Thank you.\n");

    return 0;
}
