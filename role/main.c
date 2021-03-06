#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <stdlib.h>

/****************************************************************** LOAD CSS */
static void load_css(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    const gchar *css_style_file = "style.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error = 0;
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);
    g_object_unref(provider);
}

/****************************************************************** TYPEDEF *

/*Sign in*/
typedef struct
{
    int id;
    char* name;
    int supplier;
    int price;
    double discount;
    int quantity;
} Product;

typedef struct
{
    gint id;
    gchar *email;
    gchar *pwd;
    gchar *firstName;
    gchar *lastName;
    gchar *address;
    gint type;
    gint tikuCoin;
    gint dob;
    gint mob;
    gint yob;
} Customer;

typedef struct
{
    GtkWidget *greeterlabel;
    GtkWidget *maillabel;
    GtkWidget *mailentry;
    GtkWidget *pwdlabel;
    GtkWidget *pwdentry;
    GtkWidget *enterbutton;
    GtkWidget *clearbutton;
} appWidgets;

/*Sign up*/
typedef struct
{
    GtkWidget *tmpEntry;
    GtkWidget *fnameEntry;
    GtkWidget *gnameEntry;
    GtkWidget *cityEntry;
    GtkWidget *byearSpin;
    GtkWidget *bmonthSpin;
    GtkWidget *bdaySpin;
} signUp_diaWidgets;

typedef struct
{
    GtkApplication *app;
    GtkWidget *window;
    GtkWidget *img;
    signUp_diaWidgets *d;
} signUp_appWidgets;

/****************************************************************** WINDOWS */
/*01*/ static GtkWidget *openWindow;
/*02*/ static GtkWidget *signInWindow;
/*03*/ static GtkWidget *customerMapWindow;
/*04*/ static GtkWidget *changePwdWindow;
/*05*/ static GtkWidget *changeInformationWindow;
/*06*/ static GtkWidget *notiWindow;
/*07*/ static GtkWidget *signUpWindow;
/*08*/ static GtkWidget *showProductsWindow;
/*09*/ static GtkWidget *supplierMapWindow;
/*10*/ static GtkWidget *showInforWindow;
/*11*/ static GtkWidget *paymentWindow;


/****************************************************************** GLOBAL VARIABLES */
static gint noCloseWindow = 1000;
static gint noOpenWindow = 1000;
/*Show products*/
Product databaseProducts[500];
int showedProducts[500];
int itemList[500];
static int firstIndex = 0;
GtkWidget *product1, *product2, *product3, *product4, *product5, *product6, *product7, *product8, *product9, *product10;
GtkWidget *id1, *id2, *id3, *id4, *id5, *id6, *id7, *id8, *id9, *id10;
GtkWidget *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10; //img gio hang
GtkWidget *price1, *price2, *price3, *price4, *price5, *price6, *price7, *price8, *price9, *price10;
char* itemListText;
GtkTextBuffer *buffer;
GtkWidget *idDelEntry;
/*Sign in*/

static Customer customer;
static int numberOfCustomers;
static int numberOfProducts;
static int numberOfItem;

/*Sign up*/
static Customer newAccount;
GtkWidget *firstNameEntry, *lastNameEntry, *emailEntry, *passwordEntry, *reenterPasswordEntry;
GtkWidget *monthSpinButton, *yearSpinButton, *daySpinButton;
/*Change pwd*/
GtkWidget *oldPasswordChangeEntry, *newPasswordChangeEntry, *confirmNewPasswordChangeEntry;

/*Notification*/
GtkWidget *alert;
/*Show Information*/
static char* yourFullName;
static char* yourAddress;
static char* yourDOB;
GtkWidget *nameInforLabelShow, *addressLabelShow, *dobLabelShow;
/*Payment*/
GtkWidget *moneyTotal, *moneyDiscount, *moneyCost;
GtkWidget *entryReciName, *entryAddress, *entryPhone;

/***************************************************************** PROTOTYPES */
/*Sign in*/
int findAccount(char *inputEmail);
void signIn_enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_entry_callback(GtkWidget *widget, gpointer data);

/*Sign up*/
static void signUpActivate(GtkApplication *app, gpointer user_data);
static void signUp_clear_callback();
static void signUp_enter_callback();
/****************************************************************** CALLBACKS */
static void onNoti()
{
    gtk_widget_show_all(GTK_WIDGET(notiWindow));
}
static void offNoti()
{
    gtk_widget_hide(GTK_WIDGET(notiWindow));
}
static void s17()
{
    gtk_widget_hide(GTK_WIDGET(openWindow));
    gtk_widget_show_all(GTK_WIDGET(signUpWindow));
}
static void s38()
{
    numberOfItem = 0;
    strcpy(itemListText, "You have not selected any items");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_widget_show_all(GTK_WIDGET(showProductsWindow));
}
static void s83()
{
    gtk_widget_hide(GTK_WIDGET(showProductsWindow));
    printf("\ns83: customer.type: %d", customer.type);
    if(customer.type == 0){
        gtk_widget_show_all(GTK_WIDGET(customerMapWindow));
    }else if(customer.type == 1){
        gtk_widget_show_all(GTK_WIDGET(supplierMapWindow));
    }else{
        gtk_widget_show_all(GTK_WIDGET(openWindow));
    }
}
static void s18()
{
    customer.type = -1;
    gtk_widget_hide(GTK_WIDGET(openWindow));
    gtk_widget_show_all(GTK_WIDGET(showProductsWindow));
}
static void s71()
{
    gtk_widget_hide(GTK_WIDGET(signUpWindow));
    gtk_widget_show_all(GTK_WIDGET(openWindow));
}
static void s31()
{
    numberOfItem = 0;
    strcpy(itemListText, "You have not selected any items");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_widget_show_all(GTK_WIDGET(openWindow));
}
static void s43()
{
    gtk_widget_hide(GTK_WIDGET(changePwdWindow));
    if(customer.type == 0){
        gtk_widget_show_all(GTK_WIDGET(customerMapWindow));
    }else{
        gtk_widget_show_all(GTK_WIDGET(supplierMapWindow));
    }
}
static void s_end()
{
    char *entry_reciname = gtk_entry_get_text(GTK_ENTRY(entryReciName));
    printf("\n'%s'", entry_reciname);
    char *entry_address = gtk_entry_get_text(GTK_ENTRY(entryAddress));
    printf("\n'%s'", entry_address);
    char *entry_phone = gtk_entry_get_text(GTK_ENTRY(entryPhone));
    printf("\n'%s'", entry_phone);
    if(strcmp(entry_reciname, "") != 0 && strcmp(entry_address, "") != 0 && strcmp(entry_phone, "") != 0){
        gtk_widget_hide(GTK_WIDGET(paymentWindow));
        firstIndex = 0;
        change10Product();
        numberOfItem = 0;
        strcpy(itemListText, "");
        gtk_entry_set_text(GTK_ENTRY(entryReciName), "");
        gtk_entry_set_text(GTK_ENTRY(entryPhone), "");
        gtk_entry_set_text(GTK_ENTRY(entryAddress), "");
        gtk_text_buffer_set_text (buffer, "You have not selected any items", -1);
        gtk_widget_show_all(GTK_WIDGET(showProductsWindow));
        gtk_label_set_text(alert, "Ordered successfully\nPlease continue your shopping");
        onNoti();
    }else{
        gtk_label_set_text(alert, "Please enter your complete information");
        onNoti();
    }
}
static void s811()
{
    if(customer.type == 1){
        gtk_label_set_text(alert, "Can not buy, you are the supplier of this item");
        onNoti();
    }else if(numberOfItem > 0){
        calcCost();
        gtk_widget_hide(GTK_WIDGET(showProductsWindow));
        gtk_widget_show_all(GTK_WIDGET(paymentWindow));
    }else{
        gtk_label_set_text(alert, "You have not selected any items");
        onNoti();
    }
}
static void s23()
{
    gtk_widget_hide(GTK_WIDGET(signInWindow));
    if(customer.type == 0){
        gtk_widget_show_all(GTK_WIDGET(customerMapWindow));
    }else{
        gtk_widget_show_all(GTK_WIDGET(supplierMapWindow));
    }
}
static void s12()
{
    gtk_widget_hide(GTK_WIDGET(openWindow));
    gtk_widget_show_all(GTK_WIDGET(signInWindow));
}
static void s94()
{
    gtk_widget_hide(GTK_WIDGET(supplierMapWindow));
    gtk_widget_show_all(GTK_WIDGET(changePwdWindow));
}
static void s95()
{
    gtk_widget_hide(GTK_WIDGET(supplierMapWindow));
    gtk_widget_show_all(GTK_WIDGET(changeInformationWindow));
}
static void s34()
{
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_widget_show_all(GTK_WIDGET(changePwdWindow));
}
static void s10_x()
{
    gtk_widget_hide(GTK_WIDGET(showInforWindow));
    if(customer.type == 0){
        gtk_widget_show_all(GTK_WIDGET(customerMapWindow));
    }else{
        gtk_widget_show_all(GTK_WIDGET(supplierMapWindow));
    }
}
static void s910()
{
    gtk_widget_hide(GTK_WIDGET(supplierMapWindow));
    gtk_label_set_text(GTK_LABEL(nameInforLabelShow), yourFullName);
    gtk_label_set_text(GTK_LABEL(addressLabelShow), yourAddress);
    gtk_label_set_text(GTK_LABEL(dobLabelShow), yourDOB);
    gtk_widget_show_all(GTK_WIDGET(showInforWindow));
}
static void s310()
{
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_label_set_text(GTK_LABEL(nameInforLabelShow), yourFullName);
    gtk_label_set_text(GTK_LABEL(addressLabelShow), yourAddress);
    gtk_label_set_text(GTK_LABEL(dobLabelShow), yourDOB);
    gtk_widget_show_all(GTK_WIDGET(showInforWindow));
}
static void s98()
{
    numberOfItem = 0;
    strcpy(itemListText, "You have not selected any items");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    gtk_widget_hide(GTK_WIDGET(supplierMapWindow));
    gtk_widget_show_all(GTK_WIDGET(showProductsWindow));
}
static void s91()
{
    numberOfItem = 0;
    strcpy(itemListText, "You have not selected any items");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    gtk_widget_hide(GTK_WIDGET(supplierMapWindow));
    gtk_widget_show_all(GTK_WIDGET(openWindow));
}
static void s41()
{
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_widget_show_all(GTK_WIDGET(openWindow));
}
static void s35()
{
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_widget_show_all(GTK_WIDGET(changeInformationWindow));
}
static void s53()
{
    gtk_widget_hide(GTK_WIDGET(changeInformationWindow));
    gtk_widget_show_all(GTK_WIDGET(customerMapWindow));
}
static void s11_8()
{
    gtk_widget_hide(GTK_WIDGET(paymentWindow));
    gtk_widget_show_all(GTK_WIDGET(showProductsWindow));
}
void delChar(char* str, int pos){
    for(int i = pos; i <= strlen(str) - 1; i++){
        str[i] = str[i + 1];
    }
}

