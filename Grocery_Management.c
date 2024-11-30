#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 400
#define FILENAME "inventory.txt"
#define USERNAME "admin"
#define PASSWORD "admin"  

typedef struct {
    char name[50];
    float price;
    int quantity;
} Item;

typedef struct{
    char costumer_name[100];
    float totalamount;
    Item sales_Item;
}Sales;
Item inventory[MAX_ITEMS];
int numItems = 0;

void displayMainMenu();// Display menus to the console
void manageInventory();//To add new items to inventory 
void process_Sale();//To Process Sales Record of Grocery
void updateInventory();//To update the Price, Quantity of items to invevntory
void deleteItem();// To Delete particular item form the inventory
void searchItem();// To Search for particular item in the inventory
void sortInventory();// To Sort items of inventory according to their price(Low to High)
void saveInventoryToFile();// To Write inventory data to file
void loadInventoryFromFile();// to load inventory data from file
void displayInventory();// To Display the current inventory
void DisplayTransactionHistory(); //To display the Transaction History of the Grocecry
void SaveTransaction(Sales sale_record);// To save the The transaction of the Grocery
void welcomeMessage();// To display the Welcome message to the console
int passwordProtection();//To enable password Protection

int main() {
    int attempt_left =3;
    int choice;
    loadInventoryFromFile();
    welcomeMessage();
    while(attempt_left>0){
    if(passwordProtection())
        {
    do {
        displayMainMenu();
        printf("\n\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                manageInventory();
                break;
            case 2:
                process_Sale();
                break;
            case 3:
                updateInventory();
                break;
            case 4:
                deleteItem();
                break;
            case 5:
                searchItem();
                break;
            case 6:
                sortInventory();
                break;
            case 7:
                displayInventory();
                break;
            case 8:
                DisplayTransactionHistory();
                break;
            case 9:
                printf("Exiting program.\n");
                saveInventoryToFile();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }    
        }
    while (1);
    }
       else {
        attempt_left--;
        if (attempt_left !=0){
        printf("\n\t\t\t\tIncorrect password. Please! Try Again.... \n");
        printf("\t\t\t\t\tYou have %d Attempt left:", attempt_left);
        }
        else{
           printf("\n\t\t\t\t\tYou have NO Attempt left.....\n\t\t\t\t\t\tAccess denied!\n"); 
        }
       }

    }

    return 0;
}

void displayMainMenu() {
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *              GROCERY  MANAGEMENT SYSTEM              *");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t\t\t\t1. Manage Inventory\n");
    printf("\t\t\t\t\t\t2. Process Sale\n");
    printf("\t\t\t\t\t\t3. Update Item Details\n");
    printf("\t\t\t\t\t\t4. Delete Item\n");
    printf("\t\t\t\t\t\t5. Search Item\n");
    printf("\t\t\t\t\t\t6. Sort Inventory\n");
    printf("\t\t\t\t\t\t7. Display Inventory\n");
    printf("\t\t\t\t\t\t8. Display Transaction History\n");
    printf("\t\t\t\t\t\t9. Exit\n");
}

void manageInventory() {
    char name[50];
    float price;
    int quantity;
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *              INVENTORY MANAGEMENT                    *");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    if (numItems >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more items.\n");
        return;
    }
    
    printf("Enter item details:\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Price: ");
    scanf("%f", &price);
    printf("Quantity: ");
    scanf("%d", &quantity);

    strcpy(inventory[numItems].name, name);
    inventory[numItems].price = price;
    inventory[numItems].quantity = quantity;

    numItems++;
    
    printf("\t\t\tItem added to inventory successfully.\n");
    saveInventoryToFile();
    
    
}

void process_Sale() {
    char name[50];
    int quantity;

    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *                     PROCESS SALE                     *");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\nEnter item name: ");
    scanf("%s", name);

    for (int i = 0; i < numItems; i++) {
        if (strcmp(strlwr(inventory[i].name), strlwr(name)) == 0) {
            printf("\nEnter quantity: ");
            scanf("%d", &quantity);
            if (quantity <= 0) {
                printf("Invalid quantity entered.\n");
                return;
            }
            getchar();// To catch Enter key press
        Sales sale_record;
            if (inventory[i].quantity >= quantity) {
                printf("\nEnter Costumer/Business Name: ");
                gets(sale_record.costumer_name);                
                sale_record.sales_Item.price =inventory[i].price;
                sale_record.totalamount =  inventory[i].price * quantity;
                strcpy(sale_record.sales_Item.name, inventory[i].name);
                sale_record.sales_Item.quantity = quantity;
                printf("Total amount: Rs. %.2f\n",sale_record.totalamount);
                inventory[i].quantity -= quantity;
                printf("Sale processed successfully.\n");

                saveInventoryToFile();//writing updated data to inventory file...

                SaveTransaction(sale_record);//Saving the transaction to sales_record.txt file...

                return;
            } 
            else {
                printf("Insufficient quantity in inventory.\n");
            }
            return;
        }
    }

    printf("Item not found in inventory.\n");
}


