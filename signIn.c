/**
 * GNOME/GTK+ Menu Demo Application using a GtkApplication class
 *
 * M. Horauer
 */
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>

static gchar *name;
static gchar *password;
const char* USERNAME = "user";
const char* PASSWORD = "12345";

typedef struct
{
    GtkWidget *greeterlabel;
    GtkWidget *namelabel;
    GtkWidget *nameentry;
    GtkWidget *namelabel1;
    GtkWidget *nameentry1;
    GtkWidget *enterbutton;
    GtkWidget *clearbutton;
} appWidgets;

/***************************************************************** PROTOTYPES */
void enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data);
void entry_callback(GtkWidget *widget, gpointer data);

/****************************************************************** CALLBACKS */
void enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data)
{
    gchar str[50];
    appWidgets *wid = (appWidgets *)data;

    name = gtk_entry_get_text(GTK_ENTRY(wid->nameentry));
    password = gtk_entry_get_text(GTK_ENTRY(wid->nameentry1));
    if(strcmp(name, USERNAME) == 0 && strcmp(password, PASSWORD) == 0){
        g_sprintf(str, "Hello %s!", name);
        gtk_widget_override_font(wid->greeterlabel,
                                 pango_font_description_from_string("Tahoma 20"));
        gtk_label_set_text(GTK_LABEL(wid->greeterlabel), (const gchar *)str);
    }else{
        g_sprintf(str, "Hey %s! Invalid handle/email or password", name);
        gtk_widget_override_font(wid->greeterlabel,
                                 pango_font_description_from_string("Tahoma 20"));
        gtk_label_set_text(GTK_LABEL(wid->greeterlabel), (const gchar *)str);
    }
    name = NULL;
    wid = NULL;

}

void clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data)
{
    appWidgets *wid = (appWidgets *)data;

    gtk_label_set_text(GTK_LABEL(wid->greeterlabel), "Let's sign in again");
    gtk_entry_set_text(GTK_ENTRY(wid->nameentry), "");
    gtk_entry_set_text(GTK_ENTRY(wid->nameentry1), "");

    wid = NULL;
}

void entry_callback(GtkWidget *widget, gpointer data)
{
    enter_callback(NULL, NULL, data);
}

void create_window(GtkWidget *button, gpointer window)
{

    GtkWidget *win, *label;

    //Username and Password to validate credentials
    const char* USERNAME = "u";
    const char* PASSWORD = "1";
    char* username = "user", password = "12345";

    //Checking if user's entered credentials are equal to actual USERNAME and PASSWORD
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0)
    {
        label = gtk_label_new("Username and Password is correct.");
        win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_container_add(GTK_CONTAINER(win), label);
        gtk_widget_show_all(win);
    }

    else if (strcmp(username, USERNAME) != 0 || strcmp(password, PASSWORD) != 0)

    {
        label = gtk_label_new("Username and Password is incorrect.");
        win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_container_add(GTK_CONTAINER(win), label);
        gtk_widget_show_all(win);
    }
}

/***************************************************************** GUI THREAD */
static void activate(GtkApplication *app, gpointer data)
{
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *headerbar;
    GtkStyleContext *context;

    appWidgets *wid = (appWidgets *)data;
    // map menu actions to callbacks
    const GActionEntry app_actions[] = {
        {"enter", enter_callback, NULL, NULL, NULL},
        {"clear", clear_callback, NULL, NULL, NULL}};

    // create a window with title, default size and icons
    window = gtk_application_window_new(app);
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "Sign in");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_icon_from_file("icon.png", NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // create label and entry
    wid->greeterlabel = gtk_label_new_with_mnemonic("Let's sign in!");
    gtk_widget_override_font(wid->greeterlabel,
                             pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(wid->greeterlabel, 0, 50);
    gtk_box_pack_start(GTK_BOX(vbox), wid->greeterlabel, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    wid->namelabel = gtk_label_new_with_mnemonic("Username:");
    gtk_widget_set_size_request(wid->namelabel, 60, 40);
    gtk_box_pack_start(GTK_BOX(hbox), wid->namelabel, FALSE, FALSE, 0);

    wid->nameentry = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(wid->nameentry), "tuankietbdsm21");
    gtk_box_pack_start(GTK_BOX(hbox), wid->nameentry, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(wid->nameentry), "activate",
                     G_CALLBACK(entry_callback), (gpointer)wid);

    wid->namelabel1 = gtk_label_new_with_mnemonic("Password:");
    gtk_widget_set_size_request(wid->namelabel1, 60, 40);
    gtk_box_pack_start(GTK_BOX(hbox), wid->namelabel1, FALSE, FALSE, 0);
    wid->nameentry1 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(wid->nameentry1), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(wid->nameentry1), "");
    gtk_box_pack_start(GTK_BOX(hbox), wid->nameentry1, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(wid->nameentry1), "activate",
                     G_CALLBACK(entry_callback), (gpointer)wid);
    // create a headerbar
    headerbar = gtk_header_bar_new();
    gtk_widget_show(headerbar);
    gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "F CODE");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar),
                                "Code the Circus");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

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

    gtk_widget_show_all(GTK_WIDGET(window));
}

/**************************************************************** MAIN THREAD */
int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;
    appWidgets *wid = g_malloc(sizeof(appWidgets));

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer)wid);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    g_free(wid);
    wid = NULL;
    return status;
}