/*Sign in*/
int findAccount(char *inputEmail)
{
    numberOfCustomers = 0;
    FILE *fp = fopen("customers.csv", "r");
    char *tmpStr = malloc(100);
    strcpy(tmpStr, inputEmail);
    char *str = malloc(100);
    strcpy(str, ",");
    strcpy(customer.email, "");
    strcpy(customer.firstName, "");
    strcpy(customer.lastName, "");
    strcpy(customer.pwd, "");
    strcpy(customer.address, "");
    strcat(tmpStr, ",");
    strcat(str, tmpStr);
    strcpy(tmpStr, str);
    while (fgets(str, 60, fp) != NULL)
    {
        printf("\n%s", str);
        if (strstr(str, tmpStr) == NULL)
        {
            numberOfCustomers++;
            continue;
        }
        int pos = 0;
        customer.id = 0;
        customer.tikuCoin = 0;
        customer.dob = 0;
        customer.mob = 0;
        customer.yob = 0;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            customer.id = customer.id * 10 + tmp;
            pos++;
        }

        pos++;
        while (str[pos] != ',')
        {
            pos++;
        }
        strcpy(customer.email, inputEmail);
        pos++;
        printf("\n%s", customer.email);
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos];
            strcat(customer.pwd, &tmp);
            pos++;
        }
        printf("\n%s", customer.pwd);
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos];
            strcat(customer.firstName, &tmp);
            pos++;
        }
        pos++;
        printf("\n%d", customer.id);
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos];
            strcat(customer.lastName, &tmp);
            pos++;
        }
        pos++;

        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            customer.dob = customer.dob * 10 + tmp;
            pos++;
        }
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            customer.mob = customer.mob * 10 + tmp;
            pos++;
        }
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            customer.yob = customer.yob * 10 + tmp;
            pos++;
        }
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos];
            strcat(customer.address, &tmp);
            pos++;
        }
        pos++;
        customer.type = (int)str[pos] - '0';
        pos += 2;
        printf("\n-------%c", str[pos]);
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            customer.tikuCoin = customer.tikuCoin * 10 + tmp;
            pos++;
        }
        printf("\n%d", customer.tikuCoin);
        fclose(fp);
        return 1;
    }

    fclose(fp);
    strcpy(customer.email, "");
    strcpy(customer.firstName, "");
    strcpy(customer.lastName, "");
    strcpy(customer.pwd, "");
    printf("\nkkkkkkkkkkkkkkkkkkkk  %d", numberOfCustomers);
    return 0;
}

void signIn_enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data)
{

    gchar str[50];
    appWidgets *wid = (appWidgets *)data;
    char *entry_email = gtk_entry_get_text(GTK_ENTRY(wid->mailentry));
    char *entry_password = gtk_entry_get_text(GTK_ENTRY(wid->pwdentry));
    if (findAccount(entry_email) == 1)
    {
        if (strcmp(entry_password, customer.pwd) == 0)
        {
            signIn_clear_callback(action, parameter, data);
            strcpy(yourFullName, customer.firstName);
            strcat(yourFullName, " ");
            strcat(yourFullName, customer.lastName);
            strcpy(yourAddress, customer.address);
            strcpy(yourDOB, "");
            char* tmpStr = malloc(200);
            strcpy(tmpStr, ""); itoa(customer.dob, tmpStr, 10);
            strcat(yourDOB, tmpStr);
            strcpy(tmpStr, ""); itoa(customer.mob, tmpStr, 10);
            strcat(yourDOB, "/"); strcat(yourDOB, tmpStr);
            strcpy(tmpStr, ""); itoa(customer.yob, tmpStr, 10);
            strcat(yourDOB, "/"); strcat(yourDOB, tmpStr);
            s23();
        }
        else
        {
            g_sprintf(str, "Hello %s %s! Wrong password!", customer.firstName, customer.lastName);
            gtk_widget_override_font(wid->greeterlabel,
                                     pango_font_description_from_string("Tahoma 20"));
            gtk_label_set_text(GTK_LABEL(wid->greeterlabel), (const gchar *)str);
        }
    }
    else
    {
        g_sprintf(str, "Mail not found. Please check again!");
        gtk_widget_override_font(wid->greeterlabel,
                                 pango_font_description_from_string("Tahoma 20"));
        gtk_label_set_text(GTK_LABEL(wid->greeterlabel), (const gchar *)str);
    }
    entry_email = NULL;
    wid = NULL;
}

void signIn_clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data)
{
    appWidgets *wid = (appWidgets *)data;

    gtk_label_set_text(GTK_LABEL(wid->greeterlabel), "Let's sign in again");
    gtk_entry_set_text(GTK_ENTRY(wid->mailentry), "");
    gtk_entry_set_text(GTK_ENTRY(wid->pwdentry), "");

    wid = NULL;
}

void signIn_entry_callback(GtkWidget *widget, gpointer data)
{
    signIn_enter_callback(NULL, NULL, data);
}

/*Sign up*/

static void signUp_enter_callback()
{
    char* firstName = gtk_entry_get_text(GTK_ENTRY(firstNameEntry));
    char* lastName = gtk_entry_get_text(GTK_ENTRY(lastNameEntry));
    char* email = gtk_entry_get_text(GTK_ENTRY(emailEntry));
    char* password = gtk_entry_get_text(GTK_ENTRY(passwordEntry));
    char* reenterPassword = gtk_entry_get_text(GTK_ENTRY(reenterPasswordEntry));
    int day = (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(daySpinButton));
    int month = (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(monthSpinButton));
    int year = (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(yearSpinButton));
    printf("\n%s", firstName);
    printf("\n%s", lastName);
    printf("\n%s", email);
    printf("\n%s", password);
    printf("\n%s", reenterPassword);
    printf("\n%d", day);
    printf("\n%d", month);
    printf("\n%d", year);
    if(findAccount(email) == 0){
        if(strcmp(password, reenterPassword) == 0 && strcmp(password, "") != 0){
            int xxx = findAccount("");
            printf("\nSuccessfully");
            char* newInfor = malloc(200);
            strcpy(newInfor, "");
            char* tmpStr = malloc(20);
            itoa(numberOfCustomers + 1, tmpStr, 10);
            strcat(newInfor, tmpStr);
            strcat(newInfor, ","); strcat(newInfor, email);
            strcat(newInfor, ","); strcat(newInfor, password);
            strcat(newInfor, ","); strcat(newInfor, firstName);
            strcat(newInfor, ","); strcat(newInfor, lastName);
            strcpy(tmpStr, ""); itoa(day, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcpy(tmpStr, ""); itoa(month, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcpy(tmpStr, ""); itoa(year, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcat(newInfor, ","); strcat(newInfor, "");
            strcpy(tmpStr, ""); itoa(0, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcpy(tmpStr, ""); itoa(0, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcat(newInfor, ",");
            strcpy(customer.pwd, password);
            changeLine(numberOfCustomers + 1, newInfor);
            numberOfCustomers++;
            gtk_entry_set_text(GTK_ENTRY(firstNameEntry), "");
            gtk_entry_set_text(GTK_ENTRY(lastNameEntry), "");
            gtk_entry_set_text(GTK_ENTRY(emailEntry), "");
            gtk_entry_set_text(GTK_ENTRY(passwordEntry), "");
            gtk_entry_set_text(GTK_ENTRY(reenterPasswordEntry), "");
            gtk_label_set_text(alert, "Successfully");
            onNoti();
        }else{
            printf("\nPassword does not match");
            gtk_label_set_text(alert, "Password does not match");
            onNoti();
        }
    }else{
        printf("\nMail is not available");
        gtk_label_set_text(alert, "Mail is not available");
        onNoti();
    }
}

static void signUp_clear_callback(){
    gtk_entry_set_text(GTK_ENTRY(firstNameEntry),"");
    gtk_entry_set_text(GTK_ENTRY(lastNameEntry),"");
    gtk_entry_set_text(GTK_ENTRY(emailEntry),"");
    gtk_entry_set_text(GTK_ENTRY(passwordEntry),"");
    gtk_entry_set_text(GTK_ENTRY(reenterPasswordEntry),"");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(yearSpinButton), 1990);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(monthSpinButton), 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(daySpinButton), 1);
}
/*Change pwd*/
int changeLine(int line, char* inputString){
    /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    char path[100];

    char buffer[1000];
    char newline[1000];
    strcpy(newline, inputString);
    strcat(newline, "\n");
    int count;
    strcpy(path, "C:\\msys64\\home\\snowi\\Fcode-ProjectC\\role\\customers.csv");
    /* Remove extra new line character from stdin */
    fflush(stdin);
    /*  Open all required files */
    fPtr  = fopen(path, "r");
    fTemp = fopen("inp.c", "w");
    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return 0;
    }

     /*
     * Read line from source file and write to destination
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, 1000, fPtr)) != NULL)
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
            fputs(newline, fTemp);
        else
            fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);


    /* Delete original source file */
    remove(path);

    /* Rename temporary file as original file */
    rename("inp.c", path);

    printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);

    return 0;
}
void changePwd_enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data)
{
    char *entryOldPwd = gtk_entry_get_text(GTK_ENTRY(oldPasswordChangeEntry));
    char *entryNewPwd = gtk_entry_get_text(GTK_ENTRY(newPasswordChangeEntry));
    char *entryConfirmPwd = gtk_entry_get_text(GTK_ENTRY(confirmNewPasswordChangeEntry));
    if(strcmp(entryOldPwd, customer.pwd) == 0){
        if(strcmp(entryNewPwd, entryConfirmPwd) == 0 && strcmp(entryNewPwd, "") != 0){
            printf("\nSuccessfully");
            char* newInfor = malloc(200);
            strcpy(newInfor, "");
            char* tmpStr = malloc(20);
            itoa(customer.id, tmpStr, 10);
            strcat(newInfor, tmpStr);
            strcat(newInfor, ","); strcat(newInfor, customer.email);
            strcat(newInfor, ","); strcat(newInfor, entryConfirmPwd);
            strcat(newInfor, ","); strcat(newInfor, customer.firstName);
            strcat(newInfor, ","); strcat(newInfor, customer.lastName);
            strcpy(tmpStr, ""); itoa(customer.dob, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcpy(tmpStr, ""); itoa(customer.mob, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcpy(tmpStr, ""); itoa(customer.yob, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcat(newInfor, ","); strcat(newInfor, customer.address);
            strcpy(tmpStr, ""); itoa(customer.type, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcpy(tmpStr, ""); itoa(customer.tikuCoin, tmpStr, 10);
            strcat(newInfor, ","); strcat(newInfor, tmpStr);
            strcat(newInfor, ",");
            strcpy(customer.pwd, entryConfirmPwd);
            changeLine(customer.id, newInfor);
            gtk_entry_set_text(GTK_ENTRY(oldPasswordChangeEntry), "");
            gtk_entry_set_text(GTK_ENTRY(newPasswordChangeEntry), "");
            gtk_entry_set_text(GTK_ENTRY(confirmNewPasswordChangeEntry), "");
            gtk_label_set_text(alert, "Successfully");
            onNoti();
        }else{
            printf("\nPassword does not match");
            gtk_label_set_text(alert, "Password does not match");
            onNoti();
        }
    }else{
        printf("\nWrong password");
        gtk_label_set_text(alert, "Wrong password");
        onNoti();
    }

}

/*Show Products*/
void cloneProducts(){
    numberOfProducts = 0;
    FILE *fp = fopen("products.csv", "r");
    char* str = malloc(1000);
    while (fgets(str, 1000, fp) != NULL)
    {
        printf("\n================");
        databaseProducts[numberOfProducts].id = 0;
        databaseProducts[numberOfProducts].supplier = 0;
        databaseProducts[numberOfProducts].price = 0;
        databaseProducts[numberOfProducts].discount = 0;
        databaseProducts[numberOfProducts].quantity = 0;
        int pos = 0;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].id = databaseProducts[numberOfProducts].id * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].id);
        pos++;
        strcpy(databaseProducts[numberOfProducts].name, "");
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos];
            strcat(databaseProducts[numberOfProducts].name, &tmp);
            pos++;
        }
        printf("\n%s", databaseProducts[numberOfProducts].name);
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].supplier = databaseProducts[numberOfProducts].supplier * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].supplier);
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].price = databaseProducts[numberOfProducts].price * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].price);
        pos++;
        while (str[pos] != ',')
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].discount = databaseProducts[numberOfProducts].discount * 10 + tmp;
            pos++;
        }
        printf("\n%d", databaseProducts[numberOfProducts].discount);
        pos++;
        while (str[pos] != 0)
        {
            int tmp = (int)str[pos] - '0';
            databaseProducts[numberOfProducts].quantity = databaseProducts[numberOfProducts].quantity * 10 + tmp;
            pos++;
        }
        pos++;
        printf("\n%d", databaseProducts[numberOfProducts].quantity);
        numberOfProducts++;
    }
    fclose(fp);
}

