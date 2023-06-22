#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
    struct Product *next;
};

struct Product *head = NULL;
// Function to check if a product with the given ID already exists
int isProductIdUnique(int id) {
    struct Product *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return 0; // Product ID already exists
        }
        current = current->next;
    }
    return 1; // Product ID is unique
}

// Function to add a new product
void addProduct(int id, const char *name, float price, int quantity) {
    if (!isProductIdUnique(id)) {
        printf("Product with ID %d already exists. Unable to add.\n", id);
        return;
    }

    struct Product *newProduct = (struct Product *)malloc(sizeof(struct Product));
    newProduct->id = id;
    strncpy(newProduct->name, name, sizeof(newProduct->name));
    newProduct->price = price;
    newProduct->quantity = quantity;
    newProduct->next = NULL;

    if (head == NULL) {
        head = newProduct;
    } else {
        struct Product *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newProduct;
    }

    printf("Product added successfully.\n");
}


// Function to display all products
void displayProducts() {
    if (head == NULL) {
        printf("No products available.\n");
    } else {
        struct Product *current = head;
        printf("Product List:\n");
        printf("ID\tName\tPrice\tQuantity\n");
        while (current != NULL) {
            printf("%d\t%s\t%.2f\t%d\n", current->id, current->name, current->price, current->quantity);
            current = current->next;
        }
    }
}

// Function to search for a product by ID
struct Product *searchProduct(int id) {
    struct Product *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Product not found
}

// Function to remove a product by ID
void removeProduct(int id) {
    if (head == NULL) {
        printf("No products available.\n");
        return;
    }

    struct Product *current = head;
    struct Product *prev = NULL;

    // Handle the case if the product to be removed is the head
    if (current->id == id) {
        head = current->next;
        free(current);
        printf("Product with ID %d removed successfully.\n", id);
        return;
    }

    // Search for the product by ID
    while (current != NULL) {
        if (current->id == id) {
            prev->next = current->next;
            free(current);
            printf("Product with ID %d removed successfully.\n", id);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Product with ID %d not found.\n", id);
}

int main() {
    int isAdmin = 0; // 1 if user is an admin, 0 if user is a regular user

    printf("Welcome to the Department Store Management System!\n");

    // Admin panel
    printf("\n-- Admin Panel --\n");
    printf("1. Admin Login\n");
    printf("2. User View\n");
    printf("3. Exit\n");

    int adminChoice;
    printf("\nEnter your choice: ");
    scanf("%d", &adminChoice);

    if (adminChoice == 1) {
        isAdmin = 1;
        printf("\nLogged in to Admin mode.\n");
    } else if (adminChoice == 2) {
        isAdmin = 0;
        printf("\nEntered User View.\n");
    } else {
        printf("\nExiting...\n");
        exit(0);
    }

    while (1) {
        printf("\n*** Department Store Management System ***\n");

        if (isAdmin) {
            printf("\n-- Admin Menu --\n");
            printf("1. Add Product\n");
            printf("2. Remove Product\n");
            printf("3. Modify Product\n");
            printf("4. View Products\n");
            printf("5. Exit\n");
        } else {
            printf("\n-- User Menu --\n");
            printf("1. View Products\n");
            printf("2. Exit\n");
        }

        int choice;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (isAdmin) {
            switch (choice) {
                case 1:
                    printf("\n-- Add Product --\n");
                    int id;
                    char name[50];
                    float price;
                    int quantity;

                    printf("Enter product ID: ");
                    scanf("%d", &id);
                    printf("Enter product name: ");
                    scanf("%s", name);
                    printf("Enter product price: ");
                    scanf("%f", &price);
                    printf("Enter product quantity: ");
                    scanf("%d", &quantity);

                    addProduct(id, name, price, quantity);
                    printf("Product added successfully.\n");
                    break;
                case 2:
                    printf("\n-- Remove Product --\n");
                    printf("Enter product ID to remove: ");
                    scanf("%d", &id);
                    removeProduct(id);
                    break;
                case 3:
                    printf("\n-- Modify Product --\n");
                    printf("Enter product ID to modify: ");
                    scanf("%d", &id);
                    struct Product *productToModify = searchProduct(id);
                    if (productToModify != NULL) {
                        printf("Enter new product name: ");
                        scanf("%s", productToModify->name);
                        printf("Enter new product price: ");
                        scanf("%f", &productToModify->price);
                        printf("Enter new product quantity: ");
                        scanf("%d", &productToModify->quantity);
                        printf("Product modified successfully.\n");
                    } else {
                        printf("Product with ID %d not found.\n", id);
                    }
                    break;
                case 4:
                    printf("\n-- View Products --\n");
                    displayProducts();
                    break;
                case 5:
                    printf("\nLogging out from Admin mode.\n");
                    isAdmin = 0;
                    break;
                default:
                    printf("\nInvalid choice. Try again.\n");
            }
        } else {
            switch (choice) {
                case 1:
                    printf("\n-- View Products --\n");
                    displayProducts();
                    break;
                case 2:
                    printf("\nExiting...\n");
                    exit(0);
                default:
                    printf("\nInvalid choice. Try again.\n");
            }
        }

        if (!isAdmin && choice == 4) {
            isAdmin = 1;
            printf("\nLogged in to Admin mode.\n");
        }
    }

    return 0;
}
