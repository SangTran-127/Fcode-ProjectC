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

/****************************************************************** TYPEDEF */
/*Sign in*/
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

/****************************************************************** WINDOWS */
/*1*/ static GtkWidget *openWindow;
/*2*/ static GtkWidget *signInWindow;

/****************************************************************** GLOBAL VARIABLES */
int noCloseWindow = 1000;
int noOpenWindow = 1000;
/*Sign in*/
static gchar *email;
static gchar *password;
static char *id;
static char *firstName;
static char *lastName;
static int numberOfCustomers;
char *USERNAME = "user";
char *PASSWORD = "12345";

/***************************************************************** PROTOTYPES */
void signIn_enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void signIn_entry_callback(GtkWidget *widget, gpointer data);

/****************************************************************** CALLBACKS */
static void switchWindow()
{
    switch (noCloseWindow)
    {
    case 1:
        gtk_window_close(openWindow);
        break;
    case 2:
        gtk_window_close(GTK_WIDGET(signInWindow));
        break;
    }
    switch (noOpenWindow)
    {
    case 1:
        gtk_widget_show_all(openWindow);
        break;
    case 2:
        gtk_widget_show_all(GTK_WIDGET(signInWindow));
        break;
    }
}
/*Sign in*/
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
    noOpenWindow = 2;
    noCloseWindow = 1;
    g_signal_connect(G_OBJECT(chooseSignInButton), "clicked", G_CALLBACK(switchWindow), NULL);
    //noWindow = 1;
    //g_print("\n%d", noWindow);
    //close_window();
    //g_signal_connect(G_OBJECT(chooseSignInButton), "clicked", G_CALLBACK(close_window), NULL);

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

/****************************************************************** CALLBACKS */
int main(int argc, char **argv)
{
    GtkAllocation *app;
    int status;
    app = gtk_application_new("app.shopping.cart", G_APPLICATION_FLAGS_NONE);
    /*Khúc này là gọi ra hết tất cả cửa sổ*/
    appWidgets *wid = g_malloc(sizeof(appWidgets));
    g_signal_connect(app, "activate", G_CALLBACK(signInActivate), (gpointer)wid);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    /**/
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
