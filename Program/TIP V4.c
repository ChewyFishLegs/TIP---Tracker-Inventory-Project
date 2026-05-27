#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TRANSACTIONS 100
#define MAX_PROD 10
#define PROD_NAME 50
#define CAT_SIZE 20
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

struct Product_Details {
  char product_name[PROD_NAME];
  double product_weight;
  char weight_category[CAT_SIZE];
  double price;
  char quantity_category[CAT_SIZE];
  int quantity[2];
  double cost[2];
  char DateAdded[20][2];
};

typedef struct Product_Details Product_Details;

struct Categories {
  Product_Details Beverage[MAX_PROD];
  Product_Details Canned_Goods[MAX_PROD];
  Product_Details Dairy[MAX_PROD];
  Product_Details Dry_Baking_Goods[MAX_PROD];
  Product_Details Produce[MAX_PROD];
  Product_Details Cleaners[MAX_PROD];
  Product_Details Paper_Goods[MAX_PROD];
  Product_Details Personal_Care[MAX_PROD];
  Product_Details Other[MAX_PROD];
  int BeverageCount;
  int Canned_GoodsCount;
  int DairyCount;
  int Dry_Baking_GoodsCount;
  int ProduceCount;
  int CleanersCount;
  int Paper_GoodsCount;
  int Personal_CareCount;
  int OthersCount;
};
typedef struct Categories Categories;

struct JournalEntry {
  int year;
  int month;
  int day;
  char debit[50];
  char credit[50];
  double debit_amount;
  double credit_amount;
  char small_note[100];
};
typedef struct JournalEntry JournalEntry;

JournalEntry notebook[MAX_TRANSACTIONS];

const char *getMonthName(int month) {
    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    if (month >= 1 && month <= 12) {
        return months[month - 1];
    } else {
        return "Invalid month";
    }
}


void InitializeItem(Categories *categories);
void TitleScreen();
void header();
void greeter();
void main_interface();
void Display_Interface(Categories *Category);
void DisplayBeverage(Categories *Categories);
void DisplayCanned_Goods(Categories *Categories);
void DisplayDairy(Categories *Categories);
void DisplayDry_Baking_Goods(Categories *Categories);
void DisplayProduce(Categories *Categories);
void DisplayCleaners(Categories *Categories);
void DisplayPersonal_Care(Categories *Categories);
void DisplayOthers(Categories *Categories);
void DisplayPaper_Goods(Categories *Categories);
void DisplayAll(Categories *Categories);
void DisplayInterface(Categories *Category);
int SearchProduct(Product_Details *category, int count, char *Product_Name);
void Add_Product(Categories *Category, int transaction_count, JournalEntry *notebook);
void ModifyProduct(Categories *Category);
void RemoveProduct(Categories *Category);
void InputSales(Categories *Category, int transaction_count, JournalEntry *notebook);
void NoteExplainer(int quantity, char product_name[], char account_title[], char small_note[], int size);
void RecordTransaction(int iterator, int transaction_count, JournalEntry* notebook, char account_title_1[], char account_title_2[], double amount, char small_note[]);
double MerchInvCounter(Categories *Category);
void AddMoreProduct(Categories *Category, int transaction_count, JournalEntry *notebook);
void PrintAllTransactions(JournalEntry* notebook, int number_of_entries);
void LedgerGeneratorNormalDebit(JournalEntry* notebook, char AccountTitle[], int number_of_entries);
void LedgerGeneratorNormalCredit(JournalEntry* notebook, char AccountTitle[], int number_of_entries);
double IncomeStatement(Categories *Category, JournalEntry *notebook, int number_of_entries, int month, int day, int year);
double StatementofChangesinEquity(JournalEntry* notebook, int number_of_entries, int month, int day, int last_day, int year, double profit_loss, double old_capital);
double StatementOfCashFlows(JournalEntry *notebook, int number_of_entries, int month, int day, int year, double old_cash);
double BalanceCalculatorNormalDebit(JournalEntry *notebook, char AccountTitle[], int number_of_entries);
double BalanceCalculatorNormalCredit(JournalEntry *notebook, char AccountTitle[], int number_of_entries);
void BalanceSheet(Categories *Category, JournalEntry *notebook, int number_of_entries, int month, int day, int year, double new_equity);
double MerchInvCounter(Categories *Category);
void FinancialStatementsMenu();
void Ledger_menu(JournalEntry* notebook, int transaction_count);


