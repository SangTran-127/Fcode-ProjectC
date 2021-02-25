#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>

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
/*1*/ static GtkWidget *openWindow;
/*2*/ static GtkWidget *signInWindow;
/*3*/ static GtkWidget *customerMapWindow;
/*4*/ static GtkWidget *changePwdWindow;
/*5*/ static GtkWidget *changeInformationWindow;
/*6*/ static GtkWidget *notiWindow;

/****************************************************************** GLOBAL VARIABLES */
static gint noCloseWindow = 1000;
static gint noOpenWindow = 1000;

/*Customer*/
Customer admin;

/*Sign in*/

static Customer customer;
static int numberOfCustomers;

/*Change pwd*/
GtkWidget *oldPasswordChangeEntry, *newPasswordChangeEntry, *confirmNewPasswordChangeEntry;

/*Notification*/
GtkWidget *alert;

/***************************************************************** PROTOTYPES */
/*Sign in*/
int findAccount(char *inputEmail);
void signIn_enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_entry_callback(GtkWidget *widget, gpointer data);

/*Sign up*/
static void signUpActivate(GtkApplication *app, gpointer user_data);
static void signUp_img_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data);
static void signUp_cancel_callback(GtkWidget *widget, gpointer user_data);
static void signUp_clear_callback(GtkWidget *widget, gpointer user_data);
static void signUp_add_callback(GtkWidget *widget, gpointer user_data);
static void signUp_get_datestamp(gchar *ds);
static gint signUp_get_next_id(void);
/****************************************************************** CALLBACKS */
static void onNoti()
{
    gtk_widget_show_all(GTK_WIDGET(notiWindow));
}

static void offNoti()
{
    gtk_widget_hide(GTK_WIDGET(notiWindow));
}

static void s31()
{
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_widget_show_all(GTK_WIDGET(openWindow));
}
static void s43()
{
    gtk_widget_hide(GTK_WIDGET(changePwdWindow));
    gtk_widget_show_all(GTK_WIDGET(customerMapWindow));
}
static void s23()
{
    gtk_widget_hide(GTK_WIDGET(signInWindow));
    gtk_widget_show_all(GTK_WIDGET(customerMapWindow));
}
static void s12()
{
    gtk_widget_hide(GTK_WIDGET(openWindow));
    gtk_widget_show_all(GTK_WIDGET(signInWindow));
}
static void s34()
{
    gtk_widget_hide(GTK_WIDGET(customerMapWindow));
    gtk_widget_show_all(GTK_WIDGET(changePwdWindow));
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

/*Sign in*/
int findAccount(char *inputEmail)
{
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
            continue;
        }
        int pos = 0;
        customer.id = 0;
        customer.tikuCoin = 0;
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
            printf("\nDuma");
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
static gint signUp_get_next_id(void)
{
    return 12;
}

static void
signUp_get_datestamp(gchar *ds)
{
    GTimeVal time;
    GDate date;

    g_get_current_time(&time);
    g_date_clear(&date, 1);
    g_date_set_time_val(&date, &time);
    g_date_strftime(ds, 256, "%F", &date);
}

static void
signUp_img_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GtkWidget *imgDialog;
    GtkFileFilter *filter;
    gint res;
    signUp_appWidgets *a = (signUp_appWidgets *)user_data;

    filter = gtk_file_filter_new();
    imgDialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(a->window),
                                            GTK_FILE_CHOOSER_ACTION_OPEN,
                                            "_Cancel", GTK_RESPONSE_CANCEL,
                                            "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_filter_add_mime_type(GTK_FILE_FILTER(filter), "image/png");
    gtk_file_filter_add_mime_type(GTK_FILE_FILTER(filter), "image/jpg");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(imgDialog), filter);

    res = gtk_dialog_run(GTK_DIALOG(imgDialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename, *tfilename;
        char ofilename[256] = "";
        GFile *in, *out;
        GtkWidget *image;
        const GdkPixbuf *pb;
        GError **error = NULL;

        GtkFileChooser *chooser = GTK_FILE_CHOOSER(imgDialog);
        filename = gtk_file_chooser_get_filename(chooser);

        // get size of image
        image = gtk_image_new_from_file(filename);
        pb = gtk_image_get_pixbuf(GTK_IMAGE(image));
        /* if size matches w=80 && h=90 copy it to destination and load it */
        if (gdk_pixbuf_get_width(pb) == 80 && gdk_pixbuf_get_height(pb) == 90)
        {
            /* remove the path & add a new default one "./img/" where we store all
           images */
            tfilename = g_strrstr(filename, "/");
            g_sprintf(ofilename, "./img/%s", &tfilename[1]);
            /* copy the image */
            in = g_file_new_for_path(filename);
            out = g_file_new_for_path(ofilename);
            g_file_copy(in, out, G_FILE_COPY_NONE, NULL, NULL, NULL, error);
            gtk_image_set_from_file(GTK_IMAGE(a->img), ofilename);
        }
        else
        {
            gtk_image_set_from_file(GTK_IMAGE(a->img), "src/avatar2.png");
        }
        g_free(filename);
    }
    gtk_widget_destroy(imgDialog);
}

