#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>


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

gboolean destroy(GtkWidget *widget)
{
    gtk_widget_destroy(widget);
    return TRUE;
}

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


char *USERNAME = "user";
char *PASSWORD = "12345";

 /////========================================================================
 typedef struct
{
    GtkWidget *tmpEntry;
    GtkWidget *fnameEntry;
    GtkWidget *gnameEntry;
    GtkWidget *cityEntry;
    GtkWidget *byearSpin;
    GtkWidget *bmonthSpin;
    GtkWidget *bdaySpin;
} diaWidgets;

typedef struct
{
    GtkApplication *app;
    GtkWidget *window;
    GtkWidget *img;
    diaWidgets *d;
} signUpAppWidgets;

static signUpAppWidgets *a_changed;
static GtkWidget *mark;
static GtkWidget *windoww;
static GtkWidget* mark;
static gchar *email;
static gchar *password;
static char *id;
static char *firstName;
static char *lastName;
static int numberOfCustomers;
/***************************************************************** PROTOTYPES */
static void activate_signUp(GtkApplication *app, gpointer user_data);
static void img_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data);
static void cancel_callback(GtkWidget *widget, gpointer user_data);
static void clear_callback(GtkWidget *widget, gpointer user_data);
static void add_callback(GtkWidget *widget, gpointer user_data);
static void get_datestamp(gchar *ds);
static gint get_next_id(void);

/**************************************************************** get_next_id */
static gint
get_next_id(void)
{
    return 12;
}

/************************************************************** get_datestamp */
static void
get_datestamp(gchar *ds)
{
    GTimeVal time;
    GDate date;

    g_get_current_time(&time);
    g_date_clear(&date, 1);
    g_date_set_time_val(&date, &time);
    g_date_strftime(ds, 256, "%F", &date);
}
/**************************************************************** imgCallback */
static void
img_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GtkWidget *imgDialog;
    GtkFileFilter *filter;
    gint res;
    signUpAppWidgets *a_changed = (signUpAppWidgets *)user_data;

    filter = gtk_file_filter_new();
    imgDialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(a_changed->window),
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
            gtk_image_set_from_file(GTK_IMAGE(a_changed->img), ofilename);
        }
        else
        {
            gtk_image_set_from_file(GTK_IMAGE(a_changed->img), "src/avatar2.png");
        }
        g_free(filename);
    }
    gtk_widget_destroy(imgDialog);
}

/************************************************************ Cancel Callback */
static void
cancel_callback(GtkWidget *widget, gpointer user_data)
{
    signUpAppWidgets *a_changed = (signUpAppWidgets *)user_data;

    g_print("Cancel pressed!\n");
    g_application_quit(G_APPLICATION(a_changed->app));
}

/************************************************************* Clear Callback */
static void
clear_callback(GtkWidget *widget, gpointer user_data)
{
    signUpAppWidgets *a_changed = (signUpAppWidgets *)user_data;

    g_print("Clear pressed!\n");
    gtk_entry_set_text(GTK_ENTRY(a_changed->d->tmpEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a_changed->d->fnameEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a_changed->d->gnameEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a_changed->d->cityEntry), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a_changed->d->byearSpin), 1990);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a_changed->d->bmonthSpin), 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a_changed->d->bdaySpin), 1);
    gtk_image_set_from_file(GTK_IMAGE(a_changed->img), "src/avatar.png");
}

/*************************************************************** Add Callback */
static void
add_callback(GtkWidget *widget, gpointer user_data)
{
    signUpAppWidgets *a_changed = (signUpAppWidgets *)user_data;

    g_print("Add pressed!\n");
    g_print("-------------------------------\n");
    g_print("Given Name: %s\n", gtk_entry_get_text(GTK_ENTRY(a_changed->d->tmpEntry)));
    g_print("Family Name: %s\n", gtk_entry_get_text(GTK_ENTRY(a_changed->d->fnameEntry)));
    g_print("Street: %s\n", gtk_entry_get_text(GTK_ENTRY(a_changed->d->gnameEntry)));
    g_print("City: %s\n", gtk_entry_get_text(GTK_ENTRY(a_changed->d->cityEntry)));
    g_print("Birth: %.0lf-%.0lf-%.0lf\n",
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a_changed->d->byearSpin)),
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a_changed->d->bmonthSpin)),
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a_changed->d->bdaySpin)));
    g_print("-------------------------------\n");
}