int main(){
  int transaction_count = 0;
  Categories Item_Store[100], *ItemP;
  ItemP = Item_Store;
  JournalEntry notebook[100];
  double old_inventory = 0.00;
  old_inventory = MerchInvCounter(ItemP);
  double old_capital = 0.00;
  double old_cash = 0.00;

  InitializeItem(ItemP);
  header();
  printf("\n");
  TitleScreen();
  header();
  printf("\n\n");
  greeter();
  printf("\n");
  
  int number_of_entries = sizeof(notebook) / sizeof(notebook[0]);
  int loop = 1;

  while(loop){
    printf("\n");
    main_interface();
    int choice;
    scanf("%i", &choice);
    
    if(choice == 1){
        Display_Interface(ItemP);
    }else if(choice == 2){
        Add_Product(ItemP, transaction_count, notebook);
        transaction_count++;
    }else if(choice == 3){
        ModifyProduct(ItemP);
    }else if(choice == 4){
        char removalchoice;
        bool valid_input = false;

    do {
        printf("Are you sure you want to remove that Product? (Y/N): ");
        scanf(" %c", &removalchoice);
        removalchoice = toupper(removalchoice);
        if(removalchoice == 'Y' || removalchoice == 'N') {
            valid_input = true;
        } else {
            printf("Invalid input. Please enter 'Y' or 'N'.\n");
        }
    }while (!valid_input);
        if (removalchoice == 'Y') {
            RemoveProduct(ItemP);
            printf("Product removed successfully.\n");
        } else {
            printf("Product removal canceled.\n");
        }

    }else if(choice == 5){
        InputSales(ItemP, transaction_count, notebook);
        transaction_count++;
    }else if(choice == 6){
        AddMoreProduct(ItemP, transaction_count, notebook);
        transaction_count++;
    }else if(choice == 7){

        char debit[50], credit[50], note[50];
        double amount;
        fflush(stdin);
        printf("Enter the debit account title: ");
        scanf( " %[^\n]s", debit);
        printf("Enter the credit account title: ");
        scanf( " %[^\n]s", credit);
        printf("Enter the note: ");
        scanf( " %[^\n]s", note);
        printf("Enter the amount: ");
        scanf("%lf", &amount);
        RecordTransaction(1, transaction_count, notebook, debit, credit, amount, note);
        transaction_count++;

    }else if(choice == 8){

        PrintAllTransactions(notebook, transaction_count);

    }else if(choice == 9){

        Ledger_menu(notebook, transaction_count);

    }else if(choice == 10){

        if(MerchInvCounter(ItemP)==0.00){
            RecordTransaction(1, transaction_count, notebook, "Merchandise Inventory", "Income Summary", MerchInvCounter(ItemP), "To record ending inventory");
            transaction_count++;
        }else if(MerchInvCounter(ItemP) > 0.00){
            RecordTransaction(1, transaction_count, notebook, "Income Summary", "Merchandise Inventory", old_inventory, "To remove beginning inventory");
            transaction_count++;
            RecordTransaction(1, transaction_count, notebook, "Merchandise Inventory", "Income Summary", MerchInvCounter(ItemP), "To record ending inventory");
            transaction_count++;
            old_inventory = MerchInvCounter(ItemP);
        }

        //while loop
        double profit_loss = 0;
        double new_equity = 0;
        double new_cash = 0;

        time_t currentTime;
        time(&currentTime);
        struct tm *localTime = localtime(&currentTime);

        while(choice){

        FinancialStatementsMenu();
        int choice = 0;
        scanf("%d", &choice);

            if(choice == 1){

                time_t currentTime;
                time(&currentTime);
                struct tm *localTime = localtime(&currentTime);
                double ending_inventory = 0;

                profit_loss = IncomeStatement(ItemP, notebook, transaction_count, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_year + 1900);
                
            }else if(choice == 2){

                int last_day=0;
                printf("When is the last day for this month?\n");
                scanf("%d", &last_day);

                new_equity = StatementofChangesinEquity(notebook, transaction_count, localTime->tm_mon + 1, localTime->tm_mday, last_day, localTime->tm_year + 1900, profit_loss, old_capital);
                old_capital = BalanceCalculatorNormalCredit(notebook, "Nena, Capital", transaction_count);

            }else if(choice == 3){

                BalanceSheet(ItemP, notebook, transaction_count, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_year + 1900, new_equity);

            }else if(choice == 4){

                new_cash = StatementOfCashFlows(notebook, transaction_count, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_year + 1900, old_cash);
                old_cash = new_cash;

            }else if(choice == 5){

                double sales_amount = BalanceCalculatorNormalCredit(notebook, "Sales", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Sales", "Income Summary", sales_amount, "To close nominal income accounts");
                transaction_count++;

                double sales_ra = BalanceCalculatorNormalDebit(notebook, "Sales Returns and Allowances", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Sales Returns and Allowances", sales_ra, "To close nominal income accounts");
                transaction_count++;

                double sales_discounts = BalanceCalculatorNormalDebit(notebook, "Sales Discounts", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Sales Discounts", sales_discounts, "To close nominal income accounts");
                transaction_count++;

                double purchase_ra = BalanceCalculatorNormalCredit(notebook, "Purchase Returns and ALlowances", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Purchase Returns and Allowances", "Income Summary", purchase_ra, "To close nominal expense accounts");
                transaction_count++;

                double purchase_discounts = BalanceCalculatorNormalCredit(notebook, "Purchase Discounts", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Purchase Discounts", "Income Summary", purchase_discounts, "To close nominal expense accounts");
                transaction_count++;

                double purchases = BalanceCalculatorNormalDebit(notebook, "Purchases", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Purchases", purchases, "To close nominal expense accounts");
                transaction_count++;

                double trans_in = BalanceCalculatorNormalDebit(notebook, "Transportation In", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Transportation In", trans_in, "To close nominal expense accounts");
                transaction_count++;

                double miscellaneous_exp = BalanceCalculatorNormalDebit(notebook, "Miscellaneous Expense", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Miscellaneous Expense", miscellaneous_exp, "To close nominal expense accounts");
                transaction_count++;

                double supplies_exp = BalanceCalculatorNormalDebit(notebook, "Supplies Expense", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Supplies Expense", supplies_exp, "To close nominal expense accounts");
                transaction_count++;

                double utility_exp = BalanceCalculatorNormalDebit(notebook, "Utility Expense", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Utility Expense", supplies_exp, "To close nominal expense accounts");
                transaction_count++;

                double dep_exp_building = BalanceCalculatorNormalDebit(notebook, "Depreciation Expense - Building", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Depreciation Expense - Building", dep_exp_building, "To close nominal expense accounts");
                transaction_count++;

                double dep_exp_equip = BalanceCalculatorNormalDebit(notebook, "Depreciation Expense - Equipment", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Income Summary", "Depreciation Expense - Equipment", dep_exp_equip, "To close nominal expense accounts");
                transaction_count++;

                    if(profit_loss < 0.00){
                        profit_loss = profit_loss * -1;
                        RecordTransaction(1, transaction_count, notebook, "Nena, Capital", "Income Summary", profit_loss, "To close net loss");
                        transaction_count++;
                    }else if(profit_loss > 0.00){
                        RecordTransaction(1, transaction_count, notebook, "Income Summary", "Nena, Capital", profit_loss, "To close net profit");
                        transaction_count++;
                    }

                double withdrawals = BalanceCalculatorNormalDebit(notebook, "Nena, Withdrawals", transaction_count);
                RecordTransaction(1, transaction_count, notebook, "Nena, Capital", "Nena, Withdrawals", withdrawals, "To close drawings");
                transaction_count++;
                printf("%.2lf", MerchInvCounter(ItemP));

                break;

            }else if(choice == 6){
                break;
            }

        }

    }else if(choice == 11){
        loop = 0;
    }

  }

  return 0;

}

void RemoveProduct(Categories *Category) {
    FILE *file, *temp;
    int category_choice;
    char category_name[50];
    char filename[] = "products.txt";
    char temp_filename[] = "temp.txt";
    char target_product[100];

    printf("\nSelect a Category to Remove Product\n");
    printf("1. Beverages\n");
    printf("2. Canned Goods\n");
    printf("3. Dairy\n");
    printf("4. Dry Baking Goods\n");
    printf("5. Produce\n");
    printf("6. Cleaners\n");
    printf("7. Paper Goods\n");
    printf("8. Personal Care\n");
    printf("9. Others\n");

    printf("Option: ");
    scanf("%d", &category_choice);

    switch (category_choice) {
        case 1:
            strcpy(category_name, "Beverage");
            break;
        case 2:
            strcpy(category_name, "Canned_Goods");
            break;
        case 3:
            strcpy(category_name, "Dairy");
            break;
        case 4:
            strcpy(category_name, "Dry_Baking_Goods");
            break;
        case 5:
            strcpy(category_name, "Produce");
            break;
        case 6:
            strcpy(category_name, "Cleaners");
            break;
        case 7:
            strcpy(category_name, "Paper_Goods");
            break;
        case 8:
            strcpy(category_name, "Personal_Care");
            break;
        case 9:
            strcpy(category_name, "Other");
            break;
        default:
            printf("Invalid option.\n");
            return;
    }

    printf("Enter the Product Name to Remove: ");
    scanf(" %[^\n]", target_product);

    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file(s)\n");
        return;
    }

    bool product_found = false;
    char line[2048];

    while (fgets(line, sizeof(line), file) != NULL) {
        char current_category[50];
        char product_name[100]; // Assuming product names won't exceed 100 characters

        // Parse the line to get the category and product name
        sscanf(line, "%[^|]|%[^|]", current_category, product_name);

        if (strcmp(current_category, category_name) == 0 && strcmp(product_name, target_product) == 0) {
            product_found = true;
            continue; // Skip writing this product to temp file
        }
        fputs(line, temp);
    }

    fclose(file);
    fclose(temp);

    if (!product_found) {
        printf("Product \"%s\" not found in category: %s\n", target_product, category_name);
        remove(temp_filename); // Remove the temporary file if product not found
    } else {
        remove(filename);
        rename(temp_filename, filename);
        printf("Product \"%s\" removed successfully\n", target_product);

        // Update the corresponding category array in memory
        switch (category_choice) {
            case 1:
                for (int i = 0; i < Category->BeverageCount; i++) {
                    if (strcmp(Category->Beverage[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->BeverageCount - 1; j++) {
                            Category->Beverage[j] = Category->Beverage[j + 1];
                        }
                        Category->BeverageCount--;
                        break;
                    }
                }
                break;
            case 2:
                for (int i = 0; i < Category->Canned_GoodsCount; i++) {
                    if (strcmp(Category->Canned_Goods[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->Canned_GoodsCount - 1; j++) {
                            Category->Canned_Goods[j] = Category->Canned_Goods[j + 1];
                        }
                        Category->Canned_GoodsCount--;
                        break;
                    }
                }
                break;
            case 3:
                for (int i = 0; i < Category->DairyCount; i++) {
                    if (strcmp(Category->Dairy[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->DairyCount - 1; j++) {
                            Category->Dairy[j] = Category->Dairy[j + 1];
                        }
                        Category->DairyCount--;
                        break;
                    }
                }
                break;
            case 4:
                for (int i = 0; i < Category->Dry_Baking_GoodsCount; i++) {
                    if (strcmp(Category->Dry_Baking_Goods[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->Dry_Baking_GoodsCount - 1; j++) {
                            Category->Dry_Baking_Goods[j] = Category->Dry_Baking_Goods[j + 1];
                        }
                        Category->Dry_Baking_GoodsCount--;
                        break;
                    }
                }
                break;
            case 5:
                for (int i = 0; i < Category->ProduceCount; i++) {
                    if (strcmp(Category->Produce[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->ProduceCount - 1; j++) {
                            Category->Produce[j] = Category->Produce[j + 1];
                        }
                        Category->ProduceCount--;
                        break;
                    }
                }
                break;
            case 6:
                for (int i = 0; i < Category->CleanersCount; i++) {
                    if (strcmp(Category->Cleaners[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->CleanersCount - 1; j++) {
                            Category->Cleaners[j] = Category->Cleaners[j + 1];
                        }
                        Category->CleanersCount--;
                        break;
                    }
                }
                break;
            case 7:
                for (int i = 0; i < Category->Paper_GoodsCount; i++) {
                    if (strcmp(Category->Paper_Goods[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->Paper_GoodsCount - 1; j++) {
                            Category->Paper_Goods[j] = Category->Paper_Goods[j + 1];
                        }
                        Category->Paper_GoodsCount--;
                        break;
                    }
                }
                break;
            case 8:
                for (int i = 0; i < Category->Personal_CareCount; i++) {
                    if (strcmp(Category->Personal_Care[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->Personal_CareCount - 1; j++) {
                            Category->Personal_Care[j] = Category->Personal_Care[j + 1];
                        }
                        Category->Personal_CareCount--;
                        break;
                    }
                }
                break;
            case 9:
                for (int i = 0; i < Category->OthersCount; i++) {
                    if (strcmp(Category->Other[i].product_name, target_product) == 0) {
                        for (int j = i; j < Category->OthersCount - 1; j++) {
                            Category->Other[j] = Category->Other[j + 1];
                        }
                        Category->OthersCount--;
                        break;
                    }
                }
                break;                                                                
        }
    }
}

void InitializeItem(Categories *categories) {
  FILE *file = fopen("products.txt", "r");
  if (!file) {
    perror("Failed to open file");
    exit(1);
  }

  char line[2048];
  while (fgets(line, sizeof(line), file)) {
    Product_Details product;
    char category[50];
    sscanf(line, "%[^|]|%[^|]|%lf|%[^|]|%lf|%[^|]|%d|%lf", category,
           product.product_name, &product.price, product.weight_category,
           &product.product_weight, product.quantity_category,
           &product.quantity[0],&product.cost[0]);

    if (strcmp(category, "Beverage") == 0) {
      categories->Beverage[categories->BeverageCount++] = product;
    } else if (strcmp(category, "Canned_Goods") == 0) {
      categories->Canned_Goods[categories->Canned_GoodsCount++] = product;
    } else if (strcmp(category, "Dairy") == 0) {
      categories->Dairy[categories->DairyCount++] = product;
    } else if (strcmp(category, "Dry_Baking_Goods") == 0) {
      categories->Dry_Baking_Goods[categories->Dry_Baking_GoodsCount++] =
          product;
    } else if (strcmp(category, "Produce") == 0) {
      categories->Produce[categories->ProduceCount++] = product;
    } else if (strcmp(category, "Cleaners") == 0) {
      categories->Cleaners[categories->CleanersCount++] = product;
    } else if (strcmp(category, "Paper_Goods") == 0) {
      categories->Paper_Goods[categories->Paper_GoodsCount++] = product;
    } else if (strcmp(category, "Personal_Care") == 0) {
      categories->Personal_Care[categories->Personal_CareCount++] = product;
    } else if (strcmp(category, "Other") == 0) {
      categories->Other[categories->OthersCount++] = product;
    }
  }

  fclose(file);
}

void TitleScreen() {
  char String[40] = "                ";
  printf("%s////////////    ///     ////////////\n", String);
  printf("%s    ///         ///     ///      //\n", String);
  printf("%s    ///         ///     ///      //\n", String);
  printf("%s    ///         ///     /////////\n", String);
  printf("%s    ///         ///     ///      \n", String);
  printf("%s    ///         ///     ///      \n", String);
}

void header() {
  int len = strlen("  ////         //////   ///      ");
  for (int i = 0; i < 2 * len; i++) {
    printf("-");
  }
}

void greeter() {
  for (int i = 0; i < 25; i++)
    printf(" ");
  printf("WELCOME USER!");
  for (int i = 0; i < 30; i++)
    printf(" ");
}

void main_interface() {
  printf("1. Display Products\n");
  printf("2. Add Products\n");
  printf("3. Modify Product Detail\n");
  printf("4. Remove a Product\n");
  printf("5. Input Sales\n");
  printf("6. Add Existing Product Quantity\n");
  printf("7. Record a Transaction\n");
  printf("8. Print All Transactions\n");
  printf("9. Generate Ledger\n");
  printf("10. Generate Financial Statements and Close Nominal Accounts\n");
  printf("11. Exit\n");
  printf("Input: ");
}

void Display_Interface(Categories *Category) {
  int loop = 1, choice;
  while (loop) {
    printf("\nDisplay Interface\n");
    printf("1. Beverages\n");
    printf("2. Canned Goods\n");
    printf("3. Dairy\n");
    printf("4. Dry Baking Goods\n");
    printf("5. Produce\n");
    printf("6. Cleaners\n");
    printf("7. Paper Goods\n");
    printf("8. Personal Care\n");
    printf("9. Others\n");
    printf("10. All\n");
    printf("11. Exit\n");
    printf("Input: ");
    scanf("%i", &choice);
    switch (choice) {
    case 1:
      DisplayBeverage(Category);
      break;
    case 2:
      DisplayCanned_Goods(Category);
      break;
    case 3:
      DisplayDairy(Category);
      break;
    case 4:
      DisplayDry_Baking_Goods(Category);
      break;
    case 5:
      DisplayProduce(Category);
      break;
    case 6:
      DisplayCleaners(Category);
      break;
    case 7:
      DisplayPaper_Goods(Category);
      break;
    case 8:
      DisplayPersonal_Care(Category);
      break;
    case 9:
      DisplayOthers(Category);
      break;
    case 10:
      DisplayAll(Category);
      break;
    case 11:
      loop = 0;
      break;
    default:
      break;
    }
  }
}

void DisplayBeverage(Categories *Categories) {
  printf("\nBeverages\n");
  for (int i = 0; i < Categories->BeverageCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Beverage[i].product_name);
    printf("Price: %.2f\n", Categories->Beverage[i].price);
    printf("Quantity: %i\n", Categories->Beverage[i].quantity[0]);
  }
}

void DisplayCanned_Goods(Categories *Categories) {
  printf("\nCanned Goods\n");
  for (int i = 0; i < Categories->Canned_GoodsCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Canned_Goods[i].product_name);
    printf("Price: %.2f\n", Categories->Canned_Goods[i].price);
    printf("Quantity: %i\n", Categories->Canned_Goods[i].quantity[0]);
  }
}

void DisplayDairy(Categories *Categories) {
  printf("\nDairy\n");
  for (int i = 0; i < Categories->DairyCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Dairy[i].product_name);
    printf("Price: %.2f\n", Categories->Dairy[i].price);
    printf("Quantity: %i\n", Categories->Dairy[i].quantity[0]);
  }
}

void DisplayDry_Baking_Goods(Categories *Categories) {
  printf("\nDry Baking Goods\n");
  for (int i = 0; i < Categories->Dry_Baking_GoodsCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Dry_Baking_Goods[i].product_name);
    printf("Price: %.2f\n", Categories->Dry_Baking_Goods[i].price);
    printf("Quantity: %i\n", Categories->Dry_Baking_Goods[i].quantity[0]);
  }
}

void DisplayProduce(Categories *Categories) {
  printf("\nProduce\n");
  for (int i = 0; i < Categories->ProduceCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Produce[i].product_name);
    printf("Price: %.2f\n", Categories->Produce[i].price);
    printf("Quantity: %i\n", Categories->Produce[i].quantity[0]);
  }
}

void DisplayCleaners(Categories *Categories) {
  printf("\nCleaners\n");
  for (int i = 0; i < Categories->CleanersCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Cleaners[i].product_name);
    printf("Price: %.2f\n", Categories->Cleaners[i].price);
    printf("Quantity: %i\n", Categories->Cleaners[i].quantity[0]);
  }
}

void DisplayPaper_Goods(Categories *Categories) {
  printf("\nPaper Goods\n");
  for (int i = 0; i < Categories->Paper_GoodsCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Paper_Goods[i].product_name);
    printf("Price: %.2f\n", Categories->Paper_Goods[i].price);
    printf("Quantity: %i\n", Categories->Paper_Goods[i].quantity[0]);
  }
}

void DisplayPersonal_Care(Categories *Categories) {
  printf("\nPersonal Care\n");
  for (int i = 0; i < Categories->Personal_CareCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Personal_Care[i].product_name);
    printf("Price: %.2f\n", Categories->Personal_Care[i].price);
    printf("Quantity: %i\n", Categories->Personal_Care[i].quantity[0]);
  }
}

void DisplayOthers(Categories *Categories) {
  printf("\nOthers\n");
  for (int i = 0; i < Categories->OthersCount; i++) {
    printf("\nItem %i\n", i + 1);
    printf("%s\n", Categories->Other[i].product_name);
    printf("Price: %.2f\n", Categories->Other[i].price);
    printf("Quantity: %i\n", Categories->Other[i].quantity[0]);
  }
}

void DisplayAll(Categories *Categories) {
  DisplayBeverage(Categories);
  DisplayCanned_Goods(Categories);
  DisplayDairy(Categories);
  DisplayDry_Baking_Goods(Categories);
  DisplayProduce(Categories);
  DisplayCleaners(Categories);
  DisplayPaper_Goods(Categories);
  DisplayPersonal_Care(Categories);
  DisplayOthers(Categories);
}

void Add_Product(Categories *Category, int transaction_count, JournalEntry *notebook) {
  int i = 0;
  int option, option2;
  Product_Details new_product;
  char category_name[20];

  printf("\nSelect a Category for the New Product\n");
  printf("1. Beverages\n");
  printf("2. Canned Goods\n");
  printf("3. Dairy\n");
  printf("4. Dry Baking Goods\n");
  printf("5. Produce\n");
  printf("6. Cleaners\n");
  printf("7. Paper Goods\n");
  printf("8. Personal Care\n");
  printf("9. Others\n");
  printf("10. Cancel\n");

  printf("Option: ");
  scanf("%d", &option);
  option2 = option;

    if (option == 10) {
        printf("Addition canceled.\n");
        return;
    }

  switch (option) {
  case 1:
    for (; i < MAX_PROD && strlen(Category->Beverage[i].product_name) != 0; i++)
      ; // Find the index where the product name is empty
    strcpy(category_name, "Beverage");
    break;
  case 2:
    for (; i < MAX_PROD && strlen(Category->Canned_Goods[i].product_name) != 0;
         i++)
      ;
    strcpy(category_name, "Canned_Goods");
    break;
  case 3:
    for (; i < MAX_PROD && strlen(Category->Dairy[i].product_name) != 0; i++)
      ;
    strcpy(category_name, "Dairy");
    break;
  case 4:
    for (; i < MAX_PROD &&
           strlen(Category->Dry_Baking_Goods[i].product_name) != 0;
         i++)
      ;
    strcpy(category_name, "Dry_Baking_Goods");
    break;
  case 5:
    for (; i < MAX_PROD && strlen(Category->Produce[i].product_name) != 0; i++)
      ;
    strcpy(category_name, "Produce");
    break;
  case 6:
    for (; i < MAX_PROD && strlen(Category->Cleaners[i].product_name) != 0; i++)
      ;
    strcpy(category_name, "Cleaners");
    break;
  case 7:
    for (; i < MAX_PROD && strlen(Category->Paper_Goods[i].product_name) != 0;
         i++)
      ;
    strcpy(category_name, "Paper_Goods");
    break;
  case 8:
    for (; i < MAX_PROD && strlen(Category->Personal_Care[i].product_name) != 0;
         i++)
      ;
    strcpy(category_name, "Personal_Care");
    break;
  case 9:
    for (; i < MAX_PROD && strlen(Category->Other[i].product_name) != 0; i++)
      ;
    strcpy(category_name, "Other");
    break;
  }

  if (i < MAX_PROD) {
    printf("Enter New Product Name: ");
    scanf(" %[^\n]s", new_product.product_name);
    printf("Enter Product Price: ");
    scanf("%lf", &new_product.price);
    printf("Enter Product Weight: ");
    scanf("%lf", &new_product.product_weight);
    printf("Enter Weight Category: ");
    scanf(" %[^\n]s", new_product.weight_category);
    printf("Enter Product Quantity: ");
    scanf("%d", &new_product.quantity[0]);
    printf("Enter Quantity Category: ");
    scanf(" %[^\n]s", new_product.quantity_category);
    printf("Enter Cost: ");
    scanf("%lf", &new_product.cost[0]);
    
    double amount = 0;
    double cost = new_product.cost[0];
    char small_note[20];
    
    // Update "products.txt" file with the new product details
    FILE *file = fopen("products.txt", "a");
    if (file != NULL) {
      fprintf(file, "%s|%s|%.2f|%s|%.2f|%s|%d|%.2lf\n", category_name, //Update: I modified the lf or double variable to contain merely 2 decimals para dili hugaw tanawn sa product.txt
        new_product.product_name, new_product.price,
        new_product.weight_category, new_product.product_weight,
        new_product.quantity_category, new_product.quantity[0],
        new_product.cost[0]);
      fclose(file);
    } else {
      printf("Error opening file.\n");
    }

    // Update the appropriate category array within the Categories struct with
    // the new product
    switch (option2) {
    case 1:
      Category->Beverage[i] = new_product;
        amount = cost * Category->Beverage[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Beverage[i].quantity[0], Category->Beverage[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->BeverageCount++; //Adds the Beverage Count so that mu-display ang new product after it is freshly added
      break;
    case 2:
      Category->Canned_Goods[i] = new_product;
        amount = cost * Category->Canned_Goods[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Canned_Goods[i].quantity[0], Category->Canned_Goods[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->Canned_GoodsCount++; //Adds the Canned Goods Count so that mu-display ang new product after it is freshly added
      break;
    case 3:
      Category->Dairy[i] = new_product;
        amount = cost * Category->Dairy[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Dairy[i].quantity[0], Category->Dairy[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->DairyCount++; //Adds the Dairy Count so that mu-display ang new product after it is freshly added
      break;
    case 4:
      Category->Dry_Baking_Goods[i] = new_product;
        amount = cost * Category->Dry_Baking_Goods[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Dry_Baking_Goods[i].quantity[0], Category->Dry_Baking_Goods[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->Dry_Baking_GoodsCount++; //Adds the Canned Goods Count so that mu-display ang new product after it is freshly added
      break;
    case 5:
      Category->Produce[i] = new_product;
        amount = cost * Category->Produce[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Produce[i].quantity[0], Category->Produce[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->ProduceCount++; //Adds the Produce Count so that mu-display ang new product after it is freshly added
      break;
    case 6:
      Category->Cleaners[i] = new_product;
        amount = cost * Category->Cleaners[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Cleaners[i].quantity[0], Category->Cleaners[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->CleanersCount++; //Adds the Cleaners Count so that mu-display ang new product after it is freshly added
      break;
    case 7:
      Category->Paper_Goods[i] = new_product;
        amount = cost * Category->Paper_Goods[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Paper_Goods[i].quantity[0], Category->Paper_Goods[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->Paper_GoodsCount++; // Adds the Paper Goods Count so that mu-display ang new product after it is freshly added
      break;
    case 8:
      Category->Personal_Care[i] = new_product;
        amount = cost * Category->Personal_Care[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Personal_Care[i].quantity[0], Category->Personal_Care[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->Personal_CareCount++; //Adds the Others count to ensure nga ma-display ang new product on the category
      break;
    case 9:
      Category->Other[i] = new_product;
        amount = cost * Category->Other[i].quantity[0]; //to be added ang cost function
        NoteExplainer(Category->Other[i].quantity[0], Category->Other[i].product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);
        Category->OthersCount++;
      break;
    }
    printf("New product added successfully.\n");
  } else {
    printf("Category is full. Cannot add new product.\n");
  }
}

void ModifyProduct(Categories *Category) {
    int option, category_choice, index;
    char category_name[20];
    char product_name[PROD_NAME];

    printf("\nSelect a Category to Modify the Product\n");
    printf("1. Beverages\n");
    printf("2. Canned Goods\n");
    printf("3. Dairy\n");
    printf("4. Dry Baking Goods\n");
    printf("5. Produce\n");
    printf("6. Cleaners\n");
    printf("7. Paper Goods\n");
    printf("8. Personal Care\n");
    printf("9. Others\n");
    printf("10. Cancel\n");

    printf("Option: ");
    scanf("%d", &category_choice);

    if (category_choice == 10) {
        printf("Modification canceled.\n");
        return;
    }

    switch (category_choice) {
    case 1:
        strcpy(category_name, "Beverage");
        break;
    case 2:
        strcpy(category_name, "Canned_Goods");
        break;
    case 3:
        strcpy(category_name, "Dairy");
        break;
    case 4:
        strcpy(category_name, "Dry_Baking_Goods");
        break;
    case 5:
        strcpy(category_name, "Produce");
        break;
    case 6:
        strcpy(category_name, "Cleaners");
        break;
    case 7:
        strcpy(category_name, "Paper_Goods");
        break;
    case 8:
        strcpy(category_name, "Personal_Care");
        break;
    case 9:
        strcpy(category_name, "Other");
        break;
    default:
        printf("Invalid option.\n");
        return;
    }

    printf("Enter the Product Name to Modify: ");
    scanf(" %[^\n]s", product_name);

    switch (category_choice) {
    case 1:
        index = SearchProduct(Category->Beverage, Category->BeverageCount, product_name);
        break;
    case 2:
        index = SearchProduct(Category->Canned_Goods, Category->Canned_GoodsCount, product_name);
        break;
    case 3:
        index = SearchProduct(Category->Dairy, Category->DairyCount, product_name);
        break;
    case 4:
        index = SearchProduct(Category->Dry_Baking_Goods, Category->Dry_Baking_GoodsCount, product_name);
        break;
    case 5:
        index = SearchProduct(Category->Produce, Category->ProduceCount, product_name);
        break;
    case 6:
        index = SearchProduct(Category->Cleaners, Category->CleanersCount, product_name);
        break;
    case 7:
        index = SearchProduct(Category->Paper_Goods, Category->Paper_GoodsCount, product_name);
        break;
    case 8:
        index = SearchProduct(Category->Personal_Care, Category->Personal_CareCount, product_name);
        break;
    case 9:
        index = SearchProduct(Category->Other, Category->OthersCount, product_name);
        break;
    default:
        printf("Invalid option.\n");
        return;
    }

    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    Product_Details *product;
    switch (category_choice) {
    case 1:
        product = &Category->Beverage[index];
        break;
    case 2:
        product = &Category->Canned_Goods[index];
        break;
    case 3:
        product = &Category->Dairy[index];
        break;
    case 4:
        product = &Category->Dry_Baking_Goods[index];
        break;
    case 5:
        product = &Category->Produce[index];
        break;
    case 6:
        product = &Category->Cleaners[index];
        break;
    case 7:
        product = &Category->Paper_Goods[index];
        break;
    case 8:
        product = &Category->Personal_Care[index];
        break;
    case 9:
        product = &Category->Other[index];
        break;
    }
    
    //current details
    char current_name[PROD_NAME];
    double current_price = product->price;
    double current_weight = product->product_weight;
    char current_weightcat[20];
    int current_quantity = product->quantity[0];
    char current_quantitycat[20];
    strcpy(current_name, product->product_name);
    strcpy(current_weightcat, product->weight_category);
    strcpy(current_quantitycat, product->quantity_category);

    printf("Select the Detail to Modify:\n");
    printf("1. Product Name\n");
    printf("2. Price\n");
    printf("3. Product Weight\n");
    printf("4. Weight Category\n");
    printf("5. Quantity\n");
    printf("6. Quantity Category\n");
    printf("7. Cancel\n");    
    printf("Option: ");
    scanf("%d", &option);

    if (option == 7) {
        printf("Modification canceled.\n");
        return;
    }

    switch (option) {
    case 1:
        printf("Enter New Product Name (%s): ", current_name);
        scanf(" %[^\n]s", product->product_name);
        break;
    case 2:
        printf("Enter New Product Price (%.2f): ", current_price);
        scanf("%lf", &product->price);
        break;
    case 3:
        printf("Enter New Product Weight (%.2f): ", current_weight);
        scanf("%lf", &product->product_weight);
        break;
    case 4:
        printf("Enter New Weight Category (%s): ", current_weightcat);
        scanf(" %[^\n]s", product->weight_category);
        break;
    case 5:
        printf("Enter New Product Quantity (%d): ", current_quantity);
        scanf("%d", &product->quantity[0]);
        break;
    case 6:
        printf("Enter New Quantity Category (%s): ", current_quantitycat);
        scanf(" %[^\n]s", product->quantity_category);
        break;
    default:
        printf("Invalid option.\n");
        return;
    }

    printf("Product modified successfully.\n");

    // Update file
    FILE *file = fopen("products.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[2048];
    long pos;
    while (fgets(line, sizeof(line), file)) {
        pos = ftell(file);
        char file_category[50], file_name[PROD_NAME];
        sscanf(line, "%[^|]|%[^|]", file_category, file_name);
        if (strcmp(file_category, category_name) == 0 && strcmp(file_name, product_name) == 0) {
            fseek(file, pos - strlen(line) - 1, SEEK_SET);
            fprintf(file, "%s|%s|%.2f|%s|%.2f|%s|%d|%.2lf\n", category_name,
                    product->product_name, product->price, product->weight_category,
                    product->product_weight, product->quantity_category,
                    product->quantity[0], product->cost[0]);
            break;
        }
    }

    fclose(file);
}

int SearchProduct(Product_Details *category, int count, char *Product_Name) {
  for (int i = 0; i < count; i++) {
    if (strcmp(category[i].product_name, Product_Name) == 0) {
      return i;
    }
  }
  return -1;
}

void InputSales(Categories *Category, int transaction_count, JournalEntry *notebook) {
    char product_name[PROD_NAME];
    int category_choice, index;
    int quantity_sold;

    printf("\nSelect a Category for the Product Sale\n");
    printf("1. Beverages\n");
    printf("2. Canned Goods\n");
    printf("3. Dairy\n");
    printf("4. Dry Baking Goods\n");
    printf("5. Produce\n");
    printf("6. Cleaners\n");
    printf("7. Paper Goods\n");
    printf("8. Personal Care\n");
    printf("9. Others\n");
    printf("10. Cancel\n");
    printf("Input: ");
    scanf("%d", &category_choice);

    if (category_choice == 10) {
        printf("Sale input canceled.\n");
        return;
    }

    printf("Enter Product Name: ");
    scanf(" %[^\n]s", product_name);

    char category_name[20];
    switch(category_choice) {
    case 1:
        strcpy(category_name, "Beverage");
        index = SearchProduct(Category->Beverage, Category->BeverageCount, product_name);
        break;
    case 2:
        strcpy(category_name, "Canned_Goods");
        index = SearchProduct(Category->Canned_Goods, Category->Canned_GoodsCount, product_name);
        break;
    case 3:
        strcpy(category_name, "Dairy");
        index = SearchProduct(Category->Dairy, Category->DairyCount, product_name);
        break;
    case 4:
        strcpy(category_name, "Dry_Baking_Goods");
        index = SearchProduct(Category->Dry_Baking_Goods, Category->Dry_Baking_GoodsCount, product_name);
        break;
    case 5:
        strcpy(category_name, "Produce");
        index = SearchProduct(Category->Produce, Category->ProduceCount, product_name);
        break;
    case 6:
        strcpy(category_name, "Cleaners");
        index = SearchProduct(Category->Cleaners, Category->CleanersCount, product_name);
        break;
    case 7:
        strcpy(category_name, "Paper_Goods");
        index = SearchProduct(Category->Paper_Goods, Category->Paper_GoodsCount, product_name);
        break;
    case 8:
        strcpy(category_name, "Personal_Care");
        index = SearchProduct(Category->Personal_Care, Category->Personal_CareCount, product_name);
        break;
    case 9:
        strcpy(category_name, "Other");
        index = SearchProduct(Category->Other, Category->OthersCount, product_name);
        break;
    default:
        printf("Invalid category choice.\n");
        return;
    }

    if(index == -1) {
        printf("Product not found.\n");
    } else {
        Product_Details *product;

        switch(category_choice) {
        case 1:
            product = &Category->Beverage[index];
            break;
        case 2:
            product = &Category->Canned_Goods[index];
            break;
        case 3:
            product = &Category->Dairy[index];
            break;
        case 4:
            product = &Category->Dry_Baking_Goods[index];
            break;
        case 5:
            product = &Category->Produce[index];
            break;
        case 6:
            product = &Category->Cleaners[index];
            break;
        case 7:
            product = &Category->Paper_Goods[index];
            break;
        case 8:
            product = &Category->Personal_Care[index];
            break;
        case 9:
            product = &Category->Other[index];
            break;
        }

        int available_quantity = product->quantity[0];

        do{
            printf("Enter Quantity Sold (%d %s available): ", available_quantity, product->quantity_category);
            scanf("%d", &quantity_sold);

            if (quantity_sold > available_quantity) {
                printf("Invalid quantity. The quantity sold cannot exceed the available quantity.\n");
            }
            else if(quantity_sold < 0){
                printf("Enter a positive integer.\n");
            }

        } while (quantity_sold > available_quantity || quantity_sold < 0);

        product->quantity[0] -= quantity_sold;
        double amount = quantity_sold * product->price;
        char small_note[100];
        NoteExplainer(quantity_sold, product->product_name, "Sales", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Cash", "Sales", amount, small_note);

        // Update file quantity
    FILE *file = fopen("products.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[2048];
    long pos;
    while (fgets(line, sizeof(line), file)) {
        pos = ftell(file);
        char file_category[50], file_name[PROD_NAME];
        sscanf(line, "%[^|]|%[^|]", file_category, file_name);
        if (strcmp(file_category, category_name) == 0 && strcmp(file_name, product_name) == 0) {
            fseek(file, pos - strlen(line) - 1, SEEK_SET);
            fprintf(file, "%s|%s|%.2f|%s|%.2f|%s|%d|%.2lf\n", category_name,
                    product->product_name, product->price, product->weight_category,
                    product->product_weight, product->quantity_category,
                    product->quantity[0], product->cost[0]);
            break;
        }
    }

    fclose(file);
    printf("Sales input successfully.\n");
    }
}

void AddMoreProduct(Categories *Category, int transaction_count, JournalEntry *notebook) {
    char product_name[PROD_NAME];
    int category_choice, index;
    int quantity_added;

    printf("\nSelect a Category to add for the existing product\n");
    printf("1. Beverages\n");
    printf("2. Canned Goods\n");
    printf("3. Dairy\n");
    printf("4. Dry Baking Goods\n");
    printf("5. Produce\n");
    printf("6. Cleaners\n");
    printf("7. Paper Goods\n");
    printf("8. Personal Care\n");
    printf("9. Others\n");
    printf("10. Cancel\n");
    printf("Input: ");
    scanf("%d", &category_choice);

    if (category_choice == 10) {
        printf("Sale input canceled.\n");
        return;
    }

    printf("Enter Product Name: ");
    scanf(" %[^\n]s", product_name);

    char category_name[20];
    switch(category_choice) {
    case 1:
        strcpy(category_name, "Beverage");
        index = SearchProduct(Category->Beverage, Category->BeverageCount, product_name);
        break;
    case 2:
        strcpy(category_name, "Canned_Goods");
        index = SearchProduct(Category->Canned_Goods, Category->Canned_GoodsCount, product_name);
        break;
    case 3:
        strcpy(category_name, "Dairy");
        index = SearchProduct(Category->Dairy, Category->DairyCount, product_name);
        break;
    case 4:
        strcpy(category_name, "Dry_Baking_Goods");
        index = SearchProduct(Category->Dry_Baking_Goods, Category->Dry_Baking_GoodsCount, product_name);
        break;
    case 5:
        strcpy(category_name, "Produce");
        index = SearchProduct(Category->Produce, Category->ProduceCount, product_name);
        break;
    case 6:
        strcpy(category_name, "Cleaners");
        index = SearchProduct(Category->Cleaners, Category->CleanersCount, product_name);
        break;
    case 7:
        strcpy(category_name, "Paper_Goods");
        index = SearchProduct(Category->Paper_Goods, Category->Paper_GoodsCount, product_name);
        break;
    case 8:
        strcpy(category_name, "Personal_Care");
        index = SearchProduct(Category->Personal_Care, Category->Personal_CareCount, product_name);
        break;
    case 9:
        strcpy(category_name, "Other");
        index = SearchProduct(Category->Other, Category->OthersCount, product_name);
        break;
    default:
        printf("Invalid category choice.\n");
        return;
    }

    if(index == -1) {
        printf("Product not found.\n");
    } else {
        Product_Details *product;

        switch(category_choice) {
        case 1:
            product = &Category->Beverage[index];
            break;
        case 2:
            product = &Category->Canned_Goods[index];
            break;
        case 3:
            product = &Category->Dairy[index];
            break;
        case 4:
            product = &Category->Dry_Baking_Goods[index];
            break;
        case 5:
            product = &Category->Produce[index];
            break;
        case 6:
            product = &Category->Cleaners[index];
            break;
        case 7:
            product = &Category->Paper_Goods[index];
            break;
        case 8:
            product = &Category->Personal_Care[index];
            break;
        case 9:
            product = &Category->Other[index];
            break;
        }

        int available_quantity = product->quantity[0];
       
        do{
            printf("Enter Quantity to added (%d %s available): ", available_quantity, product->quantity_category);
            scanf("%d", &quantity_added);

            if (quantity_added < 0) {
                printf("Invalid quantity. Input a positive integer.\n");
            }
        } while (quantity_added < 0); //To ensure nga dili negative ang mabutang ni Aling Nena

        product->quantity[0] = product->quantity[0] + quantity_added;
        double amount = quantity_added * product->cost[0];
        char small_note[100];
        NoteExplainer(quantity_added, product->product_name, "Purchases", small_note, sizeof(small_note));
        RecordTransaction(1, transaction_count, notebook, "Purchases", "Cash", amount, small_note);

        // Update file quantity
    FILE *file = fopen("products.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[2048];
    long pos;
    while (fgets(line, sizeof(line), file)) {
        pos = ftell(file);
        char file_category[50], file_name[PROD_NAME];
        sscanf(line, "%[^|]|%[^|]", file_category, file_name);
        if (strcmp(file_category, category_name) == 0 && strcmp(file_name, product_name) == 0) {
            fseek(file, pos - strlen(line) - 1, SEEK_SET);
            fprintf(file, "%s|%s|%.2f|%s|%.2f|%s|%d|%.2lf\n", category_name,
                    product->product_name, product->price, product->weight_category,
                    product->product_weight, product->quantity_category,
                    product->quantity[0], product->cost[0]);
            break;
        }
    }

    fclose(file);
        printf("Quantity added successfully.\n");
    }
}

void NoteExplainer(int quantity, char product_name[], char account_title[], char small_note[], int size) {
    if (strcmp(account_title, "Sales") == 0) {
        snprintf(small_note, size, "Sold %d of %s", quantity, product_name);
    } else if (strcmp(account_title, "Purchases") == 0) {
        snprintf(small_note, size, "Bought %d of %s", quantity, product_name);
    } else {
        snprintf(small_note, size, "Unknown transaction");
    }
}

void RecordTransaction(int iterator, int transaction_count, JournalEntry* notebook, char account_title_1[], char account_title_2[], double amount, char small_note[]) {
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    int index = transaction_count + iterator - 1; // Adjust index calculation

    notebook[index].year = localTime->tm_year + 1900;
    notebook[index].month = localTime->tm_mon + 1;
    notebook[index].day = localTime->tm_mday;
    notebook[index].debit_amount = amount;
    notebook[index].credit_amount = amount;
    strcpy(notebook[index].debit, account_title_1);
    strcpy(notebook[index].credit, account_title_2);
    strcpy(notebook[index].small_note, small_note);
}

void PrintAllTransactions(JournalEntry* notebook, int number_of_entries) {
    FILE *file = fopen("transaction.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    printf("%-20s%-33s%-12s%-10s\n", "Date", "Transaction", "Debit", "Credit");
    fprintf(file, "%-20s%-33s%-12s%-10s\n", "Date", "Transaction", "Debit", "Credit");

    for (int counter = 0; counter < number_of_entries; counter++) { // Adjust loop condition
        printf("\n");
        fprintf(file, "\n");
        
        printf("%d/%d/%-8d%-40s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].debit, notebook[counter].debit_amount);
        fprintf(file, "%d/%d/%-8d%-40s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].debit, notebook[counter].debit_amount);
        printf("%14s%-50s%.2lf\n", "", notebook[counter].credit, notebook[counter].credit_amount);
        fprintf(file, "%14s%-50s%.2lf\n", "", notebook[counter].credit, notebook[counter].credit_amount);
        printf("%-15s'%s'\n", "", notebook[counter].small_note);
        fprintf(file, "%-15s'%s'\n", "", notebook[counter].small_note);
    }

    printf("\n");
    fprintf(file, "\n");

    fclose(file);
}

void LedgerGeneratorNormalDebit(JournalEntry* notebook, char AccountTitle[], int number_of_entries){
    FILE *file = fopen("ledger_debit.txt", "a");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    printf("%*s\n", 50, "General Ledger");
    printf("%*s\n", 45, AccountTitle);
    fprintf(file, "%*s\n", 50, "General Ledger");
    fprintf(file, "%*s\n", 45, AccountTitle);

    for(int counter = 0; counter < number_of_entries; counter++){
        if(strcmp(notebook[counter].debit, AccountTitle) == 0){
            printf("%d/%d/%-8d%-40s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].debit_amount);
            fprintf(file, "%d/%d/%-8d%-40s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].debit_amount);
        }
        if(strcmp(notebook[counter].credit, AccountTitle) == 0){
            printf("%d/%d/%-8d%-52s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].credit_amount);
            fprintf(file, "%d/%d/%-8d%-52s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].credit_amount);
        }
    }
    printf("\n");
    fprintf(file, "\n");

    fclose(file);
}

void LedgerGeneratorNormalCredit(JournalEntry* notebook, char AccountTitle[], int number_of_entries){
    FILE *file = fopen("ledger_credit.txt", "a");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    printf("%*s\n", 50, "General Ledger");
    printf("%*s\n", 45, AccountTitle);
    fprintf(file, "%*s\n", 50, "General Ledger");
    fprintf(file, "%*s\n", 45, AccountTitle);

    for(int counter = 0; counter < number_of_entries; counter++){
        if(strcmp(notebook[counter].credit, AccountTitle) == 0){
            printf("%d/%d/%-8d%-53s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].credit_amount);
            fprintf(file, "%d/%d/%-8d%-53s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].credit_amount);
        }

        if(strcmp(notebook[counter].debit, AccountTitle) == 0){
            printf("%d/%d/%-8d%-40s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].debit_amount);
            fprintf(file, "%d/%d/%-8d%-40s%.2lf\n", notebook[counter].month, notebook[counter].day, notebook[counter].year, notebook[counter].small_note, notebook[counter].debit_amount);
        }
    }
    printf("\n");
    fprintf(file, "\n");

    fclose(file);
}

double IncomeStatement(Categories *Category, JournalEntry *notebook, int number_of_entries, int month, int day, int year){
    printf("%*s\n", 50, "Aling Nena's Store");
    printf("%*s\n", 49, "Income Statement");
    printf("                          For the month ended %s %d, %d\n", getMonthName(month), day, year);

    double sales_amount = 0.00;
    double ending_inventory = 0.00;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].credit,"Sales")==0){
            sales_amount = sales_amount + notebook[i].credit_amount;
        }else if(strcmp(notebook[i].debit,"Sales")==0){
            sales_amount = sales_amount - notebook[i].debit_amount;
        }
    }
    printf("%16s %54s %.2lf", "Gross Sales", "₱", sales_amount);
    printf("\n");

    printf("%9s", "Less");
    printf("\n");
    double salesdiscountsamount;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit,"Sales Discount")==0){
            salesdiscountsamount = salesdiscountsamount + notebook[i].debit_amount;
        }else if(strcmp(notebook[i].debit,"Sales Discount")==0){
            salesdiscountsamount = salesdiscountsamount - notebook[i].credit_amount;
        }
    }
    printf("      %s %35s %.2lf", "Sales Discounts", "₱", salesdiscountsamount);
    printf("\n");

    double sales_ra_amount = 0.00;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit,"Sales Returns and Allowances")==0){
            sales_ra_amount = sales_ra_amount + notebook[i].debit_amount;
        }else if(strcmp(notebook[i].debit,"Sales Returns and Allowances")==0){
            sales_ra_amount = sales_ra_amount - notebook[i].credit_amount;
        }
    }
    double less_sales_expenses = 0.00;
    less_sales_expenses = salesdiscountsamount + sales_ra_amount;
    printf("      %s %25.2lf %17.2lf", "Sales Returns and Allowances", sales_ra_amount, less_sales_expenses);
    printf("\n");
    printf("                                                     -------------------------\n");
    double netsales_amount = 0.00;
    netsales_amount = sales_amount - less_sales_expenses;
    printf("%14s %56s %.2lf", "Net Sales", "₱", netsales_amount);
    printf("\n");
    printf("\n");

    printf("%29s", "Less Cost of Goods Sold:");
    printf("\n");
    double beginning_inventory = 0;
    for(int i=0; i < number_of_entries; i++){
        if(strncmp(notebook[i].small_note,"To record ending inventory", 17)==0 && notebook[i].month == (month-1) && strcmp(notebook[i].debit, "Merchandise Inventory")==0){
            beginning_inventory = beginning_inventory + notebook[i].debit_amount;
        }
    }
    printf("      %s %16s %6.2lf", "Merchandise Inventory, Beginning", "₱", beginning_inventory);
    printf("\n");
    double total_purchases = 0;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit,"Purchases")==0){
            total_purchases = total_purchases + notebook[i].debit_amount;
        }if(strcmp(notebook[i].credit,"Purchases")==0){
            total_purchases = total_purchases - notebook[i].credit_amount;
        }
    }
    printf("%21s %38.2lf", "Gross Purchases", total_purchases);
    printf("\n");
    double transpo_in = 0;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit,"Transportation In")==0){
            transpo_in = transpo_in + notebook[i].debit_amount;
        }
    }
    printf("%23s %36.2lf", "Transportation In", transpo_in);
    printf("\n");
    printf("%11s", "Less:");
    printf("\n");

    double purchase_discounts = 0;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].credit,"Purchase Discounts")==0){
            purchase_discounts = purchase_discounts + notebook[i].credit_amount;
        }
    }

    printf("      %s %19s %6.2lf", "Purchase Discounts", "₱", purchase_discounts);
    printf("\n");
    double purchase_ra = 0;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].credit,"Purchase Returns and Allowances")==0){
            purchase_discounts = purchase_discounts + notebook[i].credit_amount;
        }
    }
    double total_purchase_expenses;
    total_purchase_expenses = purchase_discounts + purchase_ra;
    printf("      %s %11.2lf %10.2lf", "Purchase Returns and Allowances", purchase_discounts, total_purchase_expenses);
    printf("\n");
    printf("                                        ---------------------\n");
    double tgas;
    tgas = beginning_inventory + total_purchases + transpo_in - total_purchase_expenses;
    printf("      %s%16s%10.2lf", "Total Goods Available for Sale", "₱", tgas);
    printf("\n");
    //iterate all the quantity remaining in the inventory
    for(int i=0; i < number_of_entries; i++){
        if(strncmp(notebook[i].small_note,"To record ending inventory", 17)==0 && strcmp(notebook[i].debit, "Merchandise Inventory")==0 && notebook[i].month == month){
            ending_inventory = ending_inventory + notebook[i].debit_amount;
            break;
        }
    }
    double total_cogs;
    total_cogs = tgas - ending_inventory;
    printf("      %14s %19.2lf %17.2lf", "Less: Merhandise Inventory, Ending", ending_inventory, total_cogs);
    printf("\n");
    printf("                                         -------------------------------------\n");
    double gross_income = 0.00;

    if(total_cogs > 0){
        gross_income = netsales_amount - total_cogs;
    }else if(total_cogs < 0){
        gross_income = netsales_amount + total_cogs;
    }

    printf("%18s %52s %2.2lf", "Gross Income", "₱", gross_income);
    printf("\n");
    printf("\n");
    printf("%18s %52s %2.2lf", "Total Income", "₱",gross_income);
    printf("\n");
    printf("\n");
    printf("%19s:", "Less Expenses");
    printf("\n");
    double utility_expense;
    double supplies_expense;
    double miscellaneous_expense;
    double total_expenses;
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit,"Utility Expense")==0){
            utility_expense = utility_expense + notebook[i].debit_amount;
        }
    }
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit,"Supplies Expense")==0){
            supplies_expense = supplies_expense + notebook[i].debit_amount;
        }
    }
    for(int i=0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit,"Miscellaneous Expense")==0){
            miscellaneous_expense = miscellaneous_expense + notebook[i].debit_amount;
        }
    }
    total_expenses = utility_expense + supplies_expense + miscellaneous_expense;
    printf("%24s %35.2lf", "Utility Expense", utility_expense);
    printf("\n");
    printf("%25s %34.2lf", "Supplies Expense", supplies_expense);
    printf("\n");
    printf("%30s %29.2lf %17.2lf", "Miscellaneous Expense", supplies_expense, total_expenses);
    printf("\n");
    printf("                                                 -----------------------------\n");

    double profit_loss = 0;
    profit_loss = gross_income - total_expenses;

    if(profit_loss > 0){
        printf("%16s                                                    %s %.2lf", "Net Profit", "₱", profit_loss);
        printf("\n");
        printf("                                                                   ===========");
    }else if(profit_loss < 0){
        profit_loss = profit_loss * -1;
        printf("%14s                                                     %s (%.2lf)", "Net Loss", "₱", profit_loss);
        printf("\n");
        printf("                                                                   ============");
        profit_loss = profit_loss * -1;
    }

    printf("\n");
    
    return profit_loss;
}

double StatementofChangesinEquity(JournalEntry* notebook, int number_of_entries, int month, int day, int last_day, int year, double profit_loss, double old_capital){

    printf("%*s\n", 50, "Aling Nena's Store");
    printf("%*s\n", 56, "Statement of Changes in Equity");
    printf("                         For the month ended %s %d, %d\n", getMonthName(month), day, year);

    printf("\n");

    if(old_capital == 0){
        //do nothing
    }else{
        printf("%19s - %s %d, %d %34s %10.2lf", "Nena, Capital", getMonthName(month), day, year, "₱", old_capital);
        printf("\n");
    }

    double capital_investments = 0.00;

    for(int i = 0; i < number_of_entries; i++){
        if(strcmp(notebook[i].small_note, "To invest in the business")==0 && notebook[i].month == month){
            capital_investments = capital_investments + notebook[i].credit_amount;
        }
    }

    if(capital_investments == 0){
        //do nothing
    }else{
        printf("%30s %47.2lf", "Add: Capital Investments", capital_investments);
        printf("\n");
        printf("                                                                  ------------");
        printf("\n");
    }

    if(profit_loss > 0){
        printf("%21s %56.2lf", "Add: Net Profit", profit_loss);
        printf("\n");
        printf("                                                                  ------------");
        printf("\n");
    }else if(profit_loss <0){
        profit_loss = profit_loss * -1;
        printf("%20s                                                 (%.2lf)", "Less: Net Loss", profit_loss);
        printf("\n");
        printf("                                                                  ------------");
        printf("\n");
        profit_loss = profit_loss * -1;
    }
    double total;
    total = old_capital + profit_loss + capital_investments;
    printf("%11s %57s %10.2lf", "Total", "₱", total);
    printf("\n");
    
    double withdrawals = 0;
    for(int i = 0; i < number_of_entries; i++){
        if(strcmp(notebook[i].debit, "Nena, Withdrawals")==0){
            withdrawals = withdrawals + notebook[i].debit_amount;
        }
    }
    printf("%29s %38s (%.2lf)", "Less: Nena, Withdrawals", "", withdrawals);
    printf("\n");

    double final_equity;
    final_equity = total - withdrawals;
    printf("                                                                  ------------");
    printf("\n");
    printf("%19s - %s %d, %d %33s %10.2lf", "Nena, Capital", getMonthName(month), last_day, year, "₱", final_equity);
    printf("\n");
    printf("                                                                  ============");
    printf("\n");

    return final_equity;

}

double StatementOfCashFlows(JournalEntry *notebook, int number_of_entries, int month, int day, int year, double old_cash){

    printf("%*s\n", 50, "Aling Nena's Store");
    printf("%*s\n", 53, "Statement of Cash Flows");
    printf("                         For the month ended %s %d, %d\n", getMonthName(month), day, year);

printf("\n");
//flow from operating activities

    double operating_activities = 0;
    double investing_activities = 0;
    double financing_activities = 0;
    printf("%s\n", "Cash Flows from Operating Activities");
    for(int i=0; i <number_of_entries; i++){
        if(i==0){
            printf("%15s", "Receipts:");
            printf("\n");
        }
            if(strcmp(notebook[i].debit,"Cash")== 0 && strcmp(notebook[i].credit, "Sales")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%20s %37s %10.2lf\n",notebook[i].small_note, "₱", notebook[i].debit_amount);
            operating_activities = operating_activities + notebook[i].debit_amount;
            }else if(strcmp(notebook[i].debit,"Cash")== 0 && strcmp(notebook[i].credit, "Accounts Receivable")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%20s\n",notebook[i].small_note);
            operating_activities = operating_activities + notebook[i].debit_amount;
            }
    }

        printf("\n");

    for(int i=0; i<number_of_entries; i++){

        if(i==0){
            printf("%20s", "Disbursements:");
            printf("\n");
        }
            if(strcmp(notebook[i].debit,"Purchases")== 0 && strcmp(notebook[i].credit, "Cash")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%22s %35s(%.2lf)\n",notebook[i].small_note, "", notebook[i].credit_amount);
                operating_activities = operating_activities - notebook[i].credit_amount;
            }else if(strcmp(notebook[i].debit,"Utility Expense")== 0 && strcmp(notebook[i].credit, "Cash")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%24s %32s (%.2lf)\n",notebook[i].small_note, "", notebook[i].credit_amount);
                operating_activities = operating_activities - notebook[i].credit_amount;
            }else if(strcmp(notebook[i].debit,"Supplies Expense")== 0 && strcmp(notebook[i].credit, "Cash")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%24s%34s (%.2lf)\n",notebook[i].small_note, "", notebook[i].credit_amount);
                operating_activities = operating_activities - notebook[i].credit_amount;
            }else if(strcmp(notebook[i].debit,"Miscellaneous Expense")== 0 && strcmp(notebook[i].credit, "Cash")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%24s%34s (%.2lf)\n",notebook[i].small_note, "", notebook[i].credit_amount);
                operating_activities = operating_activities - notebook[i].credit_amount;
            }else if(strcmp(notebook[i].debit,"Transportation In")== 0 && strcmp(notebook[i].credit, "Cash")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%24s%34s (%.2lf)\n",notebook[i].small_note, "", notebook[i].credit_amount);
                operating_activities = operating_activities - notebook[i].credit_amount;
            }else if(strcmp(notebook[i].debit,"Accounts Payable")== 0 && strcmp(notebook[i].credit, "Cash")==0 && strcmp(notebook[i].small_note, "Beginning Balance")!=0 && notebook[i].month == month){
                printf("%24s%34s (%.2lf)\n",notebook[i].small_note, "", notebook[i].credit_amount);
            }
        }
    printf("%54s -------------\n", "");
    printf("\n");

    if(operating_activities < 0){
        operating_activities = operating_activities * -1;
        printf("%52s %18s %s (%.2lf)", "Net Cash Flow Provided by Operating Activities", "₱", "", operating_activities);
        operating_activities = operating_activities * -1;
    }else if (operating_activities == 0){
        printf("%.2lf", operating_activities);
    }else if (operating_activities > 0){
        printf("%52s %18s %10.2lf", "Net Cash Flow Provided by Operating Activities", "₱", operating_activities);
    }

    printf("\n");
    printf("\n");

    printf("%s\n", "Cash Flows from Investing Activities");
        //no investing activities
    printf("\n");
    investing_activities = 0;
    if(investing_activities < 0){
        investing_activities = investing_activities * -1;
        printf("%52s %18s %5s (%.2lf)", "Net Cash Flow Provided by Investing Activities", "₱", "", investing_activities);
        investing_activities = investing_activities * -1;
    }else if (investing_activities == 0){
        printf("%52s %18s %7s", "Net Cash Flow Provided by Investing Activities", "₱", "-");
    }else{
        printf("%52s %18s %3.2lf", "Net Cash Flow Provided by Investing Activities", "₱", investing_activities);
    }
    printf("\n");

    printf("\n");
    printf("%s\n", "Cash Flows from Financing Activities");
    printf("%16s", "Receipts:\n");
        for(int i=0; i<number_of_entries; i++){
            if(strcmp(notebook[i].debit,"Cash")== 0 && strcmp(notebook[i].credit, "Nena, Capital") == 0 && strcmp(notebook[i].small_note,"Beginning Balance")>0){
                printf("%23s %44s %s %.2lf\n",notebook[i].small_note, "₱", "", notebook[i].debit_amount);
                financing_activities = financing_activities + notebook[i].debit_amount;
            }
        }
    printf("\n");
    printf("%20s", "Disbursements:");
    printf("\n");
        for(int i=0; i<number_of_entries; i++){
            if(strcmp(notebook[i].debit,"Nena, Withdrawals")== 0 && strcmp(notebook[i].credit, "Cash")==0){
                printf("%37s %20s (%.2lf)\n",notebook[i].small_note, "", notebook[i].credit_amount);
                financing_activities = financing_activities - notebook[i].credit_amount;
            }
        }
    printf("%55s -------------\n", "");
    printf("\n");
    if(financing_activities < 0){
        financing_activities = financing_activities * -1;
        printf("%52s %18s %s (%.2lf)", "Net Cash Flow Provided by Financing Activities", "₱", "", financing_activities);
        financing_activities = financing_activities * -1;
    }else if (financing_activities == 0){
        printf("%52s %18s %5s %s", "Net Cash Flow Provided by Financing Activities", "₱", "", "-");
    }else if (financing_activities > 0){
        printf("%52s %18s %s %2.2lf", "Net Cash Flow Provided by Financing Activities", "₱", "", financing_activities);
    }
    printf("\n");
    printf("%67s -------------\n", "");
    printf("\n");
    double ending_cash = operating_activities + investing_activities + financing_activities;

    if(ending_cash < 0){
        ending_cash = ending_cash * -1;
        printf("%19s %50s (%.2lf)", "Net Cash Flow", "", ending_cash);
        ending_cash = ending_cash * -1;
        printf("\n");
    }else{
        printf("%19s %s %60.2lf", "Net Cash Flow", "", ending_cash);
        printf("\n");
    }

    if(old_cash < 0){
        old_cash = old_cash * -1;
        printf("%20s %52s (%.2lf)", "Less: Cash, Beginning", "", old_cash);
        printf("\n");
        old_cash = old_cash * -1;
        ending_cash = ending_cash + old_cash;
    }else{
        printf("%26s %54.2lf", "Add: Cash, Beginning", old_cash);
        printf("\n");
        ending_cash = ending_cash + old_cash;
    }


    printf("%67s -------------\n", "");

    if(ending_cash <0){
        ending_cash = ending_cash * -1;
        printf("%10s - %s %d, %d %52s (%.2lf)", "Cash", getMonthName(month), day, year, "", ending_cash);
        printf("\n");
        ending_cash = ending_cash * -1;
    }else{
        printf("%10s - %s %d, %d %45s %11.2lf", "Cash", getMonthName(month), day, year, "₱", ending_cash);
        printf("\n");
    }
    printf("%67s =============\n", "");

    return ending_cash;

}

double BalanceCalculatorNormalDebit(JournalEntry *notebook, char AccountTitle[], int number_of_entries){
    double total_sum = 0;
    for(int i=0; i<number_of_entries; i++){
        if(strcmp(notebook[i].debit, AccountTitle)==0){
            total_sum = total_sum + notebook[i].debit_amount;
        }
        
        if(strcmp(notebook[i].credit, AccountTitle)==0){
            total_sum = total_sum - notebook[i].credit_amount;
        }
    }
    return total_sum;
}

double BalanceCalculatorNormalCredit(JournalEntry *notebook, char AccountTitle[], int number_of_entries){
    double total_sum = 0;
    for(int i=0; i<number_of_entries; i++){
        if(strcmp(notebook[i].credit, AccountTitle)==0){
            total_sum = total_sum + notebook[i].credit_amount;
        }
        
        if(strcmp(notebook[i].debit, AccountTitle)==0){
            total_sum = total_sum - notebook[i].debit_amount;
        }
    }
    return total_sum;
}

void BalanceSheet(Categories *Category, JournalEntry *notebook, int number_of_entries, int month, int day, int year, double new_equity){
    printf("%*s\n", 50, "Aling Nena's Store");
    printf("%*s\n", 57, "Statement of Financial Position");
    printf("%33s %s %d, %d\n", "", getMonthName(month), day, year);
    printf("\n");

    double cash = BalanceCalculatorNormalDebit(notebook, "Cash", number_of_entries);
    double acc_rec = BalanceCalculatorNormalDebit(notebook, "Accounts Receivable", number_of_entries);
    double merch_inv = MerchInvCounter(Category);
    double supplies = BalanceCalculatorNormalDebit(notebook, "Supplies", number_of_entries);
    double current_assets = cash + acc_rec + merch_inv + supplies;

    printf("%44s", "ASSETS");
    printf("\n");

    printf("%21s","Current Assets:");
    printf("\n");
    printf("%15s %42s %10.2lf","Cash", "₱", cash);
    printf("\n");

    printf("%30s %36.2lf","Accounts Receivable", acc_rec);
    printf("\n");

    printf("%32s %34.2lf","Merchandise Inventory", merch_inv);
    printf("\n");

    printf("%19s %47.2lf","Supplies", supplies);
    printf("\n");
    printf("%53s -------------\n", "");
    printf("\n");

    printf("%31s %40s %10.2lf","Total Current Assets", "₱", current_assets);
    printf("\n");

    printf("\n");
    
    printf("%24s","Noncurrent Assets:");
    printf("\n");
    double land = BalanceCalculatorNormalDebit(notebook, "Land", number_of_entries);
    double building = BalanceCalculatorNormalDebit(notebook, "Building", number_of_entries);
    double accum_dep_building = BalanceCalculatorNormalCredit(notebook, "Accumulated Depreciation - Building", number_of_entries);
    double equipment = BalanceCalculatorNormalDebit(notebook, "Equipment", number_of_entries);
    double accum_dep_equipment = BalanceCalculatorNormalCredit(notebook, "Accumulated Depreciation - Equipment", number_of_entries);
    double noncurrent_assets = land + building - accum_dep_building + equipment - accum_dep_equipment;

    printf("%15s %42s %10.2lf","Land", "₱", land);
    printf("\n");

    printf("%19s %47.2lf","Building", building);
    printf("\n");

    printf("%46s %15s(%.2lf)","Accumulated Depreciation - Building", "", accum_dep_building);
    printf("\n");

    printf("%20s %46.2lf","Equipment", equipment);
    printf("\n");

    printf("%47s %14s(%.2lf)","Accumulated Depreciation - Equipment", "", accum_dep_equipment);
    printf("\n");
    printf("%54s -------------\n", "");

    printf("\n");

    printf("%34s %37s %11.2lf","Total Noncurrent Assets", "₱", noncurrent_assets);
    printf("\n");
    printf("%68s -------------\n", "");

    printf("\n");

    double total_assets = current_assets + noncurrent_assets;
    printf("%18s %53s %11.2lf","TOTAL ASSETS", "₱", total_assets);
    printf("\n");
    printf("%68s =============\n", "");

    printf("\n");

    printf("%55s", "LIABILITIES AND OWNER'S EQUITY");
    printf("\n");

    printf("\n");

    printf("%26s","Current Liabilities:");
    printf("\n");
    double accounts_payable = BalanceCalculatorNormalCredit(notebook, "Accounts Payable", number_of_entries);
    double capital = new_equity;

    printf("%27s %31s %11.2lf","Accounts Payable", "₱", accounts_payable);
    printf("\n");
    printf("%55s -------------\n", "");

    double current_liabilities = accounts_payable;

    printf("%36s %35s %11.2lf","Total Current Liabilities", "₱", current_liabilities);
    printf("\n");

    printf("\n");

    printf("%20s %51s %11.2lf","Nena, Capital", "₱", new_equity);
    printf("\n");
    printf("%68s -------------\n", "");

    printf("\n");

    double total_liabeq = current_liabilities + new_equity;

    printf("%42s %29s %11.2lf","TOTAL LIABILITIES AND OWNER'S EQUITY", "₱", total_liabeq);
    printf("\n");
    printf("%68s =============\n", "");
}

//add function that computes for merchandise inventory
    //get the code from ben
double MerchInvCounter(Categories *Category){
  double cost = 0; //Initialize total cost as 0
  for(int i = 0; i<Category->BeverageCount; i++){
    double cost1 = Category->Beverage[i].cost[0];
    int quantity = Category->Beverage[i].quantity[0];
    double PartialCost = cost1 * quantity; 
    //I go through all available products in each category and check for its cost and quantity
    cost = PartialCost + cost; //I will then add the cost onto the total cost variable cost
  }

  for(int i = 0; i<Category->Canned_GoodsCount; i++){
    double cost1 = Category->Canned_Goods[i].cost[0];
    int quantity = Category->Canned_Goods[i].quantity[0];
    double PartialCost = cost1 * quantity;  //Same thing goes with this one
    cost = PartialCost + cost; //Yes
  }
  for(int i = 0; i<Category->DairyCount; i++){
    double cost1 = Category->Dairy[i].cost[0];
    int quantity = Category->Dairy[i].quantity[0];
    double PartialCost = cost1 * quantity;
    cost = PartialCost + cost;
  }
  for(int i = 0; i<Category->Dry_Baking_GoodsCount; i++){
    double cost1 = Category->Dry_Baking_Goods[i].cost[0];
    int quantity = Category->Dry_Baking_Goods[i].quantity[0];
    double PartialCost = cost1 * quantity;
    cost = PartialCost + cost;
  }
  for(int i = 0; i<Category->ProduceCount; i++){
    double cost1 = Category->Produce[i].cost[0];
    int quantity = Category->Produce[i].quantity[0];
    double PartialCost = cost1 * quantity;
    cost = PartialCost + cost;
  }
  for(int i = 0; i<Category->CleanersCount; i++){
     double cost1 = Category->Cleaners[i].cost[0];
    int quantity = Category->Cleaners[i].quantity[0];
    double PartialCost = cost1 * quantity;
    cost = PartialCost+cost;
  }
  for(int i = 0; i<Category->Paper_GoodsCount; i++){
     double cost1 = Category->Paper_Goods[i].cost[0];
    int quantity = Category->Paper_Goods[i].quantity[0];
    double PartialCost = cost1 * quantity;
    cost = PartialCost+cost;
  }
  for(int i = 0; i<Category->Personal_CareCount; i++){
     double cost1 = Category->Personal_Care[i].cost[0];
    int quantity = Category->Personal_Care[i].quantity[0];
    double PartialCost = cost1 * quantity;;
    cost = PartialCost+cost;
  }
  for(int i = 0; i<Category->OthersCount; i++){
     double cost1 = Category->Other[i].cost[0];
    int quantity = Category->Other[i].quantity[0];
    double PartialCost = cost1 * quantity;
    cost = PartialCost+cost;
  }

    //add recording function here
  
  return cost;

}

//add menu that lets user pick from the financial statements and to let them close it for the appropriate period na
void FinancialStatementsMenu(){
    printf("Generate one of the following statements or close the temporary accounts for the next accounting period.\n");
    printf("Tip: When viewing these statements for the first time, generate these statements in order, from 1 to 4\n");
    printf("\n");
    printf("1. Income Statement\n");
    printf("2. Statement of Changes in Equity\n");
    printf("3. Statement of Financial Position\n");
    printf("4. Statement of Cash Flows\n");
    printf("5. Close Nominal Accounts\n");
    printf("6. Exit\n");
}
//properly add the date function thingy

void Ledger_menu(JournalEntry* notebook, int transaction_count) {
    int choice1, choice2;
    printf("\nSelect an account category:\n");
    printf("1. Assets\n");
    printf("2. Liabilities\n");
    printf("3. Capital\n");
    printf("4. Revenue\n");
    printf("5. Expenses\n");
    printf("6. Cancel\n");
    printf("Input: ");
    scanf("%d", &choice1);

    if (choice1 == 6) {
        printf("Generation canceled.\n");
        return;
    }

    switch (choice1) {
        case 1:
            printf("\nSelect an asset account:\n");
            printf("1. Cash\n");
            printf("2. Accounts Receivable\n");
            printf("3. Merchandise Inventory\n");
            printf("Input: ");
            scanf("%d", &choice2);
            if (choice2 == 1) {
                LedgerGeneratorNormalDebit(notebook, "Cash", transaction_count);
            } else if (choice2 == 2) {
                LedgerGeneratorNormalDebit(notebook, "Accounts Receivable", transaction_count);
            } else if (choice2 == 3) {
                LedgerGeneratorNormalDebit(notebook, "Merchandise Inventory", transaction_count);
            }
            break;
        case 2:
            printf("\nSelect a liabilities account:\n");
            printf("1. Accounts Payable\n");
            printf("Input: ");
            scanf("%d", &choice2);
            if(choice2 == 1) {
                LedgerGeneratorNormalCredit(notebook, "Accounts Payable", transaction_count);
            }
            break;
        case 3:
            printf("\nSelect a capital account:\n");
            printf("1. Nena, Capital\n");
            printf("2. Nena, Withdrawals\n");
            printf("Input: ");
            scanf("%d", &choice2);
            if (choice2 == 1) {
                LedgerGeneratorNormalCredit(notebook, "Nena, Capital", transaction_count);
            }else if (choice2 == 2) {
                LedgerGeneratorNormalDebit(notebook, "Nena, Withdrawals", transaction_count);
            }
            break;
        case 4:
            printf("\nSelect a revenue account:\n");
            printf("1. Sales\n");
            printf("2. Sales Discounts\n");
            printf("3. Sales Returns and Allowances\n");
            printf("Input: ");
            scanf("%d", &choice2);
            if(choice2 == 1) {
                LedgerGeneratorNormalCredit(notebook, "Sales", transaction_count);
            }else if (choice2 == 2) {
                LedgerGeneratorNormalDebit(notebook, "Sales Discounts", transaction_count);
            }else if (choice2 == 3) {
                LedgerGeneratorNormalDebit(notebook, "Sales Returns and Allowances", transaction_count);
            }
            break;
        case 5:
            printf("\nSelect an expense account:\n");
            printf("1. Purchases\n");
            printf("2. Purchase Discounts\n");
            printf("3. Purchase Returns and Allowances\n");
            printf("4. Utilities Expense\n");
            printf("5. Supplies Expense\n");
            printf("6. Miscellaneous Expense\n");
            printf("7. Transportation In\n");
            printf("Input: ");
            scanf("%d", &choice2);
            if(choice2 == 1) {
                LedgerGeneratorNormalDebit(notebook, "Purchases", transaction_count);
            } else if (choice2 == 2) {
                LedgerGeneratorNormalCredit(notebook, "Purchase Discounts", transaction_count);
            } else if (choice2 == 3) {
                LedgerGeneratorNormalCredit(notebook, "Purchase Returns and Allowances", transaction_count);
            } else if (choice2 == 4) {
                LedgerGeneratorNormalDebit(notebook, "Utility Expense", transaction_count);
            } else if (choice2 == 5) {
                LedgerGeneratorNormalDebit(notebook, "Supplies Expense", transaction_count);
            } else if (choice2 == 6) {
                LedgerGeneratorNormalDebit(notebook, "Miscellaneous Expense", transaction_count);
            } else if (choice2 == 7) {
                LedgerGeneratorNormalDebit(notebook, "Transportation In", transaction_count);
            }
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