void change10Product(){
    /*Name*/
    gtk_label_set_text(GTK_LABEL(product1), databaseProducts[showedProducts[firstIndex]].name);
    gtk_label_set_text(GTK_LABEL(product2), databaseProducts[showedProducts[firstIndex+1]].name);
    gtk_label_set_text(GTK_LABEL(product3), databaseProducts[showedProducts[firstIndex+2]].name);
    gtk_label_set_text(GTK_LABEL(product4), databaseProducts[showedProducts[firstIndex+3]].name);
    gtk_label_set_text(GTK_LABEL(product5), databaseProducts[showedProducts[firstIndex+4]].name);
    gtk_label_set_text(GTK_LABEL(product6), databaseProducts[showedProducts[firstIndex+5]].name);
    gtk_label_set_text(GTK_LABEL(product7), databaseProducts[showedProducts[firstIndex+6]].name);
    gtk_label_set_text(GTK_LABEL(product8), databaseProducts[showedProducts[firstIndex+7]].name);
    gtk_label_set_text(GTK_LABEL(product9), databaseProducts[showedProducts[firstIndex+8]].name);
    gtk_label_set_text(GTK_LABEL(product10), databaseProducts[showedProducts[firstIndex+9]].name);
    /*ID*/
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id1), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+1]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id2), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+2]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id3), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+3]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id4), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+4]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id5), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+5]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id6), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+6]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id7), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+7]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id8), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+8]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id9), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+9]].id, tmpStr, 10);
    gtk_label_set_text(GTK_LABEL(id10), tmpStr);
    /**/
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price1), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+1]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price2), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+2]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price3), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+3]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price4), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+4]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price5), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+5]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price6), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+6]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price7), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+7]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price8), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+8]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price9), tmpStr);
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+9]].price, tmpStr, 10);
    strcat(tmpStr, ".00$");
    gtk_label_set_text(GTK_LABEL(price10), tmpStr);
    /*Imagecovers/1.png"*/
    char* tmpString = malloc(200);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img1), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+1]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img2), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+2]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img3), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+3]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img4), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+4]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img5), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+5]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img6), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+6]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img7), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+7]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img8), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+8]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img9), tmpStr);
    strcpy(tmpStr, "covers/"); itoa(databaseProducts[showedProducts[firstIndex+9]].id, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".png");
    gtk_image_set_from_file(GTK_IMAGE(img10), tmpStr);


}

static void next_page(){
    if(firstIndex + 1 <= numberOfProducts - 9){
        firstIndex += 10;
        change10Product();
    }
}

static void previous_page(){
    if(firstIndex + 1 >= 10){
        firstIndex -= 10;
        change10Product();
    }
}

static void add1(){
    if(numberOfItem < 9){
        itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex]].id-1;
        strcat(itemListText, "------------------------\nID: ");
        char* tmpStr = malloc(200);
        strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
        strcat(itemListText, tmpStr);
        strcat(itemListText, "\nName: ");
        strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
        strcat(itemListText, "\nPrice: ");
        strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex]].price, tmpStr, 10);
        strcat(itemListText, tmpStr);
        strcat(itemListText, ".00$\n");
        gtk_text_buffer_set_text (buffer, itemListText, -1);
        numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add2(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+1]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+1]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add3(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+2]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+2]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add4(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+3]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+3]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add5(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+4]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+4]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add6(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+5]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+5]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add7(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+6]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+6]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add8(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+7]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+7]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add9(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+8]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+8]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}
static void add10(){
    if(numberOfItem < 9){
    itemList[numberOfItem] = databaseProducts[showedProducts[firstIndex+9]].id-1;
    strcat(itemListText, "------------------------\nID: ");
    char* tmpStr = malloc(200);
    strcpy(tmpStr, ""); itoa(numberOfItem+1, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, "\nName: ");
    strcat(itemListText, databaseProducts[itemList[numberOfItem]].name);
    strcat(itemListText, "\nPrice: ");
    strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[firstIndex+9]].price, tmpStr, 10);
    strcat(itemListText, tmpStr);
    strcat(itemListText, ".00$\n");
    gtk_text_buffer_set_text (buffer, itemListText, -1);
    numberOfItem++;
    }else{
        gtk_label_set_text(alert, "You can only buy less than 9 items");
        onNoti();
    }
}

static void showProducts_delete_callback(){
    char *entry_id = gtk_entry_get_text(GTK_ENTRY(idDelEntry));
    if(strcmp(entry_id, "") != 0){
        int pos = 0;
        while(entry_id[pos] != '\0'){
            if(entry_id[pos] < '0' || entry_id[pos] > '9'){
                delChar(entry_id, pos);
                continue;
            }
            pos++;
        }
        pos = atoi(entry_id);
        if(pos >= 1 && pos <= numberOfItem){
            for(int i = pos; i <= numberOfItem - 2; i++){
                itemList[i] = itemList[i + 1];
            }
            numberOfItem--;
            strcpy(itemListText, "");
            for(int i = 0; i <= numberOfItem - 1; i++){
                strcat(itemListText, "------------------------\nID: ");
                char* tmpStr = malloc(200);
                strcpy(tmpStr, ""); itoa(i+1, tmpStr, 10);
                strcat(itemListText, tmpStr);
                strcat(itemListText, "\nName: ");
                strcat(itemListText, databaseProducts[itemList[i]].name);
                strcat(itemListText, "\nPrice: ");
                strcpy(tmpStr, ""); itoa(databaseProducts[showedProducts[i]].price, tmpStr, 10);
                strcat(itemListText, tmpStr);
                strcat(itemListText, ".00$\n");
                gtk_text_buffer_set_text (buffer, itemListText, -1);
            }
            gtk_entry_set_text(GTK_ENTRY(idDelEntry), "");
        }
    }else{
        gtk_entry_set_text(GTK_ENTRY(idDelEntry), "");
    }
}
/*Payment window*/
void calcCost(){
    int total = 0;
    for(int i = 0; i <= numberOfItem - 1; i++){
        total += databaseProducts[showedProducts[i]].price;
    }
    char* tmpStr = malloc(200);
    char* tmpString = malloc(200);
    strcpy(tmpStr, "$"); itoa(total, tmpString, 10); strcat(tmpStr, tmpString); strcat(tmpStr, ".00");
    printf("\n%s", tmpStr);
    gtk_label_set_text(GTK_LABEL(moneyCost), tmpStr);
    gtk_label_set_text(GTK_LABEL(moneyTotal), tmpStr);
}