/********************************************************* nameentry_callback */
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
    signUpAppWidgets *a_changed = (signUpAppWidgets *)user_data;

    /* construct the eMail address */
    gname = (gchar *)gtk_entry_get_text(GTK_ENTRY(a_changed->d->tmpEntry));
    fname = (gchar *)gtk_entry_get_text(GTK_ENTRY(a_changed->d->fnameEntry));
    /* we update the fields on the top only when we got a family name */
    if ((g_strcmp0(gname, "") != 0) && (g_strcmp0(fname, "") != 0))
    {
        g_sprintf(email, "%s.%s@%s.%s", gname, fname, org, cnt);
        /* update date info when Family Name was entered */
        get_datestamp(dateStamp);
        /* construct matrnum when Family Name was entered */
        year = g_strndup(dateStamp, 4);
        g_snprintf(id, 10, "%s%d%03d", year, studyProgNr, get_next_id());
    }
}

/***************************************************************** ADD WINDOW */
static void
activate_signUp(GtkApplication *app, gpointer user_data)
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
    a_changed = (signUpAppWidgets *)user_data;

    /* create a window with title, default size,and icons */
    a_changed->window = gtk_application_window_new(a_changed->app);
    gtk_window_set_application(GTK_WINDOW(a_changed->window), GTK_APPLICATION(a_changed->app));
    gtk_window_set_title(GTK_WINDOW(a_changed->window), "Student Management Toolbox");
    gtk_window_set_default_size(GTK_WINDOW(a_changed->window), 400, 300);
    gtk_window_set_default_icon_from_file("icon.png", NULL);
    gtk_window_set_resizable(GTK_WINDOW(a_changed->window), FALSE);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    gtk_container_add(GTK_CONTAINER(a_changed->window), GTK_WIDGET(box));
    gtk_container_set_border_width(GTK_CONTAINER(a_changed->window), 10);

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
    a_changed->img = gtk_image_new_from_file("src/avatar.png");
    gtk_container_add(GTK_CONTAINER(ebox), a_changed->img);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(ebox), 1, 0, 1, 3);
    g_signal_connect(G_OBJECT(ebox), "button_press_event",
                     G_CALLBACK(img_callback), (gpointer)a_changed);

    tmpLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Given Name:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(tmpLabel), 0, 3, 1, 1);
    a_changed->d->tmpEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a_changed->d->tmpEntry), 1, 3, 1, 1);

    fnameLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Family Name:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(fnameLabel), 2, 3, 1, 1);
    a_changed->d->fnameEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a_changed->d->fnameEntry), 3, 3, 1, 1);
    g_signal_connect(G_OBJECT(a_changed->d->fnameEntry), "activate",
                     G_CALLBACK(nameentry_callback), (gpointer)a_changed);

    gnameLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Street:",
                                 "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(gnameLabel), 0, 4, 1, 1);
    a_changed->d->gnameEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a_changed->d->gnameEntry), 1, 4, 1, 1);

    cityLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "City:",
                               "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cityLabel), 2, 4, 1, 1);
    a_changed->d->cityEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a_changed->d->cityEntry), 3, 4, 1, 1);

    birthLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Date of Birth:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(birthLabel), 0, 6, 1, 1);
    a_changed->d->byearSpin = gtk_spin_button_new_with_range(1900, 2000, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a_changed->d->byearSpin), 1990);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a_changed->d->byearSpin), 1, 6, 1, 1);
    a_changed->d->bmonthSpin = gtk_spin_button_new_with_range(1, 12, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a_changed->d->bmonthSpin), 2, 6, 1, 1);
    a_changed->d->bdaySpin = gtk_spin_button_new_with_range(1, 31, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a_changed->d->bdaySpin), 3, 6, 1, 1);

    /* lowerbox: buttons */
    cButton = gtk_button_new_with_mnemonic("_Cancel");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cButton), 1, 7, 1, 1);
    g_signal_connect(G_OBJECT(cButton), "clicked", G_CALLBACK(cancel_callback),
                     (gpointer)a_changed);
    lButton = gtk_button_new_with_mnemonic("C_lear");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(lButton), 2, 7, 1, 1);
    g_signal_connect(G_OBJECT(lButton), "clicked", G_CALLBACK(clear_callback),
                     (gpointer)a_changed);
    aButton = gtk_button_new_with_mnemonic("_Add");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(aButton), 3, 7, 1, 1);
    g_signal_connect(G_OBJECT(aButton), "clicked", G_CALLBACK(add_callback),
                     (gpointer)a_changed);

    /* display all widgets */
    //gtk_widget_show_all(GTK_WIDGET(a->window));
}

 //===========================================================================