static void
signUp_cancel_callback(GtkWidget *widget, gpointer user_data)
{
    signUp_appWidgets *a = (signUp_appWidgets *)user_data;

    g_print("Cancel pressed!\n");
    g_application_quit(G_APPLICATION(a->app));
}

static void signUp_clear_callback(GtkWidget *widget, gpointer user_data)
{
    signUp_appWidgets *a = (signUp_appWidgets *)user_data;

    g_print("Clear pressed!\n");
    gtk_entry_set_text(GTK_ENTRY(a->d->tmpEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a->d->fnameEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a->d->gnameEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a->d->cityEntry), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->byearSpin), 1990);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->bmonthSpin), 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->bdaySpin), 1);
    gtk_image_set_from_file(GTK_IMAGE(a->img), "src/avatar.png");
}

static void
signUp_add_callback(GtkWidget *widget, gpointer user_data)
{
    signUp_appWidgets *a = (signUp_appWidgets *)user_data;

    g_print("Add pressed!\n");
    g_print("-------------------------------\n");
    g_print("Given Name: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->tmpEntry)));
    g_print("Family Name: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->fnameEntry)));
    g_print("Street: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->gnameEntry)));
    g_print("City: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->cityEntry)));
    g_print("Birth: %.0lf-%.0lf-%.0lf\n",
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a->d->byearSpin)),
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a->d->bmonthSpin)),
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a->d->bdaySpin)));
    g_print("-------------------------------\n");
}