/****************************************************************** GUI THREAD */
/*Openning window*/
static void activate(GtkApplication *app, gpointer data)
{
    load_css();
    GtkWidget *vboxIntro;
    GtkWidget *hboxSection;
    GtkWidget *vBoxContainer;
    GtkWidget *navbar;
    GtkWidget *logo;
    GtkWidget *header; //hbox
    GtkWidget *main;
    GtkWidget *picture;
    GtkWidget *contactButton, *aboutButton, *homeButton, *loginButton, *signUpButton;
    GtkWidget *goShoppingNow; //button
    GtkWidget *tikuLabel;
    GtkWidget *shoppingLabel;
    GtkWidget *slogan;
    tikuLabel = gtk_label_new("Tiku");
    gtk_widget_set_name(tikuLabel, "tiku");
    shoppingLabel = gtk_label_new("Shopping online");
    gtk_widget_set_name(shoppingLabel, "shoppingLabel");
    slogan = gtk_label_new("A few clicks is all it takes.\n\Life is hard enough already. Let us make it a little easier.\n\The quality service you expect.");
    contactButton = gtk_button_new_with_label("Contact");
    gtk_widget_set_name(contactButton, "contact");
    aboutButton = gtk_button_new_with_label("About");
    gtk_widget_set_name(aboutButton, "about");
    homeButton = gtk_button_new_with_label("Home");
    gtk_widget_set_name(homeButton, "home");
    signUpButton = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(signUpButton, "signup");
    g_signal_connect(G_OBJECT(signUpButton), "clicked", G_CALLBACK(s17), NULL);
    loginButton = gtk_button_new_with_label("Login");
    gtk_widget_set_name(loginButton, "loginButton");
    g_signal_connect(G_OBJECT(loginButton), "clicked", G_CALLBACK(s12), NULL);
    goShoppingNow = gtk_button_new_with_label("Go Shopping Now --->");
    gtk_widget_set_name(goShoppingNow, "goShopping");
    logo = gtk_label_new("Tiku");

    gtk_widget_set_name(logo, "logo");

    navbar = gtk_hbox_new(0, 0);

    gtk_box_pack_start(navbar, homeButton, 0, 0, 0);
    gtk_box_pack_start(navbar, aboutButton, 0, 0, 0);
    gtk_box_pack_start(navbar, contactButton, 0, 0, 0);
    gtk_box_pack_start(navbar, signUpButton, 0, 0, 0);
    gtk_box_pack_start(navbar, loginButton, 0, 0, 0);

    header = gtk_hbox_new(0, 0);
    gtk_box_pack_start(header, logo, 0, 0, 0);
    gtk_box_pack_end(header, navbar, 0, 0, 0);
    gtk_widget_set_name(header, "header");

    vboxIntro = gtk_vbox_new(0, 0);
    gtk_widget_set_name(vboxIntro, "vboxIntro");
    gtk_box_pack_start(vboxIntro, tikuLabel, 0, 0, 0);
    gtk_box_pack_start(vboxIntro, shoppingLabel, 0, 0, 0);
    gtk_box_pack_start(vboxIntro, slogan, 0, 0, 0);
    gtk_box_pack_start(vboxIntro, goShoppingNow, 0, 0, 0);
    g_signal_connect(G_OBJECT(goShoppingNow), "clicked", G_CALLBACK(s18), NULL);


    picture = gtk_image_new_from_file("background_landing_page.png");

    hboxSection = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxSection, vboxIntro, 0, 0, 0);
    gtk_box_pack_start(hboxSection, picture, 0, 0, 0);

    vBoxContainer = gtk_vbox_new(0, 0);
    gtk_box_pack_start(vBoxContainer, header, 0, 0, 0);
    gtk_box_pack_start(vBoxContainer, hboxSection, 0, 0, 0);

    openWindow = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(openWindow), "Tiku");
	gtk_window_set_default_size(GTK_WINDOW(openWindow), 350, 200);
	gtk_window_set_resizable(GTK_WINDOW(openWindow), FALSE);
	gtk_window_set_position(GTK_WINDOW(openWindow), GTK_WIN_POS_CENTER);
	gtk_container_add(openWindow, vBoxContainer);
	gtk_widget_show_all(openWindow);
}
/*Sign in window*/
static void signInActivate(GtkApplication *app, gpointer data)
{
    GtkWidget *vbox, *hbox;
    GtkWidget *headerbar;
    GtkStyleContext *context;

    appWidgets *wid = (appWidgets *)data;
    // map menu actions to callbacks
    const GActionEntry app_actions[] = {
        {"enter", signIn_enter_callback, NULL, NULL, NULL},
        {"clear", signIn_clear_callback, NULL, NULL, NULL}};

    // create a window with title, default size and icons
    signInWindow = gtk_application_window_new(app);
    gtk_window_set_application(GTK_WINDOW(signInWindow), GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(signInWindow), "Sign in");
    gtk_window_set_position(GTK_WINDOW(signInWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(signInWindow), FALSE);
    gtk_window_set_default_icon_from_file("icon.png", NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(signInWindow), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(signInWindow), 10);

    // create label and entry
    wid->greeterlabel = gtk_label_new_with_mnemonic("Let's sign in!");
    gtk_widget_override_font(wid->greeterlabel,
                             pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(wid->greeterlabel, 0, 50);
    gtk_box_pack_start(GTK_BOX(vbox), wid->greeterlabel, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    wid->maillabel = gtk_label_new_with_mnemonic("Email:");
    gtk_widget_set_size_request(wid->maillabel, 60, 40);
    gtk_box_pack_start(GTK_BOX(hbox), wid->maillabel, FALSE, FALSE, 0);

    wid->mailentry = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(wid->mailentry), "tuankietbdsm21");
    gtk_box_pack_start(GTK_BOX(hbox), wid->mailentry, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(wid->mailentry), "activate",
                     G_CALLBACK(signIn_entry_callback), (gpointer)wid);

    wid->pwdlabel = gtk_label_new_with_mnemonic("Password:");
    gtk_widget_set_size_request(wid->pwdlabel, 60, 40);
    gtk_box_pack_start(GTK_BOX(hbox), wid->pwdlabel, FALSE, FALSE, 0);
    wid->pwdentry = gtk_entry_new();

    gtk_entry_set_visibility(GTK_ENTRY(wid->pwdentry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(wid->pwdentry), "");
    gtk_box_pack_start(GTK_BOX(hbox), wid->pwdentry, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(wid->pwdentry), "activate",
                     G_CALLBACK(signIn_entry_callback), (gpointer)wid);
    // create a headerbar
    headerbar = gtk_header_bar_new();
    gtk_widget_show(headerbar);
    gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "F CODE SHOPPING");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar),
                                "Code the Circus");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(signInWindow), headerbar);

    // create Clear button
    wid->clearbutton = gtk_button_new_with_label("Clear");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(wid->clearbutton), "app.clear");
    context = gtk_widget_get_style_context(wid->clearbutton);
    gtk_style_context_add_class(context, "text-button");
    gtk_style_context_add_class(context, "destructive-action");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), wid->clearbutton);

    // create Enter button
    wid->enterbutton = gtk_button_new_with_label("Log in");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(wid->enterbutton), "app.enter");
    context = gtk_widget_get_style_context(wid->enterbutton);
    gtk_style_context_add_class(context, "text-button");
    gtk_style_context_add_class(context, "suggested-action");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), wid->enterbutton);

    g_action_map_add_action_entries(G_ACTION_MAP(app), app_actions,
                                    G_N_ELEMENTS(app_actions), wid);

    //gtk_widget_show_all(GTK_WIDGET(signInWindow));
}
/*Sign up window*/
static void signUpActivate(GtkApplication *app, gpointer data)
{

    GtkWidget *changeOption, *registerBackground;
    GtkWidget *registerLabel, *inforRegisterLabel, *askRegisterLabel, *dayLabel, *monthLabel, *yearLabel, *imgLabel;
    GtkWidget *vboxRegisterContainer, *headerBox, *userNamehBox, *dateRegisterBox, *boxAllRegister, *imgBox;
    GtkWidget *registerButton, *backRegisterButton, *imgButton, *clearButton;
    boxAllRegister = gtk_hbox_new(0, 10);
    firstNameEntry = gtk_entry_new();
    lastNameEntry = gtk_entry_new();
    emailEntry = gtk_entry_new();
    registerBackground = gtk_image_new_from_file("background.png");
    imgButton = gtk_button_new_from_icon_name("user-home", 0);
    imgLabel = gtk_label_new("Add your first avatar");
    dayLabel =  gtk_label_new("Date");
    monthLabel = gtk_label_new("Month");
    yearLabel = gtk_label_new("Year");
    monthSpinButton = gtk_spin_button_new_with_range(1, 12, 1);
    daySpinButton = gtk_spin_button_new_with_range(1, 31, 1);
    yearSpinButton = gtk_spin_button_new_with_range(1900, 2021, 1);
    passwordEntry = gtk_entry_new();
    reenterPasswordEntry = gtk_entry_new();
    registerLabel = gtk_label_new("------------Register------------");
    gtk_widget_set_name(registerLabel, "registerLabel");
    inforRegisterLabel = gtk_label_new("Create your account. It's free and only takes a minute");
    registerButton = gtk_button_new_with_label("Register Now");
    gtk_widget_set_name(registerButton, "registerButton");
    g_signal_connect(G_OBJECT(registerButton), "clicked", G_CALLBACK(signUp_enter_callback), NULL);
    askRegisterLabel = gtk_label_new("Wanna change your option?");
    backRegisterButton = gtk_button_new_with_label("Back");
    g_signal_connect(G_OBJECT(backRegisterButton), "clicked", G_CALLBACK(s71), NULL);

    clearButton = gtk_button_new_with_label("Clear");
    gtk_widget_set_name(clearButton, "clearButton");
    g_signal_connect(G_OBJECT(clearButton), "clicked", G_CALLBACK(signUp_clear_callback), NULL);
    gtk_widget_set_name(backRegisterButton,"backRegisterButton");
    gtk_entry_set_placeholder_text(firstNameEntry, "First name");
    gtk_entry_set_placeholder_text(lastNameEntry, "Last name");
    gtk_entry_set_placeholder_text(emailEntry, "Email address");
    gtk_entry_set_icon_from_icon_name(emailEntry, GTK_POS_RIGHT, "mail-read");
    gtk_entry_set_placeholder_text(passwordEntry, "Password");
    gtk_entry_set_icon_from_icon_name(passwordEntry, GTK_POS_RIGHT, "dialog-password");
    gtk_entry_set_visibility(passwordEntry, FALSE);
    gtk_entry_set_placeholder_text(reenterPasswordEntry, "Confirm password");
    gtk_entry_set_icon_from_icon_name(reenterPasswordEntry, GTK_POS_RIGHT, "dialog-password");
    gtk_entry_set_visibility(reenterPasswordEntry, FALSE);
    imgBox = gtk_hbox_new(0, 20);
    gtk_box_pack_start(imgBox, imgLabel, 0, 0, 0);
    gtk_box_pack_start(imgBox, imgButton, 0, 0, 0);
    changeOption = gtk_hbox_new(0, 10);
    gtk_box_pack_start(changeOption, clearButton, 0, 0, 0);
    gtk_box_pack_end(changeOption, backRegisterButton, 0, 0, 0);
    gtk_box_pack_end(changeOption, askRegisterLabel, 0, 0, 0);
    headerBox = gtk_vbox_new(0, 15);
    gtk_box_pack_start(headerBox, registerLabel, 0, 0, 0);
    gtk_box_pack_start(headerBox, inforRegisterLabel, 0, 0, 0);
    userNamehBox = gtk_hbox_new(0, 10);
    gtk_box_pack_start(userNamehBox, firstNameEntry, 0, 0, 0);
    gtk_box_pack_start(userNamehBox, lastNameEntry, 0, 0, 0);
    dateRegisterBox = gtk_hbox_new(0, 5);
    gtk_box_pack_start(dateRegisterBox, dayLabel, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, daySpinButton, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, monthLabel, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, monthSpinButton, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, yearLabel, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, yearSpinButton, 0, 0, 0);

    vboxRegisterContainer = gtk_vbox_new(0, 0);
    gtk_box_pack_start(vboxRegisterContainer, headerBox, 0, 0, 30);
    gtk_box_pack_start(vboxRegisterContainer, userNamehBox, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, emailEntry, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, dateRegisterBox, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, imgBox, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, passwordEntry, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, reenterPasswordEntry, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, registerButton, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, changeOption, 0, 0, 10);
    gtk_box_pack_start(boxAllRegister, registerBackground, 0, 0, 0);
    gtk_box_pack_start(boxAllRegister, vboxRegisterContainer, 0, 0, 0);
    gtk_widget_set_name(boxAllRegister,"boxAllRegister");
    signUpWindow = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(signUpWindow), "Register-Form");
	gtk_window_set_default_size(GTK_WINDOW(signUpWindow), 500, 500);
	gtk_window_set_resizable(GTK_WINDOW(signUpWindow), FALSE);
	gtk_window_set_position(GTK_WINDOW(signUpWindow), GTK_WIN_POS_CENTER);
	gtk_container_add(signUpWindow, boxAllRegister);
}