void updateInventory() {
    char name[50];
    int i;

    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *                    UPDATE INVENTORY                  *");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("Enter the name of the item to update: ");
    scanf("%s", name);

    for (i = 0; i < numItems; i++) {
        if (strcmp(strlwr(inventory[i].name), strlwr(name)) == 0) {
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Inventory updated successfully.\n");
            saveInventoryToFile();
            return;
        }
    }

    printf("Item not found in inventory.\n");
}

void deleteItem() {
    char name[50];
    int i;

    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *                      DELETE ITEM                     *");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("Enter the name of the item to delete: ");
    scanf("%s", name);

    for (i = 0; i < numItems; i++) {
        if (strcmp(strlwr(inventory[i].name), strlwr(name)) == 0) {
            printf("Item found and deleted from inventory.\n");

            // Copy the contents of the next item to the current item
            for (int j = i; j < numItems - 1; j++) {
                inventory[j] = inventory[j + 1];
            }

            numItems--;
            saveInventoryToFile();
            return;
        }
    }

    printf("Item not found in inventory.\n");
}


void searchItem() {
    char name[50];
    int i;

    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *                     SEARCH ITEM                      *");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("Enter the name of the item to search: ");
    scanf("%s", name);

    for (i = 0; i < numItems; i++) {
        if (strcmp(strlwr(inventory[i].name), strlwr(name))== 0) {
            printf("\t\t\tItem found:\n");
            printf("\t\tItem_Name: %s, Price:RS. %.2f, Quantity: %d Pcs\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
            return;
        }
    }

    printf("Item not found in inventory.\n");
}

void sortInventory() {
    Item temp;
    for (int i = 0; i < numItems - 1; i++) {
        for (int j = i + 1; j < numItems; j++) {
            if (inventory[i].price>inventory[j].price) {
                temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *              INVENTORY SORTED BY PRICE               *");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    saveInventoryToFile();
    displayInventory();

    }

        
void displayInventory() {
    loadInventoryFromFile();
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t  *                    CURRENT INVENTORY                 *\n");
    printf("\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");

    if (numItems == 0) {
        printf("Inventory is empty.\n");
    } else {
        printf("+----------------------+----------------+----------------+\n");
        printf("| %-20s | %-12s   | %-9s |\n", "Item Name", "Price", "Quantity (Pcs)");
        printf("+----------------------+----------------+----------------+\n");
        for (int i = 0; i < numItems; i++) {
            printf("| %-20s | Rs. %-9.2f  | %-13d  |\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
        }
        printf("+----------------------+----------------+----------------+\n");
    }
}



void saveInventoryToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    fwrite(&numItems, sizeof(int), 1, file);
    fwrite(inventory, sizeof(Item), numItems, file);

    fclose(file);
    printf("Inventory saved to file successfully.\n");
}

void loadInventoryFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No existing inventory file found.\n");
        return;
    }

    fread(&numItems, sizeof(int), 1, file);
    fread(inventory, sizeof(Item), numItems, file);

    fclose(file);
    
}

void DisplayTransactionHistory() {
    FILE *sale_fp = fopen("sales_record.txt", "rb"); // Open file in read mode
    if (sale_fp == NULL) {
        printf("No existing Record file found.\n");
        return;
    }

    // Declare an array of sale_record structures
    Sales sale_record[300];
    int len = 0;

    // Read sale records from file into the array and display them
    while (fread(&sale_record[len], sizeof(Sales), 1, sale_fp) == 1) {
        len++;
    }

    fclose(sale_fp);

    if (len == 0) {
        printf("No Transactions Done.\n");
    } else {
        printf("+------------------------------------------+--------------+----------------+----------------+------------------+\n");
        printf("| %-40s | %-12s | %-13s  | %-13s | %-16s |\n", "Consumer Name", "Item Name", "Price", "Quantity (Pcs)", "Sales Amount");
        printf("+------------------------------------------+--------------+----------------+----------------+------------------+\n");

        for (int i = 0; i < len; i++) {
            printf("| %-40s | %-12s | Rs. %-8.2f   | %-13d  | Rs. %-13.2f|\n", sale_record[i].costumer_name, sale_record[i].sales_Item.name,
                   sale_record[i].sales_Item.price, sale_record[i].sales_Item.quantity, sale_record[i].totalamount);
        }

        printf("+------------------------------------------+--------------+----------------+----------------+------------------+\n");
    }
}

void SaveTransaction(Sales sale_record){
    // Write sale record to sales_records.txt file
    FILE *sale_fp = fopen("sales_record.txt", "ab"); // Open file in append binary mode
    if (sale_fp == NULL) {
        printf("Error: Unable to open file for writing.\n");
            return;
                }
    fwrite(&sale_record, sizeof(Sales), 1, sale_fp); // Write the last sale record
    fclose(sale_fp); // Close the file
}

void welcomeMessage()
{
    printf("\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 GROCERY                   =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t\t Please Enter User and Password To Continue.....\n");
}

int passwordProtection() {
    char username[20];
    char password[20];
    printf("\nEnter Username: ");
    scanf("%s",username);
    printf("Enter password: ");
    scanf("%s", password);
    if((strcmp(password, PASSWORD) == 0) && (strcmp(username, USERNAME) == 0)){
        return 1; // Return true if password is correct
    }
    else {
        return 0;
    }
    
}