static void
nameentry_callback(GtkWidget *widget, gpointer user_data)
{
    gint studyProgNr = 54;
    gchar *org = "uni";
    gchar *cnt = "net";
    gchar *gname, *fname;
    gchar email[256];
    gchar dateStamp[256];
    gchar *year;
    gchar id[256] = "";
    signUp_appWidgets *a = (signUp_appWidgets *)user_data;

    /* construct the eMail address */
    gname = (gchar *)gtk_entry_get_text(GTK_ENTRY(a->d->tmpEntry));
    fname = (gchar *)gtk_entry_get_text(GTK_ENTRY(a->d->fnameEntry));
    /* we update the fields on the top only when we got a family name */
    if ((g_strcmp0(gname, "") != 0) && (g_strcmp0(fname, "") != 0))
    {
        g_sprintf(email, "%s.%s@%s.%s", gname, fname, org, cnt);
        /* update date info when Family Name was entered */
        signUp_get_datestamp(dateStamp);
        /* construct matrnum when Family Name was entered */
        year = g_strndup(dateStamp, 4);
        g_snprintf(id, 10, "%s%d%03d", year, studyProgNr, signUp_get_next_id());
    }
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
            printf("\nOke ban nha");
            char* newInfor = malloc(200);
            strcpy(newInfor, "");
            char* tmpStr = malloc(20);
            itoa(customer.id, tmpStr, 10);
            strcat(newInfor, tmpStr);
            strcat(newInfor, ","); strcat(newInfor, customer.email);
            strcat(newInfor, ","); strcat(newInfor, entryConfirmPwd);
            strcat(newInfor, ","); strcat(newInfor, customer.firstName);
            strcat(newInfor, ","); strcat(newInfor, customer.lastName);
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
            gtk_label_set_text(alert, "Doi thanh cong");
            onNoti();
        }else{
            printf("\nKhong trung kia ma");
            gtk_label_set_text(alert, "Khong trung kia ma");
            onNoti();
        }
    }else{
        printf("\nSai mat khau roi ban eiii");
        gtk_label_set_text(alert, "Sai mat khau roi ban eiii");
        onNoti();
    }

}
/****************************************************************** GUI THREAD */
/*Openning window*/
static void activate(GtkApplication *app, gpointer data)
{
    load_css();
    GtkWidget *vBoxRoleContainer;
    GtkWidget *chooseSignInButton, *chooseSignUpButton;
    GtkWidget *askRoleLabel;

    askRoleLabel = gtk_label_new("What do you want?");
    chooseSignInButton = gtk_button_new_with_label("Sign in");
    g_signal_connect(G_OBJECT(chooseSignInButton), "clicked", G_CALLBACK(s12), NULL);

    chooseSignUpButton = gtk_button_new_with_label("Sign up");

    vBoxRoleContainer = gtk_vbox_new(0, 20);
    gtk_box_pack_start(vBoxRoleContainer, askRoleLabel, 0, 0, 40);
    gtk_box_pack_start(vBoxRoleContainer, chooseSignInButton, 0, 0, 0);
    gtk_box_pack_start(vBoxRoleContainer, chooseSignUpButton, 0, 0, 0);
    gtk_widget_set_name(vBoxRoleContainer, "vBoxRoleContainer");
    openWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(openWindow), "Shopping role");
    gtk_window_set_default_size(GTK_WINDOW(openWindow), 300, 300);
    gtk_window_set_resizable(GTK_WINDOW(openWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(openWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(openWindow, vBoxRoleContainer);
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
static void signUpActivate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *box;
    GtkWidget *ebox;
    GtkWidget *grid;
    GtkWidget *tmpLabel;
    GtkWidget *fnameLabel;
    GtkWidget *gnameLabel;
    GtkWidget *cityLabel;
    GtkWidget *birthLabel;
    GtkWidget *cButton;
    GtkWidget *lButton;
    GtkWidget *aButton;
    signUp_appWidgets *a = (signUp_appWidgets *)user_data;

    /* create a window with title, default size,and icons */
    a->window = gtk_application_window_new(a->app);
    gtk_window_set_application(GTK_WINDOW(a->window), GTK_APPLICATION(a->app));
    gtk_window_set_title(GTK_WINDOW(a->window), "Student Management Toolbox");
    gtk_window_set_default_size(GTK_WINDOW(a->window), 400, 300);
    gtk_window_set_default_icon_from_file("icon.png", NULL);
    gtk_window_set_resizable(GTK_WINDOW(a->window), FALSE);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    gtk_container_add(GTK_CONTAINER(a->window), GTK_WIDGET(box));
    gtk_container_set_border_width(GTK_CONTAINER(a->window), 10);

    /* grid: image and labels */
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_size_request(GTK_WIDGET(grid), 400, 90);
    gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(grid), TRUE, TRUE, 0);

    /* clickable image top left */
    ebox = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(ebox), 150, 90);
    gtk_widget_set_valign(GTK_WIDGET(ebox), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(ebox), GTK_ALIGN_CENTER);
    a->img = gtk_image_new_from_file("src/avatar.png");
    gtk_container_add(GTK_CONTAINER(ebox), a->img);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(ebox), 1, 0, 1, 3);
    g_signal_connect(G_OBJECT(ebox), "button_press_event",
                     G_CALLBACK(signUp_img_callback), (gpointer)a);

    tmpLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Given Name:",
                              "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(tmpLabel), 0, 3, 1, 1);
    a->d->tmpEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->tmpEntry), 1, 3, 1, 1);

    fnameLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Family Name:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(fnameLabel), 2, 3, 1, 1);
    a->d->fnameEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->fnameEntry), 3, 3, 1, 1);
    g_signal_connect(G_OBJECT(a->d->fnameEntry), "activate",
                     G_CALLBACK(nameentry_callback), (gpointer)a);

    gnameLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Street:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(gnameLabel), 0, 4, 1, 1);
    a->d->gnameEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->gnameEntry), 1, 4, 1, 1);

    cityLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "City:",
                               "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cityLabel), 2, 4, 1, 1);
    a->d->cityEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->cityEntry), 3, 4, 1, 1);

    birthLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Date of Birth:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(birthLabel), 0, 6, 1, 1);
    a->d->byearSpin = gtk_spin_button_new_with_range(1900, 2000, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->byearSpin), 1990);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->byearSpin), 1, 6, 1, 1);
    a->d->bmonthSpin = gtk_spin_button_new_with_range(1, 12, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->bmonthSpin), 2, 6, 1, 1);
    a->d->bdaySpin = gtk_spin_button_new_with_range(1, 31, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->bdaySpin), 3, 6, 1, 1);

    /* lowerbox: buttons */
    cButton = gtk_button_new_with_mnemonic("_Cancel");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cButton), 1, 7, 1, 1);
    g_signal_connect(G_OBJECT(cButton), "clicked", G_CALLBACK(signUp_cancel_callback),
                     (gpointer)a);
    lButton = gtk_button_new_with_mnemonic("C_lear");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(lButton), 2, 7, 1, 1);
    g_signal_connect(G_OBJECT(lButton), "clicked", G_CALLBACK(signUp_clear_callback),
                     (gpointer)a);
    aButton = gtk_button_new_with_mnemonic("_Add");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(aButton), 3, 7, 1, 1);
    g_signal_connect(G_OBJECT(aButton), "clicked", G_CALLBACK(signUp_add_callback),
                     (gpointer)a);

    /* display all widgets */
    gtk_widget_show_all(GTK_WIDGET(a->window));
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
    showInforButton = gtk_button_new_with_label("Show informatiom");
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
    GtkWidget *addressChangeInforLabel, *nameChangeInforLabel, *phoneChangeInforLabel;

    GtkWidget *addressChangeInforEntry, *nameChangeInforEntry, *phoneChangeInforEntry;

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
    nameChangeInforEntry = gtk_entry_new();
    phoneChangeInforEntry = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(addressChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "emblem-mail");
    gtk_entry_set_placeholder_text(addressChangeInforEntry, "Enter your address");
    gtk_entry_set_icon_from_icon_name(nameChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "contact-new");
    gtk_entry_set_placeholder_text(nameChangeInforEntry, "Enter your full name");
    gtk_entry_set_icon_from_icon_name(phoneChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "phone");
    gtk_entry_set_placeholder_text(phoneChangeInforEntry, "Enter your phone number");
    //
    askBackChangeInforLabel = gtk_label_new("Change your mind ?");
    backChangeInforButton = gtk_button_new_with_label("Back");
    g_signal_connect(G_OBJECT(backChangeInforButton), "clicked", G_CALLBACK(s53), NULL);
    gtk_widget_set_name(backChangeInforButton, "backChangeInforButton");

    hboxFooter = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxFooter, askBackChangeInforLabel, 0, 0, 10);
    gtk_box_pack_end(hboxFooter, backChangeInforButton, 0, 0, 0);

    addressChangeInforLabel = gtk_label_new("Address: ");
    nameChangeInforLabel = gtk_label_new("Full name: ");
    phoneChangeInforLabel = gtk_label_new("Phone number: ");
    updateChangeInforButton = gtk_button_new_with_label("Update");

    //
    gtk_grid_attach(gridChangeInfor, nameChangeInforLabel, 0, 0, 1, 1);
    gtk_grid_attach(gridChangeInfor, nameChangeInforEntry, 1, 0, 1, 1);
    gtk_grid_attach(gridChangeInfor, phoneChangeInforLabel, 0, 1, 1, 1);
    gtk_grid_attach(gridChangeInfor, phoneChangeInforEntry, 1, 1, 1, 1);
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
    gtk_window_set_title(GTK_WINDOW(notiWindow), "");
    gtk_window_set_default_size(GTK_WINDOW(notiWindow),200,20);
    gtk_window_set_resizable(GTK_WINDOW(notiWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(notiWindow), GTK_WIN_POS_CENTER);
    gtk_container_add(notiWindow, vboxAlert);
}