/***************************************************************** PROTOTYPES */
void signIn_enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_entry_callback(GtkWidget *widget, gpointer data);

/****************************************************************** CALLBACKS */

void signIn_enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data)
{
    gchar str[50];
    appWidgets *wid = (appWidgets *)data;

    email = gtk_entry_get_text(GTK_ENTRY(wid->mailentry));
    password = gtk_entry_get_text(GTK_ENTRY(wid->pwdentry));
    if (strcmp(email, USERNAME) == 0 && strcmp(password, PASSWORD) == 0)
    {
        g_sprintf(str, "Hello %s!", email);
        gtk_widget_override_font(wid->greeterlabel,
                                 pango_font_description_from_string("Tahoma 20"));
        gtk_label_set_text(GTK_LABEL(wid->greeterlabel), (const gchar *)str);
    }
    else
    {
        g_sprintf(str, "Hey %s! Invalid email or password", email);
        gtk_widget_override_font(wid->greeterlabel,
                                 pango_font_description_from_string("Tahoma 20"));
        gtk_label_set_text(GTK_LABEL(wid->greeterlabel), (const gchar *)str);
    }
    email = NULL;
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

/***************************************************************** GUI THREAD */
static void activate_signIn(GtkApplication *app, gpointer data)
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
    windoww = gtk_application_window_new(app);
    gtk_window_set_application(GTK_WINDOW(windoww), GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(windoww), "Sign in");
    gtk_window_set_position(GTK_WINDOW(windoww), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(windoww), FALSE);
    gtk_window_set_default_icon_from_file("icon.png", NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(windoww), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(windoww), 10);

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
    gtk_window_set_titlebar(GTK_WINDOW(windoww), headerbar);

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

    //gtk_widget_show_all(GTK_WIDGET(windoww));
}

static void switchWindow(GtkWidget *widget)
{

    gtk_window_close(widget);
    gtk_widget_show_all(GTK_WIDGET(windoww));
    g_print("KKK\n");
}

static void switchWindoww(GtkWidget *widget)
{

    gtk_window_close(widget);
    gtk_widget_show_all(GTK_WIDGET(a_changed->window));
    g_print("KKK\n");
}


static void activate(GtkApplication *app, gpointer data)
{
    load_css();
    GtkWidget *window;

    GtkWidget *vBoxRoleContainer;
    GtkWidget *chooseSignInButton, *chooseSignUpButton;
    GtkWidget *askRoleLabel;


    askRoleLabel = gtk_label_new("What do you want?");
    chooseSignInButton = gtk_button_new_with_label("Sign in");
    //g_signal_connect(app, "activate", G_CALLBACK(activate_signIn), (gpointer) data);

    g_signal_connect(G_OBJECT(chooseSignInButton), "clicked", G_CALLBACK(switchWindow), (gpointer)window);
    chooseSignUpButton = gtk_button_new_with_label("Sign up");
    g_signal_connect(G_OBJECT(chooseSignUpButton), "clicked", G_CALLBACK(switchWindoww), (gpointer)window);

    vBoxRoleContainer = gtk_vbox_new(0, 20);
    gtk_box_pack_start(vBoxRoleContainer, askRoleLabel, 0, 0, 40);
    gtk_box_pack_start(vBoxRoleContainer, chooseSignInButton, 0, 0, 0);
    gtk_box_pack_start(vBoxRoleContainer, chooseSignUpButton, 0, 0, 0);
    gtk_widget_set_name(vBoxRoleContainer, "vBoxRoleContainer");
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Shopping role");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(window, vBoxRoleContainer);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkAllocation *app;

    int status;
    app = gtk_application_new("app.shopping.cart", G_APPLICATION_FLAGS_NONE);
    appWidgets *wid = g_malloc(sizeof(appWidgets));
    //g_signal_connect(app, "activate", G_CALLBACK(activate_signIn), (gpointer) wid);

    g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer) wid);
        signUpAppWidgets *a = g_malloc(sizeof(signUpAppWidgets));
    a->d = g_malloc(sizeof(diaWidgets));

    a->app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(G_OBJECT(a->app), "activate", G_CALLBACK(activate_signUp), (gpointer)a);
    g_signal_connect(app, "activate", G_CALLBACK(activate_signIn), (gpointer)wid);
    status = g_application_run(G_APPLICATION(app), argc, argv);


    status = g_application_run(G_APPLICATION(a->app), argc, argv);
    g_object_unref(a->app);
    //g_free(a->d);
    //g_free(a);
    g_object_unref(app);
    //g_free(wid);
    wid = NULL;
    return status;
}