static void customerMapActivate(GtkApplication *app, gpointer user_data)
{

    GtkWidget *clientMenu; //grid
    GtkWidget *helloLabel, *balanceLabel;
    GtkWidget *buyHistoryButton, *changePassButton, *changeInforButton, *shoppingButton, *logoutButton, *showInforButton;
    GtkWidget *headerClientBox, *topContainBox, *containerClient;
    // khoi tao
    clientMenu = gtk_grid_new();
    gtk_widget_set_name(clientMenu, "clientMenu");
    containerClient = gtk_vbox_new(0, 0);
    helloLabel = gtk_label_new("Hello customer!");
    balanceLabel = gtk_label_new("Balance: $0.00");
    buyHistoryButton = gtk_button_new_with_label("Purchase history");
    changePassButton = gtk_button_new_with_label("Change password");
    g_signal_connect(G_OBJECT(changePassButton), "clicked", G_CALLBACK(s34), NULL);
    changeInforButton = gtk_button_new_with_label("Change information");
    g_signal_connect(G_OBJECT(changeInforButton), "clicked", G_CALLBACK(s35), NULL);
    shoppingButton = gtk_button_new_with_label("Go shopping");
    g_signal_connect(G_OBJECT(shoppingButton), "clicked", G_CALLBACK(s38), NULL);
    showInforButton = gtk_button_new_with_label("Show informatiom");
    g_signal_connect(G_OBJECT(showInforButton), "clicked", G_CALLBACK(s310), NULL);
    logoutButton = gtk_button_new_with_label("Log out");
    g_signal_connect(G_OBJECT(logoutButton), "clicked", G_CALLBACK(s31), NULL);

    topContainBox = gtk_hbox_new(0, 20);
    gtk_box_pack_start(topContainBox, helloLabel, 0, 0, 0);
    gtk_box_pack_end(topContainBox, balanceLabel, 0, 0, 0);

    headerClientBox = gtk_hbox_new(0, 10);
    gtk_box_pack_start(headerClientBox, topContainBox, 0, 0, 0);
    gtk_widget_set_name(headerClientBox, "headerClientBox");

    gtk_grid_attach(clientMenu, buyHistoryButton, 0, 0, 1, 1);
    gtk_grid_attach(clientMenu, changePassButton, 1, 0, 1, 1);
    gtk_grid_attach(clientMenu, changeInforButton, 2, 0, 1, 1);
    gtk_grid_attach(clientMenu, shoppingButton, 0, 1, 1, 1);
    gtk_grid_attach(clientMenu, showInforButton, 1, 1, 1, 1);
    gtk_grid_attach(clientMenu, logoutButton, 2, 1, 1, 1);

    gtk_box_pack_start(containerClient, headerClientBox, 0, 0, 20);
    gtk_box_pack_end(containerClient, clientMenu, 0, 0, 0);

    customerMapWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(customerMapWindow), "Client site");
    gtk_window_set_default_size(GTK_WINDOW(customerMapWindow), 400, 200);
    gtk_window_set_resizable(GTK_WINDOW(customerMapWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(customerMapWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(customerMapWindow, containerClient);
    //gtk_widget_show_all(customerMapWindow);
}

static void supplierMapActivate(GtkApplication *app, gpointer user_data)
{

    GtkWidget *clientMenu; //grid
    GtkWidget *helloLabel, *balanceLabel;
    GtkWidget *buyHistoryButton, *changePassButton, *changeInforButton, *shoppingButton, *logoutButton, *showInforButton;
    GtkWidget *headerClientBox, *topContainBox, *containerClient;
    // khoi tao
    clientMenu = gtk_grid_new();
    gtk_widget_set_name(clientMenu, "clientMenu");
    containerClient = gtk_vbox_new(0, 0);
    helloLabel = gtk_label_new("Hello customer!");
    balanceLabel = gtk_label_new("Balance: $0.00");
    buyHistoryButton = gtk_button_new_with_label("Products Managerment");
    changePassButton = gtk_button_new_with_label("Change password");
    g_signal_connect(G_OBJECT(changePassButton), "clicked", G_CALLBACK(s94), NULL);
    changeInforButton = gtk_button_new_with_label("Change information");
    g_signal_connect(G_OBJECT(changeInforButton), "clicked", G_CALLBACK(s95), NULL);
    shoppingButton = gtk_button_new_with_label("See your products");
    g_signal_connect(G_OBJECT(shoppingButton), "clicked", G_CALLBACK(s98), NULL);
    showInforButton = gtk_button_new_with_label("Show information");
    g_signal_connect(G_OBJECT(showInforButton), "clicked", G_CALLBACK(s910), NULL);
    logoutButton = gtk_button_new_with_label("Log out");
    g_signal_connect(G_OBJECT(logoutButton), "clicked", G_CALLBACK(s91), NULL);

    topContainBox = gtk_hbox_new(0, 20);
    gtk_box_pack_start(topContainBox, helloLabel, 0, 0, 0);
    gtk_box_pack_end(topContainBox, balanceLabel, 0, 0, 0);

    headerClientBox = gtk_hbox_new(0, 10);
    gtk_box_pack_start(headerClientBox, topContainBox, 0, 0, 0);
    gtk_widget_set_name(headerClientBox, "headerClientBox");

    gtk_grid_attach(clientMenu, buyHistoryButton, 0, 0, 1, 1);
    gtk_grid_attach(clientMenu, changePassButton, 1, 0, 1, 1);
    gtk_grid_attach(clientMenu, changeInforButton, 2, 0, 1, 1);
    gtk_grid_attach(clientMenu, shoppingButton, 0, 1, 1, 1);
    gtk_grid_attach(clientMenu, showInforButton, 1, 1, 1, 1);
    gtk_grid_attach(clientMenu, logoutButton, 2, 1, 1, 1);

    gtk_box_pack_start(containerClient, headerClientBox, 0, 0, 20);
    gtk_box_pack_end(containerClient, clientMenu, 0, 0, 0);

    supplierMapWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(supplierMapWindow), "Client site");
    gtk_window_set_default_size(GTK_WINDOW(supplierMapWindow), 400, 200);
    gtk_window_set_resizable(GTK_WINDOW(supplierMapWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(supplierMapWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(supplierMapWindow, containerClient);
    //gtk_widget_show_all(customerMapWindow);
}

static void changePwdActivate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *containerLogin, *containerLeftSideLogin, *footerBox;
    GtkWidget *changePassWordLabel, *askBackLabel;
    GtkWidget *updateChangePasswordButton, *backChangePasswordButton;
    GtkWidget *loginImg;

    changePassWordLabel = gtk_label_new("Change your password");
    gtk_widget_set_name(changePassWordLabel, "changePassLabel");
    loginImg = gtk_image_new_from_file("login.png");

    backChangePasswordButton = gtk_button_new_with_label("Back");
    gtk_widget_set_name(backChangePasswordButton, "backChangePasswordButton");
    g_signal_connect(G_OBJECT(backChangePasswordButton), "clicked", G_CALLBACK(s43), NULL);
    askBackLabel = gtk_label_new("Change your mind?");
    footerBox = gtk_hbox_new(1, 0);
    gtk_box_pack_start(footerBox, askBackLabel, 0, 0, 10);
    gtk_box_pack_end(footerBox, backChangePasswordButton, 0, 0, 0);

    oldPasswordChangeEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(oldPasswordChangeEntry, "Enter your old password");
    gtk_entry_set_visibility(oldPasswordChangeEntry, FALSE);
    newPasswordChangeEntry = gtk_entry_new();

    gtk_entry_set_placeholder_text(newPasswordChangeEntry, "Enter your new password");
    gtk_entry_set_visibility(newPasswordChangeEntry, FALSE);
    confirmNewPasswordChangeEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(confirmNewPasswordChangeEntry, "Confirm your new password");
    gtk_entry_set_visibility(confirmNewPasswordChangeEntry, FALSE);
    updateChangePasswordButton = gtk_button_new_with_label("Update");
    gtk_widget_set_name(updateChangePasswordButton, "updateButton");
    g_signal_connect(G_OBJECT(updateChangePasswordButton), "clicked", G_CALLBACK(changePwd_enter_callback), NULL);



    containerLeftSideLogin = gtk_vbox_new(0, 0);
    gtk_box_pack_start(containerLeftSideLogin, changePassWordLabel, 0, 0, 20);
    gtk_box_pack_start(containerLeftSideLogin, oldPasswordChangeEntry, 0, 0, 5);
    gtk_box_pack_start(containerLeftSideLogin, newPasswordChangeEntry, 0, 0, 5);
    gtk_box_pack_start(containerLeftSideLogin, confirmNewPasswordChangeEntry, 0, 0, 5);
    gtk_box_pack_start(containerLeftSideLogin, updateChangePasswordButton, 0, 0, 20);
    gtk_box_pack_end(containerLeftSideLogin, footerBox, 0, 0, 0);
    gtk_widget_set_name(containerLeftSideLogin, "containerLeftSideLogin");
    containerLogin = gtk_hbox_new(1, 0);
    gtk_box_pack_start(containerLogin, loginImg, 0, 0, 0);
    gtk_box_pack_end(containerLogin, containerLeftSideLogin, 0, 0, 0);

    changePwdWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(changePwdWindow), "Saler site");
    gtk_window_set_default_size(GTK_WINDOW(changePwdWindow), 500, 300);
    gtk_window_set_resizable(GTK_WINDOW(changePwdWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(changePwdWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(changePwdWindow, containerLogin);
}

static void changeInformationActivate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *addressChangeInforLabel, *firstNameChangeInforLabel, *lastNameChangeInforLabel;

    GtkWidget *addressChangeInforEntry, *firstNameChangeInforEntry, *lastNameChangeInforEntry;

    GtkWidget *updateChangeInforButton, *backChangeInforButton;
    GtkWidget *askBackChangeInforLabel;
    GtkWidget *gridChangeInfor, *containerChangeInfor, *hboxFooter;
    GtkWidget *changeInforImg;
    //set up
    containerChangeInfor = gtk_hbox_new(1, 0);
    gridChangeInfor = gtk_grid_new();
    //
    changeInforImg = gtk_image_new_from_file("change_infor.png");
    addressChangeInforEntry = gtk_entry_new();
    firstNameChangeInforEntry = gtk_entry_new();
    lastNameChangeInforEntry = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(addressChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "emblem-mail");
    gtk_entry_set_placeholder_text(addressChangeInforEntry, "Enter your address");
    gtk_entry_set_icon_from_icon_name(firstNameChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "contact-new");
    gtk_entry_set_placeholder_text(firstNameChangeInforEntry, "Enter your first name");
    gtk_entry_set_icon_from_icon_name(lastNameChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "phone");
    gtk_entry_set_placeholder_text(lastNameChangeInforEntry, "Enter your last name");
    //
    askBackChangeInforLabel = gtk_label_new("Change your mind ?");
    backChangeInforButton = gtk_button_new_with_label("Back");
    g_signal_connect(G_OBJECT(backChangeInforButton), "clicked", G_CALLBACK(s53), NULL);
    gtk_widget_set_name(backChangeInforButton, "backChangeInforButton");

    hboxFooter = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxFooter, askBackChangeInforLabel, 0, 0, 10);
    gtk_box_pack_end(hboxFooter, backChangeInforButton, 0, 0, 0);

    addressChangeInforLabel = gtk_label_new("Address: ");
    firstNameChangeInforLabel = gtk_label_new("First name: ");
    lastNameChangeInforLabel = gtk_label_new("Last name: ");
    updateChangeInforButton = gtk_button_new_with_label("Update");

    //
    gtk_grid_attach(gridChangeInfor, firstNameChangeInforLabel, 0, 0, 1, 1);
    gtk_grid_attach(gridChangeInfor, firstNameChangeInforEntry, 1, 0, 1, 1);
    gtk_grid_attach(gridChangeInfor, lastNameChangeInforLabel, 0, 1, 1, 1);
    gtk_grid_attach(gridChangeInfor, lastNameChangeInforEntry, 1, 1, 1, 1);
    gtk_grid_attach(gridChangeInfor, addressChangeInforLabel, 0, 2, 1, 1);
    gtk_grid_attach(gridChangeInfor, addressChangeInforEntry, 1, 2, 1, 1);
    gtk_grid_attach(gridChangeInfor, updateChangeInforButton, 1, 3, 1, 1);
    gtk_grid_attach(gridChangeInfor, hboxFooter, 1, 4, 1, 1);
    gtk_grid_set_column_spacing(gridChangeInfor, 10);
    gtk_grid_set_row_spacing(gridChangeInfor, 10);
    gtk_widget_set_name(gridChangeInfor, "gridChangeInfor");
    gtk_box_pack_start(containerChangeInfor, gridChangeInfor, 0, 0, 0);
    gtk_box_pack_end(containerChangeInfor, changeInforImg, 0, 0, 0);
    gtk_widget_set_name(updateChangeInforButton, "changeInforButton");
    changeInformationWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(changeInformationWindow), "Change Information");
    gtk_window_set_default_size(GTK_WINDOW(changeInformationWindow), 350, 200);
    gtk_window_set_resizable(GTK_WINDOW(changeInformationWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(changeInformationWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(changeInformationWindow, containerChangeInfor);
}

static void notiActivate(GtkApplication *app, gpointer data) {
    load_css();

    GtkWidget *alertButton;
    GtkWidget *vboxAlert;
    GtkWidget *hboxAlert;
    GtkWidget *nonLabelAlert;
    nonLabelAlert = gtk_label_new("             ");
    vboxAlert = gtk_vbox_new(1, 0);
    alertButton = gtk_button_new_with_label("close");
    g_signal_connect(G_OBJECT(alertButton), "clicked", G_CALLBACK(offNoti), NULL);
    alert = gtk_label_new("Hello!!!");
    gtk_widget_set_name(alert, "alert");
    /*alert = gtk_label_new_with_mnemonic("Let's sign in!");
    gtk_widget_override_font(alert,
                             pango_font_description_from_string("Tahoma 20"));*/
    hboxAlert = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxAlert, nonLabelAlert, 0, 0, 0);
    gtk_box_pack_end(hboxAlert, alertButton, 0, 0, 0);
    gtk_box_pack_start(vboxAlert, alert, 0, 0, 10);
    gtk_box_pack_start(vboxAlert, hboxAlert, 0, 0, 0);
    gtk_widget_set_name(alertButton, "alertButton");
    gtk_widget_set_name(vboxAlert, "vboxAlert");
    notiWindow = gtk_application_window_new(app);
    notiWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(notiWindow), "");
    gtk_window_set_default_size(GTK_WINDOW(notiWindow),200,20);
    gtk_window_set_resizable(GTK_WINDOW(notiWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(notiWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(notiWindow, vboxAlert);
}
/*Show products*/
static void showProductsActivate(GtkApplication *app, gpointer data)
{
    GtkWidget *menuLabel;
    GtkWidget *textView, *leftSidevBox, *gridButton, *confirmDelButton, *backShowCartButton, *paymentButton;
    GtkWidget *hboxContainer, *hboxSearch, *hboxPage, *boxTop, *vboxContain; //container
    GtkWidget *GridItem;
    GtkWidget *box1, *box2, *box3, *box4, *box5, *box6, *box7, *box8, *box9, *box10; //box_gio_hang
    GtkWidget *searchLabel;
    GtkWidget *searchProducts;
    GtkWidget *searchButton;
    GtkWidget *nextPage, *previousPage;



    GtkWidget *buttonAdd1, *buttonAdd2, *buttonAdd3, *buttonAdd4, *buttonAdd5, *buttonAdd6, *buttonAdd7, *buttonAdd8, *buttonAdd9, *buttonAdd10;


    //
    textView = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textView));
    gtk_text_view_set_wrap_mode(textView, GTK_WRAP_WORD);
    gtk_text_buffer_set_text (buffer, "You have not selected any items", -1);
    gtk_text_view_set_editable(textView, FALSE);
    //
    searchLabel = gtk_label_new("Search product: ");
    searchButton = gtk_button_new_from_icon_name("system-search", 1);
    searchProducts = gtk_search_entry_new();
    gtk_widget_set_name(searchProducts, "search");

    menuLabel = gtk_label_new("ID               NAME              PRICE");
    gtk_widget_set_name(menuLabel, "menuLabel");
    nextPage = gtk_button_new_with_label(">>>>>");
    previousPage = gtk_button_new_with_label("<<<<<");

    gridButton = gtk_grid_new();
    confirmDelButton = gtk_button_new_with_label("Delete");
    gtk_widget_set_name(confirmDelButton, "Delete");
    g_signal_connect(G_OBJECT(confirmDelButton), "clicked", G_CALLBACK(showProducts_delete_callback), NULL);
    backShowCartButton = gtk_button_new_with_label("Back");
    paymentButton = gtk_button_new_with_label("Payment");
    idDelEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(idDelEntry,"Enter product's ID       ");
    gtk_widget_set_name(idDelEntry, "delId");
    gtk_grid_attach(gridButton, idDelEntry, 0, 0, 2, 1);
    gtk_grid_attach(gridButton, confirmDelButton, 3, 0, 1, 1);
    gtk_grid_attach(gridButton, paymentButton, 0, 1, 1, 1);
    gtk_grid_attach(gridButton, backShowCartButton, 3, 1, 1, 1);
    gtk_grid_set_column_spacing(gridButton, 20);
    gtk_grid_set_row_spacing(gridButton, 20);

    gtk_widget_set_name(textView, "textView");
    leftSidevBox = gtk_vbox_new(0, 0);
    gtk_box_pack_start(leftSidevBox, menuLabel, 0, 0, 0);
    gtk_box_pack_start(leftSidevBox, textView, TRUE, TRUE, 20);
    gtk_box_pack_end(leftSidevBox, gridButton, 0, 0, 0);

    gtk_widget_set_name(leftSidevBox, "leftSidevBox");
    gtk_widget_set_name(backShowCartButton, "backCart");
    g_signal_connect(G_OBJECT(backShowCartButton), "clicked", G_CALLBACK(s83), NULL);
    gtk_widget_set_name(paymentButton, "paymentButton");
    g_signal_connect(G_OBJECT(paymentButton), "clicked", G_CALLBACK(s811), NULL);
    id1 = gtk_label_new("ID1");
    gtk_widget_set_name(id1, "id1");
    id2 = gtk_label_new("ID2");
    gtk_widget_set_name(id2, "id2");
    id3 = gtk_label_new("ID3");
    gtk_widget_set_name(id3, "id3");
    id4 = gtk_label_new("ID4");
    gtk_widget_set_name(id4, "id4");
    id5 = gtk_label_new("ID5");
    gtk_widget_set_name(id5, "id5");
    id6 = gtk_label_new("ID6");
    gtk_widget_set_name(id6, "id6");
    id7 = gtk_label_new("ID7");
    gtk_widget_set_name(id7, "id7");
    id8 = gtk_label_new("ID8");
    gtk_widget_set_name(id8, "id8");
    id9 = gtk_label_new("ID9");
    gtk_widget_set_name(id9, "id9");
    id10 = gtk_label_new("ID10");
    gtk_widget_set_name(id10, "id10");

    product1 = gtk_label_new("product 1");
    product2 = gtk_label_new("product 2");
    product3 = gtk_label_new("product 3");
    product4 = gtk_label_new("product 4");
    product5 = gtk_label_new("product 5");
    product6 = gtk_label_new("product 6");
    product7 = gtk_label_new("product 7");
    product8 = gtk_label_new("product 8");
    product9 = gtk_label_new("product 9");
    product10 = gtk_label_new("product 10");


    price1 = gtk_label_new("$0.00");
    price2 = gtk_label_new("$0.00");
    price3 = gtk_label_new("$0.00");
    price4 = gtk_label_new("$0.00");
    price5 = gtk_label_new("$0.00");
    price6 = gtk_label_new("$0.00");
    price7 = gtk_label_new("$0.00");
    price8 = gtk_label_new("$0.00");
    price9 = gtk_label_new("$0.00");
    price10 = gtk_label_new("$0.00");

    buttonAdd1 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd2 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd3 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd4 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd5 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd6 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd7 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd8 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd9 = gtk_button_new_from_icon_name("list-add", 0);
    buttonAdd10 = gtk_button_new_from_icon_name("list-add", 0);

    img1 = gtk_image_new_from_file("covers/1.png");
    img2 = gtk_image_new_from_file("covers/1.png");
    img3 = gtk_image_new_from_file("covers/1.png");
    img4 = gtk_image_new_from_file("covers/1.png");
    img5 = gtk_image_new_from_file("covers/1.png");
    img6 = gtk_image_new_from_file("covers/1.png");
    img7 = gtk_image_new_from_file("covers/1.png");
    img8 = gtk_image_new_from_file("covers/1.png");
    img9 = gtk_image_new_from_file("covers/1.png");
    img10 = gtk_image_new_from_file("covers/1.png");

    box1 = gtk_vbox_new(0, 0);
    box2 = gtk_vbox_new(0, 0);
    box3 = gtk_vbox_new(0, 0);
    box4 = gtk_vbox_new(0, 0);
    box5 = gtk_vbox_new(0, 0);
    box6 = gtk_vbox_new(0, 0);
    box7 = gtk_vbox_new(0, 0);
    box8 = gtk_vbox_new(0, 0);
    box9 = gtk_vbox_new(0, 0);
    box10 = gtk_vbox_new(0, 0);

    gtk_box_pack_start(box1, id1, 0, 0, 5);
    gtk_box_pack_start(box1, img1, 0, 0, 5);
    gtk_box_pack_start(box1, product1, 0, 0, 5);
    gtk_box_pack_start(box1, price1, 0, 0, 5);
    gtk_box_pack_end(box1, buttonAdd1, 0, 0, 5);

    gtk_box_pack_start(box2, id2, 0, 0, 5);
    gtk_box_pack_start(box2, img2, 0, 0, 5);
    gtk_box_pack_start(box2, product2, 0, 0, 5);
    gtk_box_pack_start(box2, price2, 0, 0, 5);
    gtk_box_pack_end(box2, buttonAdd2, 0, 0, 5);

    gtk_box_pack_start(box3, id3, 0, 0, 5);
    gtk_box_pack_start(box3, img3, 0, 0, 5);
    gtk_box_pack_start(box3, product3, 0, 0, 5);
    gtk_box_pack_start(box3, price3, 0, 0, 5);
    gtk_box_pack_end(box3, buttonAdd3, 0, 0, 5);

    gtk_box_pack_start(box4, id4, 0, 0, 5);
    gtk_box_pack_start(box4, img4, 0, 0, 5);
    gtk_box_pack_start(box4, product4, 0, 0, 5);
    gtk_box_pack_start(box4, price4, 0, 0, 5);
    gtk_box_pack_end(box4, buttonAdd4, 0, 0, 5);

    gtk_box_pack_start(box5, id5, 0, 0, 5);
    gtk_box_pack_start(box5, img5, 0, 0, 5);
    gtk_box_pack_start(box5, product5, 0, 0, 5);
    gtk_box_pack_start(box5, price5, 0, 0, 5);
    gtk_box_pack_end(box5, buttonAdd5, 0, 0, 5);

    gtk_box_pack_start(box6, id6, 0, 0, 5);
    gtk_box_pack_start(box6, img6, 0, 0, 5);
    gtk_box_pack_start(box6, product6, 0, 0, 5);
    gtk_box_pack_start(box6, price6, 0, 0, 5);
    gtk_box_pack_end(box6, buttonAdd6, 0, 0, 5);


    gtk_box_pack_start(box7, id7, 0, 0, 5);
    gtk_box_pack_start(box7, img7, 0, 0, 5);
    gtk_box_pack_start(box7, product7, 0, 0, 5);
    gtk_box_pack_start(box7, price7, 0, 0, 5);
    gtk_box_pack_end(box7, buttonAdd7, 0, 0, 5);

    gtk_box_pack_start(box8, id8, 0, 0, 5);
    gtk_box_pack_start(box8, img8, 0, 0, 5);
    gtk_box_pack_start(box8, product8, 0, 0, 5);
    gtk_box_pack_start(box8, price8, 0, 0, 5);
    gtk_box_pack_end(box8, buttonAdd8, 0, 0, 5);

    gtk_box_pack_start(box9, id9, 0, 0, 5);
    gtk_box_pack_start(box9, img9, 0, 0, 5);
    gtk_box_pack_start(box9, product9, 0, 0, 5);
    gtk_box_pack_start(box9, price9, 0, 0, 5);
    gtk_box_pack_end(box9, buttonAdd9, 0, 0, 5);

    gtk_box_pack_start(box10, id10, 0, 0, 5);
    gtk_box_pack_start(box10, img10, 0, 0, 5);
    gtk_box_pack_start(box10, product10, 0, 0, 5);
    gtk_box_pack_start(box10, price10, 0, 0, 5);
    gtk_box_pack_end(box10, buttonAdd10, 0, 0, 5);

    g_signal_connect(G_OBJECT(buttonAdd1), "clicked", G_CALLBACK(add1), NULL);
    g_signal_connect(G_OBJECT(buttonAdd2), "clicked", G_CALLBACK(add2), NULL);
    g_signal_connect(G_OBJECT(buttonAdd3), "clicked", G_CALLBACK(add3), NULL);
    g_signal_connect(G_OBJECT(buttonAdd4), "clicked", G_CALLBACK(add4), NULL);
    g_signal_connect(G_OBJECT(buttonAdd5), "clicked", G_CALLBACK(add5), NULL);
    g_signal_connect(G_OBJECT(buttonAdd6), "clicked", G_CALLBACK(add6), NULL);
    g_signal_connect(G_OBJECT(buttonAdd7), "clicked", G_CALLBACK(add7), NULL);
    g_signal_connect(G_OBJECT(buttonAdd8), "clicked", G_CALLBACK(add8), NULL);
    g_signal_connect(G_OBJECT(buttonAdd9), "clicked", G_CALLBACK(add9), NULL);
    g_signal_connect(G_OBJECT(buttonAdd10), "clicked", G_CALLBACK(add10), NULL);

    gtk_widget_set_name(box1 ,"box1");
    gtk_widget_set_name(box2 ,"box2");
    gtk_widget_set_name(box3 ,"box3");
    gtk_widget_set_name(box4 ,"box4");
    gtk_widget_set_name(box5 ,"box5");
    gtk_widget_set_name(box6 ,"box6");
    gtk_widget_set_name(box7 ,"box7");
    gtk_widget_set_name(box8 ,"box8");
    gtk_widget_set_name(box9 ,"box9");
    gtk_widget_set_name(box10 ,"box10");


    GridItem = gtk_grid_new();
    gtk_grid_attach(GridItem, box1, 0, 0, 1, 1);
    gtk_grid_attach(GridItem, box2, 1, 0, 1, 1);
    gtk_grid_attach(GridItem, box3, 2, 0, 1, 1);
    gtk_grid_attach(GridItem, box4, 3, 0, 1, 1);
    gtk_grid_attach(GridItem, box5, 4, 0, 1, 1);
    gtk_grid_attach(GridItem, box6, 0, 1, 1, 1);
    gtk_grid_attach(GridItem, box7, 1, 1, 1, 1);
    gtk_grid_attach(GridItem, box8, 2, 1, 1, 1);
    gtk_grid_attach(GridItem, box9, 3, 1, 1, 1);
    gtk_grid_attach(GridItem, box10, 4, 1, 1, 1);

    hboxSearch = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxSearch, searchLabel, 0, 0, 0);
    gtk_box_pack_start(hboxSearch, searchProducts, 0, 0, 0);
    gtk_box_pack_start(hboxSearch, searchButton, 0, 0, 0);
    gtk_box_pack_end(hboxSearch, nextPage, 0, 0, 0);
    gtk_box_pack_end(hboxSearch, previousPage, 0, 0, 0);
    g_signal_connect(G_OBJECT(nextPage), "clicked", G_CALLBACK(next_page), NULL);
    g_signal_connect(G_OBJECT(previousPage), "clicked", G_CALLBACK(previous_page), NULL);

    vboxContain = gtk_vbox_new(0, 0);
    gtk_box_pack_start(vboxContain, hboxSearch, 0, 0, 0);
    gtk_box_pack_start(vboxContain, GridItem, 0, 0, 0);

    hboxContainer = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxContainer, vboxContain, 0, 0, 0);
    gtk_box_pack_start(hboxContainer, leftSidevBox, 0, 0, 0);
    gtk_widget_set_name(hboxSearch, "hboxSearch");
    gtk_widget_set_name(vboxContain, "vboxContain");
    showProductsWindow = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(showProductsWindow), "shopping cart");
	gtk_window_set_default_size(GTK_WINDOW(showProductsWindow),1000, 700);
	gtk_window_set_resizable(GTK_WINDOW(showProductsWindow), FALSE);
	gtk_window_set_position(GTK_WINDOW(showProductsWindow), GTK_WIN_POS_CENTER);
	gtk_container_add(showProductsWindow, hboxContainer);
    change10Product();
}
/*Show Information*/
static void showInforActivate(GtkApplication *app, gpointer data) {
    GtkWidget *containerShowInfor, *headerTiku, *mainSectionInfor, *mainInfor;
    GtkWidget *pictureInfor, *backShowInforButton;
    GtkWidget *headerLabel, *nameInforLabel, *addressLabel, *dobLabel;
    GtkWidget *headerLabelShow;
    GtkWidget *welcomeChangeInforLabel, *nameShopLabel;
    backShowInforButton = gtk_button_new_with_label("Back");
    gtk_widget_set_name(backShowInforButton, "backShowInforButton");
    g_signal_connect(G_OBJECT(backShowInforButton), "clicked", G_CALLBACK(s10_x), NULL);
    welcomeChangeInforLabel = gtk_label_new("Welcome back!");
    nameShopLabel = gtk_label_new("Tiku");
    headerTiku = gtk_hbox_new(0, 0);
    gtk_box_pack_start(headerTiku, welcomeChangeInforLabel, 0, 0, 0);
    gtk_box_pack_end(headerTiku, nameShopLabel, 0, 0, 0);
    gtk_widget_set_name(headerTiku, "headerTiku");

    pictureInfor = gtk_image_new_from_file("person.png");
    nameInforLabel = gtk_label_new("Your full name: ");
    addressLabel = gtk_label_new("Your address: ");
    dobLabel = gtk_label_new("Your date of birth: ");
    gtk_widget_set_name(pictureInfor, "pictureInfor");
    nameInforLabelShow = gtk_label_new(yourFullName);
    addressLabelShow = gtk_label_new(yourAddress);
    dobLabelShow = gtk_label_new(yourDOB);
    mainSectionInfor = gtk_vbox_new(0, 0);
    gtk_box_pack_start(mainSectionInfor, nameInforLabel,0, 0, 10);
    gtk_box_pack_start(mainSectionInfor, nameInforLabelShow,0, 0, 0);
    gtk_box_pack_start(mainSectionInfor, addressLabel,0, 0, 10);
    gtk_box_pack_start(mainSectionInfor, addressLabelShow,0, 0, 0);
    gtk_box_pack_start(mainSectionInfor, dobLabel,0, 0, 10);
    gtk_box_pack_start(mainSectionInfor, dobLabelShow,0, 0, 0);
    gtk_box_pack_end(mainSectionInfor, backShowInforButton, 0, 0, 10);
    gtk_widget_set_name(mainSectionInfor, "mainSectionInfor");
    gtk_widget_set_name(welcomeChangeInforLabel, "welcomeChangeInforLabel");
    gtk_widget_set_name(nameShopLabel, "nameShopLabel");
    gtk_widget_set_name(nameInforLabel, "nameInforLabel");
    gtk_widget_set_name(addressLabel, "addressLabel");
    gtk_widget_set_name(dobLabel, "dobLabel");
    mainInfor = gtk_hbox_new(0, 0);
    gtk_box_pack_start(mainInfor, pictureInfor, 0, 0, 0);
    gtk_box_pack_end(mainInfor, mainSectionInfor, 0, 0, 0);

    containerShowInfor = gtk_vbox_new(0, 0);
    gtk_box_pack_start(containerShowInfor, headerTiku, 0, 0, 0);
    gtk_box_pack_start(containerShowInfor , mainInfor, 0, 0, 0);
    gtk_widget_set_name(containerShowInfor, "containerShowInfor");
    showInforWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(showInforWindow), "Show Information");
    gtk_window_set_default_size(GTK_WINDOW(showInforWindow),500,200);
    gtk_window_set_resizable(GTK_WINDOW(showInforWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(showInforWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(showInforWindow, containerShowInfor);
}
/*Payment*/
static void paymentActivate(GtkApplication *app, gpointer data) {

    GtkWidget *containerBox;
    GtkWidget *gridPayment, *vbox;
    GtkWidget *helloLabel, *userReciNameLabel, *addressLabel, *phoneLabel, *paymentLabel, *couponLabel, *totalbillLabel, *discountLabel, *costLabel;
    GtkWidget *buttonBackPayment, *buttonPayment, *buttonPayment2, *buttonCoupon, *buttonOrder;
    GtkWidget *entryCoupon;
    load_css();
    paymentWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(paymentWindow), "payment");
    gtk_window_set_default_size(GTK_WINDOW(paymentWindow),500,500);
    gtk_window_set_resizable(GTK_WINDOW(paymentWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(paymentWindow), GTK_WIN_POS_CENTER);
    containerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    helloLabel = gtk_label_new("Hello Customer!");
    userReciNameLabel = gtk_label_new("Recipient's name: ");
    addressLabel = gtk_label_new("Delivery address: ");
    phoneLabel = gtk_label_new("Phone number: ");
    paymentLabel = gtk_label_new("Payment method: ");
    couponLabel = gtk_label_new("Coupon: ");
    totalbillLabel = gtk_label_new("Total bill: ");
    discountLabel = gtk_label_new("Discount: ");
    costLabel = gtk_label_new("Total cost: ");
    moneyTotal = gtk_label_new("$100.00");
    moneyDiscount = gtk_label_new(" - $00.00");
    moneyCost = gtk_label_new("$20.00");
    buttonPayment = gtk_radio_button_new_with_label(NULL, "Cash on delivery");
    buttonPayment2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(buttonPayment)), "Credit card");
    buttonBackPayment = gtk_button_new_with_label("Back");
    gtk_widget_set_name(buttonBackPayment, "buttonBackPayment");
    g_signal_connect(G_OBJECT(buttonBackPayment), "clicked", G_CALLBACK(s11_8), NULL);
    buttonCoupon = gtk_button_new_with_label("Add the coupon");
    gtk_widget_set_name(buttonCoupon, "buttonCoupon");
    buttonOrder = gtk_button_new_with_label("ORDER NOW");
    g_signal_connect(G_OBJECT(buttonOrder), "clicked", G_CALLBACK(s_end), NULL);
    //gtk_button_set_always_show_image (GTK_BUTTON(buttonOrder), TRUE);
    entryReciName = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entryReciName), GTK_ENTRY_ICON_PRIMARY, "contact-new");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryReciName), "Type your name");
    entryAddress = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entryAddress), GTK_ENTRY_ICON_PRIMARY, "emblem-mail");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryAddress), "Type your home address");
    entryPhone = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entryPhone), GTK_ENTRY_ICON_PRIMARY, "phone");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryPhone), "Type your phone number");
    entryCoupon = gtk_entry_new();
    gridPayment = gtk_grid_new();
    gtk_grid_set_row_spacing(gridPayment, 20);
    gtk_grid_set_column_spacing(gridPayment, 20);
    gtk_grid_attach(gridPayment, helloLabel, 0, 0, 1, 1);
    gtk_grid_attach(gridPayment, buttonBackPayment, 2, 0, 1, 1);
    gtk_grid_attach(gridPayment, userReciNameLabel, 0, 1, 1, 1);
    gtk_grid_attach(gridPayment, entryReciName, 1, 1, 2, 1);
    gtk_grid_attach(gridPayment, addressLabel, 0, 2, 1, 1);
    gtk_grid_attach(gridPayment, entryAddress, 1, 2, 2, 1);
    gtk_grid_attach(gridPayment, phoneLabel, 0, 3, 1, 1);
    gtk_grid_attach(gridPayment, entryPhone, 1, 3, 2, 1);
    gtk_grid_attach(gridPayment, paymentLabel, 0, 4, 1, 1);
    gtk_grid_attach(gridPayment, buttonPayment, 1, 4, 1, 1);
    gtk_grid_attach(gridPayment, buttonPayment2, 2, 4, 1, 1);
    gtk_grid_attach(gridPayment, couponLabel, 0, 5, 1, 1);
    gtk_grid_attach(gridPayment, entryCoupon, 1, 5, 1, 1);
    gtk_grid_attach(gridPayment, buttonCoupon, 2, 5, 1, 1);
    gtk_grid_attach(gridPayment, totalbillLabel, 0, 6, 1, 1);
    gtk_grid_attach(gridPayment, moneyTotal, 1, 6, 2, 1);
    gtk_grid_attach(gridPayment, discountLabel, 0, 7, 1, 1);
    gtk_grid_attach(gridPayment, moneyDiscount, 1, 7, 2, 1);
    gtk_grid_attach(gridPayment, costLabel, 0, 8, 1, 1);
    gtk_grid_attach(gridPayment, moneyCost, 1, 8, 2, 1);
    gtk_grid_attach(gridPayment, buttonOrder, 1, 9, 1, 1);
    gtk_widget_set_name(moneyCost, "moneyCost");
    gtk_widget_set_name(moneyDiscount, "moneyDiscount");
    gtk_widget_set_name(moneyTotal, "moneyTotal");
    gtk_widget_set_name(gridPayment, "gridPayment");
    gtk_widget_set_name(buttonOrder, "buttonOrder");
    gtk_widget_set_name(entryAddress, "entryAddress");
    gtk_widget_set_name(entryCoupon, "entryCoupon");
    gtk_widget_set_name(entryPhone, "entryPhone");
    gtk_widget_set_name(entryReciName, "entryReciName");
    gtk_container_add(GTK_CONTAINER(paymentWindow), gridPayment);
}
/****************************************************************** CALLBACKS */
int main(int argc, char **argv)
{
    GtkAllocation *app;
    int status;
    app = gtk_application_new("app.shopping.cart", G_APPLICATION_FLAGS_NONE);
    /*Khúc này là gọi ra hết tất cả cửa sổ*/
    /*Payment*/
    g_signal_connect(app, "activate", G_CALLBACK(paymentActivate), NULL);
    /*Sign in*/
    customer.email = malloc(200);
    customer.firstName = malloc(200);
    customer.lastName = malloc(200);
    customer.pwd = malloc(200);
    customer.address = malloc(200);
    yourFullName = malloc(200);
    strcpy(yourFullName, "");
    yourAddress = malloc(200);
    strcpy(yourAddress, "");
    yourDOB = malloc(200);
    strcpy(yourDOB, "");
    /*sign up*/
    newAccount.email = malloc(200);
    newAccount.firstName = malloc(200);
    newAccount.lastName = malloc(200);
    newAccount.pwd = malloc(200);
    newAccount.address = malloc(200);
    /*show products*/
    for(int i  = 0; i < 500; i++){
        databaseProducts[i].name = malloc(200);
    }
    for(int i  = 0; i < 500; i++){
        showedProducts[i] = i;
    }
    cloneProducts();
    itemListText = malloc(1000);
    strcpy(itemListText, "");
    numberOfItem = 0;
    /*show Information*/
    g_signal_connect(app, "activate", G_CALLBACK(showInforActivate), NULL);
    /*supplierMapActivate*/
    g_signal_connect(app, "activate", G_CALLBACK(supplierMapActivate), NULL);
    /*show products window*/
    g_signal_connect(app, "activate", G_CALLBACK(showProductsActivate), NULL);
    /*notification window*/
    g_signal_connect(app, "activate", G_CALLBACK(notiActivate), NULL);
    /*Change Information Window*/
    g_signal_connect(app, "activate", G_CALLBACK(changeInformationActivate), NULL);
    /*Change pwd window*/

    g_signal_connect(app, "activate", G_CALLBACK(changePwdActivate), NULL);
    /*Sign Up*/
    g_signal_connect(app, "activate", G_CALLBACK(signUpActivate), NULL);
    /*Sign in*/
    appWidgets *wid = g_malloc(sizeof(appWidgets));
    g_signal_connect(app, "activate", G_CALLBACK(signInActivate), (gpointer)wid);
    /*Customer Map window*/
    g_signal_connect(app, "activate", G_CALLBACK(customerMapActivate), NULL);
    /*Open window*/
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    /**/

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