/****************************************************************** CALLBACKS */
int main(int argc, char **argv)
{
    GtkAllocation *app;
    int status;
    app = gtk_application_new("app.shopping.cart", G_APPLICATION_FLAGS_NONE);
    /*Sign in*/
    customer.email = malloc(200);
    customer.firstName = malloc(200);
    customer.lastName = malloc(200);
    customer.pwd = malloc(200);
    customer.address = malloc(200);
    /**/

    /*Khúc này là gọi ra hết tất cả cửa sổ*/
    /*notification window*/
    g_signal_connect(app, "activate", G_CALLBACK(notiActivate), NULL);
    /*Change Information Window*/
    g_signal_connect(app, "activate", G_CALLBACK(changeInformationActivate), NULL);
    /*Change pwd window*/

    g_signal_connect(app, "activate", G_CALLBACK(changePwdActivate), NULL);
    /*Sign Up*/
    signUp_appWidgets *a = g_malloc(sizeof(signUp_appWidgets));
    a->d = g_malloc(sizeof(signUp_diaWidgets));
    //g_signal_connect(G_OBJECT(a->app), "activate", G_CALLBACK(signUpActivate), (gpointer)a);
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
    /*Sign up*/
    g_object_unref(G_OBJECT(a->app));
    g_free(a->d);
    g_free(a);
    return status;
}
